#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int ab;				// holds response time

struct PROCESS			//PROCESS structure
{
	string process;		// process ID
	int arrival;		// process Arrival Time
	int burst;		// process CPU Burst Time
	int completion;		// process Completion Time
	int turnaround;		// process Turn Around Time
	int waiting;		// process Waiting Time
};




bool compare(PROCESS a, PROCESS b)		// returns Ascending or Descending Sort
{
	return a.arrival < b.arrival;		// sorts according to Arrival Time
}

bool compare2(PROCESS a, PROCESS b)		// returns Ascending or Descending Sort
{
	return a.burst < b.burst && a.arrival <= ab;	// sorts according to CPU Burst Time & Arrival Time
}




int main()
{
	int n, i, j;
	int total_tat=0, total_wt=0;

	struct PROCESS p[] = {{"1",0,10}, {"2",1,5}, {"3",2,8}};		// creates process pool
	n = sizeof(p)/sizeof(p[0]);						// calculates no. of processes

	sort(p, p+n, compare);				// sorts PROCESS structure

	// initial values
	p[0].completion = p[0].burst + p[0].arrival;
	p[0].turnaround = p[0].completion - p[0].arrival;
	p[0].waiting = p[0].turnaround - p[0].burst;

	for(i=1;i<n;i++)
	{
		ab = p[i-1].completion;			
		// 'ab' holds response time of PROCESS[i]
		// i.e PROCESS[i-1].CT  (Completion Time of previous process)
										
		sort(p+i, p+n, compare2);		// sorts PROCESS structure
		
		if(p[i-1].completion < p[i].arrival)	
		{
			/* when the Arrival Time of current process is (greater than) Completion Time of the previous process */
			
			/* |     P1(6)    | <-idle state->|    P2(3)    |
			   |______________|_______________|_____________|  
			   |              |               |             |
			  0              (6)             (8)           11 
			  
			  P1 - arrival(0), burst(6), completion(6)
			  P2 - arrival(8), burst(3), completion(?)
			  
			  here P1(completion) < P2(arrival)
			*/
			
			p[i].completion = p[i].burst + p[i].arrival;
			/* CT = First Response + CPU Burst Time
				  = Arrival Time + CPU Burst Time
			*/
		}
		else
		{
			/* when the Arrival Time of current process is (less than) Completion Time of the previous process */
			p[i].completion = p[i-1].completion + p[i].burst;
			/* CT = First response + CPU Burst Time */
		}
		
		p[i].turnaround = p[i].completion - p[i].arrival;
		// for SJF : TAT = Completion Time - Arrival Time
		
		p[i].waiting = p[i].turnaround - p[i].burst;
		// for SJF : WT = First Response - Arrival Time
		// i.e WT = Turn Around Time - CPU Burst Time
	}


	cout<<"PROCESS\t BURST TIME\t ARRIVAL TIME\t WAITING TIME\t TURN AROUND TIME"<<endl;
	for(i=0;i<n;i++)				//display loop
	{
		total_wt += p[i].waiting;		//total WT
		total_tat += p[i].turnaround;		//total TAT
		cout<<" "<<p[i].process;		//process ID[i]
		cout<<"\t  "<<p[i].burst;		//CPU burst time[i]
		cout<<"\t\t  "<<p[i].arrival;		//arrival time[i]
		cout<<"\t\t  "<<p[i].waiting;		//WT[i]
		cout<<"\t\t  "<<p[i].turnaround;	//TAT[i]
		cout<<"\n";
	}
	
	
	float avt, avw;						
	avt = (float)total_tat/(float)n;		//average TAT
	avw = (float)total_wt/(float)n;			//average WT
	cout<<"\n Average Waitng Time : "<<avw;
	cout<<"\n Average Turn Around Time : "<<avt;
	
	return 0;
}
