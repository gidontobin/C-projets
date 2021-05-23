/***************
 * Gidon Tobin
 * 320518020
 * 01
 * ex6
 ***************/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*********************************************************************************************
 *Function Name: createQueue
 * Input:
 * Output: Queue* (pointer to Queue type)
 * Function Operation: The function creates a Queue type, and reaturns a pointer to it.
 *                     If the malooc failed, it will return NULL.
 *********************************************************************************************/
Queue* createQueue(){
    Queue* newQueue=(Queue *) malloc(sizeof(Queue));
    if (newQueue==NULL)
        return NULL;
    newQueue->front=NULL;
    newQueue->rear=NULL;
    return newQueue;
}

/*********************************************************************************************
 *Function Name: enQueue
 * Input: Queue* q (pointer to Queue type), void* k (pointer to any type)
 * Output: int (values between 1-0)
 * Function Operation: The function creates a Qnode type, and adds k to the key of the node,
 *                     and adds it to the queue. If the malloc faills the function will send back 0.
 *                     Else, it will send back 1.
 *********************************************************************************************/
int enQueue(Queue* q, void* k) {
    if (q==NULL||k==NULL)
        return 1;
    QNode* newQNode=(QNode *) malloc(sizeof(QNode));
    if (newQNode==NULL){
        destroyQueue(q);
        return 0;
    }
    newQNode->key=k;
    newQNode->next=NULL;
    if (q->front==NULL)
        q->front=newQNode;
    if (q->rear!=NULL)
        q->rear->next=newQNode;
    q->rear=newQNode;
    return 1;
}

/*********************************************************************************************
 *Function Name: deQueue
 * Input: Queue* q (pointer to Queue type)
 * Output: void
 * Function Operation: The function removes the front of the queue and makes the front be the
 *                     qnode next in line, and frees the use to be front of line.
 *********************************************************************************************/
void deQueue(Queue* q) {
    if (q==NULL||q->front==NULL)
        return;
    QNode* temp =q->front;
    q->front=q->front->next;
    free(temp);
}

/*********************************************************************************************
 *Function Name: isEmpty
 * Input: Queue* q (pointer to Queue type)
 * Output: void
 * Function Operation: The function checks if the queue is empty. If it is, it will return 1.
 *                     If not - it will return 0.
 *********************************************************************************************/
int isEmpty(Queue* q){
    if (q->front==NULL)
        return 1;
    return 0;
}

/*********************************************************************************************
 *Function Name: destroyQueue
 * Input: Queue* q (pointer to Queue type)
 * Output: void
 * Function Operation: The function destroys the queue given, by useing recrucion, and freeing
 *                     all the qnodes and the queue itself.
 *********************************************************************************************/
void destroyQueue(Queue* q){
    if (q==NULL)
        return;
    if (isEmpty(q)) {
        free(q);
        return;
    }
    deQueue(q);
    destroyQueue(q);
}