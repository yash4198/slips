#include <stdio.h>

int available[10];
int total[10];
int allocation[10][10];
int max[10][10];
int need[10][10];
int num_resources, num_processes;

void acceptAvailable() 
{
    printf("Enter total resources:\n");
    for (int i = 0; i < num_resources; i++) 
    {
        scanf("%d", &available[i]);
    }
}

void acceptAllocationMax() 
{
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the max matrix:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void displayAllocationMax() 
{
    printf("Allocation Matrix:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Max Matrix:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
}

void displayNeed() 
{
    printf("Need Matrix:\n");
    for (int i = 0; i < num_processes; i++) 
    {
        for (int j = 0; j < num_resources; j++) 
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

void displayAvailable() 
{
    printf("Available Resources:\n");
    for (int i = 0; i < num_resources; i++) 
    {
        printf("%d ", available[i]);
    }
    printf("\n");
}

int isSafe() 
{
    int work[num_resources];
    int finish[num_processes];

    // Initialize work and finish arrays
    for (int i = 0; i < num_resources; i++) 
    {
        work[i] = available[i];
    }
    for (int i = 0; i < num_processes; i++) 
    {
        finish[i] = 0;
    }

    int count = 0;
    int safeSequence[num_processes];

    while (count < num_processes) 
    {
        int found = 0;
        for (int i = 0; i < num_processes; i++) 
        {
            if (finish[i] == 0) 
            {
                int j;
                for (j = 0; j < num_resources; j++) 
                {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == num_resources) 
                {
                    for (int k = 0; k < num_resources; k++) 
                    {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) 
        {
            printf("System is not in safe state.\n");
            return 0;
        }
    }

    printf("System is in safe state.\nSafe sequence: ");
    for (int i = 0; i < num_processes; i++) 
    {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");

    return 1;
}

int isDeadlock() 
{
    for (int i = 0; i < num_processes; i++) 
    {
        int canAllocate = 0;
        for (int j = 0; j < num_resources; j++) 
        {
            if (need[i][j] <= available[j]) 
            {
                canAllocate = 1;
                break;
            }
        }
        if (!canAllocate) 
        {
            printf("Deadlock detected!\n");
            return 1;
        }
    }
    printf("No deadlock detected.\n");
    return 0;
}

int main() 
{
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    acceptAllocationMax();

    int choice;

    printf("\nMenu:\n");
    printf("1. Accept Total\n");
    printf("2. Display Allocation, Max\n");
    printf("3. Display Need Matrix\n");
    printf("4. Display Available\n");
    printf("5. Check Safety\n");
    printf("6. Check Deadlock\n");
    printf("7. Exit\n");

    while (1) 
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                acceptAvailable();
                break;
            case 2:
                displayAllocationMax();
                break;
            case 3:
                displayNeed();
                break;
            case 4:
                displayAvailable();
                break;
            case 5:
                isSafe();
                break;
            case 6:
                isDeadlock();
                break;
            case 7:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Please choose again.\n");
        }
    }

    return 0;
}