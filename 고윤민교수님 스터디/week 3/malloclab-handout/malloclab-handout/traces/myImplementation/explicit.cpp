// Header File

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
#define PREV_BLRP(bp) ((char*)(bp) - GET_SIZE( ((char *)(bp) - DSIZE )))      // Previous Block of bp

// Free List

#define GET_PREV(bp) (*(void**)bp)                                          // Prev Block Pointer of bp
#define GET_NEXT(bp) (*(void**)(bp+WSIZE))                                  // Next Block Pointer of bp

#define PREV_A_TO_B(bp1,bp2) (*(void **)bp1 = bp2)                          // Connecting Prev BP of bp1 to Address which is pointed by bp2  
#define NEXT_A_TO_B(bp1,bp2) (*(void **)(bp1+WSIZE) = bp2)                  // Connecting Next BP of bp1 to Address which is pointed by bp2

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

    void* mem_sbrk(int incr);
    int mm_init(void);
    void* extend_heap(size_t words);
    void mm_free(void* bp);
    void* coalesce(void *bp);   
    void* mm_malloc(size_t size);
    void* find_fit(size_t asize);
    void place(void *bp , size_t asize);
    void disconnect(void * bp);
    void new_connect(void * bp);
    
    // Print
    void print_all_block();
    void print_free_block();
};


// ----------------------------------------------------------------------------------------------------------------------------------------------------------





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Member Functions /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//  Sub Functions -------------------------------------------------------------------------------------------------------------------------------------------


// 1) extend_heap
// A function that increases space of heap when it is lack.

void * Mymalloc::extend_heap (size_t words)
{
    

    void *bp;
    size_t size;
    cout <<"U";
    size = (words % 2) ? (words +1) * WSIZE : words * WSIZE;    // Double Word (8) Alignment
    cout <<"G";
    if((bp = mem_sbrk(size)) == (void *) -1) return (void *)-1;
    
    // Modifying header and footer
    
    PUT(HDBP(bp),PACK(size , 0));
    PUT(FTBP(bp) ,PACK(size , 0));
    PUT(HDBP(NEXT_BLKP(bp)) , PACK(0,1));  // Moving Last block

    return coalesce(bp);                   // If the previous block is not allocated, combine the two blocks.
}

// 2) Mem_sbrk
// The function that increases the size of the heap

void* Mymalloc::mem_sbrk(int incr){
    char* old_brk = brk;    

    if( (incr < 0) || ( (brk + incr) > max_addr) ){     // Error
        perror("mem_sbrk failed.");
        return (void *)-1;
    }
    
    brk += incr;            // Heap Size increases
    return (void *)old_brk;  // return previous brk
}

// 3) Disconnect
// Disconnecting the free block pointed by bp from the free list
void Mymalloc::disconnect(void * bp){
    
    void* prev = (void *)GET_PREV(bp);
    void* next = (void *)GET_NEXT(bp);
        
    if(prev) {
        if(!next) NEXT_A_TO_B(prev,NULL);
        else NEXT_A_TO_B(prev, next);
    }
    if(next){
        if(!prev){ PREV_A_TO_B(next,NULL); free_list = (char *)next; }
        else PREV_A_TO_B(next,prev);
    } 

    PREV_A_TO_B(bp,NULL);
    NEXT_A_TO_B(bp,NULL);

}

// 4) New_conncect
// Connecting the free block pointed by bp to the free list (LIFO order)
void Mymalloc ::new_connect(void * bp){
    PREV_A_TO_B(bp , NULL);
    NEXT_A_TO_B(bp,free_list);

    PREV_A_TO_B(free_list , bp);
    
    free_list = (char *)bp;

}

// 5) Coalesce
// Combining the free blocks

void * Mymalloc::coalesce(void *bp){
    
    size_t size = GET_SIZE(HDBP(bp));
    size_t prev_alloc = GET_ALLOC(HDBP(PREV_BLRP(bp)));
    size_t next_alloc = GET_ALLOC(HDBP(NEXT_BLKP(bp)));

    // cout <<  "size" << GET_SIZE(HDBP(PREV_BLRP(bp)))<< GET_SIZE(HDBP(NEXT_BLKP(bp))) << endl;
    // Case 1
    // Prev & Next block are allocated blocks
    if(prev_alloc == 1 && next_alloc == 1){

        // New Free block connect
        new_connect(bp);

        return bp;
    }

    // Case 2
    // Prev block is free block
    // Next block is allocated block
    else if( prev_alloc == 0  && next_alloc == 1){

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
    else if(prev_alloc == 1 && next_alloc == 0 ) {

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

void * Mymalloc::find_fit(size_t asize){
    void* bp;

    for(bp = (void *)free_list ; GET_ALLOC(HDBP(bp)) != 0 ; bp = GET_NEXT(bp) ){   // Finding list
        if(GET_SIZE(HDBP(bp)) < asize) continue;  // not fit
        
        cout << "!!!"<< GET_SIZE(HDBP(bp)) << endl;
        
    }

    if( GET_SIZE(HDBP(bp)) == 0) return NULL; // NOT FOUND

    return bp;    // return bp
}



// 7) place
// If the block size is large, put the remaining block back in the free list

void Mymalloc::place(void *bp, size_t asize){

    size_t csize = GET_SIZE(HDBP(bp));

    if((csize - asize) >= 3 * DSIZE){
        PUT(HDBP(bp) , PACK(asize , 1));
        PUT(FTBP(bp) , PACK(asize , 1));
        
        cout <<" THIS is : " << csize << "/" << asize << endl;

        PUT(HDBP(NEXT_BLKP(bp)),PACK(csize-asize , 0));
        PUT(FTBP(NEXT_BLKP(bp)) , PACK(csize-asize , 0));

        new_connect(NEXT_BLKP(bp));

    }   
    else{
        PUT(HDBP(bp) , PACK(csize , 1));
        PUT(FTBP(bp) , PACK(csize, 1));
    }

    // 해제
    disconnect(bp);


}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------






// mm Functions ----------------------------------------------------------------------------------------------------------------------------------------------

// 1) mm_init
// For Initialization

int Mymalloc::mm_init(){

    if( ( mem_sbrk(6 * WSIZE)) == (void *)-1 ) return -1;  // Padding + Header + Prev Pointer + Next Pointer + Footer + Last Block
    
    PUT(heap , 0);                                      // Padding
    PUT(heap + 1 * WSIZE , PACK( 2 * DSIZE , 1));       // Header
    PUT(heap + 2 * WSIZE, NULL);                        // Prev Pointer
    
    free_list = heap + (2 * WSIZE);                       // free list init

    PUT(heap + 3 * WSIZE, NULL);                        // Next Pointer
    PUT(heap + 4 * WSIZE , PACK( 2 * DSIZE , 1));       // Footer
    PUT(heap + 5 * WSIZE , PACK(0,1));                  // Last Block
    heap += (2 * WSIZE);                                // bp

    if(extend_heap(CHUNKSIZE / WSIZE) == (void *)-1 ) return -1;   // Extend_heap 1 MB (= 4 MB / 4 )

    return 0;
}



// 2) mm_free
// Function to free the allocated block

void Mymalloc::mm_free(void* bp)
{
    size_t size = GET_SIZE(HDBP(bp));   // block size

    PUT(HDBP(bp),PACK(size,0));         // block header modify
    PUT(FTBP(bp),PACK(size,0));         // block footer modify
    coalesce(bp);                       // Merge with neighboring block

}


// 3) mm_malloc
// Malloc Implementation

void * Mymalloc::mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize;
    void *bp;

    if(size == 0) return NULL;

    // Alignment - Double word ( 8bytes )
    if(size <= DSIZE) asize = 3 * DSIZE;        // IF Size is small
    else asize = (2 * DSIZE) + (((size + DSIZE -1)/DSIZE) * DSIZE);     // Other Cases
    
    cout << "D";
    // Finding Free block
    if((bp = find_fit(asize)) != NULL){
        cout << "E";
        place(bp,asize);
        return bp;
    }
    // If heap size is lack -> extend_heap
    else if( (bp = extend_heap(CHUNKSIZE / WSIZE)) == (void *)-1 ) return NULL;
    
    cout << "B";
    place(bp,asize);
    return bp;
    
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------




// Print Function -------------------------------------------------------------------------------------------------------------------------------------------


// 1) print_all_block

void Mymalloc::print_all_block(){
    char * search = heap;
    for(search ; GET_SIZE(HDBP(search)) != 0 ; search = NEXT_BLKP(search) ){
        cout << "[ SIZE / ALLOC ] :" << GET_SIZE(HDBP(search)) << " / "  << GET_ALLOC(HDBP(search)) << endl;
    }
}


// 2) print_free_block

void Mymalloc::print_free_block(){
    char * search = free_list;
    for(search ; GET_ALLOC(HDBP(search)) != 1 ; search = (char *)GET_NEXT(search)){
        cout << "[ SIZE / ALLOC ] :" << GET_SIZE(HDBP(search)) << " / "  << GET_ALLOC(HDBP(search)) << endl;
    }
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------



// Main 

int main(void){

    Mymalloc M1;

    int * p;
    int * q;
    int * z;
    int * m;

    m = (int*)M1.mm_malloc(30);
    p = (int*)M1.mm_malloc(20);
    q = (int*)M1.mm_malloc(10);
    z = (int*)M1.mm_malloc(40);
    
    M1.mm_malloc(50);

    // M1.mm_free(p);
    // M1.mm_free(q);
    // M1.mm_free(m);
    // M1.mm_free(z);
    
    cout << endl;
    cout << "<<<<<   All Blocks   >>>>>" << endl;
    cout << endl;
    M1.print_all_block();
    
    cout << endl;
    cout << "<<<<<   Free List  >>>>>" << endl;
    cout << endl;
    M1.print_free_block();
    
}