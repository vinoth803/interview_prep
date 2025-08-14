#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

// A simple queue data structure
typedef struct {
    unsigned char buffer[MAX_SIZE];
    int head;
    int tail;
    int count;
} Queue;

// Function to initialize the queue
void init_queue(Queue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

// Function to check if the queue is full
bool is_full(Queue *q) {
    return q->count == MAX_SIZE;
}

// Function to check if the queue is empty
bool is_empty(Queue *q) {
    return q->count == 0;
}

// Function to enqueue a byte
void enqueue(Queue *q, unsigned char data) {
    if (is_full(q)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    q->buffer[q->head] = data;
    q->head = (q->head + 1) % MAX_SIZE;
    q->count++;
}

// Function to dequeue a byte
unsigned char dequeue(Queue *q) {
    if (is_empty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return 0; // Return a default value
    }
    unsigned char data = q->buffer[q->tail];
    q->tail = (q->tail + 1) % MAX_SIZE;
    q->count--;
    return data;
}

int main() {
    Queue my_queue;
    init_queue(&my_queue);

    // Enqueue some data
    for (int i = 0; i < 50; i++) {
        enqueue(&my_queue, (unsigned char)i);
    }
    printf("Enqueued 50 bytes. Count: %d\n", my_queue.count);

    // Dequeue some data
    unsigned char dequeued_data = dequeue(&my_queue);
    printf("Dequeued: %d\n", dequeued_data);
    dequeued_data = dequeue(&my_queue);
    printf("Dequeued: %d\n", dequeued_data);

    printf("Current queue count: %d\n", my_queue.count);

    // Enqueue more data, showing the wrap-around
    for (int i = 50; i < 100; i++) {
        enqueue(&my_queue, (unsigned char)i);
    }
    printf("Enqueued more data. Count: %d\n", my_queue.count);

    return 0;
}
