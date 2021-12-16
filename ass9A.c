#include<stdio.h>
#include <fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
    int f1, f2;
    
    char *fifo_1 = "file1", str1[100], str2[100];
    char *fifo_2 = "file2";
    
    f1 = mkfifo(fifo_1, 0666);
    f2 = mkfifo(fifo_2, 0666);
    
    char str;
    int k=0;
    
    printf("\nEnter a string: ");
    
    while ((str = getchar())!='#')
    
    str1[k++] = str;
    str1[k] == '\0';
    
    f1 = open(fifo_1, O_WRONLY);
    write(f1, str1, strlen(str1) + 1);
    
    close(f1);
    
    f2 = open(fifo_2, O_RDONLY);
    read(f2, str2, 100);
    
    printf("\nOutput from Process fifo 2: \n%s", str2);
    
    close(f2);
       
    return 0;
}