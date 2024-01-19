#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#define CACHE_SIZE (2 * 1024 * 1024) // 2 MB cache size

// Rutgers University 2021 Spring CS 211 Computer Architecture
// Assignment based on CS:APP Cache Lab

// 64-bit memory address
typedef unsigned long long int mem_addr_t;

// cache properties
unsigned char s = 0; // set index bits
unsigned short S = 1; // set count

unsigned char E = 16; // way associative cache; lines per set

unsigned char b = 4; // block offset bits
unsigned short B = 1<<4; // block size in bytes

// fully associative cache line
typedef struct cache_line {
    mem_addr_t tag;
    struct cache_line* next_cache_line;
} cache_line_t;

typedef struct fifo_cache_set {
    cache_line_t* front; // front (head) of the queue
    cache_line_t* back; // back (tail) of the queue
    unsigned char occupancy;
} fully_associative_fifo_cache_t;

// accessData - Access data at memory address addr.

void accessData (
    mem_addr_t addr,
    fully_associative_fifo_cache_t* cache,
    unsigned int* hit_count,
    unsigned int* miss_count,
    unsigned int* eviction_count
) {

    // Cache indices for this address
    mem_addr_t tag = addr >> (s+b);

    // Cache hit
    cache_line_t* curr_line = cache->front;
    while ( curr_line != NULL ) {
        if ( curr_line->tag == tag ) {
            (*hit_count)++;
            return;
        }
        curr_line = curr_line->next_cache_line;
    }

    // Otherwise, record a cache miss

    (*miss_count)++;

    // If cache is full, evict oldest line due to FIFO cache replacement policy
    if ( cache->occupancy == E ) {
        // dequeue from front of FIFO, update occupancy, and record an eviction
        cache_line_t* line_to_evict = cache->front;
        cache->front = cache->front->next_cache_line;
        free(line_to_evict);
        cache->occupancy--;
        (*eviction_count)++;
    }

    // Due to cache miss, enqueue cache line, and update occupancy
    cache_line_t* new_line = (cache_line_t*) malloc(sizeof(cache_line_t));
    new_line->tag = tag;
    new_line->next_cache_line = NULL;

    if ( cache->occupancy == 0 ) {
        cache->front = new_line;
        cache->back = new_line;
    }
    else {
        cache->back->next_cache_line = new_line;
        cache->back = new_line;
    }

    cache->occupancy++;
}


int main(int argc,char *argv[]) {
    // Initialize cache

fully_associative_fifo_cache_t cache;
cache.front = NULL;
cache.back = NULL;
cache.occupancy = 0;


// Initialize counters
unsigned int hit_count = 0;
unsigned int miss_count = 0;
unsigned int eviction_count = 0;

// Read in memory accesses from file
FILE* trace_file = fopen(argv[1], "r");
if (trace_file == NULL) {
    printf("Error opening trace file\n");
    exit(EXIT_FAILURE);
}

char operation;
mem_addr_t addr;
while ( fscanf(trace_file, " %c %llx", &operation, &addr) == 2 ) {
    switch(operation) {
        case 'I': // instruction load; ignore
            break;
        case 'M': // modify
            accessData(addr, &cache, &hit_count, &miss_count, &eviction_count);
            accessData(addr, &cache, &hit_count, &miss_count, &eviction_count);
            break;
        case 'L': // load
            accessData(addr, &cache, &hit_count, &miss_count, &eviction_count);
            break;
        case 'S': // store
            accessData(addr, &cache, &hit_count, &miss_count, &eviction_count);
            break;
        default: // ignore
            break;
    }
}

// Print results
printf("hits:%u misses:%u evictions:%u\n", hit_count, miss_count, eviction_count);

// Cleanup
cache_line_t* curr_line = cache.front;
while ( curr_line != NULL ) {
    cache_line_t* next_line = curr_line->next_cache_line;
    free(curr_line);
    curr_line = next_line;
}

fclose(trace_file);

return 0;
}
