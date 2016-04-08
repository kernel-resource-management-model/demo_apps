//
//  main.c
//  disk_demo2
//
//  Created by Jenny on 27.10.15.
//  Copyright © 2015 com.mipt. All rights reserved.
//

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 512
int fdin, fdout;
char out_filename[SIZE];
char buffer[SIZE];
struct stat statbuf;


int main(int argc, const char * argv[]) {
    ssize_t c;
    if (argc <= 1) {
        return 0;
    }
    
    if ((fdin = open(argv[1], O_RDONLY)) < 0) {
        return -1;
    }
    
    if (fstat(fdin, &statbuf) < 0) {
        return -1;
    }
    
    strcat(out_filename, argv[1]);
    strcat(out_filename, "copy");
    
    if  ((fdout = open(out_filename, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, statbuf.st_mode)) < 0 ) {
    
        return -1;
    }
    
    while((c = read(fdin, buffer, SIZE)) > 0) {
        if (write(fdout, buffer, c) < 0) {
           
            return -1;
        }
    }

    return 0;
}
