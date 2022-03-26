#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct key{
	char date[50];
	char amount[50];
	char f1[50];
	char f2[50];
	char m1[50];
	char m2[50];
	char price[50];
}dict;

typedef struct bk{
	char nm[50];
	char amount[50];
	char f1[50];
	char f2[50];
	char m1[50];
	char m2[50];
	char mprice[50];
	char price[50];
}buy;

typedef struct sk{
	char nm[50];
	char amount[50];
	char f1[50];
	char f2[50];
	char m1[50];
	char m2[50];
	char mprice[50];
	char price[50];
}sell;

int bcompare(const void *s1, const void *s2){
    struct bk *e1 = (struct bk *)s1;
    struct bk *e2 = (struct bk *)s2;
    int gendercompare = strcmp(e1->amount, e2->amount);
    if (gendercompare == 0)  /* same gender so sort by id */
    	return atof(e1->amount), atof(e2->amount);
    else
        return -gendercompare;
}
    
int scompare(const void *s1, const void *s2){
    struct sk *e1 = (struct sk *)s1;
    struct sk *e2 = (struct sk *)s2;
    int gendercompare = strcmp(e1->amount, e2->amount);
    if (gendercompare == 0)  /* same gender so sort by id */
        return atof(e1->amount), atof(e2->amount);
    else
        return -gendercompare;
}
    
char * strrepl(char * src, char * dst, size_t dst_size,char * search,char * replace_with){
    char * replace_buf = (char *)malloc(dst_size);
    if (replace_buf){
        replace_buf[0] = 0;
        char * p = (char *)src;
        char * pos = NULL;
        while ( (pos = strstr(p, search)) != NULL ){
            size_t n = (size_t)(pos-p);
            strncat(replace_buf, p, n > dst_size ? dst_size : n);
            strncat(replace_buf, replace_with, dst_size-strlen(replace_buf)-1);
            p = pos + strlen(search);
        }
        snprintf(dst, dst_size, "%s%s", replace_buf, p);
        free(replace_buf);
    }
    return dst;
}

int main(void){
	clock_t start, bend, send;
	start = clock();
    //檔案儲存資訊結構體 
    struct _finddata_t fileinfo;
    //儲存檔案控制代碼 
    long fHandle;
	buy valb[999];
	sell vals[999];
	int y=0,z=0;
	fHandle=_findfirst( "*.csv", &fileinfo );
    do{
    	char buff[1024];
		dict values[999];
		int row_count=0;
		int field_count=0;
		int fd_count=0;
		int i=0;
		char fname[4];
	
		strncpy(fname, fileinfo.name, 4);
        FILE* fp = fopen(fileinfo.name, "r");
		char sub[1024];
		i=0;
	    while(fgets(buff,1024,fp)){
	    	field_count=0;
	    	row_count++;
	    	if(row_count==1){ //skip label name
	    		continue;
			}
			char *field=strtok(buff,"\"");
			while(field){
//				printf("%s\n",field);
				if(field_count==0){
					strcpy(values[i].date,field);
				}
				if(field_count==3){
					strcpy(values[i].amount,field);
				}
				if(field_count==6){
					fd_count=0;
					char *fd=strtok(field,",");
					while(fd){
						if(fd_count==0){
							strcpy(values[i].f1,fd);
						}
						if(fd_count==1){
							strcpy(values[i].f2,fd);
						}
						if(fd_count==5){
							strcpy(values[i].m1,fd);
						}
						if(fd_count==6){
							strcpy(values[i].m2,fd);
						}
						if(fd_count==7){
							strcpy(values[i].price,fd);
						}
						fd=strtok(NULL,",");
						fd_count++;
					}
				}
				field=strtok(NULL,"\"");
				field_count++;
			}
			i++;
		}
		fclose(fp);
		float addi=0;
		float month=0;
		char a[50],b[50];
		strrepl(values[0].amount, a, strlen(values[0].amount), ",", "");
		strrepl(values[4].amount, b, strlen(values[4].amount), ",", "");
		int addp=atoi(a)-atoi(b);
		float max=atof(values[0].price);
		float min=atof(values[0].price);
		float maxp,minp;
		if(atof(values[0].price)<100){
			month=atof(values[0].m2)-atof(values[1].m2);
			addi=atof(values[0].m2)-atof(values[4].m2);
			maxp=atof(values[0].m2);
			minp=atof(values[0].m2);
			for(i=0;i<170;i++){
				if(atof(values[i].m2)>maxp){
					maxp=atof(values[i].m2);
				}
				if(atof(values[i].m2)<minp){
					minp=atof(values[i].m2);
				}
			}
		}
		if(atof(values[0].price)>=100){
			month=atof(values[0].f1)-atof(values[1].f1);
			addi=atof(values[0].f1)-atof(values[4].f1);
			maxp=atof(values[0].f1);
			minp=atof(values[0].f1);
			for(i=0;i<170;i++){
				if(atof(values[i].f1)>maxp){
					maxp=atof(values[i].f1);
				}
				if(atof(values[i].f1)<minp){
					minp=atof(values[i].f1);
				}
			}
		}
		for(i=0;i<170;i++){
			if(atof(values[i].price)>max){
				max=atof(values[i].price);
			}
			if(atof(values[i].price)<min){
				min=atof(values[i].price);
			}
		}
		if(month>1 && addi>=3){
			char buf[BUFSIZ];
			strcpy(valb[z].nm,fname);
  			snprintf(buf, sizeof(buf), "%.2f", addi);
			strcpy(valb[z].amount,buf);
			snprintf(buf, sizeof(buf), "%d", addp);
			strcpy(valb[z].f1,buf);
			snprintf(buf, sizeof(buf), "%.2f", maxp);
			strcpy(valb[z].f2,buf);
			snprintf(buf, sizeof(buf), "%.2f", minp);
			strcpy(valb[z].m1,buf);
			snprintf(buf, sizeof(buf), "%.2f", atof(values[0].price));
			strcpy(valb[z].m2,buf);
			snprintf(buf, sizeof(buf), "%.2f", max);
			strcpy(valb[z].mprice,buf);
			snprintf(buf, sizeof(buf), "%.2f", min);
			strcpy(valb[z].price,buf);
			z++;
//			printf("%s %.2f %d %.2f %.2f %.2f %.2f %.2f\n",fname,addi,addp,maxp,minp,atof(values[0].price),max,min);	
		}
		if(month<=-1 && addi<=-3){
			char buf[BUFSIZ];
			strcpy(vals[y].nm,fname);
  			snprintf(buf, sizeof(buf), "%.2f", addi);
			strcpy(vals[y].amount,buf);
			snprintf(buf, sizeof(buf), "%d", addp);
			strcpy(vals[y].f1,buf);
			snprintf(buf, sizeof(buf), "%.2f", maxp);
			strcpy(vals[y].f2,buf);
			snprintf(buf, sizeof(buf), "%.2f", minp);
			strcpy(vals[y].m1,buf);
			snprintf(buf, sizeof(buf), "%.2f", atof(values[0].price));
			strcpy(vals[y].m2,buf);
			snprintf(buf, sizeof(buf), "%.2f", max);
			strcpy(vals[y].mprice,buf);
			snprintf(buf, sizeof(buf), "%.2f", min);
			strcpy(vals[y].price,buf);
			y++;	
		}
    }while( _findnext(fHandle,&fileinfo)==0);
    //關閉檔案 
    
    _findclose( fHandle );
	qsort(valb, z, sizeof(struct bk), bcompare);
	bend = clock();
	qsort(vals, y, sizeof(struct sk), scompare);
	send = clock();
    printf("共%d筆符合買入\n",z);
    for(int j=0;j<z;j++){
    	
		printf("%s %s %s %s %s %s %s %s\n",valb[j].nm,valb[j].amount,valb[j].f1,valb[j].f2,valb[j].m1,valb[j].m2,valb[j].mprice,valb[j].price);
	}
    printf("----------------------------------------------\n");
    printf("共%d筆符合賣出\n",y);
    for(int j=0;j<y;j++){
		printf("%s %s %s %s %s %s %s %s\n",vals[j].nm,vals[j].amount,vals[j].f1,vals[j].f2,vals[j].m1,vals[j].m2,vals[j].mprice,vals[j].price);
	}
	
	printf("----------------------------------------------\n");
	int buytime = bend - start;
	int selltime = send - start;
    printf("buy_time:%d ms  sell_time:%d ms", buytime,selltime);
}
