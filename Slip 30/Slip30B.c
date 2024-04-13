#include<stdio.h>
#include<stdlib.h>

void FCFS(int *requests,int n, int head)
{
	int i;
	int totalHeadMovements=0;
	int currentPos=head;
	
	printf("FCFS Scheduling order: \n");
	
	for(i=0;i<n;i++)
	{
		printf("%d ",requests[i]);
		totalHeadMovements+=abs(requests[i]-currentPos);
		currentPos=requests[i];
	}
	printf("\n\nTotal head movements: %d\n",totalHeadMovements);
		
}

int main()
{
	int n,i;
	printf("Enter the number of requests: ");
	scanf("%d",&n);
	
	int *requests=(int*)malloc(n*sizeof(int));
	if(requests==NULL)
	{
		printf("Memory allocation failed\n");
		return 1;
	}
	printf("Enter the requests: \n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&requests[i]);
	}
	
	int head;
	printf("Enter current head position: ");
	scanf("%d",&head);
	
	FCFS(requests,n,head);
	free(requests);
	return 0;
}