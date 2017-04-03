#include "types.h"
#include "stat.h"
#include "user.h"

#define NITER 50
#define SIZE 10

int buffer[SIZE];
int left;
int right;
int count;

lock_t mutex;
cond_t empty;
cond_t full;

void put(int value)
{
	buffer[right] = value;
	right = (right+1)%SIZE;
	count++;
}

int get()
{
	int value = buffer[left];
	left = (left+1)%SIZE;
	count--;
	return value;
}

void producer(void *arg)
{
	int i;
	for(i=0;i<NITER;i++)
	{
		thread_lock(&mutex);
		while (count == SIZE)
				cond_wait(&full, &mutex);
		put(i);
		cond_signal(&empty);
		thread_unlock(&mutex);
	}
	exit();
}

void consumer(void *arg)
{
	int i;
	for(i=0;i<NITER;i++)
	{
		thread_lock(&mutex);
		while (count == 0)
				cond_wait(&empty, &mutex);
		int value = get(i);
		cond_signal(&full);
		thread_unlock(&mutex);
		printf(1,"%d   ",value);
	}
	exit();
}
int main(int argc, char **argv)
{
	printf(1,"\t\tproducer consumer problem\nparent : begin\n");
	lock_init(&mutex);	
	cond_init(&empty);
	cond_init(&full);
	
	thread_t p1,p2;
	thread_create(&p1, producer, "A");
	thread_create(&p2, consumer, "B");
	
	
	thread_join();
	thread_join();
	printf(1,"\nparent : end\n");
exit();
}
