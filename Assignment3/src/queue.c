#include <stdio.h>
#include <stdlib.h>
#include "queue.h"




void initialize_q(queue *q)
 {
 q->front=NULL;
 q->rear=NULL;
 }
 
 void enqueue(queue *q,thread *t)
  {
  node *temp = (node*)malloc(sizeof(node));
  temp->t=t;
  if(q->front == NULL)
   {
    q->front=temp;
    }
    else
     {
     q->rear->next=temp;
     }
     q->rear=temp;
     q->rear->next=q->front;
     }
     
    thread *deQueue(queue *q)
      {
      thread *t1;
      if(q->front == NULL)
       return NULL;
       node *temp=(node*)malloc(sizeof(node));
       
       if(q->front==q->rear){
       t1=q->front->t;
       free(q->front);
       q->front=NULL;
       q->rear=NULL;
       }
       else
        {
        temp = q->front;
        t1=temp->t;
        q->front=q->front->next;
        q->rear->next=q->front;
        free(temp);
        }
        return t1;
       }
       
      thread *removeFromQueue(queue *q, int id)
        {
        node *prev=(node*)malloc(sizeof(node));
        node *curr=(node*)malloc(sizeof(node));
        thread *temp;
        curr=q->front;
        prev=curr;
        if(id==q->front->t->tid)
         deQueue(q);
         else
          {
          while(curr->t->tid!=id)
           {
           prev=curr;
           curr=curr->next;
           }
           }
           temp=curr->t;
           if(curr==q->rear)
           {
           prev->next=curr->next;
           q->rear=prev;
           free(curr);
           }
           else
           {
           prev->next=curr->next;
           free(curr);
           }
           return temp;
           }
           
           thread *getNextThread(queue *q, thread *t)
            {
            node *temp=(node*)malloc(sizeof(node));
            temp=q->front;
            while(temp->t!=t)
             {
             temp=temp->next;
             }
             return temp->next->t;
             }
             
             int isQueueEmpty(queue *q)
             {
             if(q->front ==NULL)
             return 1;
             return 0;
             }
            void print_queue(queue *q)
             {
             node *tmp=(node*)malloc(sizeof(node));
             printf("%d ",q->front->t->tid);
             tmp=q->front->next;
             while(tmp!=q->front)
             {
             printf("%d ",tmp->t->tid);
             tmp=tmp->next;
             }
             printf("\n");
             }
  
