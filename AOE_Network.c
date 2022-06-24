#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define  MAX_VERTEX_NUM 100
//邊的最早開始,邊的最晚開始
int ve[MAX_VERTEX_NUM],vl[MAX_VERTEX_NUM];
typedef struct ArcNode{
    int adjvex,dut;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode{
    int data;
    ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;

typedef struct {
    int start,dut,end;
}Map;
Map arr[MAX_VERTEX_NUM];
int LocateVex(ALGraph G,int u){
    for (int i=0; i<G.vexnum; i++) {
        if (G.vertices[i].data==u) {
            return i;
        }
    }
    return -1;
}

void CreateAOE(ALGraph **G){
    *G=(ALGraph*)malloc(sizeof(ALGraph));
   	
    scanf("%d",&((*G)->arcnum));
    ((*G)->vexnum)=0; 
	int initial,end,dut;
	
    for (int i=0; i<(*G)->arcnum; i++) {
        scanf("%d-%d-%d",&initial,&dut,&end);
		arr[i].start=initial;
		arr[i].dut=dut;
		arr[i].end=end;
		if(end>((*G)->vexnum))
			((*G)->vexnum)=end;
    }
    ((*G)->vexnum)++;
    
    for (int i=0; i<(*G)->vexnum; i++) {
        (*G)->vertices[i].data=i;
        (*G)->vertices[i].firstarc=NULL;
    }
    
    for (int i=0; i<(*G)->arcnum; i++) {
       
        ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=LocateVex(*(*G), arr[i].end);
        p->nextarc=NULL;
        p->dut=arr[i].dut;
       
        int locate=LocateVex(*(*G), arr[i].start);
        p->nextarc=(*G)->vertices[locate].firstarc;
        (*G)->vertices[locate].firstarc=p;
    }
}

typedef struct stack{
    int data;
    struct stack * next;
}stack;

stack *T;

void initStack(stack* *S){
    (*S)=(stack*)malloc(sizeof(stack));
    (*S)->next=NULL;
}

bool StackEmpty(stack S){
    if (S.next==NULL) {
        return true;
    }
    return false;
}

void push(stack *S,int u){
    stack *p=(stack*)malloc(sizeof(stack));
    p->data=u;
    p->next=NULL;
    p->next=S->next;
    S->next=p;
}

void pop(stack *S,int *i){
    stack *p=S->next;
    *i=p->data;
    S->next=S->next->next;
    free(p);
}

void FindInDegree(ALGraph G,int indegree[]){
    
    for (int i=0; i<G.vexnum; i++) {
        indegree[i]=0;
    }

    for (int i=0; i<G.vexnum; i++) {
        ArcNode *p=G.vertices[i].firstarc;
        while (p) {
            indegree[p->adjvex]++;
            p=p->nextarc;
        }
    }
}

bool TopologicalOrder(ALGraph G){
    int indegree[G.vexnum];
    FindInDegree(G,indegree);
    
    stack *S;
    
    initStack(&S);
    for (int i=0; i<G.vexnum; i++) {
        ve[i]=0;
    }
   
    for (int i=0; i<G.vexnum; i++) {
        if (!indegree[i]) {
            push(S, i);
        }
    }
    int count=0;
    
    while (!StackEmpty(*S)) {
        int index;
        
        pop(S,&index);
       
        push(T, index);
        ++count;
       
        for (ArcNode *p=G.vertices[index].firstarc; p ; p=p->nextarc) {
           
            int k=p->adjvex;
           
            if (!(--indegree[k])) {
                
                push(S, k);
            }
            
            if (ve[index]+p->dut>ve[k]) {
                ve[k]=ve[index]+p->dut;
            }
        }
    }
    
    if (count<G.vexnum) {
        printf("\n Network has a cycle. Sort terminated. \n");
        return false;
    }
    return true;
}

void CriticalPath(ALGraph G){
    if (!TopologicalOrder(G)) {
        return ;
    }
    for (int i=0 ; i<G.vexnum ; i++) {
        vl[i]=ve[G.vexnum-1];
    }
    int i,j,k;
    while (!StackEmpty(*T)) {
        pop(T, &j);
        for (ArcNode* p=G.vertices[j].firstarc ; p ; p=p->nextarc) {
            k=p->adjvex;
            
            if (vl[k]-p->dut<vl[j]) {
                vl[j] = vl[k]-p->dut;
            }
        }
    }
    for(i=0; i<G.arcnum;i++){
    	for (j = 0; j < G.vexnum; j++) {
	        for (ArcNode*p = G.vertices[j].firstarc; p ;p = p->nextarc) {
	            k = p->adjvex;
	            int ee = ve[j], el = vl[k]-p->dut;
	            if(j==arr[i].start && k==arr[i].end){
	            	if(ee==el)
		            	printf("%d-%d/%d/%d/yes\n",j,k,ee,el);
		            else
		            	printf("%d-%d/%d/%d/no\n",j,k,ee,el);
				}
	        }
	    }
	}
    
}
int main(){
    ALGraph *G;
    CreateAOE(&G);
    initStack(&T);
    TopologicalOrder(*G);
    CriticalPath(*G);
    return  0;
}
