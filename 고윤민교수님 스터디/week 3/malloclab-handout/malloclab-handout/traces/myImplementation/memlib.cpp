#include <iostream>

using namespace std;

#define MAX_HEAP 10 * (1<<20) // 100MB;

#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE (1<<12)

#define MAX(x,y) ((x) > (y) ? (x) : (y))

// size + alloc bit
#define PACK(size, alloc) ((size) | (alloc))

// GET , SET Function block pointer
#define GET(p) (*(unsigned int *)(p))
#define PUT(p,val) (*(unsigned int*)(p) = (val))

#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + (GET_SIZE(HDRP(bp))) - DSIZE )

#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLRP(bp) ((char*)(bp) - GET_SIZE( (char *)(bp) - DSIZE ))


class Mymalloc{

private:
    char* heap;
    char* brk;
    char* max_addr;

public:
    Mymalloc(){
        heap = new char [MAX_HEAP];
        brk = heap;
        max_addr = heap + MAX_HEAP;
    }
    ~Mymalloc(){
        delete[] heap;
    };

    char* mem_sbrk(int incr);
    int mm_init(void);
    char* extend_heap(size_t words);
    void mm_free(char* bp);
    char* coalesce(char *bp);   
    char* mm_malloc(size_t size);
    char* find_fit(size_t asize);
    void place(char *bp , size_t asize);

};

char* Mymalloc::mem_sbrk(int incr){
    char* old_brk = brk;

    if( (incr < 0) || ( (brk + incr) > max_addr) ){
        perror("mem_sbrk failed.");
        return (char *)-1;
    }
    
    brk += incr;
    return (char*)old_brk;
}

int Mymalloc::mm_init(){
    if( (heap = (char *)mem_sbrk(4 * WSIZE)) == (char* )-1 ) return -1;

    PUT(heap , 0); // why 0 ?
    PUT(heap + 1 * WSIZE , PACK(DSIZE , 1));
    PUT(heap + 2 * WSIZE , PACK(DSIZE , 1));
    PUT(heap + 3 * WSIZE , PACK(0,1));
    heap += (2 * WSIZE);

    if(extend_heap(CHUNKSIZE / WSIZE) == NULL) return -1;

    return 0;
}



char* Mymalloc::extend_heap (size_t words)
{
    char *bp;
    size_t size;

    size = (words % 2) ? (words +1) * WSIZE : words * WSIZE;

    if((long)(bp = mem_sbrk(size)) == -1) return NULL;

    brk += size;

    PUT(HDRP(bp),PACK(size , 0));
    PUT(FTRP(bp) ,PACK(size , 0));
    PUT(HDRP(NEXT_BLKP(bp)) , PACK(0,1));

    return coalesce(bp);
}


void Mymalloc::mm_free(char* bp)
{
    size_t size = GET_SIZE(HDRP(bp));

    PUT(HDRP(bp),PACK(size,0));
    PUT(FTRP(bp),PACK(size,0));
    coalesce(bp);

}

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
        size += GET_SIZE(PREV_BLRP(bp)) + GET_SIZE(NEXT_BLKP(bp));
        PUT( HDRP(PREV_BLRP(bp)) , PACK(size , 0));
        PUT( FTRP(NEXT_BLKP(bp)), PACK(size,0));

        bp = PREV_BLRP(bp);
    }

    return bp;
}



char * Mymalloc::mm_malloc(size_t size)
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
    return bp;
    
}

char * Mymalloc::find_fit(size_t asize){
    char* bp;

    for(bp = heap ; GET_SIZE(HDRP(bp)) > 0; bp += GET_SIZE(HDRP(bp)) ){
        if(GET_ALLOC(HDRP(bp))) continue;
        else if(GET_SIZE(HDRP(bp)) < asize){
            continue;
        }
        else{
            return bp;
        }
    }

    return NULL;
}

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