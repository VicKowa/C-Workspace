#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node *next;
    
} node;

node * init() {
    node *first = (node *) malloc(sizeof(node));
    return first;
};

void add(node *e, int i) {
    //erzeuge neues node Element
    node *temp = e;
    node *toAdd = init();
    toAdd->data = i;
    toAdd->next = NULL;


    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = toAdd;
};

void delete(node *e, int position) {
    node *temp = e;
    node *todelete;
    if(position == 0) {
        printf("linked list is empty \n");
    } else if(position == 0) {
        e = temp->next;
        free(temp);
        temp = NULL;
    } else {
        for (int i = 0; i < position; i++) {
        temp = temp->next;
        }
        todelete = temp->next;
        temp->next = todelete->next;
        free(todelete);
        todelete = NULL;
    }
};

int get(node *e, int position) {
    node *temp = e;
    int value = 0;

    if (temp == NULL) {
        printf("linked list is empty \n");
        return 0;
    } else {
        
        for (int i = 0; i <= position; i++)
        {
            temp = temp->next;
        }
        value = temp->data;
    }
    return value;
};

int main() {
    node *head;
    head = init();
    add(head, 69);
    add(head, 420);
    add(head, 22);
    delete(head, 1);
    printf("%d", get(head, 1));

    return 0;
};