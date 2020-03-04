#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void firstFit(int blockSize[], int m, int processSize[], int n)
{
	int allocation[n];
	memset(allocation,-1,sizeof(allocation));
	
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<m; j++)
		{
			if(blockSize[j] >= processSize[i])
			{
				allocation[i] = j;
				blockSize[j] -= processSize[i];
				break;
			}
		}
	}
	
	cout<<"\nProcess no. \tProcess Size \t Block no.\n";
	
	for(int i=0; i<n; i++)
	{
		cout<<"  "<<i+1<<"\t\t  "<<processSize[i]<<"\t\t  ";
		if(allocation[i] != -1)
			cout<<allocation[i] + 1;
		else
			cout<<"Not Allocated";
		cout<<endl;
	}
	
}



int main()
{
	int blockSize[] = {100, 500, 200, 300, 600};
	int processSize[] = {212, 417, 112, 426};
	int m = sizeof(blockSize)/sizeof(blockSize[0]);
	int n = sizeof(processSize)/sizeof(processSize[0]);
	firstFit(blockSize, m, processSize, n);
	return 0;
}
