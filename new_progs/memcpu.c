#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <unistd.h>

#define SIZE 4021010432 //total memory in bytes

volatile double *big_data;

int main(int argc, const char * argv[]) {
	if (argc != 3) {
		printf("Wrong number of arguments\n");
		return 0;
	}

	struct timeval tv, old_tv, diff;
	struct timezone tz;
	suseconds_t work_interval = 100000 * atoi(argv[2]) / 100, sleep_interval = 100000 * (100 - atoi(argv[2])) / 100;


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

	/*Making CPU work*/
	gettimeofday(&old_tv, &tz);
	for (i = 0; i < 300000000; i++) {
		gettimeofday(&tv, &tz);
		timersub(&tv, &old_tv, &diff);
		if (diff.tv_usec >= work_interval) {
			usleep(sleep_interval);
			gettimeofday(&old_tv, &tz);
		}
		else
			continue;
		//printf("%d s, %d msec\n", tv.tv_sec, tv.tv_usec);
	}
	
	munmap(big_data, doubles * sizeof(double));
	return 0;
}
