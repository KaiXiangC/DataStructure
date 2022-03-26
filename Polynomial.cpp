#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#define MAX 500

char polya[MAX];

typedef struct{
	float coefficient[100];
	int order[100];
}pol;

void separate(int n,char poly_temp[]);
void readPoly();
void print();   
void eval();
void mul();                                             
void add();    
void order_answer();
void print_answer();

pol poly[50],answer[1],aa[1],bb[1];
int main(){
	int option;
	do{
		scanf("%d",&option);
		switch(option){
			case 1://read
				readPoly();
				break;
			case 2://print
				print();
				break;
			case 3://add
				add();
				order_answer();
				print_answer();
				break;
			case 4://mul					
				mul();
				order_answer();
				print_answer();
			    break;
			case 5://eval
				eval();
			    break;
		}
	}while(option!=6);
	printf("leave menu\n");
}

void eval(){
	float nums=0,sum=0,s=0;
	char cho[1]; 
	scanf("%f %s",&nums,cho);
	int asc=cho[0]-64;

	for(int i=0;i<MAX;i++){
		s=1;
		if(poly[asc].coefficient[i]!=0 && poly[asc].order[i]!=0){
			for(int j=0;j<poly[asc].order[i];j++){
				s*=nums;
			}
			sum=sum+poly[asc].coefficient[i]*s;
		}
		if(poly[asc].order[i]==0){
			sum=sum+poly[asc].coefficient[i];
		}
	}
	printf("%.1f\n",sum);
}

void readPoly(){
	int field_count=0,ri=0;
	char *token;
	char ei[50];				
	
	while(ri==0){
		scanf("%s",ei);
		if(strlen(ei)<=2 || ('+'==ei[1]) || ('-'==ei[1]) || (('='==ei[1]) && (('-'==ei[2])||('+'==ei[2])||('='==ei[2])))|| ('-'==ei[strlen(ei)-1])|| ('+'==ei[strlen(ei)-1])){
			printf("erro\n");
			ri=0;
		}
		else{
			strcat(ei, ".");
			int asc=ei[0]-64;
			strcpy(polya,ei);
			token= strtok(polya, "=");
		   	while( token != NULL ){
				if(field_count==1){
				   	separate(asc,token);
				}
		      	token = strtok(NULL, "=");
		      	field_count++;
		   	}
			ri=1;
		}
	}
}

void print(){
	char num[10];
	scanf("%s",num);
	int asc=num[0]-64;


		for(int i=0;i<MAX;i++){//不理係數為0的項
			if(poly[asc].order[i]==1){//一次方
				if(poly[asc].coefficient[i]==1){
					if(i==0)//第1項
					printf("x");
					else    //不是第1項,x前面要加+號
					printf("+x");
				}
				else if(poly[asc].coefficient[i]==-1){
					printf("-x");
				}
				else if(poly[asc].coefficient[i]!=0){
					if(i==0 || poly[asc].coefficient[i]<0)
					printf("%.1fx",poly[asc].coefficient[i]);
					else      //不是第1項,x前面要加+號
					printf("+%.1fx",poly[asc].coefficient[i]);
				}
			}
			else if(poly[asc].order[i]==0){//零次方(常數項)
				if(poly[asc].coefficient[i]==1){
					if(i==0)
					printf("1");
					else
					printf("+1");
				}
				else if(poly[asc].coefficient[i]==-1){
					printf("-1");
				}
				else if(poly[asc].coefficient[i]!=0){
					if(i==0 || poly[asc].coefficient[i]<0)
					printf("%.1f",poly[asc].coefficient[i]);
					else
					printf("+%.1f",poly[asc].coefficient[i]);
				}
			}	
			else{//(x大於一次方)或(x為等於小於-1次方)
				if(poly[asc].coefficient[i]==1){
					if(i==0)
					printf("x^%d",poly[asc].order[i]);
					else
					printf("+x^%d",poly[asc].order[i]);
				}
				else if(poly[asc].coefficient[i]==-1){
					printf("-x^%d",poly[asc].order[i]);
				}
				else if(poly[asc].coefficient[i]!=0){
					if(i==0 || poly[asc].coefficient[i]<0)
					printf("%.1fx^%d",poly[asc].coefficient[i],poly[asc].order[i]);
					else     //不是第1項,x前面加+號
					printf("+%.1fx^%d",poly[asc].coefficient[i],poly[asc].order[i]);
				}
			}
		}
		printf("\n");
}
void separate(int n,char poly_temp[])
{
	char term[MAX],temp[MAX];
	int i,j=0,k=0,c=0,e=0,exist_x=0;

	for(i=1;i<=(strlen(poly_temp)-1);i++){
		if((poly_temp[i]=='+')||(poly_temp[i]=='-')||(i==strlen(poly_temp)-1)){
			strncpy(term,&poly_temp[j],i-j);
			term[i-j]='\0';
            exist_x=0; 
			for(k=0;k<=(i-j-1);k++){
				if(term[k]=='x'){//非常數項
					exist_x=1;
					if((term[k-1]=='+')||(k==0)){//x前一個字元是+,則係數為1
						poly[n].coefficient[c]=1;
						c++;
					}
				
				    if(term[k-1]=='-'){//x前一個字元是-,則係數為-1
						poly[n].coefficient[c]=-1;
						c++;
					}
					
				    if(term[k+1]=='^'){//x^後面的數字表次方
						strncpy(temp,&term[k+2],strlen(term)-k-2); //x^後面的數字複製到temp(字串)
						temp[strlen(term)-k-2]='\0';
						poly[n].order[e]=atoi(temp); //char型態轉成int型態
						e++;					
					}
					if(term[k+1]!='^'){//x後面一個字元不是^,次方為1
						poly[n].order[e]=1;
                   		e++;
                   	}
				    if((term[k-1]!='+')&&(k!=0)&&(term[k-1]!='-')){//i=='\0'
						strncpy(temp,term,k);
						temp[k]='\0';
						poly[n].coefficient[c]=atof(temp);
						c++;					
					}
				}
			}
			if(exist_x==0){
				poly[n].order[e]=0;
				e++;
				strncpy(temp,term,strlen(term));
				temp[k]='\0';
				poly[n].coefficient[c]=atof(temp);
				c++;				
			}			
			j=i;
		}
	}
}

void mul(){
	char fn[10],f2[10];
	scanf("%s",&f2);
	scanf("%s",&fn);
	int m1_asc=f2[0]-64;
	int m2_asc=fn[0]-64;
	
	int i,j,k=0;
	for(int p=0;p<=MAX;p++){
		answer[0].coefficient[p]=0;
		answer[0].order[p]=0;
	}
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++){
			if(poly[m1_asc].coefficient[i]!=0&&poly[m2_asc].coefficient[j]!=0){
				answer[0].coefficient[k]=poly[m1_asc].coefficient[i]*poly[m2_asc].coefficient[j];
				answer[0].order[k]=poly[m1_asc].order[i]+poly[m2_asc].order[j];
				k++;
			}
		}
	}
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++){
			if(answer[0].order[i]==answer[0].order[j]&&i!=j){
				answer[0].coefficient[i]=answer[0].coefficient[i]+answer[0].coefficient[j];
				answer[0].coefficient[j]=0;
				answer[0].order[j]=0;
			}
		}
	}
}
void add(){
	char ff[10],f1[10];
	
	scanf("%s",&f1);
	scanf("%s",&ff);
	int m1_asc=f1[0]-64;
	int m2_asc=ff[0]-64;

	int i,j,k=0;
	for(int p=0;p<=MAX;p++){
		answer[0].coefficient[p]=0;
		answer[0].order[p]=0;
		aa[0].coefficient[p]=poly[m1_asc].coefficient[p];
		aa[0].order[p]=poly[m1_asc].order[p];
		bb[0].coefficient[p]=poly[m2_asc].coefficient[p];
		bb[0].order[p]=poly[m2_asc].order[p];
	}
	for(i=0;i<MAX;i++){
			for(j=0;j<MAX;j++){   
				if(bb[0].order[i]==aa[0].order[j]&&bb[0].coefficient[i]!=0&&aa[0].coefficient[j]!=0){
					answer[0].coefficient[k]=bb[0].coefficient[i]+aa[0].coefficient[j];
					answer[0].order[k]=bb[0].order[i];
					bb[0].coefficient[i]=0;
					aa[0].coefficient[j]=0;
					k++;
				}
			}
		}
		for(i=0;i<MAX;i++){
			if(bb[0].coefficient[i]!=0){
				answer[0].coefficient[k]=bb[0].coefficient[i];
				answer[0].order[k]=bb[0].order[i];
				k++;
			}
			if(aa[0].coefficient[i]!=0){
				answer[0].coefficient[k]=aa[0].coefficient[i];
				answer[0].order[k]=aa[0].order[i];
				k++;
			}	
		}
}
void order_answer(){
	int i,j,largest_index;
	pol temp[0];

	for(i=0;i<MAX;i++){
		largest_index=i;//假設最大的值在最前面
		for(j=i;j<MAX;j++){//如果有找到更大的就被取代
			if(answer[0].order[j]>answer[0].order[largest_index]){		
				largest_index=j;
			}				
		}			
		temp[0].coefficient[0]=answer[0].coefficient[i];
		temp[0].order[0]=answer[0].order[i];
			
		answer[0].coefficient[i]=answer[0].coefficient[largest_index];
		answer[0].order[i]=answer[0].order[largest_index];
			
		answer[0].coefficient[largest_index]=temp[0].coefficient[0];
		answer[0].order[largest_index]=temp[0].order[0];
	}		
}

void print_answer(){
	int i;
	for(i=0;i<MAX;i++){//不理係數為0的項
		if(answer[0].order[i]==1){//一次方
			if(answer[0].coefficient[i]==1){
				if(i==0)//第1項
				printf("x");
				else    //不是第1項,x前面要加+號
				printf("+x");
			}
			else if(answer[0].coefficient[i]==-1){
				printf("-x");
			}
			else if(answer[0].coefficient[i]!=0){
				if(i==0 || answer[0].coefficient[i]<0) 
				printf("%.1fx",answer[0].coefficient[i]);
				else      //不是第1項,x前面要加+號
				printf("+%.1fx",answer[0].coefficient[i]);
			}
		}
		else if(answer[0].order[i]==0){//零次方(常數項)
			if(answer[0].coefficient[i]==1){
				if(i==0)
				printf("1");
				else
				printf("+1");
			}
			else if(answer[0].coefficient[i]==-1){
				printf("-1");
			}
			else if(answer[0].coefficient[i]!=0){
				if(i==0 || answer[0].coefficient[i]<0)
				printf("%.1f",answer[0].coefficient[i]);
				else
				printf("+%.1f",answer[0].coefficient[i]);
			}
		}	
		else{//(x大於一次方)或(x為等於小於-1次方)
			if(answer[0].coefficient[i]==1){
				if(i==0)
				printf("x^%d",answer[0].order[i]);
				else
				printf("+x^%d",answer[0].order[i]);
			}
			else if(answer[0].coefficient[i]==-1){
				printf("-x^%d",answer[0].order[i]);
			}
			else if(answer[0].coefficient[i]!=0){
				if(i==0 || answer[0].coefficient[i]<0)
				printf("%.1fx^%d",answer[0].coefficient[i],answer[0].order[i]);
				else     //不是第1項,x前面加+號
				printf("+%.1fx^%d",answer[0].coefficient[i],answer[0].order[i]);
			}
		}
	}
	printf("\n");
}
