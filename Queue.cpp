#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
//Queue

typedef struct{
	int raw;
	int column;
	char value[5];
}item;

item *queue;
int rear=-1,front=-1,n=0;
bool flag=0;
void print();
void InputSize();
void Pop();
void PopNData();
void IsFull();
int main(){
	scanf("%d",&n);
	queue = (item*)malloc(n*sizeof(item));
	int option=0;
	do{
		scanf("%d",&option);
		switch(option){
			case 1://PrintSize
				print();
				break;
			case 2://InputSize
				InputSize();
				break;
			case 3://Pop
				Pop();
				break;
			case 4://PopNData
				PopNData();
				break;
			case 5://IsFull
				IsFull();
				break;
		}
	}while(option!=6);
	printf("leave\n");
}

void print(){
	printf("queue size %d\n",sizeof(queue)*n/sizeof(queue));
}

void InputSize(){
	int r=0,c=0;
	char v[5];
	if(rear%n == front && flag == 1 || rear == n-1 && front == -1){
		printf("Queue is full!\n");
		int ns=0;
		while(scanf("%d",&ns)){
			if(ns%2==0)
				break;
			printf("Please enter a multiple of 2!\n");
		}
		n+=ns;
		queue = (item*)realloc(queue,n*sizeof(item));
	}else{
		scanf("%d %d %s",&r,&c,v);
		rear=(rear+1)%n;
		queue[rear].raw=r;
		queue[rear].column=c;
		strcpy(queue[rear].value,v);
		if (front == rear) flag = 1;
	}
}

void Pop(){
	if(front == rear && flag == 0){
		printf("No item, queue is empty!\n");
	}else{
	    front=(front+1)%n;
		printf("Item %d %d %s poped\n",queue[front].raw,queue[front].column,queue[front].value);
		if (front == rear) flag = 0;
	}
}

void PopNData(){
	if(front == rear && flag == 0){
		printf("No item, queue is empty!\n");
	}else{
	    int nd=0;
		scanf("%d",&nd);
		front=(front+nd)%n;
		if (front == rear) flag = 0;
	}
}

void IsFull(){
	if(rear%n == front && flag == 1 || rear == n-1 && front == -1)
		printf("Full!\n");
	else
		printf("Not full!\n");
}
