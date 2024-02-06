#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
#define ITERATIONS   1000000

int i = 0;

void	*increment(void *arg)
{
	for (int j = 0; j < ITERATIONS; j++)
	{
		i++;
	}
    pthread_exit(NULL);
}

int	main()
{
	pthread_t threads[NUM_THREADS];

	for (int t = 0; t < NUM_THREADS; t++)
	{
		pthread_create(&threads[t], NULL, increment, NULL);
	}
	for (int t = 0; t < NUM_THREADS; t++)
	{
		pthread_join(threads[t], NULL);
	}
	printf("Final value of i: %d\n", i);
	return (0);
}

/*

Final value of i: 1224464
Final value of i: 988294
Final value of i: 1005062
Final value of i: 1055194
*/