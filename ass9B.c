#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
    FILE *fp;
    
    int f1, f2;
    int lines=1, words=1, characters=0, i;
    
    char *fifo_1 = "file1", str1[100];
    char *fifo_2 = "file2", str2[100];

    f1 = open(fifo_1, O_RDONLY);
    read(f1, str1, 100);

    printf("\nAt Process 1: %s", str1);

    i=0;

    while(str1[i] != '\0')
    {
        if(str1[i] == '.' || str1[i] == '\n')
        {  
            lines++;
        }
    
        else if(str1[i] == ' ')
        {
            words++;
        }
    
        else
        {
            characters++;
        }
    
        i++;
    }

    printf("\nNumber of Characters: %d", characters);
    printf("\nNumber of Words: %d", words);
    printf("\nNumber of Lines: %d\n", lines);

    fp = fopen("output.txt", "w");
    
    fprintf(fp, "\nNumber of Characters: %d", characters);
    fprintf(fp, "\nNo of Words: %d", words);
    fprintf(fp, "\nNo of Lines: %d\n", lines);

    fclose(fp);
    
    fp = fopen("output.txt", "r");

    int ch;
    
    ch = fgetc(fp);
    
    i=0;

    while(ch != EOF)
    { 
        str2[i]= ch;
        i++;
        ch = fgetc(fp);
    }

    str2[i] = '\0';
    
    fclose(fp);

    close(f1);

    f2 = open(fifo_2, O_WRONLY);
    write(f2, str2, strlen(str2) + 1);

    close(f2); 

    return 0;
}