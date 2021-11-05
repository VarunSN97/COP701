#include <signal.h>
#include <ucontext.h>
#include <time.h>
#include "queue.h"
#include "myThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

#define STACK 32768

static int count=0;
static int initialize=0;
static int in_time=0;
static queue *ready;
static queue *completed;
static thread *running;
static thread *new_running;

static attr *attribute;

thread *pointer;
  
 struct itimerval tvalue;
 
 int myThread_self()
  {
  return running->tid;
  }
  myThread_attr_init(attr *a)
  {
  a->stacksize=STACK;
  }
  
  myThread_attr_destroy(attr *a)
   {
   free(a);
   }
  
   
 static void block()
  {
  sigset_t sigprof;
  sigemptyset(&sigprof);
  sigaddset(&sigprof,SIGPROF);
  if(sigprocmask(SIG_BLOCK,&sigprof,NULL)==-1)
  abort();
  }
  static void unblock()
  {
  sigset_t sigprof;
  sigemptyset(&sigprof);
  sigaddset(&sigprof,SIGPROF);
  if(sigprocmask(SIG_UNBLOCK,&sigprof,NULL)==-1)
  abort();
  }
 static void handle(int sig,siginfo_t *info,void *context)
 {
 block();
 pointer=running;
 enqueue(ready,running);
 running = deQueue(ready);
 if(running->need_lock != running->acquire_lock)
  {
  myThread_yield();
  unblock();
  }
  else
 swapcontext(&pointer->context,&running->context);
  }
  
  mythread_cancel(thread *t)
  {
  thread *temp=removeFromQueue(ready,t->tid);
  free(temp);
  }
 void scheduler()
  {
  thread *main=(thread*)malloc(sizeof(thread));
  main->tid=101;
  main->ts=RUNNING;
  getcontext(&main->context);
  main->start_routine=NULL;
  main->argument=NULL;
  main->return_value=NULL;
  main->need_lock=0;
  main->acquire_lock=0;
  enqueue(ready,main);
  running=main;
  struct sigaction sa;
  memset(&sa,0,sizeof(sa));
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction=&handle;
  sa.sa_flags=SA_NODEFER;
  sigaction(SIGPROF,&sa,NULL);
  struct itimerval it_val;
  it_val.it_interval.tv_sec=0;
  it_val.it_interval.tv_usec=50000;
  it_val.it_value.tv_sec=0;
  it_val.it_value.tv_usec=50000;
  setitimer(ITIMER_PROF,&it_val,NULL);
  
  }
  
  static void wrapper(void *(*fun)(void *),void *a)
   {
   fun(a);
   myThread_exit(running->ts);
   }
  
  
  int mythread_create(thread *t,attr *a,void *(*threadfunc)(void *),void *arg)
   {
   block();
 
   
   if(initialize==0)
    {
    ready=(queue*)malloc(sizeof(queue));
    initialize_q(ready);
  
    completed=(queue*)malloc(sizeof(queue));
    initialize_q(completed);
    initialize=1;
    }
    if(in_time==0)
     {
     scheduler();
     in_time=1;
     }
    
     t->tid = count++;
     if(getcontext(&t->context)==-1)
      return (0);
      t->context.uc_stack.ss_sp=malloc(32768);
      t->context.uc_stack.ss_size=32768;
      t->start_routine=threadfunc;
      t->argument=arg;
      t->need_lock=0;
      t->acquire_lock=0;
      enqueue(ready,t);
      makecontext(&t->context,(void (*)())wrapper,2,threadfunc,arg);
      unblock();
      return t->tid;
      
      }
      
      void myThread_exit(enum thread_state ts)
       {
       running->ts=DEAD;
       if(running==NULL)
       {
       exit(1);
       }
       block();
       (enqueue(completed,running));
       if(isQueueEmpty(ready)==1)
       exit(1);
       myThread_yield();
       unblock();
       }
       
       int myThread_join(int tid)
        {
        block();
        thread *temp=removeFromQueue(completed,tid);
        unblock();
        if(temp==NULL)
         return 0;
        else
         {
         free(temp);
         }
         return tid;
         } 
         
         void myThread_yield()
         {
        struct itimerval it_val;
  	it_val.it_interval.tv_sec=0;
  	it_val.it_interval.tv_usec=50000;
  	it_val.it_value.tv_sec=0;
  	it_val.it_value.tv_usec=50000;
  	setitimer(ITIMER_PROF,&it_val,NULL);
  
        raise(SIGPROF);
         }
         
         
         void set_lock(lock *l)
          {
          if(__sync_val_compare_and_swap(&(l->key),0,1))
           {
           running->need_lock=1;
           running->acquire_lock=0;
           if(l->waiting_list==NULL)
            {
            l->waiting_list=(lock_list*)malloc(sizeof(lock_list));
            l->waiting_list->t=running;
            }
            
           
            myThread_yield();
            }
            else
            {
            running->need_lock=1;
            running->acquire_lock=1;
           }
           }
           
           void release_lock(lock *l)
           {
           if(l->waiting_list==NULL)
           return;
           else
            {
            running->need_lock=0;
            running->acquire_lock=0;
            }
            }
           
           
         
  
