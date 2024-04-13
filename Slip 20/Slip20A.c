#include <stdio.h>
#include <stdlib.h>

int findMinimum(int *requests, int size) 
{
    int min = requests[0];
    for (int i = 1; i < size; i++) {
        if (requests[i] < min) {
            min = requests[i];
        }
    }
    return min;
}

int findMaximum(int *requests, int size) 
{
    int max = requests[0];
    for (int i = 1; i < size; i++) 
    {
        if (requests[i] > max) 
        {
            max = requests[i];
        }
    }

    return max;
}

void SCAN(int *requests, int n, int head, int direction) 
{
    int totalHeadMovements = 0;
    int maxCylinder;
    int minCylinder;

    if (direction == 1) 
    {
        printf("Enter max range of memory: ");
        scanf("%d",&maxCylinder);

        printf("SCAN Scheduling order: \n");

        minCylinder=findMinimum(requests,n);

        for (int i = head; i <= maxCylinder; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                if (requests[j] == i) 
                {
                    printf("%d ",head);

                    totalHeadMovements += abs(head - requests[j]);
                    head = requests[j];
                    requests[j] = -1;
                }
            }
        }

        printf("%d ",head);
        totalHeadMovements+=abs(head-maxCylinder);
        head=maxCylinder;

        for (int i = head; i >= minCylinder; i--) 
        {
            for (int j = 0; j < n; j++) 
            {
                if (requests[j] == i) 
                {
                    printf("%d ",head);

                    totalHeadMovements += abs(head - requests[j]);
                    head = requests[j];
                    requests[j] = -1;
                }
            }
        }

        printf("%d ",head);
    } 
    
    else if (direction == -1) 
    {
        maxCylinder=findMaximum(requests, n);
        minCylinder=0;

        for (int i = head; i >= minCylinder; i--) 
        {
            for (int j = 0; j < n; j++) 
            {
                if (requests[j] == i) 
                {
                    printf("%d ",head);

                    totalHeadMovements += abs(head - requests[j]);
                    head = requests[j];
                    requests[j] = -1;
                }
            }
        }

        printf("%d ",head);
        totalHeadMovements+=abs(head-minCylinder);
        head=minCylinder;

        for (int i = head; i <= maxCylinder; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                if (requests[j] == i) 
                {
                    printf("%d ",head);
                    totalHeadMovements += abs(head - requests[j]);
                    head = requests[j];
                    requests[j] = -1;
                }
            }
        }
        printf("%d ",head);
    }

    printf("\nTotal head movements: %d\n", totalHeadMovements);
}

int main() 
{
    int n, head, direction;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int *requests = (int *)malloc(n * sizeof(int));

    if (requests == NULL) 
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the requests: \n");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &requests[i]);
    }

    printf("Enter current head position: ");
    scanf("%d", &head);

    printf("Enter the direction (1 for right/greater, -1 for left/smaller): ");
    scanf("%d", &direction);

    SCAN(requests, n, head, direction);
    free(requests);
    return 0;
}