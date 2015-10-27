//
//  main.c
//  memory_demo
//
//  Created by Jenny on 07.10.15.
//  Copyright © 2015 com.mipt. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#define SIZE 10000

volatile double big_data[SIZE][SIZE][SIZE];

int main(int argc, const char * argv[]) {
    int i, j, k;
    
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < SIZE; k++) {
                big_data[i][j][k] = MAXFLOAT;
            }
        }
    }
    
    
    return 0;
}
