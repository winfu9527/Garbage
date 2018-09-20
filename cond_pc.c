#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define CONSUMERS_COUNT 2 
#define PRODUCERS_COUNT 4


pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_t g_thread[CONSUMERS_COUNT+PRODUCERS_COUNT];
int nready = 0;

void *consume(void *arg)
{
	int num = (int)arg;
	
	while(1) {
		pthread_mutex_lock(&mutex);
		printf("%d consume lock....\n",num);
		sleep(6);

		while (nready <= 0) {
			printf("%d begin wait a conditon!\n",num);	
			pthread_cond_wait(&cond, &mutex);
		}
		printf("%d begin consume produce...\n",num);
		nready--;
		printf("%d end consume produce!\n",num);
		printf("%d consume unlock....\n",num);
		pthread_mutex_unlock(&mutex);
		sleep(3);
	}
}

void *produce(void *arg)
{
	int num = (int)arg;

	while(1) {
		pthread_mutex_lock(&mutex);
		printf("%d produce lock....\n",num);
		printf("%d begin produce product...\n",num);	
		nready++;
		printf("%d end produce product!\n",num);
		pthread_cond_signal(&cond);
		printf("%d produce unlock....\n",num);
		pthread_mutex_unlock(&mutex);
		sleep(6);
	}
}

int main(int argc,char *argv[])
{
	int i;

	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);

	//消费者
	for (i=0; i<CONSUMERS_COUNT; i++)
		pthread_create(g_thread+i, NULL, consume, (void*)i);

	//生产者
	for (i=0; i<PRODUCERS_COUNT; i++)
		pthread_create(&g_thread[CONSUMERS_COUNT+i], NULL, produce, (void*)i);

	for (i=0; i<CONSUMERS_COUNT+PRODUCERS_COUNT; i++)
		pthread_join(g_thread[i],NULL);

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
}
