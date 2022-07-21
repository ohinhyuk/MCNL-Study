/**
 * @file Implicit_allocator.cpp
 * @author Oh Inhyuk (8156217@naver.com)
 * @brief This is simple implementation of Implicit allocator for Dynamic allocation in Java / Lisp
 *        This Code has malloc Functions ( malloc , calloc , realloc , free )
 * @version 0.1
 * @date 2022-07-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */


// Header File

#include <iostream>

using namespace std;


/**
 * @brief Macros for Size
 */

#define MAX_HEAP 10 * (1<<20) // 100MB;

#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE (1<<12)


/**
 * @brief Macros for Block Size & Alloc 
 */

// size + alloc bit
#define PACK(size, alloc) ((size) | (alloc))

// GET , SET Function block pointer
#define GET(p) (*(unsigned int *)(p))
#define PUT(p,val) (*(unsigned int*)(p) = (val))

#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)


/**
 * @brief Macros for Block
 */

#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + (GET_SIZE(HDRP(bp))) - DSIZE )

#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLRP(bp) ((char*)(bp) - GET_SIZE( (char *)(bp) - DSIZE ))


/**
 * @brief My malloc class
 */

class Mymalloc{

private:

    char* heap ;        // Start point of Heap                      
    char* brk;          // End point of Heap
    char* max_addr;     // Max Address of Heap

public:

    // Constructor

    Mymalloc(){
        heap = new char [MAX_HEAP];
        brk = heap;
        max_addr = heap + MAX_HEAP;
        
        mm_init();          // malloc init using mm_init function
    }

    // Destructor

    ~Mymalloc(){
        delete[] heap;
    };

    
    // Member Functions

    
    // Sub Functions
    char* mem_sbrk(int incr);
    char* extend_heap(size_t words);
    char* coalesce(char *bp);   
    char* find_fit(size_t asize);
    void place(char *bp , size_t asize);
    void print_all_blocks();

    // mm_Functions
    void mm_init(void);
    void* mm_malloc(size_t size);
    void mm_free(void* bp);

};




/**
 * @brief Functions
 * 
 * Sub Functions
 */


/**
 * @brief The function that increases space of heap when it is lack
 * 
 * @param words : Number of words ( word : 4 Bytes ) 
 * @return void* : New Free block pointer
 */
char* Mymalloc::extend_heap (size_t words)
{
    char *bp;
    size_t size;

    size = (words % 2) ? (words +1) * WSIZE : words * WSIZE;

    if((long)(bp = mem_sbrk(size)) == -1) return NULL;

    PUT(HDRP(bp),PACK(size , 0));
    PUT(FTRP(bp) ,PACK(size , 0));
    PUT(HDRP(NEXT_BLKP(bp)) , PACK(0,1));

    return coalesce(bp);
}



/**
 * @brief The function that increases the size of the heap
 * 
 * @param incr : Amount of increasement of heap
 * @return void* : Brk pointer before increasement
 */
char* Mymalloc::mem_sbrk(int incr){
    char* old_brk = brk;

    if( (incr < 0) || ( (brk + incr) > max_addr) ){
        perror("mem_sbrk failed.");
        return (char *)-1;
    }
    
    brk += incr;
    return (char*)old_brk;
}

/**
 * @brief The function that combines the free blocks
 * 
 * @param bp : Pointer which is pointing free block
 * @return void* : Pointer which is pointing combined free block
 */
char * Mymalloc::coalesce(char *bp){
    
    size_t size = GET_SIZE(HDRP(bp));
    size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLRP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));

    if(prev_alloc && next_alloc){
        return bp;
    }

    else if( !prev_alloc  && next_alloc){
        size += GET_SIZE(HDRP(PREV_BLRP(bp)));
        PUT(HDRP(PREV_BLRP(bp)),PACK(size , 0));
        PUT(FTRP(bp), PACK(size,0));

        bp = PREV_BLRP(bp);
    }

    else if(prev_alloc && !next_alloc ) {
        size += GET_SIZE( HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size,0));
        PUT(FTRP(bp) , PACK(size,0));

    }

    else{
        size += GET_SIZE(HDRP(PREV_BLRP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT( HDRP(PREV_BLRP(bp)) , PACK(size , 0));
        PUT( FTRP(NEXT_BLKP(bp)), PACK(size,0));

        bp = PREV_BLRP(bp);
    }

    return bp;
}

/**
 * @brief The function that searches fit free block, in heap( First-Fit )
 * 
 * @param asize : Demanded size
 * @return void* : Pointer which is pointing fit free block. ( IF there isn't, return nullptr )
 */
char * Mymalloc::find_fit(size_t asize){
    char* bp;

    for(bp = heap ; GET_SIZE(HDRP(bp)) > 0; bp += GET_SIZE(HDRP(bp)) ){
        if(!GET_ALLOC(HDRP(bp)) && GET_SIZE(HDRP(bp)) >= asize) return bp;
    }

    return NULL;
}


/**
 * @brief The function that put the remaining block back in the heap again, when Free block is too large
 * 
 * @param bp : Pointer which is pointing large free block
 * @param asize : Size of large free block
 */
void Mymalloc::place(char *bp, size_t asize){

    size_t csize = GET_SIZE(HDRP(bp));

    if((csize - asize) >= 2 * DSIZE){
        PUT(HDRP(bp) , PACK(asize , 1));
        PUT(FTRP(bp) , PACK(asize , 1));
        PUT(HDRP(NEXT_BLKP(bp)),PACK(csize-asize , 0));
        PUT(FTRP(NEXT_BLKP(bp)) , PACK(csize-asize , 0));
    }   
    else{
        PUT(HDRP(bp) , PACK(csize , 1));
        PUT(FTRP(bp) , PACK(csize, 1));
    }

}


/**
 * @brief Printing all blocks in heap
 */
void Mymalloc::print_all_blocks(){
    char* bp = heap;

    for(bp; GET_SIZE(HDRP(bp))!=0 ; bp = NEXT_BLKP(bp)){
        cout << "[ SIZE / ALLOC ] " << GET_SIZE(HDRP(bp)) << " / " << GET_ALLOC(HDRP(bp)) << endl;
    }
}

/**
 * @brief Functions
 * 
 * mm_functions
 */


/**
 * @brief Heap initalization for allocation
 */
void Mymalloc::mm_init(){
    if( (heap = (char *)mem_sbrk(4 * WSIZE)) == (char* )-1 ) return ;

    PUT(heap , 0); 
    PUT(heap + 1 * WSIZE , PACK(DSIZE , 1));
    PUT(heap + 2 * WSIZE , PACK(DSIZE , 1));
    PUT(heap + 3 * WSIZE , PACK(0,1));
    heap += (2 * WSIZE);

    if(extend_heap(CHUNKSIZE / WSIZE) == NULL) return ;

    return ;
}



/**
 * @brief Memory allocation Function
 * 
 * @param size : Size of allocation
 * @return void* : Pointer which is pointing allocated memory
 */
void * Mymalloc::mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize;
    char *bp;

    if(size == 0) return NULL;

    if(size <= DSIZE){
        asize = 2 * DSIZE;
    }
    else{
        asize = DSIZE + ((size + DSIZE -1) / DSIZE) * DSIZE ;
    }

    if((bp = find_fit(asize)) != NULL){
        
        place(bp,asize);
        return bp;
    }

    if( (bp = extend_heap(asize / WSIZE)) == NULL) return NULL;
    
    place(bp,asize);
    return (void *)bp;
    
}


/**
 * @brief Free function to deallocate allocated block
 * 
 * @param bp : Pointer which is pointing allocated block
 */
void Mymalloc::mm_free(void* bp)
{
    size_t size = GET_SIZE(HDRP(bp));

    PUT(HDRP(bp),PACK(size,0));
    PUT(FTRP(bp),PACK(size,0));
    coalesce((char *)bp);

}


/**
 * @brief Main
 *  
 */

int main(void){

    Mymalloc M1;
    int * p;
    int * q;
    int * r;
    p= (int *)M1.mm_malloc(2000);
    q= (int *)M1.mm_malloc(1000);
    r =(int *)M1.mm_malloc(8000);
    M1.mm_free(p);
    M1.mm_free(r);
    M1.mm_free(q);
    M1.print_all_blocks();

}