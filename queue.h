#ifndef PULSE_OXIMETER_QUEUE_H
#define PULSE_OXIMETER_QUEUE_H

#include "define.h"

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
absorp getValue(Queue* queue, unsigned short index);
void EnQueue(Queue* queue, absorp value);
absorp DeQueue(Queue* queue);
void DeleteQueue(Queue* queue);

#endif //PULSE_OXIMETER_QUEUE_H
