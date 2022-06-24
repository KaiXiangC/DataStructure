#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};

void InsertNode(struct node **head){
	int val=0;
	scanf("%d",&val);
    //create a new node
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = val;
    newNode->next = NULL;

    //if head is NULL, it is an empty list
    if(*head == NULL)
        *head = newNode;
    //Otherwise, find the last node and add the newNode
    else{
        struct node *lastNode = *head;
        //last node's next address will be NULL.
        while(lastNode->next != NULL){
            lastNode = lastNode->next;
        }
        //add the newNode at the end of the linked list
        lastNode->next = newNode;
    }
}

void PrintList(struct node *head){
    struct node *temp = head;
    //iterate the entire linked list and print the data
    if (temp== NULL){
	    printf("No data!\n");
    }
    else{
    	while(temp != NULL){
	    	printf("%d", temp->data);
		    temp = temp->next;
	    	if (temp != NULL){
		        printf("->");
	     	}
	    }
	    printf("\n");
	}
}

void DeleteNode(struct node** head_ref){
	int key=0;
	scanf("%d",&key);
	struct node *temp = *head_ref, *prev;
	
	if (temp != NULL && temp->data == key){
		*head_ref = temp->next;
		free(temp);
		return;
	}
	// Find the key to be deleted
	while (temp != NULL && temp->data != key){
		prev = temp;
		temp = temp->next;
	}
	// If the key is not present
	if (temp == NULL){
		printf("Not in the list!\n");
		return;
	}
	// Remove the node
	prev->next = temp->next;
	free(temp);
}

void Length(struct node *head){
	int count = 0;  // Initialize count
    struct node* current = head;  // Initialize current
    while (current != NULL){
        count++;
        current = current->next;
    }
    printf("length=%d\n",count);
}

void ReverseList(struct node** head_ref){
    struct node* prev = NULL;
    struct node* current = *head_ref;
    struct node* next = NULL;
    while (current != NULL){
        // Store next
        next = current->next;
        // Reverse current node's pointer
        current->next = prev;
        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

void DeleteList(struct node** head_ref){
   /* deref head_ref to get the real head */
   struct node* current = *head_ref;
   struct node* next;
   while (current != NULL){
       next = current->next;
       free(current);
       current = next;
   }
   /* deref head_ref to affect the real head back in the caller. */
   *head_ref = NULL;
}

int main(){
	struct node *head = NULL;
	int choice=0;
	do{
	scanf("%d",&choice);
		switch(choice){
			case 1:
				InsertNode(&head);
				break;
			case 2:
				DeleteNode(&head);
				break;
			case 3:
				PrintList(head);
				break;
			case 4:
				Length(head);
				break;
			case 5:
				ReverseList(&head);
				break;
			case 6:	
				DeleteList(&head);
				break;
		}
	}while(choice!=7);
	printf("leave\n");
}

