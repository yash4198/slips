#include <stdio.h>

int allocation[10][10];
int max[10][10];
int need[10][10];
int available[10];
int num_processes, num_resources;

void calculateNeed() 
{
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafe(int request[], int process) 
{
    for (int i = 0; i < num_resources; i++) 
    {
        if (request[i] > need[process][i]) 
        {
            return 0;
        }
    }

    for (int i = 0; i < num_resources; i++) 
    {
        if (request[i] > available[i]) 
        {
            return 0; 
        }
    }

    return 1;
}

void grantRequest(int request[], int process) 
{
    for (int i = 0; i < num_resources; i++) 
    {
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
        available[i] -= request[i];
    }
}

int main() 
{
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resource types: ");
    scanf("%d", &num_resources);

    printf("Enter the available instances of each resource type: ");
    for (int i = 0; i < num_resources; i++) 
    {
        scanf("%d", &available[i]);
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum requirement matrix:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            scanf("%d", &max[i][j]);
        }
    }

    calculateNeed();

    printf("Need Matrix:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Accept request
    int request[10];
    int process;

    printf("Enter the process number making the request (0 to %d): ", num_processes - 1);
    scanf("%d", &process);

    printf("Enter the request for each resource type: ");
    for (int i = 0; i < num_resources; i++) 
    {
        scanf("%d", &request[i]);
    }

    if (isSafe(request, process)) 
    {
        grantRequest(request, process);
        printf("Request can be granted.\n");
    } 
    else 
    {
        printf("Request cannot be granted.\n");
    }

    return 0;
}
