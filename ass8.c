#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <math.h>
bool in_frame(int page, int n, int frame[])
{
    for (int i = 0; i < n; i++)
    {
        if (page == frame[i])
            return true;
    }
    return false;
}
void fifo(int pages[], int pr, int n)
{
    bool empty = true; 
    int page_faults = 0;
    int queue[n];
    int j = 0;
    for (int i = 0; i < pr; i++)
    {
        if (i == 0)
        {
            printf("Page fault occured for reference string %d on page %d\n", pages[i], (i + 1));
            page_faults++;
            queue[j] = pages[i];
            j = (j + 1) % n;
            continue;
        }
        if (empty)
        {
            if (!in_frame(pages[i], j, queue))
            {
                printf("Page fault occured for reference string %d on page %d\n", pages[i], (i + 1));
                page_faults++;
                queue[j] = pages[i];
                j = (j + 1) % n;
                if (j == 0)
                {
                    empty = false;
                }
            }
        }
        else
        {
            bool hit = in_frame(pages[i], n, queue);
            if (!hit)
            {
                printf("Page fault occured for reference string %d on page %d\n", pages[i], (i + 1));
                page_faults++;
                queue[j] = pages[i];
                j = (j + 1) % n;
            }
        }
    }
    printf("\nTotal Page faults: %d\n", page_faults);
    float page_fault_ratio = (float)page_faults / pr;
    printf("\nPage Fault ratio is : %.2f %%\n\n", page_fault_ratio * 100);
}
void lru(int pages[], int pr, int n)
{
    int page_faults = 0;
    int oc[pr];
    int frame[n];
    int j = 0;

    for (int i = 0; i < pr; i++)
    {
        oc[i] = -1;
    }

    bool full = false;
    for (int i = 0; i < pr; i++)
    {
        if (i == 0)
        {
            page_faults++;
            printf("Page fault occured for reference string %d on page %d\n", pages[i], (i + 1));
            oc[pages[i]] = i;
            frame[j] = pages[i];
            j++;
            continue;
        }

        if (!full)
        {
            if (!in_frame(pages[i], j, frame))
            {
                page_faults++;
                printf("Page fault occured for reference string %d on page %d\n", pages[i], (i + 1));
                frame[j] = pages[i];
                j++;
                if (j == n)
                {
                    full = true;
                }
            }
            oc[pages[i]] = i;
        }

        else
        {
            bool hit = in_frame(pages[i], n, frame);
            if (!hit)
            {
                printf("Page fault occured for reference string %d on page %d\n", pages[i], (i + 1));
                page_faults++;
                int change = 0;
                int min = pr;
                for (int k = 0; k < n; k++)
                {
                    if (oc[frame[k]] < min)
                    {
                        change = k;
                        min = oc[frame[k]];
                    }
                }
                frame[change] = pages[i];
            }
            oc[pages[i]] = i;
        }
    }
    printf("\nTotal Page faults: %d\n", page_faults);
    float page_fault_ratio = (float)page_faults / pr;
    printf("\nPage Fault ratio is : %.2f %%\n\n", page_fault_ratio * 100);
}
void optimal(int pages[], int pr, int n)
{
    int page_faults = 0;
    int frame[n];
    int j = 0;
    bool full = false;
    for (int i = 0; i < pr; i++)
    {
        if (i == 0)
        {
            page_faults++;
            printf("Page fault occured for reference string %d on page %d\n", pages[i], (i + 1));
            frame[j] = pages[i];
            j++;
            continue;
        }
        if (!full)
        {
            if (!in_frame(pages[i], j, frame))
            {
                page_faults++;
                printf("Page fault occured for reference string %d on page %d\n", pages[i], (i + 1));
                frame[j] = pages[i];
                j++;
                if (j == n)
                {
                    full = true;
                }
            }
        }
        else
        {
            bool hit = in_frame(pages[i], n, frame);
            if (!hit)
            {
                printf("Page fault occured for reference string %d on page %d\n", pages[i], (i + 1));
                page_faults++;
                int farthest = -1;
                int frame_no = 0;
                int remove = 0;
                if (i != (n - 1))
                {
                    for (int k = i + 1; k < pr; k++)
                    {
                        if (frame_no == 3)
                        {
                            break;
                        }
                        if (pages[k] == frame[frame_no])
                        {
                            if (k > farthest)
                            {
                                farthest = k;
                                remove = frame_no;
                            }
                            frame_no++;
                        }
                    }
                    frame[remove] = pages[i];
                }
            }
        }
    }
    printf("\nTotal Page faults: %d\n", page_faults);
    float page_fault_ratio = (float)page_faults / pr;
    printf("\nPage Fault ratio is : %.2f %%\n\n", page_fault_ratio * 100);
}
int main()
{
    int n = 0;
    int pr;
    printf("\nEnter the frame size:");
    scanf("%d", &n);

    printf("\nEnter the number of page references:");
    scanf("%d", &pr);

    int pages[pr];

    printf("\nEnter the order in which pages appear:");
    for (int i = 0; i < pr; i++)
    {
        scanf("%d", &pages[i]);
    }

    int choice;
    while (choice != 4)
    {
        printf("1.FIFO\n");
        printf("2.LRU\n");
        printf("3.OPTIMAL\n");
        printf("4.EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            fifo(pages, pr, n);
            break;
        case 2:
            lru(pages, pr, n);
            break;
        case 3:
            optimal(pages, pr, n);
            break;
        case 4:
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}
