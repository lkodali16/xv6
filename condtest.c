#include "types.h"
#include "stat.h"
#include "user.h"

//volatile int counter = 0;
static volatile int done = 0;
lock_t lock;
cond_t cond;
void worker(void *arg)
{
	int i=0;
	for(i=0;i<100;i++);
	thread_lock(&lock);
	done = 1;
	cond_signal(&cond);
	thread_unlock(&lock);
	printf(1,"Child ends\t %s\n", (char*) arg);
	
exit();
}
int main(int argc, char **argv)
{
	printf(1,"Initialising main\n");
	lock_init(&lock);	
	cond_init(&cond);
	thread_t p1;
	int ret=thread_create(&p1, worker, "A");
	
	printf(1,"created thread with pid: %d and waiting for it to finish..\n",ret);
	
	//Wait for child to finish work
	thread_lock(&lock);
	while (!done)
		cond_wait(&cond, &lock);
	thread_unlock(&lock);
	
	//wait for the child to fully finish
	ret = thread_join();
	//thread_join();
	printf(1,"parent finishes \treturned pid: %d\n",ret);
exit();
}
