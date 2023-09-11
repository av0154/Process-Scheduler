#include<conio.h>
#include<stdio.h>
#include <iostream>
using namespace std;
class cpuschedule
{
    int n,Bu[20];
    float Twt,Awt,A[10],Wt[10],w;
public:
    //Getting the No of processes & burst time
    void Getdata();
    //First come First served Algorithm
    void Fcfs();
    //Shortest job First Algorithm
    void Sjf();
    //Shortest job First Algorithm with Preemption
    void SjfP();
    //Shortest job First Algorithm with NonPreemption
    void SjfNp();
    //Round Robin Algorithm
    void RoundRobin();
    //Priority Algorithm
    void Priority();
};
// Implementation file for Cpu scheduling
//Getting no of processes and Burst time
void cpuschedule::Getdata()
{
    int i;
    cout<<"\nEnter the no of processes:";
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cout<<"\nEnter The BurstTime for Process p"<<i<<"=  ";
        cin>>Bu[i];
    }
}


//First come First served Algorithm
void cpuschedule::Fcfs()
{
    int i,B[10];
    Twt=0.0;
    for(i=1;i<=n;i++)
    {
        B[i]=Bu[i];
        cout<<"\nBurst time for process p"<<i<<"=   ";
        cout<<"\n"<<B[i];
    }
    Wt[1]=0;
    for(i=2;i<=n;i++)
    {
        Wt[i]=B[i-1]+Wt[i-1];
    }


    //Calculating Average Weighting Time
    for(i=1;i<=n;i++)
        Twt=Twt+Wt[i];
    Awt=Twt/n;
    cout<<"\nTotal Waiting Time="<<Twt;
    cout<<"\nAverage Waiting Time="<<Awt<<"";
}


//Shortest job First Algorithm
void cpuschedule::Sjf()
{
    int i,j,temp,B[10];
    Twt=0.0;
    for(i=1;i<=n;i++)
    {
        B[i]=Bu[i];
        cout<<"\nBurst time for process p"<<i<<"=   ";
        cout<<"\n"<<B[i];
    }
    for(i=n;i>=1;i--)
    {
        for(j=1;j<=n;j++)
        {
            if(B[j-1]>B[j])
            {
                temp=B[j-1];
                B[j-1]=B[j];
                B[j]=temp;
            }
        }
    }


    Wt[1]=0;
    for(i=2;i<=n;i++)
    {
        Wt[i]=B[i-1]+Wt[i-1];
    }
    //calculating Average Weighting Time
    for(i=1;i<=n;i++)
        Twt=Twt+Wt[i];
    Awt=Twt/n;
    cout<<"\nTotal Waiting Time="<<Twt;
    cout<<"\nAverage Waiting Time="<<Awt<<"";
}
//Priority Algorithm


void cpuschedule::Priority()
{
    int i,B[10],P[10],j;
    w=0.0;
    int max;
    Twt=0.0;
    max=1;
    for(i=1;i<=n;i++)
    {
        B[i]=Bu[i];
        cout<<"\nBurst time for process p"<<i<<"=   ";
        cout<<B[i];
        cout<<"\nEnter the priority for process P"<<i<<"=   ";
        cin>>P[i];
        if(max<P[i])
            max=P[i];
    }
    j=1;
    while(j<=max)
    {
        i=1;
        while(i<=n)
        {
            if(P[i]==j)
            {
                Wt[i]=w;
                w=w+B[i];
            }
            i++;
        }
        j++;
    }


    //calculating average weighting Time
    for(i=1;i<=n;i++)
        Twt=Twt+Wt[i];
    Awt=Twt/n;
    cout<<"\nTotal Waiting Time="<<Twt<<"";
    cout<<"\nAverage Waiting Time="<<Awt<<"";
}
//Round Robin Algorithm
void cpuschedule::RoundRobin()
{


    int i,j,tq,k,B[10],Rrobin[10][10],count[10];
    int max=0;
    int m;
    Twt=0.0;
    for(i=1;i<=n;i++)
    {
        B[i]=Bu[i];
        cout<<"\nBurst time for process p"<<i<<"=   ";
        cout<<B[i];
        if(max<B[i])
            max=B[i];
        Wt[i]=0;
    }
    cout<<"\nEnter the Time Quantum=";
    cin>>tq;
    //TO find the dimension of the Rrobin array
    m=max/tq+1;


    //initializing Rrobin array
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            Rrobin[i][j]=0;
        }
    }
    //placing value in the Rrobin array
    i=1;
    while(i<=n)
    {
        j=1;
        while(B[i]>0)
        {
            if(B[i]>=tq)
            {
                B[i]=B[i]-tq;
                Rrobin[i][j]=tq;
                j++;
            }
            else
            {
                Rrobin[i][j]=B[i];
                B[i]=0;
                j++;
            }
        }
        count[i]=j-1;
        i++;
    }


    cout<<"\nDisplay";
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            cout<<"\nRr["<<i<<","<<j<<"]="<<Rrobin[i][j];
            cout<<"\n   ";
        }
        cout<<"\n";
    }
    //calculating weighting time
    int x=1;
    i=1;
    while(x<=n)
    {
        for(int a=1;a<x;a++)
        {
            Wt[x]=Wt[x]+Rrobin[a][i];
        }
        i=1;
        int z=x;
        j=count[z];
        k=1;
        while(k<=j-1)
        {
            if(i==n+1)
            {
                i=1;
                k++;
            }
            else
            {
                if(i!=z)
                {
                    Wt[z]=Wt[z]+Rrobin[i][k];
                }
                i++;
            }
        }
        x++;
    }
    for(i=1;i<=n;i++)
        cout<<"\nWaiting Time for process P"<<i<<"="<<Wt[i];


    //calculating Average Weighting Time
    for(i=1;i<=n;i++)
        Twt=Twt+Wt[i];
    Awt=Twt/n;
    cout<<"\nTotal Waiting Time="<<Twt;
    cout<<"\nAverage Waiting Time="<<Awt<<"\n\n\n\n\n";
}


//Application file for cpu Scheduling


int main()
{
    int ch,cho;
    cpuschedule c;
    do
    {
        cout<<"\n\n\n\n\n\n\nMENU";
        cout<<"\n1.Getting BurstTime";
        cout<<"\n2.FirstComeFirstServed";
        cout<<"\n3.ShortestJobFirst";
        cout<<"\n4.RoundRobin";
        cout<<"\n5.Priority";
        cout<<"\n6.EXIT";
        cout<<"\nEnter your choice:";
        cin>>ch;
        switch(ch)
        {
        case 1:
            c.Getdata();
            break;
        case 2:
            cout<<"\nFIRST COME FIRST SERVED SCHEDULING";
            c.Fcfs();
            break;
        case 3:
            cout<<"\nSHORTEST JOB FIRST SCHEDULING";
                cout<<"\n1.SJF";
                c.Sjf();
               
            break;
        case 4:
            cout<<"\nROUND ROBIN SCHEDULING";
            c.RoundRobin();
            break;
        case 5:
            cout<<"\nPRIORITY SCHEDULING";
            c.Priority();
            break;
        case 6:
            break;
        }
    }while(ch<=5);
return 0;
}        
