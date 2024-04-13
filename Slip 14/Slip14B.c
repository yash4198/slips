#include<stdio.h>
#include<stdlib.h>

int findShortestSeekTime(int *requests,int n,int head)
{
	int i,seekTime;
	int shortestIndex=-1;
	int shortestSeekTime=1000;
	
	for(i=0;i<n;i++)
	{
		if(requests[i]!=-1)
		{
			seekTime=abs(requests[i]-head);
			if(seekTime<shortestSeekTime)
			{
				shortestSeekTime=seekTime;
				shortestIndex=i;
			}
		}
	}
	return shortestIndex;
}

void SSTF(int *requests,int n, int head)
{
	int i;
	int totalHeadMovements=0;
	printf("SSTF Scheduling order: \n");
	for(i=0;i<n;i++)
	{
		int shortestIndex=findShortestSeekTime(requests,n,head);
		totalHeadMovements+=abs(requests[shortestIndex]-head);
		printf("%d ",requests[shortestIndex]);
		head=requests[shortestIndex];
		requests[shortestIndex]=-1;
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
	
	SSTF(requests,n,head);
	free(requests);
	return 0;
}