#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for each node in the queue
typedef struct Node {
    unsigned char data;
    struct Node *next;
} Node;

// Structure for the queue itself
typedef struct {
    Node *head;
    Node *tail;
    int count;
} DynamicQueue;

// Function to initialize the dynamic queue
void init_dynamic_queue(DynamicQueue *q) {
    q->head = NULL;
    q->tail = NULL;
    q->count = 0;
}

// Function to check if the queue is empty
bool is_dynamic_empty(DynamicQueue *q) {
    return q->head == NULL;
}

// Function to enqueue a byte
void enqueue_dynamic(DynamicQueue *q, unsigned char data) {
    // 1. Create a new node
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed. Cannot enqueue.\n");
        return;
    }
    new_node->data = data;
    new_node->next = NULL;

    // 2. If the queue is empty, set both head and tail to the new node
    if (is_dynamic_empty(q)) {
        q->head = new_node;
        q->tail = new_node;
    } else {
        // 3. Otherwise, link the current tail to the new node
        q->tail->next = new_node;
        q->tail = new_node;
    }

    q->count++;
}

// Function to dequeue a byte
unsigned char dequeue_dynamic(DynamicQueue *q) {
    if (is_dynamic_empty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return 0;
    }

    // 1. Get the data from the head node
    unsigned char data = q->head->data;

    // 2. Save a pointer to the current head to free it later
    Node *temp = q->head;

    // 3. Move the head pointer to the next node
    q->head = q->head->next;

    // 4. If the queue becomes empty, reset the tail pointer
    if (q->head == NULL) {
        q->tail = NULL;
    }

    // 5. Free the old head node
    free(temp);
    q->count--;
    return data;
}

int main() {
    DynamicQueue my_queue;
    init_dynamic_queue(&my_queue);

    // Enqueue some data
    for (int i = 0; i < 50; i++) {
        enqueue_dynamic(&my_queue, (unsigned char)i);
    }
    printf("Enqueued 50 bytes. Count: %d\n", my_queue.count);

    // Dequeue some data
    unsigned char dequeued_data = dequeue_dynamic(&my_queue);
    printf("Dequeued: %d\n", dequeued_data);

    printf("Current queue count: %d\n", my_queue.count);

    return 0;
}
