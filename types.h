typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
typedef unsigned int thread_t;

typedef struct _lock_t{
	uint flag;
	}lock_t;
	
typedef struct {
	 
  int id;
  int queue[64]; // 
 
} cond_t;