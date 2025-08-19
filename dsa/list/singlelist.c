// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *next;
}Node;

Node* create_node(int value)
{ 
    Node *new_node;
    new_node=(Node *)malloc(sizeof(Node));
    new_node->data=value;
    new_node->next=NULL;
    
    return new_node;
}

bool singlelist_insert(int pos, int value,Node **head)
{
    int i=0;
    Node *new_node, *trace;
    
    new_node=create_node(value);
    if(*head==NULL)
    {
        *head=new_node;
        return true;
    }
        
    if(pos == 1)
    {
        new_node->next=*head;
        *head=new_node;
        return true;
    }
    
    trace=*head;
    for(i=1;(trace->next!=NULL && (i<pos-1));i++)
       trace=trace->next;
    
    new_node->next=trace->next;
    trace->next=new_node;
    
    return true;
}

bool singlelist_delete(int pos, Node **head)
{
    Node *trace, *temp;
    
    if(*head==NULL)
    {
        printf("lkist is empty\n");
        return false;
    }
    
    trace=*head;
    if(pos==1)
    {
        *head=(*head)->next;
        free(trace);
        return true;
    }
    
    for(int i=1; (trace->next!=NULL && (i < (pos -1))); i++)
       trace=trace->next;
    
    temp=trace;
    trace=trace->next;
    temp->next=trace->next;
    free(trace);
    
    return true;
}

void singlelist_display(Node **head)
{
    Node *trace;
    if(*head==NULL)
    {
        printf("Lis is empty");
        return;
    }
    printf("\nThe List \n");
    trace=*head;
    while(trace->next != NULL)
    {
        printf("%d\t", trace->data);
        trace=trace->next;
    }
}   


int main() {
    int i;
    Node *head = NULL;
    Node **listhead = &head;
    
    for(i=0;i<10;i++)
      singlelist_insert(i,(i*10),listhead);
    
    singlelist_display(listhead);

    singlelist_delete(1,listhead);
    singlelist_delete(5,listhead);
    
    singlelist_display(listhead);
    return 0;
}
