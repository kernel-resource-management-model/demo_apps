//
//  main.c
//  memory_demo
//
//  Created by Stasia on 07.10.15.
//  Copyright © 2015 com.mipt. All rights reserved.
//

#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#define SIZE 10000000000000

volatile double *big_data;

int main(int argc, const char * argv[]) {
    long int i;
    
    if ((big_data = mmap(0, SIZE*sizeof(double), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0)) == MAP_FAILED) {
        return errno;
    }
    
    for (i = 0; i < SIZE; i++) {
        big_data[i] = MAXFLOAT;
    }
    
    munmap(big_data, SIZE);
    
    return 0;
}
