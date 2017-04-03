#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "memlayout.h"

#include <stddef.h>


int thread_create(thread_t *p, void (*funct) (void *),void *arg)
{
	void *stack = malloc(sizeof(char)* PGSIZE);
	if(stack == NULL){
		printf(1,"out of memory!!");
		return -1;
	}
	
	int ret = clone(funct, stack, arg);
	if(ret < 0)
		{
			printf(1,"clone error");
			return -1;
		}
	return ret;
}

int thread_join()
{
	void *thread_stack;		//to store the user stack address of thre thread
	
	int ret = join(&thread_stack);
	free(thread_stack);		//free the user stack created in thread create used for spawning thread		
	return ret;
}		


void lock_init(lock_t *lock) {
  lock->flag = 0;
}

// spin locks
void thread_lock(lock_t *lock) {
  while(xchg(&lock->flag, 1) != 0);
}

//spinlock with hardware support
void thread_unlock(lock_t *lock) {
  xchg(&lock->flag, 0);
}

//locks with OS support 

//if the lock is acquired by someone else, the process gives up its quantum and lets the other process to run
/*void thread_lock(lock_t *lock) {
  while(xchg(&lock->flag, 1) != 0)
	  yieldl();
}

void thread_unlock(lock_t *lock) {
  xchg(&lock->flag, 0);
}
*/

//conditional variables
void cond_init(cond_t *cond)
{
	cond->id = 0;
}

void cond_wait(cond_t * cond, lock_t * lock){
  
  cond->queue[cond->id] = getpid(); 	//to store the pid of the process in the queue
  (cond->id) = cond->id + 1;				
 
  sleep_cond(lock);							
  thread_lock(lock);  
}

void cond_signal(cond_t * cond){
  
  if (cond->id !=0){ 
      (cond->id) = cond->id - 1;  
      int pid=cond->queue[cond->id];
      wake_cond(pid);
  }
}



