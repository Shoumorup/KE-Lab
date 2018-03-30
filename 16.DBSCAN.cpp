#include<bits/stdc++.h>
#define e 4
#define mini 5
using namespace std;
vector<pair<int,int> >data;
set<pair<int,int> >present;

bool allvisited(vector<bool>& v)
{
	for(int i=0;i<v.size();i++)
	{
		if(!v[i])  return false;
	}
	return true;
}

double dist(pair<int,int> a,pair<int,int> b)
{
	return ((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}

int main()
{
	fstream fin;
	fin.open("DBSCANInput.txt");
	srand(time(NULL));
	string ch="";
	while(fin)
	{
		int x,y;
		getline(fin,ch);
		int i=0;
		ch+=' '; string tmp="";
		while(i<ch.length() && ch[i]!=' ') tmp+=ch[i++];
		x=atoi(tmp.c_str()); tmp="";
		while(i<ch.length()) tmp+=ch[i++];
		y=atoi(tmp.c_str());
		data.push_back(make_pair(x,y));	//Data points now stored.
	}
	data.pop_back();//1. Difficulty in reading the file.
	
	vector<vector<pair<int,int> > >cluster; cluster.clear();
	vector<bool>visit(data.size(),false);//All marked unvisited.
	while(!allvisited(visit))
	{
	  	//Choose a randomly unvisited data point
	  	int j; vector<pair<int,int> >store;
	  	while(true)
	  	{
	  	  j=rand()%data.size();
		  if(!visit[j]) break;
		}
		//Check if it is a core point
		visit[j]=true;
		int cnt=0; vector<bool>x(data.size(),false);
		for(int i=0;i<data.size();i++)
		{
			if(j==i) continue; //Ignore that same point
			double d=dist(data[j],data[i]);
			if(d<=e)//Within Epsilon Neighbourhood
			{
				++cnt; x[i]=true;
			}
		}//Checking to see if noise or can be considered
		vector<pair<pair<int,int>,int> >cand;
		if(cnt>=mini)//We have got a core point
		{
			store.push_back(data[j]);
			present.insert(data[j]);
			//Push in all the points to generate the  candidate set
			for(int k=0;k<x.size();k++)
			{
			  if(x[k])	cand.push_back(make_pair(data[k],k));
			}

			for(int s=0;s<cand.size();s++)
		    {
		    	if(!visit[cand[s].second])
				{
				   visit[cand[s].second]=true;
				   //If the epsilon neighbourhood of this point has at least mini points,add them to cand
				   int c=0; vector<bool>y(data.size(),false);
		           for(int i=0;i<data.size();i++)
		           {
			         if(cand[s].second==i) continue; //Ignore that same point
			         double d=dist(cand[s].first,data[i]);
			         if(d<=e)//Within Epsilon Neighbourhood
			         {
				       ++c; y[i]=true;
			         }
				   }
				   if(c>=mini)
				   {
				   	for(int g=0;g<y.size();g++)
				   	{
				   	  if(y[g]) cand.push_back(make_pair(data[g],g));
					}
				   }
				}
		        if(present.find(cand[s].first)==present.end())//Not present in any other cluster
				{
					store.push_back(cand[s].first);
					present.insert(cand[s].first);
			    }
			}
			cluster.push_back(store);
		}
	}
	cout<<"Clusters are: "<<endl;
	for(int i=0;i<cluster.size();i++)
	{
		for(int j=0;j<cluster[i].size();i++)
		{
			cout<<"("<<cluster[i][j].first<<","<<cluster[i][j].second<<")";
		}
		cout<<endl;
	}
	fin.close();
	return 0;
}
