#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_ELEMENTS 100
typedef struct
{
	int key;
	char what[20];
 	char who[20];
	char when[20];
 	char where[20];
	
}element;
int n=0,size=0;
element heap[MAX_ELEMENTS];

int parent(int i){
    return i / 2;
}

int leftChild(int i){
    return 2 * i;
}

int rightChild(int i){
    return ((2 * i) + 1);
}

void swape( element *a, element *b ) {
  element t = *a;
  *a= *b;
  *b = t;
}

element inputElement() {
  element temp;
  int x=0;
  char a[20],b[20],c[20],d[20];
  scanf("%d %s %s %s %s",&x,a,b,c,d);
  temp.key=x;
  strcpy(temp.what,a);
  strcpy(temp.who,b);
  strcpy(temp.when,c);
  strcpy(temp.where,d);
  return temp;
}

void createHeap() {
  	scanf("%d",&size);
}

element popLowest(int*n){
	if(size==0)
		printf("please createHeap!\n");
	else{
		if(*n==0){
			printf("the heap is empty.\n");
		}	
		else{
			element item, temp, x;
    		int now, change;
    		item=heap[1];
		    heap[1] = heap[(*n)--];
		    now = 1;
		    while(now * 2 <= *n){
		        int fb = 1;
		        if(heap[2*now].key < heap[now].key) fb = 0;
		        else if((2 * now + 1)<= *n && heap[2* now + 1].key < heap[now].key) fb = 0;
		        if(fb) break;
		        change = 2* now;
		        if((2 * now + 1) <= *n && heap[2 * now + 1].key < heap[2 * now].key) change = 2 * now + 1;
		        x = heap[change]; heap[change] = heap[now]; heap[now] = x;
		        now = change;
		    }
			printf("%d %s %s %s %s\n",item.key,item.what,item.who,item.when,item.where);
		   	return item;
		}
	}
}

void pushElement(element item, int *n){
	if(size==0)
		printf("please createHeap!\n");
	else{
		if(*n==size){
			printf("The heap is full.\n");
		}
		else{
			scanf("%d %s %s %s %s",&item.key,item.what ,item.who,item.when,item.where);
	    	int i = ++(*n);
			while(i!=1 && (item.key < heap[parent(i)].key)){
				heap[i]=heap[parent(i)];
	       		i=parent(i);
			}
			heap[i]=item;
		}
	}
}

void shiftUp(int i){
	if (i && heap[parent(i)].key > heap[i].key){
        swape(&heap[i], &heap[parent(i)]);
        shiftUp(parent(i));
    }
}

void shiftDown(int i){
	if (i<n && heap[leftChild(i)].key < heap[i].key && heap[leftChild(i)].key!=0){
        swape(&heap[i], &heap[leftChild(i)]);
        shiftDown(leftChild(i));
    }
    if (i<n && heap[rightChild(i)].key < heap[i].key && heap[rightChild(i)].key!=0){
        swape(&heap[i], &heap[rightChild(i)]);
        shiftDown(rightChild(i));
    }
}

void changePriority(int old_key, int new_key){

		int idx = 0,i = 1;
	    for (i=1 ; i <= size; i++) {
	        if (heap[i].key == old_key) {
	            idx = i;
	            heap[i].key = new_key;
	            break; 
	        }
	    }
		if(idx!=0){
		    if (new_key > old_key) {
				shiftDown(idx);
		    }
		    else {
		        shiftUp(idx);
		    }	    
		    printf("change priority successfully!\n");
		} 
		else{
			printf("the key do not exist in the heap!\n");
		}
}

void printHeap(){
	if(size==0)
		printf("please createHeap!\n");
	if(size!=0 && n==0)
		printf("the heap is empty.\n");
	else{
		while(n!=0){
			popLowest(&n);	
		}
	}	
}

int main(){
	element item;
	int choice=0,oldk=0,newk=0;
	do{
	scanf("%d",&choice);
		switch(choice){
			case 1://elementinputElement()
				inputElement();
				break;
			case 2://createHeap()
				createHeap();
				break;
			case 3://elementpopLowest(int*n)
				popLowest(&n);
				break;
			case 4://voidpushElement(elementitem, int *n)
				pushElement(item, &n);
				break;
			case 5://voidchangePriority(intold_key, intnew_key)
				if(size==0){
					printf("please createHeap!\n");
				}
				else{
					scanf("%d %d",&oldk,&newk);
					changePriority(oldk, newk);
				}
				break;
			case 6://voidprintHeap()
				printHeap();
				break;
		}
	}while(choice!=7);
	printf("leave\n");
}
