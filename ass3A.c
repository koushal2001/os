#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void forkex(int arr[], int n)
{
    int i;
	char *arrChar[n+1];
	int pid = fork();

	if(pid == 0)
	{
		for(i=0;i<n+1;i++)
		{
			char a[sizeof(int)];   
			snprintf(a, sizeof(int), "%d", arr[i]);
		    arrChar[i] = malloc(sizeof(a));
		    strcpy(arrChar[i], a);
        }
            	arrChar[i] = NULL;
		execve("./binary",arrChar,NULL); 
	}
    else
    {
        bubbleSort(arr,n);
    }
	
}
int main()
{
	int i,n;
	printf("Enter number of elements:");
	scanf("%d",&n);
	int arr[n+1];
	
	printf("Enter %d elements:",n);
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	printf("\nEntered elements are::\n");
	for(i=0;i<n;i++)
		printf("\t%d",arr[i]);
	printf("\nEnter element to be search:");
	scanf("%d",&arr[i]);
    forkex(arr,n);
    
	return 0;
}