#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DirectoryEntry 
{
    char filename[50];
    int start_block;
    int length;
};

void showBitVector(int *bitVector, int n) 
{
    printf("Bit Vector: ");
    for (int i=0;i<n;i++)
    {
        printf("%d",bitVector[i]);
    }
    printf("\n");
}

void createNewFile(struct DirectoryEntry **directory,int *bitVector,int n,int *directorySize) 
{
    char filename[50];
    int numBlocks;

    printf("Enter file name: ");
    scanf("%s",filename);
    printf("Enter number of blocks: ");
    scanf("%d",&numBlocks);

    int startBlock=-1;
    for(int i=0;i<=n-numBlocks;i++)
    {
        int j;
        for(j=0;j<numBlocks;j++)
        {
            if(bitVector[i+j]==0)
            {
                break;
            }
        }
        if(j==numBlocks) 
        {
            startBlock=i;
            break;
        }
    }

    if (startBlock!=-1) 
    {
        for(int i=startBlock;i<startBlock+numBlocks;i++) 
        {
            bitVector[i]=0;
        }
        *directory=(struct DirectoryEntry*)realloc(*directory,(*directorySize+1)*sizeof(struct DirectoryEntry));
        strcpy((*directory)[*directorySize].filename,filename);
        (*directory)[*directorySize].start_block=startBlock;
        (*directory)[*directorySize].length=numBlocks;
        (*directorySize)++;
        printf("File '%s' created successfully.\n", filename);
    }
    else
    {
        printf("Not enough contiguous space available.\n");
    }
}
void showDirectory(struct DirectoryEntry *directory,int directorySize) 
{
    printf("Directory:\n");
    for(int i=0;i<directorySize;i++)
    {
        printf("Filename: %s,Start Block: %d,Length: %d\n", directory[i].filename,directory[i].start_block, directory[i].length);
    }
}

void deleteFile(struct DirectoryEntry *directory,int *bitVector,int *directorySize) 
{
    char filename[50];
    printf("Enter filename to delete: ");
    scanf("%s",filename);

    int found=0;
    for(int i=0;i<*directorySize;i++)
    {
        if(strcmp(directory[i].filename,filename)==0) 
        {
            for(int j=directory[i].start_block;j<directory[i].start_block+directory[i].length;j++) 
            {
                bitVector[j]=1;
            }
            for(int j=i;j<*directorySize-1;j++) 
            {
                directory[j]=directory[j+1];
            }

            (*directorySize)--;
            found=1;
            printf("File '%s' deleted successfully.\n",filename);
            break;
        }
    }

    if(!found)
    {
        printf("File '%s' not found.\n",filename);
    }
}

int main() 
{
    int n;
    printf("Enter the number of blocks on disk: ");
    scanf("%d",&n);

    int *bitVector=(int *)malloc(n*sizeof(int));
    if(bitVector==NULL) 
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    for(int i=0;i<n;i++) 
    {
        bitVector[i]=rand()%2;
    }

    struct DirectoryEntry *directory=NULL;
    int directorySize=0;

    int choice;
    do 
    {
        printf("\nMenu:\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
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
                printf("Exiting...\n");
                printf("----------------------------------------------------------");
                break;
            default:
                printf("Invalid choice.\n");
        }
    }while(choice != 5);

    free(bitVector);
    free(directory);

    return 0;
}