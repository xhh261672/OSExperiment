#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

typedef int buffer_item;
#define BUFFER_SIZE 5

buffer_item  buffer[BUFFER_SIZE];

int insertItem(buffer_item item){

}

int  removeItem (buffer_item *item){

}

void * producer(void *param){
	buffer_item randNum;
	while(1){
		sleep(rand()%5);
		randNum = rand()%10;
		printf("producer produced %d\n",randNum );
	}
}
void *consumer(void *param){
	buffer_item randNum;
	while(1){
		sleep(rand()%5);
		randNum = rand()%10;
		printf("consumer consumed %d\n",randNum );
	}
}

int main(int argc, char *argv[])
{
	int sleepTime = atoi(argv[1]);
	int producerNum = atoi(argv[2]);
	int consumerNum = atoi(argv[3]);

	buffer_item buffer[BUFFER_SIZE];
	
	pthread_t ptid[producerNum];
	pthread_t ctid[consumerNum];
	pthread_attr_t pattr[producerNum];
	pthread_attr_t cattr[consumerNum];

	for (int i = 0; i < producerNum; i++)
	{
		pthread_attr_init(&pattr[i]);
		pthread_create(&ptid[i] , &pattr[i], producer,NULL);
//		pthread_join(ptid[i],NULL);
	}
	for (int i = 0; i < consumerNum; i++)
	{
		pthread_attr_init(&cattr[i]);
		pthread_create(&ctid[i] , &cattr[i], consumer,NULL);
	}

	sleep(sleepTime);
	return 0;
}