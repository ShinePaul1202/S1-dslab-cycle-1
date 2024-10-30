#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    int items[MAX];
    int front, rear;
} CircularQueue;

CircularQueue* createQueue() {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

int isFull(CircularQueue* queue) {
    return (queue->front == (queue->rear + 1) % MAX);
}

int isEmpty(CircularQueue* queue) {
    return (queue->front == -1);
}

void enqueue(CircularQueue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear = (queue->rear + 1) % MAX;
    queue->items[queue->rear] = value;
    printf("Enqueued: %d\n", value);
}

int dequeue(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int item = queue->items[queue->front];
    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX;
    }
    printf("Dequeued: %d\n", item);
    return item;
}

void display(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue: ");
    int i = queue->front;
    while (1) {
        printf("%d ", queue->items[i]);
        if (i == queue->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    CircularQueue* queue = createQueue();

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    display(queue);

    dequeue(queue);
    display(queue);

    enqueue(queue, 40);
    enqueue(queue, 50);
    enqueue(queue, 60);
    display(queue);

    dequeue(queue);
    dequeue(queue);
    display(queue);

    enqueue(queue, 70);
    display(queue);

    return 0;
}
