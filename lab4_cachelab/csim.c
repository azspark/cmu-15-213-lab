/*
    Author: azspark
    Email: one12546@126.com
*/
#include "cachelab.h"
#include <getopt.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h>

typedef struct cache_block{
    unsigned long address;
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
        (cb + i)->address = 0;
        (cb + i)->valid = 0;
        (cb + i)->last_accessed_time = 0;
    }
}

int main(int argc, char* argv[]) {
    int showTraces = 0;
    char* traceFileName;
    char c;
    int s;
    int E;
    int b;
    /*Parse arguments*/
    while ((c = getopt(argc, argv, "Vs:E:b:t:")) != -1) {
        switch (c) {
            case 'V':
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
    pFile = fopen(traceFileName, 'r');
    char access_type;
    unsigned long address;
    int size;
    while (fscanf(pFile, " %c %lx, %d", &access_type, &address, &size) > 0) {
        if (access_type == 'L') {
            
        } else if (access_type == 'S') {

        } else if (access_type == 'M') {

        }
    }
    
    fclose(pFile);
    free(cb);
    printSummary(0, 0, 0);
    return 0;
}
