#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binarySearch(int arr[], int l, int r, int target)
{
    if (r >= l)
    {
        int m = l + (r - l) / 2;
        if (arr[m] == target)
            return m;
        if (arr[m] > target)
            return binarySearch(arr, l, m - 1, target);
        return binarySearch(arr, m + 1, r, target);
    }
    return -1;
}

int main(int argc, char **argv)
{
    int arr[5];
    for (int i = 0; i < argc; i++)
    {
        //printf("%s ", argv[i]);
        //arr[i-1] = atoi(argv[i]);
        arr[i] = atoi(argv[i]);
    }
    printf("Enter element to be searched: ");
    int target;
    scanf("%d", &target);
    int pos = binarySearch(arr, 0, 5, target);
    // printf("pos = %d", pos);
    if (pos == -1)
        printf("Element not found in the array.\n");
    else
        printf("%d found at index %d\n", target, pos);
    return 0;
}