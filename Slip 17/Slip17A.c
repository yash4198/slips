#include<stdio.h>
#include<stdlib.h>

#define pf printf
#define sf scanf

int files[50],indexBlock[50],indBlock,n;
void recurse1();
void recurse2();

void recurse1()
{
	pf("\nEnter the index block:");
	sf("%d",&indBlock);
	if(files[indBlock]!=1)
	{
		pf("\n Enterthe number of blocks and needed for the index %d on the disk: ",indBlock);
		sf("%d",&n);
		files[indBlock]=1;
		
	}
	else
	{
		pf("\n%d is already allocated\n",indBlock);
		recurse1();
	}
	recurse2();	
}


void recurse2()
{
	int ch;
	int flag=0;
	for(int i=0;i<n;i++)
	{
		indexBlock[i]=rand()%50+1;
		if(files[indexBlock[i]]==0)
			flag++;
	}
	if(flag == n)
	{
		for(int j=0;j<n;j++)
		{
			files[indexBlock[j]]=1;
		}
		pf("Allocated\n");
		pf("File Indexed\n");
		for(int k=0;k<n;k++)
		{
			pf("%d------->%d : %d\n",indBlock,indexBlock[k],files[indexBlock[k]]);
		}
		
	}
	else
	{
		pf("File in the index is already allocated\n");
		pf("Enter another indexed file\n");
		recurse2();
		
	}
	pf("\n Do you want to enter more files?\n");
	pf("\n Enter (1: YES || 0: NO):");
	sf("%d",&ch);
	if(ch==1)
	{
		recurse1();
	}
	else
	{
		exit(0);
	}
	return;
}

void main()
{
	for(int i=0;i<50;i++)
	{
		files[i]=0;
	}
	recurse1();
	
}