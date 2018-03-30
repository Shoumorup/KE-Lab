#include<bits/stdc++.h>
using namespace std;

map<vector<int>,int>m1;
map<vector<int>,int>m2;
map<vector<int>,int>global;
map<int,vector<int> >database;

bool isInm1(vector<int>& s,map<vector<int>,int>& m1)
{
	for(map<vector<int>,int>::iterator it=m1.begin();it!=m1.end();it++)
	{
		int f=0;
		for(int i=0;i<it->first.size();i++)
		{
		  if(s[i]!=it->first[i])
		  {
		  	f=1; break;
		  }
		}
		if(!f) return true;
	}
	return false;
}

void apriori(vector<int>& v1,vector<bool>& v2,map<vector<int>,int>& m1,int k,int n,bool& flag)
{
  if(n==0)
  {
  	vector<int>s; s.push_back(-1);
  	for(int i=0;i<v1.size();i++)
  	{
  		if(v2[i]) s.push_back(v1[i]);
  	}
  	if(s.size()==k+1 && !isInm1(s,m1)) flag=false;
  	return;
  }
  v2[n]=true;
  apriori(v1,v2,m1,k,n-1,flag);
  v2[n]=false;
  apriori(v1,v2,m1,k,n-1,flag);
}

void check(map<vector<int>,int>& m1,map<vector<int>,int>& m2,int k)
{
	for(map<vector<int>,int>::iterator it=m2.begin();it!=m2.end();it++)
	{
	  vector<int> v1=it->first;
	  vector<bool> v2(v1.size(),false);
	  bool flag=true;
	  apriori(v1,v2,m1,k,v1.size()-1,flag);
	  if(!flag)	m2.erase(it);
	}
}

void callapriori(map<int,vector<int> >&support,map<vector<int>,int>&m1,int threshold,int z)
{
	int k=1;
	cout<<"This is for Partition: "<<z<<endl;
	while(true)
	{
		if(m1.empty()) break;
		cout<<"C"<<k<<" is: "<<endl;

		for(map<vector<int>,int>::iterator it=m1.begin();it!=m1.end();it++)
	    {
		  for(int s=0;s<it->first.size();s++) cout<<it->first[s]<<" ";
		  cout<<it->second<<endl;
	    }

		cout<<"................................................."<<endl;

	   	for(map<vector<int>,int>::iterator it=m1.begin();it!=m1.end();)
	   	{
	   		if(it->second<threshold) it=m1.erase(it);
	   		else ++it;
	   	}//Generating L1
		if(m1.empty()) break;
	    m2.clear();

	    cout<<"L"<<k<<" is: "<<endl;
	    for(map<vector<int>,int>::iterator it=m1.begin();it!=m1.end();it++)
	    {
		  for(int s=0;s<it->first.size();s++) cout<<it->first[s]<<" ";
		  cout<<it->second<<endl;
	    }
    	cout<<"--------------------------------------------------"<<endl;
	   	//Generating the Item sets by comparing the first 'k' elements in my map's vector.
	  	for(map<vector<int>,int>::iterator it=m1.begin();it!=m1.end();it++)
	   	{
	   	   map<vector<int>,int>::iterator it2=it; it2++;
	   	   while(it2!=m1.end())
		   {
		   	 int j;
		   	 vector<int>p; p.clear();
		   	 for(j=0;j<k;j++)
		   	 {
		   	 	if(it->first[j]!=it2->first[j]) break;
		   	 	else p.push_back(it->first[j]);
		   	 }
		   	 if(j==k)
		   	 {
		   	 	p.push_back(it->first[j]); p.push_back(it2->first[j]);
		   	 	m2[p]=0;
		   	 }
		   	 ++it2;
		   }
	   	}
		if(m2.empty()) break;//Terminating Condition for the Apriori
		//Pruning Stage -Generate Subsets of size k-1 for each entry in m2 and check if it is available in m1.
	    // After this we will get pruned C2. Now update it with support counts.
	    check(m1,m2,k);
	    ++k;
		//C2 generated and stored in m2 without support counts.
		if(m2.empty()) break;

		for(map<vector<int>,int>::iterator it=m2.begin();it!=m2.end();it++)
	   	{
	   	   int cnt=0,s;
	   	   for(map<int,vector<int> >::iterator ip=support.begin();ip!=support.end();ip++)
	   	   {
	   	   	 int c=0;
	   	   	 for(int x=0;x<ip->second.size();x++)
	   	   	 {
	   	   	 	for(int y=0;y<it->first.size();y++)
	   	   	 	{
	   	   	 		if(ip->second[x]==it->first[y])
					{
						++c; break;
	   	   	 		}
	   	   	 	}
	   	   	 	if(c==it->first.size()-1)
	   	   	 	{
	   	   	 		++cnt; break;
	   	   	 	}
	   	   	 }
	   	   }
	   	   it->second=cnt;
	   	}

	  	//Generated C2
	   	swap(m1,m2);//Now do it until the end
	}
	//Store m1 in global itemset
	for(map<vector<int>,int>::iterator it=m1.begin();it!=m1.end();it++)
	{
		vector<int>w; w.clear();
		for(int s=0;s<it->first.size();s++) w.push_back(it->first[s]);
	    global[w]+=it->second;
	}
	cout<<endl<<endl<<endl;
}

int main()
{
	fstream fin;
	fin.open("Transaction.txt");
	map<int,vector<int> >support;
	database.clear();
	support.clear();
	global.clear();
	m1.clear();
	m2.clear();
	int threshold=2,z=0;//Support Count for my Entire Program
	//Number of Partitions of the Database--Call Apriori for Each partition.
	string ch="";
	getline(fin,ch); int a=0;
	while(fin)
	{
		ch="";
		getline(fin,ch);
		string tmp="",t="";
		int i=1;
		while(i<ch.length() && ch.at(i)!=' ')
		{
			tmp+=ch.at(i);
			++i;
		}
		i=i+5;
		for(;i<ch.length();i++)
		{
			char c=ch.at(i);
			if(c!=' ') t+=c;
			else
			{
				support[atoi(tmp.c_str())].push_back(atoi(t.c_str()));
				database[atoi(tmp.c_str())].push_back(atoi(t.c_str()));
				vector<int>st;
				st.push_back(-1);
				st.push_back(atoi(t.c_str()));
				m1[st]++;
				t="";
			}
		}
		++a; //Reading a line
		if(a==5)//No. of transactions in a partition.
		{
		  ++z;
		  callapriori(support,m1,(threshold/2),z);
		  a=0;
		  support.clear();
		  m1.clear();
		  m2.clear();
		}
	}
	//Second pass over the Database to see if they are frequent or not.

	for(map<vector<int>,int>::iterator it=global.begin();it!=global.end();it++)
	{
	   	int cnt=0,s;
	   	for(map<int,vector<int> >::iterator ip=database.begin();ip!=database.end();ip++)
	   	{
	   	    int c=0;
	   	   	for(int x=0;x<ip->second.size();x++)
	   	   	{
	   	   	 	for(int y=0;y<it->first.size();y++)
	   	   	    {
	   	   	 		if(ip->second[x]==it->first[y])
					{
						++c; break;
	   	   	 		}
	   	   	 	}
	   	   	 	if(c==it->first.size()-1)
	   	   	 	{
	   	   	 		++cnt; break;
	   	   	 	}
	   	   	}
	   	}
	   it->second=cnt;
	}

	for(map<vector<int>,int>::iterator it=global.begin();it!=global.end();it++)
	{
	   	if(it->second<threshold) m1.erase(it);

	}
	cout<<"The global itemset is: "<<endl;
	for(map<vector<int>,int>::iterator it=global.begin();it!=global.end();it++)
	{
		for(int s=0;s<it->first.size();s++) cout<<it->first[s]<<" ";
		cout<<it->second<<endl;
	}
	fin.close();
	return 0;
}
