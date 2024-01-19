#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Rutgers University 2021 Spring CS 211 Computer Architecture
// Assignment based on CS:APP Cache Lab

// 64-bit memory address
typedef unsigned long long int mem_addr_t;

// cache properties
unsigned char s = 4; // set index bits
unsigned char b = 4; // block offset bits

// direct mapped cache set/line
typedef struct cache_set_line {
    bool valid;
    mem_addr_t tag;
} cache_set_line_t;

typedef cache_set_line_t* cache_t;

// accessData - Access data at memory address addr.
void accessData (
    mem_addr_t addr,
    cache_t cache,
    unsigned int* hit_count, // If it is already in cache, increase hit_count
    unsigned int* miss_count, // If it is not in cache, bring it in cache, increase miss_count
    unsigned int* eviction_count // Also increase eviction_count if a line is evicted
) {

    // Cache indices for this address
    unsigned short indexset = (addr >> b) & ((1 << s) - 1);
    mem_addr_t tag = addr >> (s + b);

    // Cache hit
    if (cache[indexset].valid && cache[indexset].tag == tag) {
        (*hit_count)++;
    }

    // Otherwise, cache miss
    else {
        (*miss_count)++;
        // If cache set line already in use as indicated by the valid variable, then evict the existing cache set line
        if (cache[indexset].valid && cache[indexset].tag != tag) {
            (*eviction_count)++;
        }
        cache[indexset].valid = true;
        cache[indexset].tag = tag;
    }
}

int main(int argc, char* argv[]) {

    // path to memory trace
    if ( argc != 2 ) {
        printf( "Usage: ./directMapped <mem_trace_file>" );
        return EXIT_FAILURE;
    }
    char* mem_trace_file = argv[1];
    FILE *fp = fopen(mem_trace_file, "r");
    if (!fp) {
        fprintf(stderr, "Error opening file '%s'\n", mem_trace_file);
        return EXIT_FAILURE;
    }

    // Cache properties
    unsigned short S = 1 << s; // set count

    // Allocate memory, write 0's for valid and tag
    cache_t cache = (cache_set_line_t*) calloc( S, sizeof(cache_set_line_t) );
    if (!cache) {
        fprintf(stderr, "Error allocating memory for cache\n");
        return EXIT_FAILURE;
    }

    // Process memory accesses
    unsigned int hit_count = 0;
    unsigned int miss_count = 0;
    unsigned int eviction_count = 0;
    char access_type;
    mem_addr_t address;
    while (fscanf(fp, " %c %llx", &access_type, &address) == 2) {
        switch (access_type) {
            case 'L':
            case 'S':
                accessData(address, cache, &hit_count, &miss_count, &eviction_count);
                break;
            case 'M':
                // A modify operation is equivalent to a load followed by a store
                accessData(address, cache, &hit_count, &miss_count, &eviction_count);
                accessData(address, cache, &hit_count, &miss_count, &eviction_count);
                break;
            default:
                break;
        }
    }
    printf("hits:%u misses:%u evictions:%u\n", hit_count, miss_count, eviction_count);

    // Free allocated memory
    free(cache);

    return 0;
}
