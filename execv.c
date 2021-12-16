#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
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

void printArr(int arr[], int n)
{
    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void forkEx(int arr[], int n)
{
    pid_t cpid;
    //char *c_arr[] = {"1", "2", "8", "4", "5", 0};
    char a1[4];
    char a2[4];
    char a3[4];
    char a4[4];
    char a5[4];
    char *c_arr[] = {a1, a2, a3, a4, a5, 0};
    cpid = fork();
    if (cpid == -1)
        printf("Error occured.\n");
    else if (cpid == 0)
    {
        sleep(1);
        int i = 0;
        for (; i < 5; i++)
        {
            sprintf(c_arr[i], "%d", arr[i]);
        }
        printf("Calling child process to search.\n");
        execv("./bs.out", c_arr);
    }
    else
    {
        bubbleSort(arr, 5);
        printArr(arr, 5);
        wait(NULL);
    }
}

int main()
{
    printf("Enter 5 numbers: ");
    static int *arr;
    arr = mmap(NULL, sizeof(int) * 5, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &arr[i]);
    }
    forkEx(arr, 5);
    return 0;
}
