#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node* cirlist_get_node(int value) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = value;
    new->next = NULL;
    return new;
}

bool cirlist_insert_node(int pos, int value, Node **head) {
    Node *new_node = cirlist_get_node(value);

    if (*head == NULL) {
        if (pos != 1) return false;
        new_node->next = new_node;
        *head = new_node;
        return true;
    }

    if (pos == 1) {
        Node *last = *head;
        while (last->next != *head)
            last = last->next;
        last->next = new_node;
        new_node->next = *head;
        *head = new_node;
        return true;
    }

    Node *trace = *head;
    int i = 1;
    while (i < pos - 1 && trace->next != *head) {
        trace = trace->next;
        i++;
    }

    if (i != pos - 1) return false;

    new_node->next = trace->next;
    trace->next = new_node;
    return true;
}

bool crilist_delete_node(int pos, Node **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return false;
    }

    Node *trace = *head, *temp;
    int i = 1;

    // Case 1: Delete head node
    if (pos == 1) {
        // Only one node in the list
        if (trace->next == *head) {
            free(*head);
            *head = NULL;
            return true;
        }

        // More than one node
        while (trace->next != *head)
            trace = trace->next;

        temp = *head;
        *head = (*head)->next;
        trace->next = *head;
        free(temp);
        return true;
    }

    // Case 2: Delete non-head node
    trace = *head;
    for (i = 1; i < pos - 1 && trace->next != *head; i++) {
        trace = trace->next;
    }

    // If position is invalid
    if (trace->next == *head || i != pos - 1) {
        printf("Invalid position\n");
        return false;
    }

    temp = trace->next;
    trace->next = temp->next;
    free(temp);
    return true;
}


void cirlist_print_list(Node **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node *trace = *head;
    printf("List: ");
    do {
        printf("%d ", trace->data);
        trace = trace->next;
    } while (trace != *head);
    printf("\n");
}

int main() {
    Node *head = NULL;
    Node **list_head = &head;
    bool sts;

    for (int i = 1; i <= 10; i++) {
        sts = cirlist_insert_node(i, i * 10, list_head); // insert 10, 20, ..., 100
        if (sts)
            printf("Successfully inserted at pos %d\n", i);
        else
            printf("Unsuccessfully inserted at pos %d\n", i);
    }

    // Insert 888 at position 8
    cirlist_insert_node(1, 111, list_head);
    cirlist_insert_node(8, 888, list_head);
    cirlist_insert_node(13, 333, list_head);

    cirlist_print_list(list_head);
    
    crilist_delete_node(2, list_head);
    crilist_delete_node(6, list_head);
    
    cirlist_print_list(list_head);
    return 0;
}
