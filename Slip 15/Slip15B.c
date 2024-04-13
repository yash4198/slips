#include <stdio.h>
#include <stdlib.h>

void C_SCAN(int *requests, int n, int head, int direction) 
{
    int totalHeadMovements = 0;
    int maxCylinder, minCylinder;

    printf("Enter max range of memory: ");
    scanf("%d", &maxCylinder);

    minCylinder = 0;

    printf("C-SCAN Scheduling order: \n");

    if (direction == 1) 
    {
        for (int i = head; i <= maxCylinder; i++) {
            for (int j = 0; j < n; j++) {
                if (requests[j] == i) 
                {
                    printf("%d ", head);

                    totalHeadMovements += abs(head - requests[j]);
                    head = requests[j];
                    requests[j] = -1;
                }
            }
        }
        printf("%d ", maxCylinder); // Move to the end

        totalHeadMovements += abs(head - maxCylinder);
        head = maxCylinder;

        totalHeadMovements += head;
        head = minCylinder;

        for (int i = head; i <= maxCylinder; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                if (requests[j] == i) 
                {
                    printf("%d ", head);

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
        for (int i = head; i >= minCylinder; i--) 
        {
            for (int j = 0; j < n; j++) 
            {
                if (requests[j] == i) 
                {
                    printf("%d ", head);

                    totalHeadMovements += abs(head - requests[j]);
                    head = requests[j];
                    requests[j] = -1;
                }
            }
        }
        printf("%d ",head);
        printf("%d ", minCylinder);
        totalHeadMovements += head;
        head = minCylinder;

        totalHeadMovements += abs(head - maxCylinder);
        head = maxCylinder;

        for (int i = maxCylinder; i >= minCylinder; i--) 
        {
            for (int j = 0; j < n; j++) 
            {
                if (requests[j] == i) 
                {
                    printf("%d ", head);

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

    C_SCAN(requests, n, head, direction);
    free(requests);
    return 0;
}
