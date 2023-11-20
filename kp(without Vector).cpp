#include<iostream>
#include<algorithm>
using namespace std;
# define p 20
struct Node
{
	float weight;
	float profit;
};

bool compare(Node first,Node second)
{
	float profit1=first.profit/first.weight;
	float profit2=second.profit/second.weight;
	if(profit1>profit2)
	{
		return true;	
	}
	return false;	
}

float greedy(int profit[],int weight[],int n,int wt)
{
	float sum;
	float profits =0;
	Node data[4];
	for(int i=0;i<n;i++)
	{
		data[i].profit=profit[i];
		data[i].weight=weight[i];
	}
	sort(data,data+n,compare);
	for(int i=0;i<n;i++)
	{
		if(data[i].weight<= wt)
		{
			wt = wt - data[i].weight;
			profits = profits + data[i].profit;
		}
		else
		{
			profits = profits + (data[i].profit/data[i].weight) * wt;
			break;
		}
	}
	return profits;
}

int dp(int profit[],int weight[],int n,int wt)
{
	int matrix[n][wt + 1];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<= wt;j++)
		{
			if(i==0 || j==0)
			{
				matrix[i][j]=0;
			}
			else
			{
				if(weight[i] <= j)
				{
					matrix[i][j] = max(matrix[i - 1][j],profit[i] + matrix[i - 1][j - weight[i]]);
				}
				else
				{
					matrix[i][j] = matrix[i - 1][j];
				}
			}
		}
	}
	return matrix[n - 1][wt];
}

int main()
{
	int weight[p] ;
    int profit[p] ;
	int n;
	int wt;
	cout<<"enter no of items : \n";
	cin>>n;
	cout<<"enter the knapsack weight : \n";
	cin>>wt;
	cout<<"enter profit : \n";
	for(int i=0;i<n;i++)
	{
		cin>>profit[i];
	}
	cout<<"enter weight : \n";
	for(int i=0;i<n;i++)
	{
		cin>>weight[i];
	}
	float ans1 = greedy(profit,weight,n,wt);
	cout<<"greedy answer = "<<ans1<<endl;
	float ans2 = dp(profit,weight,n,wt);
	cout<<"dp answer = "<<ans2<<endl;
	if(ans1>ans2)
	{
		cout<<"knapsack problem using dynamic programming will be best in this case";
	}
	else
	{
		if(ans2>ans1)
		{
			cout<<"knapsack problem using greedy approch will be best in this case";
		}
		else
		{
			cout<<"both will be optimal";
		}
	}
}
