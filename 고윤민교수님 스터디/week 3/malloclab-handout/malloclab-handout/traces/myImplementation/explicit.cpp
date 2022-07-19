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

// Q1. HEADER와 FOOTER가 4Byte인 이유는 int가 4 Byte이기 때문인가?
// Block Size & Alloc

#define PACK(size, alloc) ((size) | (alloc))    // Block Size( Multiple of 8. using 29 bit ) + IsAlloc( 000 : Free / 001 Alloc using 3 bit 0~7 ) 

#define GET(p) (*(unsigned int*)p)              // From Pointer p, getting 'int information'( PACK(size, alloc) )
#define PUT(p,val) (*(unsigned int*)(p) = val)  // Putting 'int value' to Pointer P

#define GET_SIZE(p) (GET(p) & (~0x7))           // Getting Block Size information
#define GET_ALLOC(p) (GET(p) & (0x1))           // Getting IsAllock information

// Block

#define HDBP(bp) (bp - WSIZE)                                               // Header Block of bp
#define FTBP(bp) (bp + GET_SIZE(HDBP(bp)) - DSIZE)                          // Footer Block of bp

#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE(HDBP(bp)))                    // Next Block of bp
#define PREV_BLRP(bp) ((char*)(bp) - GET_SIZE( (char *)(bp) - DSIZE ))      // Previous Block of bp

// Free List

#define GET_PREV(bp) (*(void**)bp)                                          // Prev Block Pointer of bp
#define GET_NEXT(bp) (*(void**)(bp+DSIZE))                                  // Next Block Pointer of bp

#define PREV_A_TO_B(bp1,bp2) (*(void **)bp1 = bp2)                          // Connecting Prev BP of bp1 to Address which is pointed by bp2
#define NEXT_A_TO_B(bp1,bp2) (*(void **)(bp1+DSIZE) = bp2)                  // Connecting Next BP of bp1 to Address which is pointed by bp2




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

    if((long)(bp = mem_sbrk(size)) == -1) return NULL;

    brk += size;                                                // End point increases

    // Modifying header and footer

    PUT(HDBP(bp),PACK(size , 0));                                               
    PUT(FTBP(bp) ,PACK(size , 0));
    PUT(HDBP(NEXT_BLKP(bp)) , PACK(0,1));  // Moving Last block

    return coalesce(bp);                   // If the previous block is not allocated, combine the two blocks.
}


char* Mymalloc::mem_sbrk(int incr){
    char* old_brk = brk;

    if( (incr < 0) || ( (brk + incr) > max_addr) ){
        perror("mem_sbrk failed.");
        return (char *)-1;
    }
    
    brk += incr;
    return (char*)old_brk;
}




char * Mymalloc::coalesce(char *bp){
    
    size_t size = GET_SIZE(HDBP(bp));
    size_t prev_alloc = GET_ALLOC(HDBP(PREV_BLRP(bp)));
    size_t next_alloc = GET_ALLOC(HDBP(NEXT_BLKP(bp)));

    if(prev_alloc && next_alloc){

        // New node connect
        PREV_A_TO_B(bp , NULL);
        NEXT_A_TO_B(bp,free_list);

        PREV_A_TO_B(free_list , bp);

        free_list = bp;

        return bp;
    }

    else if( !prev_alloc  && next_alloc){
        size += GET_SIZE(HDBP(PREV_BLRP(bp)));
        PUT(HDBP(PREV_BLRP(bp)),PACK(size , 0));
        PUT(FTBP(bp), PACK(size,0));

        // prev 노드 찾아서 해체 시키기.
        // prev 노드 합치기

        bp = PREV_BLRP(bp);
        
        PREV_A_TO_B(bp , NULL);
        NEXT_A_TO_B(bp,free_list);

        PREV_A_TO_B(free_list , bp);

        free_list = bp;

    }

    else if(prev_alloc && !next_alloc ) {
        size += GET_SIZE( HDBP(NEXT_BLKP(bp)));
        PUT(HDBP(bp), PACK(size,0));
        PUT(FTBP(bp) , PACK(size,0));


        // next 노드 찾아서 해체 시키기.
        // next 노드 합치기.

        PREV_A_TO_B(bp , NULL);
        NEXT_A_TO_B(bp,free_list);

        PREV_A_TO_B(free_list , bp);

        free_list = bp;
    }

    else{
        size += GET_SIZE(PREV_BLRP(bp)) + GET_SIZE(NEXT_BLKP(bp));
        PUT( HDBP(PREV_BLRP(bp)) , PACK(size , 0));
        PUT( FTBP(NEXT_BLKP(bp)), PACK(size,0));

        // next 노드 , prev 노드 모두 찾아서 해체 시키기.
        // next 노드 , prev 노드 합치기

        bp = PREV_BLRP(bp);

        PREV_A_TO_B(bp , NULL);
        NEXT_A_TO_B(bp,free_list);

        PREV_A_TO_B(free_list , bp);

        free_list = bp;
    }

    return bp;
}


char * Mymalloc::find_fit(size_t asize){
    char* bp;

    for(bp = free_list ; !GET_NEXT(bp) ; bp = (char *)GET_NEXT(bp) ){
        if(GET_SIZE(bp) < asize) continue;
        
        return bp;
    }

    return NULL;
}

void Mymalloc::place(char *bp, size_t asize){

    size_t csize = GET_SIZE(HDBP(bp));

    if((csize - asize) >= 4 * DSIZE){ // pointer 가 8이 라면
        PUT(HDBP(bp) , PACK(asize , 1));
        PUT(FTBP(bp) , PACK(asize , 1));
        
        bp = NEXT_BLKP(bp);
        
        PUT(HDBP(bp),PACK(csize-asize , 0));
        PUT(FTBP(bp) , PACK(csize-asize , 0));

        PREV_A_TO_B(bp , NULL);
        NEXT_A_TO_B(bp,free_list);

        PREV_A_TO_B(free_list , bp);

        free_list = bp;
    }   
    else{
        PUT(HDBP(bp) , PACK(csize , 1));
        PUT(FTBP(bp) , PACK(csize, 1));
    }

    // 해제
    char * prev = (char *)GET_PREV(bp);
    char * next = (char *)GET_NEXT(bp);

    if(prev){
        if(!next) GET_NEXT(prev) = NULL;
        GET_NEXT(prev) = next;
    }
    if(next){ 
        if(!prev) GET_PREV(next) = NULL;
        else GET_PREV(next) = prev;    
    }

    GET_PREV(bp) = NULL;
    GET_NEXT(bp) = NULL;


}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------






// mm Functions ----------------------------------------------------------------------------------------------------------------------------------------------

// 1) mm_init
// For Initialization

int Mymalloc::mm_init(){

    if( (heap = mem_sbrk(8 * WSIZE)) == (char*)-1 ) return -1;  // Padding + Header + Prev Pointer + Next Pointer + Footer + Last Block

    PUT(heap , 0);                                      // Padding
    PUT(heap + 1 * WSIZE , PACK( 3 * DSIZE , 1));       // Header
    PUT(heap + 2 * WSIZE, NULL);                        // Prev Pointer
    free_list = heap + 2 * WSIZE;                       // free list init

    PUT(heap + 4 * WSIZE, NULL);                        // Next Pointer
    PUT(heap + 6 * WSIZE , PACK( 3 * DSIZE , 1));       // Footer
    PUT(heap + 7 * WSIZE , PACK(0,1));                  // Last Block
    heap += (2 * WSIZE);                                // bp

    if(extend_heap(CHUNKSIZE / WSIZE) == NULL) return -1;   // Extend_heap 1 MB (= 4 MB / 4 )

    return 0;
}





void Mymalloc::mm_free(char* bp)
{
    size_t size = GET_SIZE(HDBP(bp));

    PUT(HDBP(bp),PACK(size,0));
    PUT(FTBP(bp),PACK(size,0));
    coalesce(bp);

}



char * Mymalloc::mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize;
    char *bp;

    if(size == 0) return NULL;

    if(size <= DSIZE){
        // asize = 3 * DSIZE;
        asize = 4 * DSIZE;  // pointer가 8이라면
    }
    else{
        // asize = 2 * DSIZE + ((size + DSIZE -1) / DSIZE) * DSIZE ;
        asize = 3 * DSIZE + ((size + DSIZE -1)/DSIZE) * DSIZE;
    }

    if((bp = find_fit(asize)) != NULL){

        place(bp,asize);
        return bp;
    }

    if( (bp = extend_heap(asize / WSIZE)) == NULL) return NULL;
    
    place(bp,asize);
    return bp;
    
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------