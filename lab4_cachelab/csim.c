/*
    Author: azspark
    Email: one12546@126.com
*/
#include "cachelab.h"
#include <getopt.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

typedef struct cache_block{
    unsigned long tag;
    int valid;
    unsigned int last_accessed_time;
} cache_block;

int powerOf2(int x) {
    /*Naive Implementation without Fast Exponentiation*/
    
    if (x < 0) return -1; //No other Expectation handling for this lab
    int out = 1;
    while (x-- > 0) {
        out *= 2;
    }
    return out;
}

void initCacheBlock(cache_block* cb, int cache_block_size) {
    
    for (int i = 0; i < cache_block_size; i++) {
        (cb + i)->tag = 0;
        (cb + i)->valid = 0;
        (cb + i)->last_accessed_time = 0;
    }
}

void parseSetidxTag(unsigned long address, int s, int b, int tagSize, 
    
    int setNum, unsigned long* tag, unsigned long* setIdx) {
    *setIdx = (address << tagSize) >> (tagSize + b);
    *tag = address >> (s + b);
    if (*setIdx >= setNum) {
        perror("Set Index is not set properly");
        exit(-1);
    }
}

/*
 * searchBlock - search if there is any match block in specified set,
 *               if not, return the block index to add accroding to
 *               emptiness or LRU(Least recent used) and update information.
 */
int searchBlock(cache_block* cb, unsigned long tag, unsigned long setIdx, int E,
     int showTrace, int* hit, int* miss) {
    
    int candidateAddedIdx = -1;
    unsigned int leastRecentAccessBlockTime = UINT_MAX;
    int findEmpty = 0;
    int hitTarget = 0;
    for (int i = 0; i < E; i++) {
        cache_block* curCB = cb + (setIdx * E + i);
        if (curCB->valid) {
            if (curCB->tag == tag) {
                hitTarget = 1;
                break;
            } else if (!findEmpty) {  //Have not find the target, so find an insert target
                if (curCB->last_accessed_time < leastRecentAccessBlockTime) {
                    candidateAddedIdx = i;
                    leastRecentAccessBlockTime = curCB->last_accessed_time;
                }
            }
        } else {
            if (!findEmpty) {
                candidateAddedIdx = i;
                findEmpty = 1;
            }
        }
    }

    if (hitTarget) {
        if (showTrace) printf("hit ");
        *hit += 1;
        return -1;
    } else {
        if (showTrace) printf("miss ");
        *miss += 1;
        return candidateAddedIdx;
    }
}

/*
 * addBlock - 
 */
void addBlock(int blockIdx, cache_block* cb, unsigned long tag, unsigned long setIdx, int E,
     int showTrace, int time, int* eviction) {
    
    cache_block* addCB = cb + (setIdx * E + blockIdx);
    if (addCB->valid) {
        *eviction += 1;
        if (showTrace) printf("eviction ");
    }
    addCB->valid = 1;
    addCB->last_accessed_time = time;
    addCB->tag = tag;
}

void loadOrStoreData(cache_block* cb, unsigned long tag, unsigned long setIdx, int E,
     int showTrace, int time, int* hit, int* miss, int* eviction) {
    
    int searchOutcome = searchBlock(cb, tag, setIdx, E, showTrace, hit, miss);
    if (searchOutcome != -1) {
        addBlock(searchOutcome, cb, tag, setIdx, E, showTrace, time, eviction);        
    }
}

void modifyData(cache_block* cb, unsigned long tag, unsigned long setIdx, int E,
     int showTrace, int time, int* hit, int* miss, int* eviction) {
    
    loadOrStoreData(cb, tag, setIdx, E, showTrace, time, hit, miss, eviction);
    *hit += 1;
    if (showTrace) printf("hit ");
}


int main(int argc, char* argv[]) {
    
    int showTraces = 0;
    char* traceFileName;
    char c;
    int s;
    int E;
    int b;
    /*Parse arguments*/
    while ((c = getopt(argc, argv, "vs:E:b:t:")) != -1) {
        switch (c) {
            case 'v':
                showTraces = 1;
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                traceFileName = optarg;
        }
    }
    int setNum = powerOf2(s);
    int tagSize = 64 - (s + b);

    cache_block* cb = (cache_block *) malloc(sizeof(cache_block) * (setNum * E));
    initCacheBlock(cb, setNum * E);

    /*Initialize Metric Value*/
    int hit = 0;
    int miss = 0;
    int eviction = 0;
    /*Start reading file and simulating*/
    FILE *pFile;
    pFile = fopen(traceFileName, "r");
    char access_type;
    unsigned long address;
    int size;

    unsigned long tag, setIdx;
    int time = 0;
    while (fscanf(pFile, " %c %lx, %d", &access_type, &address, &size) > 0) {
        if (access_type != ' ')
            parseSetidxTag(address, s, b, tagSize, setNum, &tag, &setIdx);
        else 
            continue;
        time++;
        if (access_type == 'L' || access_type == 'S') {
            if (showTraces) printf("%c %lx, %d ", access_type, address, size);
            loadOrStoreData(cb, tag, setIdx, E, showTraces, time, &hit, &miss, &eviction);
            if (showTraces) printf("\n");
        } else if (access_type == 'M') {
            if (showTraces) printf("%c %lx, %d ", access_type, address, size);
            modifyData(cb, tag, setIdx, E, showTraces, time, &hit, &miss, &eviction);
            if (showTraces) printf("\n");
        }
        
    }
    
    fclose(pFile);
    free(cb);
    printSummary(hit, miss, eviction);
    return 0;
}
