#include<bits/stdc++.h>
#define n 30
#define error 0.0000001
using namespace std;

struct points
{
	double x,y;
};

void generate(vector<points>& store)
{
	points p;
	for(int i=1;i<=30;i++) 
	{
	  p.x=(rand())%1000;
	  p.y=(rand())%1000;
	  store.push_back(p);	
	}	
}

double dist(points p,points q)
{
	return ( ((p.x-q.x)*(p.x-q.x))+((p.y-q.y)*(p.y-q.y)) );
}

bool mycomp(points p1,points p2)
{
	if(p1.y==p2.y) return (p1.x<p2.x);
	return (p1.y<p2.y);	
}

bool timeToBreak(vector<points>& a,vector<points>& b)
{
	for(int i=0;i<a.size();i++)
	{
		if(abs(a[i].x-b[i].x)>error) return false;
		else if(abs(a[i].y-b[i].y)>error) return false;
	}
	return true;
}

void calc(vector<points>& store,int k)
{
	vector<points>centres; vector<points>newcentres;
	for(int i=0;i<k;i++) centres.push_back(store[i]);//Assigned the first k centres.
	
	while(true)
	{
		vector<vector<points> >cluster(k);
		cluster.clear();
		for(int i=0;i<store.size();i++)
		{
			double mini=INT_MAX,pos=0;
			for(int j=0;j<k;j++)
			{
				double x=dist(store[i],centres[j]);
				if(x<mini) 
				{
					mini=x; pos=j;
				}
			}
			cluster[pos].push_back(store[i]);
		}
		//Find the mean of all clusters
		newcentres.clear();
		for(int i=0;i<k;i++)
		{
			double sumX=0.0,sumY=0.0;
			for(int j=0;j<cluster[i].size();j++)
			{
			   sumX+=cluster[i][j].x;
			   sumY+=cluster[i][j].y;	
			}
			sumX=sumX/(double)(cluster[i].size());
			sumY=sumY/(double)(cluster[i].size());
			points t;
			t.x=sumX; t.y=sumY;
			newcentres.push_back(t);
		}
		sort(centres.begin(),centres.end(),mycomp);
		sort(newcentres.begin(),newcentres.end(),mycomp);
		
		if(timeToBreak(centres,newcentres)) break;
		centres=newcentres;
		
		cout<<"The centres for the current cluster will be :"<<endl;
		for(int a=0;a<centres.size();a++) cout<<centres[a].x<<" , "<<centres[a].y<<endl;
		cout<<endl;		 
	}	
	
	cout<<"Final cluster centres are: "<<endl;
	for(int a=0;a<newcentres.size();a++) cout<<newcentres[a].x<<" , "<<newcentres[a].y<<endl;
}

int main()
{
  srand(time(NULL));
  vector<points>store;
  generate(store);	
  
  int k;
  cin>>k;
  calc(store,k);
  return  0;
}
