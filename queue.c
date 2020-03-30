#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

Queue* CreateQueue(){
    Queue* emptyQueue = (Queue*)malloc(sizeof(Queue));   //creates a new list
    emptyQueue->front = NULL;                            //the list is empty so there is no front cell
    emptyQueue->size = 0;
    return emptyQueue;                                   //return the address of the new list
}
unsigned short isEmptyQueue(Queue* queue){
    if (queue->front != NULL){                          //the list is empty if the first cell doesn't exist (NULL)
        return 0;
    }
    else return 1;
}

unsigned short queueSize(Queue* queue){
    return queue->size;
}

void EnQueue(Queue* queue, absorp value){
    if(queueSize(queue) == 51){                          //makes sure there is never more than 51 value in the queue
        DeQueue(queue);
    }
    queue->size++;
    struct Node* NewCell = (Node*)malloc(sizeof(Node));
    NewCell->data = value;                              //the new cell contain the new value
    NewCell->next = NULL;                               //the new cell is the last cell and points towards nothing
    if (isEmptyQueue(queue) == 0){
        (queue->rear)->next = NewCell;                  //if the list is not empty the actual last cell now points toward the new cell
    }
    queue -> rear = NewCell;                            //the last cell is now the new cell
    if (isEmptyQueue(queue) == 1){
        queue -> front = queue -> rear;                 //if the list was empty then the last cell is also the first one
    }
}
absorp DeQueue(Queue* queue){
    queue->size--;
    if (isEmptyQueue(queue) == 1){
        absorp error;
        error.acr = ERR_VAL;
        error.acir = ERR_VAL;
        error.dcir = ERR_VAL;
        error.dcr = ERR_VAL;
        return error;                                   //if the list is empty we cannot pop so we return a forbidden value
    }
    Node* NextCell = (queue->front)->next;              //saves the address of the second cell
    absorp value = (queue->front)->data;                //saves the value of the first cell
    free (queue->front);                                //free the memory allocated to the first cell
    queue->front = NextCell;                            //the first cell is now the old second cell
    return value;                                       //return the value we saved
}
void DeleteQueue(Queue* queue){
    struct Node* NextCell;                              //creates a new pointer towards a list
    while (isEmptyQueue(queue) != 1){                   //until the list is empty
        NextCell = queue->front;                        //NextCell points toward the first cell
        queue->front = (queue->front)->next;            //the second cell becomes the first cell
        free (NextCell);                                //free the memory allocated to the first cell
    }
    free(queue);                                        //free the entire list
}