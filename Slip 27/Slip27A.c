#include <stdio.h>
#include <stdlib.h>

void LOOK(int *requests, int n, int head, int direction) 
{
    int totalHeadMovements = 0;
    int maxCylinder = 199;
    int minCylinder = 0;

    printf("LOOK Scheduling order: \n");

    // Sort the requests
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (requests[j] > requests[j + 1]) 
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int index = 0;

    // Find index of head in sorted requests
    for (int i = 0; i < n; i++) 
    {
        if (requests[i] >= head) 
        {
            index = i;
            break;
        }
    }

    if (direction == 1) 
    { 
        for (int i = index; i < n; i++) 
        {
            printf("%d ", requests[i]);
            totalHeadMovements += abs(head - requests[i]);
            head = requests[i];
        }
        for (int i = index - 1; i >= 0; i--) 
        {
            printf("%d ", requests[i]);
            totalHeadMovements += abs(head - requests[i]);
            head = requests[i];
        }
    } 
    else if (direction == -1) 
    {
        for (int i = index - 1; i >= 0; i--) 
        {
            printf("%d ", requests[i]);
            totalHeadMovements += abs(head - requests[i]);
            head = requests[i];
        }

        for (int i = index; i < n; i++) {
            printf("%d ", requests[i]);
            totalHeadMovements += abs(head - requests[i]);
            head = requests[i];
        }
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

    LOOK(requests, n, head, direction);
    free(requests);
    return 0;
}