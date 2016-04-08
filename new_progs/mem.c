/* This program only consumes memory.
Watch the statistics with "top -d 1 -p PID",
where PID is id of this process.*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include <float.h>

#define SIZE 4021010432 //total memory in bytes

volatile double *big_data;

int main(int argc, const char * argv[]) {
	if (argc != 2) {
		printf("Wrong number of arguments\n");
		return 0;
	}
	long int i;
	int percentage = atoi(argv[1]);
	long int doubles = SIZE * percentage / 800;
	if ((big_data = mmap(0, doubles * sizeof(double), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0)) == MAP_FAILED) {
		printf("mmap failed\n");
		//fails at >= 84%
		return errno;
	}
    
	for (i = 0; i < doubles; i++) {
		big_data[i] = 19999.99;
	}

	sleep(20);
	munmap(big_data, doubles * sizeof(double));
	return 0;
}
