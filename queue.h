//
// Created by adrien on 30/03/2020.
//

#ifndef PULSE_OXIMETER_QUEUE_H
#define PULSE_OXIMETER_QUEUE_H

#include "define.h"

#define ERR_VAL -2147483648 //smallest value for an integer (32bits)

typedef struct Node{
    absorp data;
    struct Node* next;
} Node;

typedef struct{
    struct Node* front;
    struct Node* rear;
    unsigned short size;
} Queue;

Queue* CreateQueue();
unsigned short isEmptyQueue(Queue* queue);
unsigned short queueSize(Queue* queue);
void EnQueue(Queue* queue, absorp value);
absorp DeQueue(Queue* queue);
void DeleteQueue(Queue* queue);

#endif //PULSE_OXIMETER_QUEUE_H
