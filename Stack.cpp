#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Stack
typedef struct{
	int raw;
	int column;
	char value[5];
}item;

item *stack;
int top=-1,n=0;
void print();
void InputSize();
void Pop();
void PopNData();
void IsFull();
int main(){
	scanf("%d",&n);
	stack = (item*)malloc(n*sizeof(item));
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
	printf("stack size %d\n",sizeof(stack)*n/sizeof(stack));
}

void InputSize(){
	int r=0,c=0;
	char v[5];
	if(top>=n-1){
		printf("Stack is full!\n");
		int ns=0;
		while(scanf("%d",&ns)){
			if(ns%2==0)
				break;
			printf("Please enter a multiple of 2!\n");
		}
		n+=ns;
		stack = (item*)realloc(stack,n*sizeof(item));
	}else{
		scanf("%d %d %s",&r,&c,v);
		top++;
		stack[top].raw=r;
		stack[top].column=c;
		strcpy(stack[top].value,v);
	}
}

void Pop(){
	if(top==-1){
		printf("No item,stack is empty!\n");
	}else{
		printf("Item %d %d %s poped\n",stack[top].raw,stack[top].column,stack[top].value);
		top--; 
	}
}

void PopNData(){
	int nd=0;
	scanf("%d",&nd);
	top-=nd;
}

void IsFull(){
	if(top==n-1)
		printf("Full!\n");
	else
		printf("Not full!\n");
}
