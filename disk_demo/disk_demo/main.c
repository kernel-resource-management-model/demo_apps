//
//  main.c
//  disk_demo
//
//  Created by Stasia on 27.10.15.
//  Copyright © 2015 com.mipt. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include "logger.c"
#define FORMAT "copy"
#define PATH_SIZE 512
#define SIZE 512
int fdin, fdout;
struct stat statbuf;
char out_dir[PATH_SIZE] = "./";
char in_filename[SIZE], out_filename[SIZE];
char buffer[SIZE];


char *curr_out_dir(void) {
    return out_dir;
}


int set_dir(char *object, int mode) {
    strcat(out_dir, object);
    strcat(out_dir, FORMAT);
    strcat(out_dir, "/");
    if (mkdir(out_dir, mode) < 0) {
        return errno;
    }
   
    return 0;
}

int is_good_file(char *filename) {
    return strcmp(filename, ".") && strcmp(filename, "..")&&(filename[0] != '.');
}

int prev_dir(void) {
    unsigned long int curr;
    
    curr = strlen(out_dir) - 1;
    while(curr > 0) {
        curr--;
        if (out_dir[curr] == '/') {
            out_dir[curr + 1] = '\0';
            break;
        }
    }
    
    return 0;
}

char *get_filename(char *path) {
    unsigned long int curr;

    curr = strlen(path);
    while(curr > 0) {
        curr--;
        if (path[curr] == '/') {
            return path + curr + 1;
        }
    }
    
    return path;
}

char *get_dir_name(char *path) {
    unsigned long int curr;
    
    curr = strlen(path);
    while(curr > 0) {
        curr--;
        if (path[curr] == '/') {
            return path + curr;
        }
    }
    
    return path;
}

int process_path(char *in_path, char *out_path) {
    memset(in_filename, '\0', SIZE);
    memset(out_filename, '\0', SIZE);
    strcpy(in_filename, in_path);
    strcpy(out_filename, out_path);
    //log_add(DEBUGGING, "in %s\n", in_filename);
    strcat(out_filename, get_filename(in_filename));
    
    return 0;
}


int copy_file(char *in_path, char *out_path) {
      ssize_t c;
    //log_add(DEBUGGING, "In copy_file\n");
    process_path(in_path, out_path);
    strcat(out_filename, FORMAT);
   // log_add(DEBUGGING, "out %s\n", out_filename);
    
    if ((fdin = open(in_filename, O_RDONLY)) < 0) {
       // log_add(FATAL, "Can't open input file\n");
        return errno;
    }
    
    if (fstat(fdin, &statbuf) < 0) {
       // log_add(FATAL, "Can't determine the input file size\n");
        return errno;
    }
    
    if  ((fdout = open(out_filename, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, statbuf.st_mode)) < 0 ) {
       // log_add(FATAL, "Can't create output file\n");
        return errno;
    }
    
    while((c = read(fdin, buffer, SIZE)) > 0) {
        if (write(fdout, buffer, c) < 0) {
          //  log_add(FATAL, "Writing failed\n");
            return errno;
        }
    }
    
    return 0;
}

int copy(char *in_object) {
    
    char object[PATH_SIZE];
    
    strcpy(object, in_object);
    struct stat buf;
   // log_add(DEBUGGING, "In copy %s\n", object);
    if (stat(object, &buf) != 0) {
        log_add(FATAL, "stat failed\n");
        return errno;
    }
    if(S_ISDIR(buf.st_mode)) {
        DIR *dir;
        struct dirent *entry;
        
        if ((dir = opendir(object)) == 0) {
            log_add(FATAL, "Can't open directory\n");
            return errno;
        }

        set_dir(get_filename(object), buf.st_mode);
        
        while ((entry = readdir(dir)) != NULL) {
           // log_add(DEBUGGING, "In while\n");
           // log_add(DEBUGGING, "object is %s\n", object);
          //  log_add(DEBUGGING, "file %s\n", entry->d_name);
            if (is_good_file(entry->d_name)) {
                
                strcat(object, "/");
                strcat(object, entry->d_name);
                
                copy(object);
                object[strlen(object)-strlen(entry->d_name)-1] = '\0';
            }
            
        }
        closedir(dir);
        prev_dir();
    }
    else {
       
        copy_file(object, curr_out_dir());
    }
    
    return 0;
}


int main(int argc, const char * argv[]) {
    if (argc <= 1) {
        return 0;
    }
    copy(argv[1]);
    return 0;
}
