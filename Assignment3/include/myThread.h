typedef struct myThread_userView {
	pid_t tid;
	} myThread_u;

typedef struct myThread_tcb {
	pid_t tid;
	int state;
	void *(*start_routine)(void *);
	void *arg;
	void *return_val;
	struct myThread_tcb *prev,*next;
	}  myThread_t;
	
	
typedef struct myThread_attr{
 unsigned long stackSize;
 } myThread_attr_t;
 
int myThread_create(myThread_u *thread,myThread_attr_t *attr,void *(*start_routine)(void *),(void *)arg);
void myThread_exit(void *status);
int myThread_cancel(myThread_u thread);
int myThread_attr_init(myThread_attr_t *attr);
int myThread_attr_destroy(myThread_attr_t *attr);
myThread_t myThread_self(void);
int myThread_yield(void);
int myThread_join(int tid);
