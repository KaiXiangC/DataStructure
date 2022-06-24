#include <stdio.h>
#include <stdlib.h>
#define SIZE 13          /*定義雜湊表的大小為13*/
#define EMPTY -99999  /*定義雜湊表的空位為EMPTY*/


/*使用線性探測法將鍵值key放入雜湊表ht*/ 
int linear_probe(int ht[], int key){
	int address;
	address = key % SIZE;              /*將鍵值轉換為位址*/
	while(ht[address] != EMPTY)     /*當發生碰撞時*/ 
		address = (address + 1) % SIZE;  /*往下一個位址探測*/
	ht[address] = key;   
}

int linear_search(int ht[], int key){
	int address;
	address = key % SIZE;              /*將鍵值轉換為位址*/
	while(ht[address] != key){       /*當不等於鍵值時*/  
		address = (address + 1) % SIZE;  /*往下一個位址探測*/
		if (ht[address] == EMPTY || address == key % SIZE) /*若為空位或返回原處*/
			return -1;                                      /*表示搜尋失敗*/ 
  	}
  	return address;  
}

/*主程式*/
main(){
	int ht[SIZE];                  /*宣告ht[]為雜湊表*/
	int i, c;
	for(i = 0; i < SIZE; i++)      /*將雜湊表初始化為EMPTY*/
		ht[i] = EMPTY;

	while(scanf("%d", &c)!=EOF){ //input 1 2 3 4 5 6 14 15 16 27 13 13
		linear_probe(ht, c);
	}
	for(i = 0; i < SIZE; i++)
		printf("%d\n",ht[i]);
	return 0;  
}
