/*#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREADNUM 100000

long int result;

void *print(void *number)
{
	//printf("thread #%d, id = 0x%lx is created\n", *(int *)number, pthread_self());
	result++;
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t *thr = (pthread_t *)malloc(THREADNUM * sizeof(pthread_t));
	int *numbers = (int *)malloc(THREADNUM * sizeof(int));
	for (int i = 0; i < THREADNUM; i++)
	{
		numbers[i] = i + 1;
		if (pthread_create(&thr[i], (pthread_attr_t *) NULL, print, (void *)&(numbers[i])) != 0)
		{
			printf("Cant create threads\n");
			return -1;
		}
	}
	for (int i = 0; i < THREADNUM; i++)
	{
		if (pthread_join(thr[i], (void **)NULL) != 0)
		{
			printf("Cant close thread\n");
			return -1;
		}
		//printf("thread #%d, id = 0x%lx is closed\n", numbers[i], thr[i]);
	}
	free(numbers);
	free(thr);
	return 0;
}
*/

#include <stdio.h>
#include <time.h>
#include <omp.h>

int main() {
    double start, end;
    double runTime;
    start = omp_get_wtime();
    int num = 1,primes = 0;

    int limit = 100000;

#pragma omp parallel for schedule(dynamic) reduction(+ : primes)
    for (num = 1; num <= limit; num++) { 
        int i = 2; 
        while(i <= num) { 
            if(num % i == 0)
                break;
            i++; 
        }
        if(i == num)
            primes++;
//      printf("%d prime numbers calculated\n",primes);
    }

    end = omp_get_wtime();
    runTime = end - start;
    printf("This machine calculated all %d prime numbers under %d in %g seconds\n",primes,limit,runTime);

    return 0;
}
