#include "types.h"
#include "stat.h"
#include "user.h"


void child(void *arg)
{	
	
	printf(1,"this is child\t %s\n", (char*) arg);
	exit();
}
int main(int argc, char* argv[])
{
	printf(1,"main:begin\n");
	thread_t p1;
	int ret=thread_create(&p1, child, "A");
	

	ret = thread_join();
	printf(1,"returned to main from %d\n",ret);
	exit();
}
