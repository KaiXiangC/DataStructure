#include <stdio.h>
#include <stdlib.h>
#define SIZE 13          /*�w�q������j�p��13*/
#define EMPTY -99999  /*�w�q������Ŧ쬰EMPTY*/


/*�ϥνu�ʱ����k�N���key��J�����ht*/ 
int linear_probe(int ht[], int key){
	int address;
	address = key % SIZE;              /*�N����ഫ����}*/
	while(ht[address] != EMPTY)     /*��o�͸I����*/ 
		address = (address + 1) % SIZE;  /*���U�@�Ӧ�}����*/
	ht[address] = key;   
}

int linear_search(int ht[], int key){
	int address;
	address = key % SIZE;              /*�N����ഫ����}*/
	while(ht[address] != key){       /*��������Ȯ�*/  
		address = (address + 1) % SIZE;  /*���U�@�Ӧ�}����*/
		if (ht[address] == EMPTY || address == key % SIZE) /*�Y���Ŧ�Ϊ�^��B*/
			return -1;                                      /*��ܷj�M����*/ 
  	}
  	return address;  
}

/*�D�{��*/
main(){
	int ht[SIZE];                  /*�ŧiht[]�������*/
	int i, c;
	for(i = 0; i < SIZE; i++)      /*�N������l�Ƭ�EMPTY*/
		ht[i] = EMPTY;

	while(scanf("%d", &c)!=EOF){ //input 1 2 3 4 5 6 14 15 16 27 13 13
		linear_probe(ht, c);
	}
	for(i = 0; i < SIZE; i++)
		printf("%d\n",ht[i]);
	return 0;  
}
