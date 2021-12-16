#include <stdio.h>     
#include <stdlib.h>     

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

int main (int argc,char *argv[])
{
  int i,key,n;
  int arr[argc];

  for(i=0;i<argc-1;i++)
  {
  	n = atoi(argv[i]);
  	arr[i] = n;
  }
  key = atoi(argv[i]);
 for(int loop = 0; loop < argc-1; loop++)
      printf("%d ", arr[loop]);
  int pos = binarySearch(arr, 0, argc-1, key);
  if (pos!=-1)
    printf ("\n%d is in the array. At %d \n",key,pos);
  else
    printf ("\n%d is not in the array.\n",key);
  
  return 0;
}