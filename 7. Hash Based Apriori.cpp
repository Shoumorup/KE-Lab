#include<bits/stdc++.h>
using namespace std;

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

int main()
{
	fstream fin;
	fin.open("Transaction.txt");
	map<int,vector<int> >support;
	map<vector<int>,int>m1; m1.clear();
	map<vector<int>,int>m2; m2.clear();
	map<int,vector<pair<int,int> > >hash;
	int threshold=2;//Support Count for my Entire Program
	string ch="";
	getline(fin,ch); 
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
		for(i=8;i<ch.length();i++)
		{
			char c=ch.at(i);
			if(c!=' ') t+=c;
			else 
			{
				support[atoi(tmp.c_str())].push_back(atoi(t.c_str())); 
				t="";			
			}
		}		
	}
	
	//Hashing
	for(map<int,vector<int> >::iterator it=support.begin();it!=support.end();it++)	
	{
		for(int i=0;i<it->second.size();i++)
		{
			for(int j=i+1;j<it->second.size();j++)
			{
				int h=(it->second[i]*10+it->second[j])%7;
				hash[h].push_back(make_pair(it->second[i],it->second[j]));			
			}
		}
	}
	
    //Prune now from the hash.
	m1.clear();
	for(map<int,vector<pair<int,int> > >::iterator it=hash.begin();it!=hash.end();it++)
	{
		if(it->second.size()<threshold) hash.erase(it);
		else
		{
		  for(int i=0;i<it->second.size();i++)
		  {
		    int cnt=0;	
		    for(map<int,vector<int> >::iterator itt=support.begin();itt!=support.end();itt++)
		    {
		       int f=0;
		  	   for(vector<int>::iterator s=itt->second.begin();s!=itt->second.end();s++)
		  	   {
		  	   	 if(*s==it->second[i].first || *s==it->second[i].second) ++f;
		  	   }
		  	   if(f==2) ++cnt;
		    }
		    
			if(cnt>=threshold) 
			{
				vector<int>l; l.push_back(-1);
				l.push_back(it->second[i].first); 
				l.push_back(it->second[i].second);
				m1[l]=cnt;
			}	
		 }
	   }
	}
	int k=2;
	while(true)
	{
	   	if(m1.empty()) break;    
		if(k!=2)
		{
			cout<<"C"<<k<<" is: "<<endl;
			for(map<vector<int>,int>::iterator it=m1.begin();it!=m1.end();it++)	
	        {
		      for(int s=0;s<it->first.size();s++) cout<<it->first[s]<<" ";
		      cout<<it->second<<endl;
	        }	    
		    cout<<"................................................."<<endl;
		
	   		for(map<vector<int>,int>::iterator it=m1.begin();it!=m1.end();it++)
	   		{
	   			if(it->second<threshold) m1.erase(it);
	   		}//Generating L1
			if(m1.empty()) break; 
	    }
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
	fin.close();
}
