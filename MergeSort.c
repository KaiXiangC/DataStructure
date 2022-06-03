#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Merge Function
void merge(long long int arr[], long long int l, long long int m, long long int r){
	long long int i, j, k;
	long long int n1 = m - l + 1;
	long long int n2 = r - m;
	long long int L[n1], R[n2];
	
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
		
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];
		
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2){
		if (L[i] <= R[j]){
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2){
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(long long int arr[], long long int l, long long int r){
	if (l < r){
		long long int m = l+(r-l)/2;
		printf("middle=%d\n",m);
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

int main(){
	char str[10000], copy[10000];
    char *pt, *pt1;
    long long int arr_size=0, i=0;
    scanf("%s", str);//input 19,28,17,76,95,104,33,82,11,0,13,15,17,99
    strcpy(copy, str);
    pt = strtok (str, ",");
    while (pt != NULL) {
        arr_size++;
        pt = strtok (NULL, ",");
    }
    
	long long int arr[arr_size];
    pt1 = strtok (copy, ",");
    while (pt1 != NULL) {
        long long int a = atoi(pt1);
        arr[i]=a;
        i++;
        pt1 = strtok (NULL, ",");
    }

	mergeSort(arr, 0, arr_size - 1);
	
	printf("Sorting results:");
	for (i=0; i < arr_size; i++)
		printf(" %d", arr[i]);
	printf("\n");

}
