#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(long long int *a, long long int *b){
	long long int temp = *a;
	*a = *b;
	*b = temp;
}
  
void heapify(long long int arr[], long long int n, long long int i){
    // Find smallest among root, left child and right child
    long long int smallest = i;
    long long int left = 2 * i + 1;
    long long int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[smallest])
    	smallest = left;
  
    if (right < n && arr[right] > arr[smallest])
    	smallest = right;
  
    if (smallest != i) {
    	swap(&arr[i], &arr[smallest]);
    	heapify(arr, n, smallest);
    }
}
  
// Main function to do heap sort
void heapSort(long long int arr[], long long int n) {
	long long int i, j;
    // Build min heap
    for (i = n / 2 - 1; i >= 0; i--)
    	heapify(arr, n, i);
  
    // Heap sort
    for (i = n - 1; i >= 0; i--) {
    	for (j = 0; j < n; ++j)
      		printf(" %lld", arr[j]);
    	printf("\n");
    	swap(&arr[0], &arr[i]);
  
      	// Heapify root element to get highest element at root again
    	heapify(arr, i, 0);
    }
}

int main() {
	
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
    pt1 = strtok (copy,",");
    while (pt1 != NULL) {
        long long int a = atoi(pt1);
        arr[i]=a;
        i++;
        pt1 = strtok (NULL, ",");
    }
	
    heapSort(arr, arr_size);

    printf("Sorting results:");
    for (i = 0; i < arr_size; ++i)
    	printf(" %lld", arr[i]);
    printf("\n");
}
