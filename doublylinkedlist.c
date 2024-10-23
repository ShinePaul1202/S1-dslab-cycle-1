#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node;

node *head = NULL;
int count = 0;

void display() {
    node *temp = head;
    if (temp == NULL) {
        printf("Empty linked list\n");
    } else {
        while (temp != NULL) {
            printf("%d <--> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void insert_beg() {
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL) {
        printf("\nMemory allocation failed.\n");
        return;
    }
    printf("\nEnter the data: ");
    scanf("%d", &newnode->data);
    newnode->next = head;
    newnode->prev = NULL;
    if (head != NULL) {
        head->prev = newnode;
    }
    head = newnode;
    ++count;
    printf("\nNode inserted at beginning.\n");
}

void insert_end() {
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL) {
        printf("\nMemory allocation failed.\n");
        return;
    }
    printf("\nEnter the data: ");
    scanf("%d", &newnode->data);
    newnode->next = NULL;
    if (head == NULL) {
        head = newnode;
        newnode->prev = NULL;
    } else {
        node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->prev = temp;
    }
    ++count;
    printf("\nNode inserted at end.\n");
}

void insert_pos() {
    int pos;
    printf("\nEnter the position to insert the data: ");
    if (scanf("%d", &pos) != 1) {
        printf("\nInvalid input.\n");
        return;
    }
    if (pos < 1 || pos > count + 1) {
        printf("\nInvalid position.\n");
        return;
    }

    node *newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL) {
        printf("\nMemory allocation failed.\n");
        return;
    }
    printf("\nEnter the data: ");
    if (scanf("%d", &newnode->data) != 1) {
        printf("\nInvalid input.\n");
        free(newnode);
        return;
    }

    newnode->next = NULL;
    newnode->prev = NULL;

    if (pos == 1) {
        newnode->next = head;
        if (head != NULL) {
            head->prev = newnode;
        }
        head = newnode;
    } else {
        node *temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }
        newnode->next = temp->next;
        newnode->prev = temp;
        if (temp->next != NULL) {
            temp->next->prev = newnode;
        }
        temp->next = newnode;
    }
   
    count++;
    printf("\nNode inserted at position %d.\n", pos);
}

void delete_beg() {
    if (head == NULL) {
        printf("\nEmpty linked list.\n");
        return;
    }
    node *temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    free(temp);
    --count;
    printf("\nNode deleted from beginning.\n");
}

void delete_end() {
    if (head == NULL) {
        printf("\nEmpty linked list.\n");
        return;
    }
    if (head->next == NULL) {
        delete_beg();
        return;
    }
    node *temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    --count;
    printf("\nNode deleted from end.\n");
}

void delete_pos() {
    int pos;
    printf("\nEnter the position to delete the node: ");
    scanf("%d", &pos);
    if (pos < 1 || pos > count) {
        printf("\nInvalid position.\n");
        return;
    }
    if (pos == 1) {
        delete_beg();
    } else if (pos == count) {
        delete_end();
    } else {
        node *temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }
        node *del = temp->next;
        temp->next = del->next;
        if (del->next != NULL) {
            del->next->prev = temp;
        }
        free(del);
        --count;
        printf("\nNode deleted from position %d.\n", pos);
    }
}

int main() {
    int ch;
    do {
        printf("\nLinked List Operations:\n");
        printf("1. Display\n");
        printf("2. Insert at beginning\n");
        printf("3. Insert at end\n");
        printf("4. Insert at a position\n");
        printf("5. Delete from beginning\n");
        printf("6. Delete from end\n");
        printf("7. Delete from a position\n");
        printf("8. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                display();
                break;
            case 2:
                insert_beg();
                break;
            case 3:
                insert_end();
                break;
            case 4:
                insert_pos();
                break;
            case 5:
                delete_beg();
                break;
            case 6:
                delete_end();
                break;
            case 7:
                delete_pos();
                break;
            case 8:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice.\n");
                break;
        }
    } while (ch != 8);
    return 0;
}
