#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int row[500];
    int col[500];
    int val[500];
}entry;
entry a[100],addm[1],mulm[1],tranm[1],trant[1];
void read();
void print();
void add();
void transpose();
void multiply();

int main(){
	
	int option=0;
	do{
		scanf("%d",&option);
		switch(option){
			case 1://read
				read();
				break;
			case 2://print
				print();
				break;
			case 3://add
				add();
				break;
			case 4://Transpose
				transpose();
				break;
			case 5://Multiply
				multiply();
				break;
		}
	}while(option!=6);
	printf("leave\n");
}

void read(){
	char alph[10];
	int from=0,to=0,r=0,c=0,k=1,value=0,i=0,j=0,asc=0;
	float Sparse=0;
	scanf("%s",alph);
	scanf("%d %d",&r,&c);
	scanf("%d %d",&from,&to);
	asc=alph[0]-64;
	a[asc].row[0]=r;
	a[asc].col[0]=c;
	Sparse=(r*c);
//	printf("%d",asc);
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			scanf("%d",&value);
			if(value!=0){
				a[asc].row[k]=i;
				a[asc].col[k]=j;
				a[asc].val[k]=value;
				k++;
			}
		}
	}
	a[asc].val[0]=k-1;
	Sparse=100-(((k-1)/Sparse)*100);
	int sp=(int)Sparse;
	if(from<to){
		if(sp>to || sp<from){
			memset(a[asc].row,0,sizeof(a[asc].row));
			memset(a[asc].col,0,sizeof(a[asc].col));
			memset(a[asc].val,0,sizeof(a[asc].val));
			printf("out of range\n");
		}
	}
		 
	else if(from>to){
		if(sp<to || sp>from){
			memset(a[asc].row,0,sizeof(a[asc].row));
			memset(a[asc].col,0,sizeof(a[asc].col));
			memset(a[asc].val,0,sizeof(a[asc].val));
			printf("out of range\n");
		}
	}	 
}

void print(){
	char alph[1];
	int from=0,to=0,r=0,c=0,k=0,value=0,i=0,j=0;
	scanf("%s",alph);
	int asc=alph[0]-64;

	for(i=1;i<=a[asc].val[0];i++)
		printf("%c[%d] %d %d %d\n",alph[0],i-1,a[asc].row[i],a[asc].col[i],a[asc].val[i]);
}

void add(){
	int i=0,j=0,t1=0,t2=0,k=0;
	char alph1[10],alph2[10];
	scanf("%s",alph1);
	scanf("%s",alph2);
	int m1_asc=alph1[0]-64;
	int m2_asc=alph2[0]-64;
//	printf("%s\n%s",alph1,alph2);
	if(a[m1_asc].col[0]!=a[m2_asc].col[0] || a[m1_asc].row[0]!=a[m2_asc].row[0]){
		printf("AddSparseMatrixs error\n");
	}
	else{
		t1=a[m1_asc].val[0];
		t2=a[m2_asc].val[0];
		i=j=k=0;
		   
		addm[0].row[0]=a[m1_asc].row[0];
		addm[0].col[0]=a[m1_asc].col[0];
		   
		while(i<=t1&&j<=t2){
			if(a[m1_asc].row[i]<a[m2_asc].row[j]){     
				addm[0].row[k]=a[m1_asc].row[i]; 
				addm[0].col[k]=a[m1_asc].col[i];          
				addm[0].val[k]=a[m1_asc].val[i];       
				k++; i++;
			}       
			else if(a[m1_asc].row[i]>a[m2_asc].row[j]){     
				addm[0].row[k]=a[m2_asc].row[j];	           
				addm[0].col[k]=a[m2_asc].col[j];	           
				addm[0].val[k]=a[m2_asc].val[j];      
			    k++; j++;     
			}     
			else if(a[m1_asc].col[i]<a[m2_asc].col[j]){       
				addm[0].row[k]=a[m1_asc].row[i];           
				addm[0].col[k]=a[m1_asc].col[i];           
				addm[0].val[k]=a[m1_asc].val[i];           
				k++; i++;
			}    
			else if(a[m1_asc].col[i]>a[m2_asc].col[j]){       
				addm[0].row[k]=a[m2_asc].row[j];          
				addm[0].col[k]=a[m2_asc].col[j];	           
				addm[0].val[k]=a[m2_asc].val[j];  
			    k++; j++;   
			}     
			else{
			    addm[0].row[k]=a[m1_asc].row[i];     
				addm[0].col[k]=a[m1_asc].col[i];	           
				addm[0].val[k]=a[m1_asc].val[i]+a[m2_asc].val[j];               
				k++; i++; j++;     
			}
		}
		while(i<=t1){
			addm[0].row[k]=a[m1_asc].row[i];	           
			addm[0].col[k]=a[m1_asc].col[i];	           
			addm[0].val[k]=a[m1_asc].val[i];
			i++; k++;
		}
		while(j<=t2){
			addm[0].row[k]=a[m2_asc].row[j];	           
			addm[0].col[k]=a[m2_asc].col[j];	           
			addm[0].val[k]=a[m2_asc].val[j]; 
			j++; k++;
		}
		addm[0].val[0]=k-1;
		for(i=1;i<=addm[0].val[0];i++)
			printf("add[%d] %d %d %d\n",i-1,addm[0].row[i],addm[0].col[i],addm[0].val[i]);
	}
}

void transpose(){
	char alph[1];
	scanf("%s",alph);
	int asc=alph[0]-64;
    int i=0,j=0,c=0,rowTerms[500]={0},startingPos[500]={1};
    c=a[asc].val[0];
    
    if(a[asc].val[0]>0){
        for(i=0;i<=a[asc].val[0];i++)
            rowTerms[a[asc].col[i]]++;
        for(i=1;i<a[asc].col[0];i++)
            startingPos[i]=startingPos[i-1]+rowTerms[i-1];
        for(i=0;i<=a[asc].val[0];i++){
            j = startingPos[a[asc].col[i]]++;
            tranm[0].row[j]=a[asc].col[i];
    		tranm[0].col[j]=a[asc].row[i];
    		tranm[0].val[j]=a[asc].val[i];
        }
    }
    
	for(i=1;i<=c;i++)
		printf("Transpose[%d] %d %d %d\n",i-1,tranm[0].row[i],tranm[0].col[i],tranm[0].val[i]);
}

void multiply(){
	char alph1[10],alph2[10];
	scanf("%s",alph1);
	scanf("%s",alph2);
	int m1_asc=alph1[0]-64;
	int m2_asc=alph2[0]-64;
	int i=0,j=0,k=0,iA=0,iC=0,iA1=0,iB1=0,iA1row=0,iB1row=0,sum=0;
	if (a[m1_asc].col[0] != a[m2_asc].row[0]){
        printf("MatrixMultiply error\n");
    }
    else{
		int rowTerms[500]={0}, startingPos[500]={1};
	    
	    if(a[m2_asc].val[0]>0){
	        for(i=0;i<=a[m2_asc].val[0];i++)
	            rowTerms[a[m2_asc].col[i]]++;
	        for(i=1;i<a[m2_asc].col[0];i++)
	            startingPos[i]=startingPos[i-1]+rowTerms[i-1];
	        for(i=0;i<=a[m2_asc].val[0];i++){
	            j = startingPos[a[m2_asc].col[i]]++;
	            trant[0].row[j]=a[m2_asc].col[i];
	    		trant[0].col[j]=a[m2_asc].row[i];
	    		trant[0].val[j]=a[m2_asc].val[i];
	        }
	    }
			
		mulm[0].row[0]=a[m1_asc].row[0];
	    mulm[0].col[0]=a[m2_asc].col[0];
	    mulm[0].val[0]=0;
	    iA = iC = 1;
	    while (iA <= a[m1_asc].val[0]){
	        sum=0;
	        iA1=iA; iB1=1;
	        iA1row=a[m1_asc].row[iA1]; iB1row=trant[0].row[iB1];
	        while (iB1<=trant[0].val[0]){
	            if (a[m1_asc].col[iA1]==trant[0].col[iB1]){
	                sum+=a[m1_asc].val[iA1]*trant[0].val[iB1];
	                iA1++; iB1++;
	            }
	            else if (a[m1_asc].col[iA1]>trant[0].col[iB1])
	                iB1++;
	            else
	                iA1++;
	            if (a[m1_asc].row[iA1]!=iA1row)
	                while (trant[0].row[iB1]==iB1row) iB1++;
	            if (trant[0].row[iB1] != iB1row){
	                if (iB1<=trant[0].val[0])
	                    iA1=iA;
	                else
	                    while (a[m1_asc].row[iA1]==iA1row) iA1++;
	                if (sum!=0){
	                    mulm[0].val[0]++;
	                    mulm[0].row[iC]=iA1row;
	                    mulm[0].col[iC]=iB1row;
	                    mulm[0].val[iC++]=sum;
	                    sum=0;
	                }
	                iB1row=trant[0].row[iB1];
	            }
	        }
	        iA=iA1;
	    }
			
	    for(i=1;i<=mulm[0].val[0];i++)
	    	printf("Multiply[%d] %d %d %d\n",i-1,mulm[0].row[i],mulm[0].col[i],mulm[0].val[i]);
	}
}
