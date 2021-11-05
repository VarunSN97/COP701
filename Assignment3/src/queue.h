#ifndef QUEUE_H
#define QUEUE_H


#include "myThread.h"
#include <unistd.h>
typedef struct queue queue;
typedef struct qNode node;

struct qNode {
thread *t;
struct qNode *next;
};

 struct queue {
node *front,*rear;
};

void initialize_q(queue *q);
void enqueue(queue *q, thread *t);
thread *deQueue(queue *q);
thread *removeFromQueue(queue *q,int id);
thread *getNextThread(queue *q,thread *t);
int isQueueEmpty(queue *q);
void print_queue(queue *q);

#endif
