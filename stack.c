#include<stdio.h>
#include<stdlib.h>

struct Node{
   int data;
   struct Node *next;
};


void push(struct Node**top,int value){
   struct Node*newNode=(struct Node*)malloc(sizeof(struct Node));
   if(!newNode){
      printf("stack overflow\n");
      return;
   }
   newNode->data=value;
   newNode->next=*top;
   *top=newNode;
   printf("%d pushed onto the stack\n",value);
}


void pop(struct Node**top){
   if(*top==NULL){
      printf("stack underflow\n");
      return;
   }
   struct Node*temp=*top;
   *top=(*top)->next;
   printf("%d popped from the stack\n",temp->data);
   free(temp);
}



void display(struct Node*top){
   if(top==NULL){
       printf("Stack is empty\n");
       return;
   }
   printf("stack elements:\n");
   struct Node*temp=top;
   while(temp!=NULL){
      printf("%d->",temp->data);
      temp=temp->next;
   }
   printf("NULL\n");
}



void search(struct Node *top,int value){
   struct Node *temp=top;
   int position=1;
   while(temp!=NULL){
      if(temp->data==value){
         printf("%d found at position %d\n",value,position);
         return;
      }
      temp=temp->next;
      position++;
   }
   printf("%d not found in the stack\n",value);
}

int main(){
   struct Node*stack=NULL;
   int choice,value;

   while(1){
      printf("\nChoose an operation:\n");
      printf("1.Push\n");
      printf("2.Pop\n");
      printf("3.Display\n");
      printf("4.Search\n");
      printf("5.Exit\n");
      printf("Enter your choice:");
      scanf("%d",&choice);

      switch (choice){
         case 1:
            printf("Enter value to push:");
            scanf("%d",&value);
            push(&stack,value);
            break;
         case 2:
            pop(&stack);
            break;
         case 3:
            display(stack);
            break;
         case 4:
            printf("Enter value to search:");
            scanf("%d",&value);
            search(stack,value);
            break;
         case 5:
            printf("Exiting program.\n");
            exit(0);
         default:
            printf("Invalid choice.Please try again.\n");
     }
   }
   return 0;
}

