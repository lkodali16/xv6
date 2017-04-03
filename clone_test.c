#include "types.h"
#include "stat.h"
#include "user.h"

void child(void *arg){
	printf(1,"this is child\t%s\n",(char*) arg);
	//exit ();
}

int main(int argc, char* argv[])
{
	void *stack = (void *)malloc(4096);	
	int ret=clone(child,stack,"A");
	printf(1,"thread %d is spawned\n",ret);
	//sleep(10);
exit();
}
