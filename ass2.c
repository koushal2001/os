#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include<stdlib.h>
#define SIZE 100
int arr[SIZE],n;

void print_arr(int arr[], int n)
{
	int i;
	printf("[");
 
	for(i=0;i<n-1;i++)
		printf(" %d, ", arr[i]);

	printf(" %d ]",arr[i]);
    printf("\n");
}


void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void merge_sort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
  
        merge_sort(arr, l, m); 
        merge_sort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

void bubble_sort(int arr[], int n)
{
    int i, j,temp;
    for (i = 0; i < n-1; i++)    
     
    for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            temp=arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=temp;
}
 

void forkEx()
{
    int cpid = fork();

    if (cpid < 0)
        printf("Fork unsuccessful.\n");
    else if (cpid == 0)
    {
        printf("In child process.\n");
        bubble_sort(arr,n);
        print_arr(arr,n);
        printf("1.child process id is %d\n",getpid());
        printf("1.parent process id is %d\n",getppid());
        // sleep(5);
        printf("3.child process iD is %d\n",getpid());
        printf("3.Parent process iD is %d\n",getppid());
    }
    else
    {
        printf("In parent process.\n");
        merge_sort(arr,0,n-1);
        print_arr(arr,n);
        // sleep(10);
        // wait(NULL);
        printf("2.Parent process iD is %d\n",getpid());
       
    }
}
int main()
{

    
    printf("\n\nEnter the size of array:- ");
	scanf("%d",&n);

	printf("\nPlease enter the elements in the array:- \n");
	for(int i=0;i<n;i++)
	{
		printf("Enter the element [%d]:- ", i);
		scanf("%d", &arr[i]);
	}
    forkEx();
    return 0;
}