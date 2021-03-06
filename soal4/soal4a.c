#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define NUM_THREADS 4 * 5


int (*value)[10];

int Aa[4][2] = {{2,1},
               {3,1},
               {1,4},
               {2,1}
              };
int Bb[2][5] = {{2,2,1,3,1}, 
               {2,1,3,1,2}
              };



struct v
{
	int i;
	int j;
};

void *runner(void *ptr);

int main(int argc, char **argv)
{
	int i, j;
	int thread_counter = 0;
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int[10][10]), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);
    
	
	pthread_t workers[NUM_THREADS];
	
	for (i=0; i < 4; i++)
	{
		for (j = 0; j < 5; j++) 
		{
			struct v *data = (struct v *) malloc(sizeof(struct v));
			data->i = i;
			data->j = j;
			pthread_create(&workers[thread_counter], NULL, runner, data);
			pthread_join(workers[thread_counter], NULL);
			thread_counter++;
		}
	}

	for (i=0;i<NUM_THREADS;i++)
	{
	    pthread_join(workers[i], NULL);
	}
	
	for(i=0;i<4;i++)
	{ 
		for(j=0;j< 5;j++)
		{ 
			printf("%d\t", value[i][j]);
		}
		printf("\n");
	}
	return 0;
}

void *runner(void *ptr)
{	
	struct v *data=ptr;
	int i, sum=0;
	
	for(i=0;i<2;i++)
	{	
		sum+=Aa[data->i][i]*Bb[i][data->j];
	}
	
	value[data->i][data->j]=sum;
	pthread_exit(0);
}