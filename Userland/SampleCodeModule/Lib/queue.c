#include "../include/queue.h"

/*
typedef struct
{
    int front, rear, size;
    uint16_t array[SIZE];
} Queue;
*/

int isFull(Queue *queue)
{
    return (queue->size == SIZE);
}

int isEmpty(Queue *queue)
{
    return (queue->size == 0);
}

void enqueue(Queue *queue, int item)
{
    if (isFull(queue))
        return;
    queue->array[queue->rear] = item;
    queue->rear = (queue->rear + 1) % SIZE;
    queue->size = queue->size + 1;
}

int dequeue(Queue *queue)
{
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % SIZE;
    queue->size = queue->size - 1;
    return item;
}