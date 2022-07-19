// 해야할 것
// char*  -> void *

#include <iostream>

using namespace std;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MACRO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 

// Size

#define WSIZE 4                     // 1 BYTE
#define DSIZE 8                     // Double BYTE 
#define MAX_HEAP 100 * (1<<20)      // Maximum of HEAP 100 MB

#define CHUNKSIZE (1<<12)                       // 4 MB

// Block Size & Alloc

#define PACK(size, alloc) ((size) | (alloc))    // Block Size( Multiple of 8. using 29 bit ) + IsAlloc( 000 : Free / 001 Alloc using 3 bit 0~7 ) 

#define GET(p) (*(unsigned int*)p)              // From Pointer p, getting 'int information'( PACK(size, alloc) )
#define PUT(p,val) (*(unsigned int*)(p) = val)  // Putting 'int value' to Pointer P

#define GET_SIZE(p) (GET(p) & (~0x7))           // Getting Block Size information
#define GET_ALLOC(p) (GET(p) & (0x1))           // Getting IsAllock information

// Block

#define HDBP(bp) ((char *)bp - WSIZE)                                               // Header Block of bp
#define FTBP(bp) ((char *)bp + GET_SIZE(HDBP(bp)) - DSIZE)                          // Footer Block of bp

#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE(HDBP(bp)))                    // Next Block of bp
#define PREV_BLRP(bp) ((char*)(bp) - GET_SIZE( (char *)(bp) - DSIZE ))      // Previous Block of bp

// Free List

#define GET_PREV(bp) (*(char**)bp)                                          // Prev Block Pointer of bp
#define GET_NEXT(bp) (*(char**)(bp+WSIZE))                                  // Next Block Pointer of bp

#define PREV_A_TO_B(bp1,bp2) (*(char **)bp1 = bp2)                          // Connecting Prev BP of bp1 to Address which is pointed by bp2  
#define NEXT_A_TO_B(bp1,bp2) (*(char **)(bp1+WSIZE) = bp2)                  // Connecting Next BP of bp1 to Address which is pointed by bp2

// 위를 void ** 로 해야할 지 char ** 로 해야할 지 모르겠다.
// 위의 (*(void**) ((char*)bp1 + WSIZE)) = bp2로 해야하나?


// ----------------------------------------------------------------------------------------------------------------------------------------------------------





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Mymalloc{

private :
    char* heap ;        // Start point of Heap                        // Q2. 왜 Char*로 해주는 지. 왜 const를 써주는지
    char* brk;          // End point of Heap
    char* max_addr;     // Max Address of Heap

    char* free_list;    // Pointing Front Free Block

public :

    // Constructor

    Mymalloc(){
        heap = new char [MAX_HEAP];
        brk = heap;
        max_addr = heap + MAX_HEAP;
        mm_init();
    }

    // Destructor

    ~Mymalloc(){
        delete[] heap;
    };

    // Member Functions

    char* mem_sbrk(int incr);
    int mm_init(void);
    char* extend_heap(size_t words);
    void mm_free(char* bp);
    char* coalesce(char *bp);   
    char* mm_malloc(size_t size);
    char* find_fit(size_t asize);
    void place(char *bp , size_t asize);
    void disconnect(char * bp);
    void new_connect(char * bp);
};


// ----------------------------------------------------------------------------------------------------------------------------------------------------------





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Member Functions /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//  Sub Functions -------------------------------------------------------------------------------------------------------------------------------------------


// 1) extend_heap
// A function that increases space of heap when it is lack.

char* Mymalloc::extend_heap (size_t words)
{
    char *bp;
    size_t size;

    size = (words % 2) ? (words +1) * WSIZE : words * WSIZE;    // Double Word (8) Alignment

    if((int)(bp = mem_sbrk(size)) == -1) return NULL;

    brk += size;                                                // End point increases

    // Modifying header and footer

    PUT(HDBP(bp),PACK(size , 0));                                               
    PUT(FTBP(bp) ,PACK(size , 0));
    PUT(HDBP(NEXT_BLKP(bp)) , PACK(0,1));  // Moving Last block

    return coalesce(bp);                   // If the previous block is not allocated, combine the two blocks.
}

// 2) Mem_sbrk
// The function that increases the size of the heap

char* Mymalloc::mem_sbrk(int incr){
    char* old_brk = brk;    

    if( (incr < 0) || ( (brk + incr) > max_addr) ){     // Error
        perror("mem_sbrk failed.");
        return (char *)-1;
    }
    
    brk += incr;            // Heap Size increases
    return old_brk;  // return previous brk
}

// 3) Disconnect
// Disconnecting the free block pointed by bp from the free list
void Mymalloc::disconnect(char * bp){
    
    char* prev = (char *)GET_PREV(bp);
    char* next = (char *)GET_NEXT(bp);
        
    if(prev) {
        if(!next) NEXT_A_TO_B(prev,NULL);
        else NEXT_A_TO_B(prev, next);
    }
    if(next){
        if(!prev) PREV_A_TO_B(next,NULL);
        else PREV_A_TO_B(next,prev);
    } 

}

// 4) New_conncect
// Connecting the free block pointed by bp to the free list (LIFO order)
void Mymalloc ::new_connect(char * bp){
    PREV_A_TO_B(bp , NULL);
    NEXT_A_TO_B(bp,free_list);

    PREV_A_TO_B(free_list , bp);
    
    free_list = bp;
}

// 5) Coalesce
// Combining the free blocks

char * Mymalloc::coalesce(char *bp){
    
    size_t size = GET_SIZE(HDBP(bp));
    size_t prev_alloc = GET_ALLOC(HDBP(PREV_BLRP(bp)));
    size_t next_alloc = GET_ALLOC(HDBP(NEXT_BLKP(bp)));

    // Case 1
    // Prev & Next block are allocated blocks
    if(prev_alloc && next_alloc){

        // New Free block connect
        new_connect(bp);

        return bp;
    }

    // Case 2
    // Prev block is free block
    // Next block is allocated block
    else if( !prev_alloc  && next_alloc){

        // Combining Block Prev block + Curr block
        size += GET_SIZE(HDBP(PREV_BLRP(bp)));
        PUT(HDBP(PREV_BLRP(bp)),PACK(size , 0));
        PUT(FTBP(bp), PACK(size,0));
 
        // prev free block disconnect
        disconnect(PREV_BLRP(bp));

        // New Free block connect
        bp = PREV_BLRP(bp);
        
        new_connect(bp);

    }

    // Case 3
    // Prev block is allocated block
    // Next block is free block
    else if(prev_alloc && !next_alloc ) {

        // Combining Block Curr block + Next block
        size += GET_SIZE( HDBP(NEXT_BLKP(bp)));
        PUT(HDBP(bp), PACK(size,0));
        PUT(FTBP(bp) , PACK(size,0));

        // Next free block disconnect
        
        disconnect(NEXT_BLKP(bp));

        // New Free block connect
        new_connect(bp);

    }

    // Case 4
    // Prev & Next block are free block
    else{

        // Combining Block Prev block + Curr block + Next block
        size += GET_SIZE(PREV_BLRP(bp)) + GET_SIZE(NEXT_BLKP(bp));
        PUT( HDBP(PREV_BLRP(bp)) , PACK(size , 0));
        PUT( FTBP(NEXT_BLKP(bp)), PACK(size,0));

        // Prev , Next free block disconnect
       
        disconnect(PREV_BLRP(bp));
        disconnect(NEXT_BLKP(bp));


        // New Free block connect
        bp = PREV_BLRP(bp);

        new_connect(bp);

    }

    return bp;
}



// 6) find_fit
// Finding fit free block, in free list (LIFO order)

char * Mymalloc::find_fit(size_t asize){
    char* bp;

    for(bp = free_list ; !GET_NEXT(bp) ; bp = (char *)GET_NEXT(bp) ){   // Finding list
        if(GET_SIZE(bp) < asize) continue;  // not fit
        
        return bp;  // Found
    }

    return NULL;    // Not Found
}



// 7) place
// If the block size is large, put the remaining block back in the free list

void Mymalloc::place(char *bp, size_t asize){

    size_t csize = GET_SIZE(HDBP(bp));

    if((csize - asize) >= 3 * DSIZE){
        PUT(HDBP(bp) , PACK(asize , 1));
        PUT(FTBP(bp) , PACK(asize , 1));
        
        bp = NEXT_BLKP(bp);
        
        PUT(HDBP(bp),PACK(csize-asize , 0));
        PUT(FTBP(bp) , PACK(csize-asize , 0));

        new_connect(bp);

    }   
    else{
        PUT(HDBP(bp) , PACK(csize , 1));
        PUT(FTBP(bp) , PACK(csize, 1));
    }

    // 해제
    disconnect(bp);

    PREV_A_TO_B(bp,NULL);
    NEXT_A_TO_B(bp,NULL);


}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------






// mm Functions ----------------------------------------------------------------------------------------------------------------------------------------------

// 1) mm_init
// For Initialization

int Mymalloc::mm_init(){

    if( (heap = mem_sbrk(6 * WSIZE)) == (char*)-1 ) return -1;  // Padding + Header + Prev Pointer + Next Pointer + Footer + Last Block

    PUT(heap , 0);                                      // Padding
    PUT(heap + 1 * WSIZE , PACK( 2 * DSIZE , 1));       // Header
    PUT(heap + 2 * WSIZE, NULL);                        // Prev Pointer
    free_list = heap + 2 * WSIZE;                       // free list init

    PUT(heap + 3 * WSIZE, NULL);                        // Next Pointer
    PUT(heap + 4 * WSIZE , PACK( 2 * DSIZE , 1));       // Footer
    PUT(heap + 5 * WSIZE , PACK(0,1));                  // Last Block
    heap += (2 * WSIZE);                                // bp

    if(extend_heap(CHUNKSIZE / WSIZE) == NULL) return -1;   // Extend_heap 1 MB (= 4 MB / 4 )

    return 0;
}



// 2) mm_free
// Function to free the allocated block

void Mymalloc::mm_free(char* bp)
{
    size_t size = GET_SIZE(HDBP((char *)bp));   // block size

    PUT(HDBP(bp),PACK(size,0));         // block header modify
    PUT(FTBP(bp),PACK(size,0));         // block footer modify
    coalesce(bp);                       // Merge with neighboring block

}


// 3) mm_malloc
// Malloc Implementation

char * Mymalloc::mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize;
    char *bp;

    if(size == 0) return NULL;


    // Alignment - Double word ( 8bytes )
    if(size <= DSIZE) asize = 3 * DSIZE;        // IF Size is small
    else asize = 2 * DSIZE + ((size + DSIZE -1)/DSIZE) * DSIZE;     // Other Cases
    

    // Finding Free block
    if((bp = find_fit(asize)) != NULL){
        place(bp,asize);
        return bp;
    }

    // If heap size is lack -> extend_heap
    if( (bp = extend_heap(asize / WSIZE)) == NULL) return NULL;
    
    place(bp,asize);
    return (char *)bp;
    
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------