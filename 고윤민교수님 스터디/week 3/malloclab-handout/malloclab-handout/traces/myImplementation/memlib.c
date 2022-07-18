#include <stdio.h>

#define MAX_HEAP 10 * (1<<20) // 100MB;

int mm_init(void);
void *mm_malloc (size_t size);
void mm_free (void *ptr);

/* Private global variables */
static char *mem_heap;
static char *mem_brk;
static char *mem_max_addr;

void mem_init(void)
{
    mem_heap = (char *) Malloc(MAX_HEAP);
    mem_brk = (char*) mem_heap;
    mem_max_addr = (char *)(mem_heap + MAX_HEAP);
}

void * mem_sbrk(int incr){
    char* old_brk = mem_brk;

    if( (incr <0) || ((mem_brk + incr) > mem_max_addr) ){
        perror("mem_sbrk failed.");
        return (void *) -1;
    }
    mem_brk += incr;
    return (void*)old_brk;
}


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
#define PREV_BLKP(bp) ((char*)(bp) - GET_SIZE( (char *)(bp) - DSIZE ))

int mm_init(void)
{
    if( mem_heap = mem_sbrk(4 * WSIZE) == (void* )-1 ) return -1;

    PUT(mem_heap , 0); // why 0 ?
    PUT(mem_heap + WSIZE , PACK(DSIZE , 1))
    PUT(mem_heap + 2 * WSISE , PACK(DSIZE , 1));
    PUT(mem_heap + 3 * WSIZE , PACK(0,1));
    mem_heap += (2 * WSIZE);

    if(extend_heap(CHUNKSIZE / WSIZE) == NULL) return -1;

    return 0;
}

static void* extend_heap (size_t words)
{
    char *bp;
    size_t size;

    size = (words % 2) ? (words +1) * WSIZE : words * WSIZE;

    if((long)(bp = mem_sbrk(size)) == -1) return NULL;

    mem_brk += size;

    PUT(HDRP(bp),PACK(size , 0));
    PUT(FTRP(bp) ,PACK(size , 0));
    PUT(HDRP(NEXT_BLKP(bp)) , PACK(0,1));

    return clalesce(bp);
}

void mm_free(void* bp)
{
    size_t size = GET_SIZE(HDRP(bp));

    PUT(HDRP(bp),PACK(size,0));
    PUT(FTRP(bp),PACK(size,0));
    clalesce(bp);

}

static void *coalesce(void *bp){
    
    size_t size = GET_SIZE(HDRP(bp));
    size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));

    if(prev_alloc && next_alloc){
        return bp;
    }

    else if( !prev_alloc  && next_alloc){
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)),PACK(size , 0));
        PUT(FTRP(bp), PACK(size,0));

        bp = PREV_BLKP(bp);
    }

    else if(prev_alloc && !next_alloc ) {
        size += GET_SIZE( HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size,0));
        PUT(FTRP(bp) , PACK(size,0));

    }

    else{
        size += GET_SIZE(PREV_BLKP(bp)) + GET_SIZE(NEXT_BLKP(bp));
        PUT( HDRP(PREV_BLKP(bp)) , PACK(size , 0));
        PUT( FTRP(NEXT_BLKP(bp)), PACK(size,0));

        bp = PREV_BLKP(bp);
    }

    return bp;
}


void * mm_malloc(size_t size)
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

    if(bp = extend_heap(asize / WSIZE) == NULL) return NULL;
    
    place(bp,asize);
    return bp;
    
}

static void *find_fit(size_t asize){
    void* bp;

    for(bp = mem_heap ; GET_SIZE(HDRP(bp)) > 0; bp += GET_SIZE(HDRP(bp)) ){
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

static void place(void *bp, size_t asize){

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