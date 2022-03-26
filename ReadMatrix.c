#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct entry{
    int row;
    int col;
};
struct entry a[500];

int main(){
	FILE *fp,*outfile;
	fp=fopen("input.txt","r");
	outfile=fopen("output.txt","a");
	int k=0,i=0,j=0,all=1,counter=0;
	char name[100],mt[1000][1000];

	char R[50];
	while( fgets(R, 50, fp)!=NULL ){
		strcpy(name,R);
		char *field=strtok(name," ");
		int j=0;
		counter++;
		if(strlen(R)==1){
		  	all++;
			counter=0;
		}
		while(field){
			field=strtok(NULL," ");
			j++;
		}
		a[all].col=j;
		a[all].row=counter;
	}	
	fclose(fp);
	fp=fopen("input.txt","r");
	if(fp==NULL){
		printf("File Error\n");
	}
	else{
		for(k=1;k<=all;k++){
			memset(mt,0,sizeof(mt));
			for(i=0;i<a[k].row;i++){
				for(j=0;j<a[k].col;j++){
					fscanf(fp,"%d",&mt[i][j]);
				}
			}
			fprintf(outfile,"%c\n",64+k);
			for(i=0;i<a[k].row;i++){
				for(j=0;j<a[k].col;j++){
					if(mt[i][j]!=0){
						fprintf(outfile,"%d %d %d\n",i,j,mt[i][j]);
					}
				}
			}
		}
	fclose(fp);
	fclose(outfile);
	}
}
