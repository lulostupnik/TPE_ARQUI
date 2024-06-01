#ifndef QUEUE_H
#define QUEUE_H
#include <stdint.h>

#define SIZE 10

typedef struct
{
    int front, rear, size;
    uint16_t array[SIZE];
} Queue;

int isEmpty(Queue *queue);
int isFull(Queue *queue);
void enqueue(Queue *queue, int item);
int dequeue(Queue *queue);

#endif // QUEUE_H
