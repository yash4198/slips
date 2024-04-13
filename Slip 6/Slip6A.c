#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Block
{
	int block_number;
	struct Block *next_block;
};

struct DirectoryEntry
{
	char filename[50];
	struct Block *start_block;
	int length;
};

void showBitVector(struct Block **bitVector, int n)
{
	int i;
	printf("Bit Vector:\n");
	for(i=0;i<n;i++)
	{
		printf("Block %d: ",i);
		struct Block *current_block=bitVector[i];
		while(current_block!=NULL)
		{
			printf("%d->",current_block->block_number);
			current_block=current_block->next_block;
		}
		printf("\n");
	}
}

void createNewFile(struct DirectoryEntry **directory, struct Block **bitVector, int n, int *directorySize)
{
	int start,end;
	int i;
	char filename[100];
	int numBlocks;
	
	printf("Enter file name: ");
	scanf("%s",filename);
	printf("Enter start Block: ");
	scanf("%d",&start);
	printf("Enter end Block: ");
	scanf("%d",&end);
	printf("Enter number of blocks: ");
	scanf("%d",&numBlocks);
	
	struct Block *startBlock=NULL;
	struct Block *prevBlock=NULL;
	
	for(i=0;i<numBlocks;i++)
	{
		int blockNum=rand()%(start-end+1)+end;		
		if(blockNum>=n || blockNum<0)
		{
			printf("Invalid block number\n");
			return;
		}
		
		struct Block *newBlock=(struct Block*)malloc(sizeof(struct Block));
		if(newBlock==NULL)
		{
			printf("Memory allocation failed\n");
			return;
		}
		
		newBlock->block_number=blockNum;
		newBlock->next_block=NULL;
		
		if(startBlock==NULL)
		{
			startBlock=newBlock;
		}
		else
		{
			prevBlock->next_block=newBlock;
		}
		
		prevBlock=newBlock;
		
		if(bitVector[blockNum]==NULL)
		{
			bitVector[blockNum]=newBlock;
		}
		else
		{
			struct Block *currentBlock=bitVector[blockNum];
			while(currentBlock->next_block!=NULL)
			{
				currentBlock=currentBlock->next_block;
			}
			currentBlock->next_block=newBlock;
		}
	}
	
	*directory=(struct DirectoryEntry*)realloc(*directory,(*directorySize+1)*sizeof(struct DirectoryEntry));
	strcpy((*directory)[*directorySize].filename,filename);
	(*directory)[*directorySize].start_block=startBlock;
	(*directory)[*directorySize].length=numBlocks;
	(*directorySize)++;
	
	printf("File '%s' created successfully\n",filename);
}

void showDirectory(struct DirectoryEntry *directory, int directorySize)
{
	int i;
	printf("Directory: \n");
	for(i=0;i<directorySize;i++)
	{
		printf("Filename: %s\tBlocks: ",directory[i].filename);
		struct Block *currentBlock=directory[i].start_block;
		while(currentBlock!=NULL)
		{
			printf("%d ",currentBlock->block_number);
			currentBlock=currentBlock->next_block;
		}
		printf("\n");
	}
}

void deleteFile(struct DirectoryEntry *directory, struct Block **bitVector, int *directorySize)
{
	int i,j;
	char filename[100];
	printf("Enter filename to delete: ");
	scanf("%s",filename);
	
	int found=0;
	for(i=0;i<*directorySize;i++)
	{
		if(strcmp(directory[i].filename,filename)==0)
		{
			struct Block *currentBlock=directory[i].start_block;
			while (currentBlock!=NULL)
			{
				int blockNum=currentBlock->block_number;
				struct Block *temp=currentBlock;
				currentBlock=currentBlock->next_block;
				free(temp);
				bitVector[blockNum]=NULL;
			}
			for(j=i;j<*directorySize-1;j++)
			{
				directory[j]=directory[j+1];
			}
			(*directorySize--);
			found=1;
			printf("File '%s' deleted successfully\n",filename);
			break;
		}
	}
	if(!found)
	{
		printf("File %s not found.\n",filename);
	}
}

int main()
{
	int n,i;
	printf("Enter the number of blocks on disk: ");
	scanf("%d",&n);
	
	struct Block **bitVector=(struct Block**)malloc(n*sizeof(struct Block*));
	if(bitVector==NULL)
	{
		printf("Memory allocation failed.\n");
		return 1;
	}
	
	for(i=0;i<n;i++)
	{
		bitVector[i]=NULL;
	}
	struct DirectoryEntry *directory=NULL;
	int directorySize=0;
	int choice;
	do
	{
		printf("\nMENU\n");
		printf("1. SHOW BIT VECTOR\n");
		printf("2. CREATE NEW FILE\n");
		printf("3. SHOW DIRECTORY\n");
		printf("4. DELETE FILE\n");
		printf("5. EXIT\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				showBitVector(bitVector,n);
				break;
			case 2:
				createNewFile(&directory,bitVector,n,&directorySize);
				break;
			case 3:
				showDirectory(directory,directorySize);
				break;
			case 4:
				deleteFile(directory,bitVector,&directorySize);
				break;
			case 5:
				printf("\nExiting...\n");
				break;
			default:
				printf("Invalid Choice\n");
		}
	}while(choice!=5);
	
	free(bitVector);
	free(directory);
		
	return 0;
}