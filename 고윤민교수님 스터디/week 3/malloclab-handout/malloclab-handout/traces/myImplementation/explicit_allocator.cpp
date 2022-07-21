/**
 * @file explicit_allocator.cpp
 * @author Oh InHyuk ( 8156217@naver.com )
 * @brief This is simple implementation of explicit allocator for Dynamic allocation in C / C++
 *        It uses free list ( doubly linked list ) for Free block management
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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MACRO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 

 
/**
 * @brief Macros for Size
 */

#define WSIZE 4                     // 1 BYTE
#define DSIZE 8                     // Double BYTE 
#define MAX_HEAP 100 * (1<<20)      // Maximum of HEAP 100 MB
#define CHUNKSIZE (1<<9)            // Size for Heap increasement ( 256 Bytes )


/**
 * @brief Macros for Block Size & Alloc 
 */

#define PACK(size, alloc) ((size) | (alloc))    // Block Size( Multiple of 8. using 29 bit ) + IsAlloc( 000 : Free / 001 Alloc using 3 bit 0~7 ) 

#define GET(p) (*(unsigned int*)p)              // From Pointer p, getting 'int information'( PACK(size, alloc) )
#define PUT(p,val) (*(unsigned int*)(p) = val)  // Putting 'int value' to Pointer P

#define GET_SIZE(p) (GET(p) & (~0x7))           // Getting Block Size information
#define GET_ALLOC(p) (GET(p) & (0x1))           // Getting IsAllock information


/**
 * @brief Macros for Block
 */

#define HDBP(bp) ((char *)bp - WSIZE)                                               // Header Block of bp
#define FTBP(bp) ((char *)bp + GET_SIZE(HDBP(bp)) - DSIZE)                          // Footer Block of bp

#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE(HDBP(bp)))                    // Next Block of bp
#define PREV_BLKP(bp) ((char*)(bp) - GET_SIZE( ((char *)(bp) - DSIZE )))      // Previous Block of bp




/**
 * @brief Macros for free List Macros
 */

#define GET_PREV(bp) (*(void**)bp)                                          // Prev Block Pointer of bp
#define GET_NEXT(bp) (*(void**)((char *)bp+WSIZE))                                  // Next Block Pointer of bp

#define PREV_A_TO_B(bp1,bp2) (*(void **)bp1 = bp2)                          // Connecting Prev BP of bp1 to Address which is pointed by bp2  
#define NEXT_A_TO_B(bp1,bp2) (*(void **)((char*)bp1+WSIZE) = bp2)                  // Connecting Next BP of bp1 to Address which is pointed by bp2




// ----------------------------------------------------------------------------------------------------------------------------------------------------------






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief My malloc class
 */

class Mymalloc{

private :

    char* heap ;        // Start point of Heap                      
    char* brk;          // End point of Heap
    char* max_addr;     // Max Address of Heap

    char* free_list;    // Pointing Front Free Block

public :

    // Constructor

    Mymalloc(){
        heap = new char [MAX_HEAP];
        brk = heap;
        max_addr = heap + MAX_HEAP;
        
        mm_init();      // malloc init using mm_init function
    }

    // Destructor

    ~Mymalloc(){
        delete[] heap;
    };


    // Member Functions
    
    // Sub Functions
    void* mem_sbrk(int incr);
    void* extend_heap(size_t words);
    void* coalesce(void *bp);   
    void* find_fit(size_t asize);
    void place(void *bp , size_t asize);
    void disconnect(void * bp);
    void new_connect(void * bp);
    
    // mm_Functions
    void mm_init(void);
    void* mm_malloc(size_t size);
    void * mm_calloc(size_t size);
    void * mm_realloc(void* bp ,size_t size);
    void mm_free(void* bp);

    // Print functions for Check
    void print_all_block();
    void print_free_block();

};


// ----------------------------------------------------------------------------------------------------------------------------------------------------------






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Member Functions /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//  Sub Functions -------------------------------------------------------------------------------------------------------------------------------------------


/**
 * @brief The function that increases space of heap when it is lack
 * 
 * @param words : Number of words ( word : 4 Bytes ) 
 * @return void* : New Free block pointer
 */

void * Mymalloc::extend_heap (size_t words)
{    

    void *bp;
    size_t size;
    
    size = (words % 2) ? (words +1) * WSIZE : words * WSIZE;    // Double Word (8) Alignment
    
    if((bp = mem_sbrk(size)) == (void *) -1) return (void *)-1;
    
    // Modifying header and footer

    PUT(HDBP(bp),PACK(size , 0));
    PUT(FTBP(bp) ,PACK(size , 0));
    PUT(HDBP(NEXT_BLKP(bp)) , PACK(0,1));  // Moving Last block

    return coalesce(bp);                   // If the previous block is not allocated, combine the two blocks
}


/**
 * @brief The function that increases the size of the heap
 * 
 * @param incr : Amount of increasement of heap
 * @return void* : Brk pointer before increasement
 */
void* Mymalloc::mem_sbrk(int incr){
    char* old_brk = brk;    

    if( (incr < 0) || ( (brk + incr) > max_addr) ){     // Error
        perror("mem_sbrk failed.");
        return (void *)-1;
    }
    
    brk += incr;            // Heap Size increases

    
    if(old_brk == heap) cout << "[ Heap Increasement ] " <<" Before : " << old_brk-heap << " Bytes " << " -> " <<" After : " << brk-heap << " Bytes " << " [ + " << incr <<" Bytes ] " << endl;
    else cout << "[ Heap Increasement ] " <<" Before : " << old_brk-(heap - DSIZE) << " Bytes " << " -> " <<" After : " << brk-(heap - DSIZE) << " Bytes " << " [ + " << incr <<" Bytes ] " << endl;

    return (void *)old_brk;  // return previous brk
}



/**
 * @brief The function that disconnects the free block pointed by bp from the free list
 * 
 * @param bp : Pointer which is pointing to use free block
 */
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


/**
 * @brief The function that connects the free block pointed by bp to the free list (LIFO order).
 * 
 * @param bp : pointer which is pointing new free block.
 */

void Mymalloc ::new_connect(void * bp){

    PREV_A_TO_B(bp , NULL);
    NEXT_A_TO_B(bp,free_list);

    PREV_A_TO_B(free_list , bp);
    
    free_list = (char *)bp;

}


/**
 * @brief The function that combines the free blocks
 * 
 * @param bp : Pointer which is pointing free block
 * @return void* : Pointer which is pointing combined free block
 */

void * Mymalloc::coalesce(void *bp){
    
    size_t size = GET_SIZE(HDBP(bp));                       // Size of bp's block
    size_t prev_alloc = GET_ALLOC(HDBP(PREV_BLKP(bp)));     // Isalloc of Prev block of bp 
    size_t next_alloc = GET_ALLOC(HDBP(NEXT_BLKP(bp)));     // Isallco if Next block of bp


    // Case 0 (For realloc)
    // Curr block is Allocated
    // Next block is free block
    if(GET_ALLOC(HDBP(bp)) == 1 && next_alloc == 0){
       
       // Next block disconnect
       disconnect(NEXT_BLKP(bp));
       
       // Combining Curr block + Next block
       size += GET_SIZE(HDBP(NEXT_BLKP(bp)));
       PUT(HDBP(bp) , PACK(size , 1));
       PUT(FTBP(bp) , PACK(size , 1));

        return bp;
    }

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
        size += GET_SIZE(HDBP(PREV_BLKP(bp)));
        PUT(HDBP(PREV_BLKP(bp)),PACK(size , 0));
        PUT(FTBP(bp), PACK(size,0));

        // prev free block disconnect
        disconnect(PREV_BLKP(bp));

        // New Free block connect
        bp = PREV_BLKP(bp);
        
        new_connect(bp);

    }

    // Case 3
    // Prev block is allocated block
    // Next block is free block
    else if(prev_alloc == 1 && next_alloc == 0 ) {

        // Next free block disconnect
        
        disconnect(NEXT_BLKP(bp));

        // Combining Block Curr block + Next block
        size += GET_SIZE( HDBP(NEXT_BLKP(bp)));
        PUT(HDBP(bp), PACK(size,0));
        PUT(FTBP(bp) , PACK(size,0));

        // New Free block connect
        new_connect(bp);

    }

    // Case 4
    // Prev & Next block are free block
    else{

        // Combining Block Prev block + Curr block + Next block
        size += GET_SIZE(HDBP(PREV_BLKP(bp))) + GET_SIZE(HDBP(NEXT_BLKP(bp)));
        PUT( HDBP(PREV_BLKP(bp)) , PACK(size , 0));
        PUT( FTBP(NEXT_BLKP(bp)), PACK(size,0));

        // Prev , Next free block disconnect
       
        disconnect(PREV_BLKP(bp));
        disconnect(NEXT_BLKP(bp));


        // New Free block connect
        bp = PREV_BLKP(bp);

        new_connect(bp);

    }

    return bp;
}



/**
 * @brief The function that searches fit free block, in free list (LIFO order)
 * 
 * @param asize : Demanded size
 * @return void* : Pointer which is pointing fit free block. ( IF there isn't, return nullptr )
 */
void * Mymalloc::find_fit(size_t asize){
    void* bp;

    for(bp = (void *)free_list ; GET_ALLOC(HDBP(bp)) == 0 ; bp = GET_NEXT(bp) ){   // Finding list
        if(GET_SIZE(HDBP(bp)) >= asize) return bp;  // fit
    }

    return nullptr;
}


/**
 * @brief The function that put the remaining block back in the free list again, when Free block is too large
 * 
 * @param bp : Pointer which is pointing large free block
 * @param asize : Size of large free block
 */
void Mymalloc::place(void *bp, size_t asize){

    size_t csize = GET_SIZE(HDBP(bp));

    if((csize - asize) >= 2 * DSIZE){
        PUT(HDBP(bp) , PACK(asize , 1));
        PUT(FTBP(bp) , PACK(asize , 1));

        PUT(HDBP(NEXT_BLKP(bp)), PACK(csize-asize , 0));
        PUT(FTBP(NEXT_BLKP(bp)), PACK(csize-asize , 0));

        new_connect(NEXT_BLKP(bp));

    }   
    else{
        PUT(HDBP(bp) , PACK(csize , 1));
        PUT(FTBP(bp) , PACK(csize, 1));
    }

    // Disconnecting allocated block from free list
    disconnect(bp);

}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------






// mm Functions ----------------------------------------------------------------------------------------------------------------------------------------------


/**
 * @brief Heap initalization for allocation
 */
void Mymalloc::mm_init(){

    cout << "[ Heap init ] Heap is initalized. " << endl;

    if( ( mem_sbrk(6 * WSIZE)) == (void *)-1 ) return ;  // Padding + Header + Prev Pointer + Next Pointer + Footer + Last Block

    PUT(heap , 0);                                      // Padding
    PUT(heap + 1 * WSIZE , PACK( 2 * DSIZE , 1));       // Header
    PREV_A_TO_B((heap+ 2 * WSIZE) , NULL);              // Prev Pointer
    
    
    free_list = heap + (2 * WSIZE);                     // free list init

    NEXT_A_TO_B((heap+ 2 * WSIZE) , NULL);              // Next Pointer
    PUT(heap + 4 * WSIZE , PACK( 2 * DSIZE , 1));       // Footer
    PUT(heap + 5 * WSIZE , PACK(0,1));                  // Last Block
    heap += (2 * WSIZE);                                // bp

    if(extend_heap(CHUNKSIZE / WSIZE) == (void *)-1 ) return ;   // Extend_heap 1 MB (= 4 MB / 4 )

}



/**
 * @brief Free function to deallocate allocated block
 * 
 * @param bp : Pointer which is pointing allocated block
 */
void Mymalloc::mm_free(void* bp)
{
    size_t size = GET_SIZE(HDBP(bp));   // block size

    if( GET_ALLOC(HDBP(bp)) == 0 ){
        cout << "[ Free Failed ] Pointing Memory isn't allocated. ";
        return ;
    } 

    PUT(HDBP(bp),PACK(size,0));         // block header modify
    PUT(FTBP(bp),PACK(size,0));         // block footer modify
    coalesce(bp);                       // Merge with neighboring block

    cout << "[ Free Success ] " << size << " Bytes are decallocated." << endl;
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
    void *bp;

    if(size == 0) return NULL;

    // Alignment - Double word ( 8bytes )
    if(size <= DSIZE) asize = 2 * DSIZE;        // IF Size is small
    else asize = (1 * DSIZE) + (((size + DSIZE -1)/DSIZE) * DSIZE);     // Other Cases

    // Finding Free block
    if((bp = find_fit(asize)) != nullptr){
        place(bp,asize);

        cout << "[ Malloc Success ] " << asize << " Bytes is allocated. " << endl;

        return bp;
    }

    // If heap size is lack -> extend_heap
    if( (bp = extend_heap(CHUNKSIZE / WSIZE)) == (void *)-1 ) return NULL;

    return mm_malloc(size);
    
}


/**
 * @brief Memory allocation + initalization ( Zero )
 * 
 * @param size : Size of allocation
 * @return void* : Pointer which is pointing allocated memory
 */
void * Mymalloc::mm_calloc(size_t size){

    void* bp;
    if((bp = mm_malloc(size)) == NULL) return NULL;

    // size_t asize;
    
    // Alignment - Double word ( 8bytes )
    if(size <= DSIZE) size = DSIZE;        // IF Size is small
    else size = ((size + DSIZE -1)/DSIZE) * DSIZE;

    for(int i = 0 ; i < size/WSIZE ; ++i){
        *((int*)bp+i) = 0x0;
    }

    return bp;
}


/**
 * @brief Resizing allocated memory
 * 
 * @param bp : Pointer which is pointing allocated memory
 * @param size : Resizing size
 * @return void* : Pointer which is pointing reallocated memory
 */
void * Mymalloc::mm_realloc(void* bp ,size_t size){

    if( GET_ALLOC(HDBP(bp)) == 0) return NULL;
    
    size_t before_size = GET_SIZE(HDBP(bp));
    size_t asize = DSIZE + ((size + (DSIZE -1)) / DSIZE) *DSIZE;

    cout << "[ Realloc Start ] Request size is " << asize <<" Bytes "  << endl;

    // Size Increasement
    if(asize > GET_SIZE(HDBP(bp))){

        // Case 1
        // Next block is free Block & Big enough
        if(GET_ALLOC(HDBP(NEXT_BLKP(bp))) == 0 && GET_SIZE(HDBP(NEXT_BLKP(bp))) >= asize - GET_SIZE(HDBP(bp))){
            coalesce(bp);
            
            cout << "[ Realloc End ] "<< before_size << " Bytes -> After " << GET_SIZE(HDBP(bp)) << " Bytes  " << endl;
            return bp;
        }

        // Case 2
        // Finding free block which is big enough
        else {
            mm_free(bp);    // Deallocate

            void * new_bp = mm_malloc(size);    // Allocate big enough memory

            for(int i = 0 ; i < (GET_SIZE(HDBP(bp)) - DSIZE)/WSIZE ; ++i){
                *((int *)new_bp+i) = *((int *)bp+i);                            // Content Copy
            }

            cout << "[ Realloc End ] "<< before_size << " Bytes -> After " << GET_SIZE(HDBP(new_bp)) << " Bytes  " << endl;

            return new_bp;
        }
    }
    // Size Decreasement
    else if(asize < GET_SIZE(HDBP(bp))){
        size_t csize = GET_SIZE(HDBP(bp))-asize;

        // Case 1
        // Remaining memory is bigger than DSIZE * 2

        if(csize >= DSIZE * 2){

            // Shrink
            PUT(HDBP(bp), PACK(asize,1));
            PUT(FTBP(bp) ,PACK(asize,1));
            
            // Remaining block
            PUT(HDBP(NEXT_BLKP(bp)) , PACK(csize,0));
            PUT(FTBP(NEXT_BLKP(bp)) , PACK(csize,0));

            coalesce(NEXT_BLKP(bp));

            cout << "[ Realloc End ] "<< before_size << " Bytes -> After " << GET_SIZE(HDBP(bp)) << " Bytes  " << endl;

            return bp;
        }
    }
}





// ----------------------------------------------------------------------------------------------------------------------------------------------------------




// Print Function -------------------------------------------------------------------------------------------------------------------------------------------



/**
 * @brief Printing all blocks in heap
 */
void Mymalloc::print_all_block(){
    char * search = heap;
    
    cout << endl;
    cout << "<<<<<   All Blocks   >>>>>" << endl;
    cout << endl;

    for(search ; GET_SIZE(HDBP(search)) != 0 ; search = NEXT_BLKP(search) ){
        cout << "[ SIZE / ALLOC ] : " << GET_SIZE(HDBP(search)) << " / "  << GET_ALLOC(HDBP(search)) << endl;
    }
}



/**
 * @brief Printing all free blocks in free list
 */
void Mymalloc::print_free_block(){
    
    char * search = free_list;
    
    cout << endl;
    cout << "<<<<<   Free List  >>>>>" << endl;
    cout << endl;
    
    for(search ; GET_ALLOC(HDBP(search)) != 1 ; search = (char *)GET_NEXT(search)){
        cout << "[ SIZE / ALLOC ] : " << GET_SIZE(HDBP(search)) << " / "  << GET_ALLOC(HDBP(search)) << endl;
    }
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(void){

    Mymalloc M1;

    int * p;
    int * q;
    int * z;
    int * m;

    m = (int*)M1.mm_malloc();
    
    M1.print_all_block(); 
    M1.print_free_block();
}