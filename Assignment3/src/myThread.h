#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

enum thread_state{READY,RUNNING,COMPLETED,BLOCKED,DEAD} ;
typedef struct tcb{
 int tid;
 enum thread_state ts ;
 ucontext_t context;
 void *(*start_routine)(void *);
 void *argument;
 void *return_value;
 int need_lock;
 int acquire_lock;
 }thread;
 
 typedef struct attr{
 int stacksize;
 }attr;
 
 
 typedef struct list_l{
 thread *t;
 struct list_l *next;
 struct list_l *head;
 }lock_list;
 
 typedef struct lock{
 lock_list *waiting_list;
 int key;
 }lock;
 
 int mythread_create(thread *t,attr *a,void *(*threadfunc)(void *),void *arg);
 void myThread_yield();
 int myThread_join(int tid);
 void myThread_exit();
 void set_lock(lock *l);
 void release_lock(lock *l);
 

#endif
