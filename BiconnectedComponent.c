#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
#define MIN2(x,y) ((x)<(y)?(x):(y))
typedef struct{
	int from;
	int end;
}element;
element stack[MAX_VERTICES];

struct node{
	int vertex;
	struct node* link;
};
typedef struct node* nodePointer;
nodePointer graph[MAX_VERTICES];

int visited[MAX_VERTICES], dfn[MAX_VERTICES], low[MAX_VERTICES];
int n=0, num=0, top=-1;

void inputGraph(){
	int i=0,j=0,m=0;
	scanf("%d",&n);
	int admatrix[n][n];
	nodePointer ptr, tail;
  
	for (i = 0; i < n; i++){
		graph[i] = (nodePointer)malloc(sizeof(nodePointer)); 
    	graph[i]->vertex = i;
    	graph[i]->link = NULL;
    	visited[i] = 0;
	}
  	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			scanf("%d",&m);
			admatrix[i][j]=m;
		}
	}

	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
  			if (admatrix[i][j] != 0){
		        ptr = (nodePointer)malloc(sizeof(nodePointer));
		        ptr->vertex = j;
		        ptr->link = NULL;
		        tail = graph[i];                  
		        while (tail->link != NULL){
		        	tail = tail->link;
				} 
		        tail->link = ptr;     
	      	}   
		}
	}
}

void printGraph(){
	int i=0;
	nodePointer tmp;
	printf("Adjacency List:\n");
    for (i = 0; i < n; i++){
		printf("%d : ", graph[i]->vertex);
		tmp = graph[i]->link;
		while (tmp != NULL){
			if(tmp->link!=NULL)       
				printf("%d->", tmp->vertex);
			else
				printf("%d", tmp->vertex);
	    	tmp = tmp->link;                  
	    }
		printf("\n");
	}   
}

void init(void){
	int i;
	for(i=0;i<n;i++){
		visited[i] = 0;
		dfn[i]=low[i]=-1;
	}
	num=0;
}

void push(int x, int y){
	++top;
	stack[top].from=x;
	stack[top].end=y;
}

void pop(int *x,int *y){
	*x= stack[top].from;
	*y= stack[top].end;
	top--;
}

void bicon(int u, int v){
	nodePointer ptr;
  	int w,x,y;
	dfn[u]=low[u]=num++;
	for(ptr=graph[u];ptr;ptr=ptr->link){
		w=ptr->vertex;
		if(v!=w && dfn[w]<dfn[u])
			push(u,w);
			if(dfn[w]<0){
				bicon(w,u);
				low[u]=MIN2(low[u],low[w]);
				if(low[w]>=dfn[u]){
					printf("New biconnected component:");
					do{
						pop(&x,&y);
						if(x<=y)
							printf("<%d,%d>",x,y);
						else
							printf("<%d,%d>",y,x);
					}while(!((x==u) && (y==w)));
					printf("\n");
				}
			}
			else if (w!=v) low[u]=MIN2(low[u],dfn[w]);	
	}
}

void apUtil(int node,int isVisited[],int des[],int parent[],int low[],int ap[]){
    nodePointer temp=NULL;
    static int time=0;
    int children=0;
    temp = graph[node];
    isVisited[node]=1;
    time++;

    des[node]=low[node]=time;

    while(temp!=NULL){       
		if(!isVisited[temp->vertex]){
        	children++;
        	parent[temp->vertex]=node;
        	apUtil(temp->vertex,isVisited,des,parent,low,ap);

      		low[node]= MIN2(low[node],low[temp->vertex]);

          	if(parent[node]==-1 && children>1)
            	ap[node]=1;

      		if(parent[node]!=-1 && des[node]<=low[temp->vertex])
            	ap[node]=1;           
        }    
        else if(temp->vertex!=parent[node]){
            low[node]=MIN2(low[node],des[temp->vertex]);
        }
    	temp= temp->link;
    }
    //printf("%d",node);
}

void AP(){
    int i;
    int des[MAX_VERTICES],isVisited[MAX_VERTICES],parent[MAX_VERTICES],low[MAX_VERTICES],ap[MAX_VERTICES];

    for(i=0;i<n;i++){
        isVisited[i]=0;
        parent[i]=-1;
        ap[i]=0;
    }
    for(i=0;i<n;i++){
        if(isVisited[i]==0){
            apUtil(i,isVisited,des,parent,low,ap);
        }
    }
    int flag=0;
    for(i=0;i<n;i++){
        if(ap[i]==1){
		  	flag=1;
		  	printf("%d is an articulation point\n",i);
		}
    }
    if(flag==0)
		printf("no articulation point in this graph\n");
}

int main(){
	int choice=0;
	do{
	scanf("%d",&choice);
		switch(choice){
			case 1://input
				inputGraph();
				break;
			case 2://print
				if(n==0)
					printf("please enter a graph\n");
				else	 
					printGraph();
				break;
			case 3://AP
				if(n==0)
					printf("please enter a graph\n");
				else	 
					AP();
				break;
			case 4://BCC
				if(n==0)
					printf("please enter a graph\n");
				else{
					init();
					bicon(0, -1);
				}	 
				break;
		}
	}while(choice!=5);
	printf("leave\n");
}
