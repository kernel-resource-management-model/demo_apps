/*A program that only consumes CPU.*/
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
	if (argc != 2) {
		printf("Wrong number of arguments\n");
		return 0;
	}
	//int sleep_sec = 100000 * atoi(argv[1]) / 100, work_sec = 100000 - sleep_sec;
	struct timeval tv, old_tv, diff;
	struct timezone tz;
	suseconds_t work_interval = 100000 * atoi(argv[1]) / 100, sleep_interval = 100000 * (100 - atoi(argv[1])) / 100;
	long int i;
	gettimeofday(&old_tv, &tz);
	for (i = 0; i < 300000000; i++) {
		gettimeofday(&tv, &tz);
		timersub(&tv, &old_tv, &diff);
		if (diff.tv_usec >= work_interval) { //50000
			usleep(sleep_interval);
			gettimeofday(&old_tv, &tz);
			//memcpy(&old_tv, &tv, sizeof(struct timeval));
		}
		else
			//printf("oh\n");
			continue;
		//printf("%d s, %d msec\n", tv.tv_sec, tv.tv_usec);
	}
	return 0;
}
