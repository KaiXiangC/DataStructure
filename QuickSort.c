#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void quicksort(long long int *arr, long long int low, long long int high, long long int n){
	long long int pivot, i, j, temp;
	if(low < high){
	    pivot = low; // select a pivot element
	    i = low;
	    j = high;
    
	    while(i < j){
	    	// increment i till you get a number greater than the pivot element
	    	while(arr[i] <= arr[pivot] && i <= high)
	        	i++;
	      	// decrement j till you get a number less than the pivot element
	      	while(arr[j] > arr[pivot] && j >= low)
	        	j--;
	      	// if i < j swap the elements in locations i and j
	      	if(i < j) {
		        temp = arr[i];
		        arr[i] = arr[j];
		        arr[j] = temp;
	      	}
	    }
		
	    // when i >= j it means the j-th position is the correct position
	    // of the pivot element, hence swap the pivot element with the
	    // element in the j-th position
	    temp = arr[j];
	    arr[j] = arr[pivot];
	    arr[pivot] = temp;
	    
	    for (i = 0; i < n; i++)
			printf(" %lld", arr[i]);
		printf("\n");
	    // Repeat quicksort for the two sub-arrays, one to the left of j
	    // and one to the right of j
	    quicksort(arr, low, j-1, n);
	    quicksort(arr, j+1, high, n);
  	}
}

int main(){
  	char str[10000], copy[10000];
    char *pt, *pt1;
    long long int arr_size=0, i=0;
    scanf("%s", str); //input 19,28,17,76,95,104,33,82,11,0,13,15,17,99 
    strcpy(copy, str);
    pt = strtok (str,",");
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

  	quicksort(arr, 0, arr_size-1, arr_size);

	printf("Sorting results:");
    for (i = 0; i < arr_size; ++i)
    	printf(" %lld", arr[i]);
    printf("\n");
}
