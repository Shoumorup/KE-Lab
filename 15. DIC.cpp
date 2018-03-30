#include<bits/stdc++.h>
#define threshold 2
#define M 5
#define s_ize 15
#define map_loop(it,m) for(map<vector<int>,pair<int,int> >::iterator (it)=(m).begin();(it)!=(m).end();(it)++)
using namespace std;
int n_of=s_ize/M;//Number of partitions.
void update_count(map<vector<int>,pair<int,int> >& m1,map<int,vector<int> >& support,int pos)
{
	map_loop(it,m1)
  	{
  	  map<int,vector<int> >::iterator ip=support.begin();
	  for(int i=1;i<=pos*M;i++) ip++;
  	  int cnt=0,k=0;
	  for(;k<M;ip++,k++)
	  {
	  	int c=0;
		for(int x=0;x<it->first.size();x++)//For each itemset in dc
		{
			for(int y=0;y<ip->second.size();y++)
			{
				if(ip->second[y]==it->first[x])
				{
				   ++c; break;
				}
			}
		}
		if(c==it->first.size()) ++cnt;
	  }
	 (it->second).first+=cnt;
    }
}

void move_to_solid(map<vector<int>,pair<int,int> >& src,map<vector<int>,pair<int,int> >& dest)
{
  	for(map<vector<int>,pair<int,int> >::iterator it=src.begin();it!=src.end();)
  	{
	  if((it->second).second==n_of)
	  {
	  	dest[it->first]=it->second;
	  	it=src.erase(it);
	  }
	  else it++;
	}
}

void check(map<vector<int>,pair<int,int> >&sb,map<vector<int>,pair<int,int> >&db,vector<int>&res,vector<bool>& v2,bool& flag,int i)
{
	if(i==res.size())
	{
		vector<int>p;
		p.clear();
		for(int i=0;i<res.size();i++)
		{
			if(v2[i]) p.push_back(res[i]);
		}
		if(p.size()==0 || p.size()==res.size()) return;
		if(sb.find(p)==sb.end() && db.find(p)==db.end()) flag=false;
		return;
	}
	v2[i]=true;
	check(sb,db,res,v2,flag,i+1);
	v2[i]=false;
	check(sb,db,res,v2,flag,i+1);
}

int main()
{
  fstream fin;
  fin.open("Transaction.txt");
  map<int,vector<int> >support;
  map<vector<int>,pair<int,int> >sb;//Confirmed Frequent
  map<vector<int>,pair<int,int> >sc;//Confirmed Infrequent
  map<vector<int>,pair<int,int> >db;//Suspected Frequent
  map<vector<int>,pair<int,int> >dc;//Suspected Infrequent

  vector<int>p; p.push_back(-1);
  sb[p]=make_pair(s_ize,0);//Pushing in the empty set
  //Pushing in all the 1-itemsets into dc
  for(int i=0;i<5;i++)
  {
  	p.clear();
  	p.push_back(i+1);
    dc[p]=make_pair(0,0);
  }
  cout<<"DC initially is: "<<endl;
  for(map<vector<int>,pair<int,int> >::iterator it=dc.begin();it!=dc.end();it++)
  {
      for(int i=0;i<it->first.size();i++) cout<<it->first[i]<<" ";
      cout<<"-> "<<(it->second).first<<" "<<(it->second).second<<endl;
  }
  //For simplicity, read whole DB into map support first. //2. Change this later
  string ch="";
  getline(fin,ch); support.clear();
  while(fin)
  {
    string tmp="",t="";
    getline(fin,ch);
    ch+=' ';
	int i=1;
	while(i<ch.length() && ch[i]!=' ') tmp+=ch[i++];
	i=i+5;
	while(i<ch.length())
	{
		 if(ch[i]!=' ')t+=ch[i];
		 else
		 {
		 	support[atoi(tmp.c_str())].push_back(atoi(t.c_str()));
		 	t="";
		 }
		 ++i;
	}
  }
  int pos=0;//Keeps track of the current partition.
  while(!db.empty() || !dc.empty()) //1. Check this Condition
  {
  	//Increment count values for all itemsets in db and dc
  	update_count(dc,support,pos);
  	update_count(db,support,pos);

  	cout<<"---------------------------"<<endl;
  	cout<<"Pos is now: "<<pos<<endl<<endl;
  	cout<<"Count updated DC is now: "<<endl;
    for(map<vector<int>,pair<int,int> >::iterator it=dc.begin();it!=dc.end();it++)
    {
      for(int i=0;i<it->first.size();i++) cout<<it->first[i]<<" ";
      cout<<"-> "<<(it->second).first<<" "<<(it->second).second<<endl;
      (it->second).second++;
    }
    cout<<endl;


    if(db.empty()) cout<<"DB is empty"<<endl<<endl;
    else
    {
       cout<<"Count updated DB is now: "<<endl;
       for(map<vector<int>,pair<int,int> >::iterator it=db.begin();it!=db.end();it++)
       {
         for(int i=0;i<it->first.size();i++) cout<<it->first[i]<<" ";
         cout<<"-> "<<(it->second).first<<" "<<(it->second).second<<endl;
         (it->second).second++;
       }
       cout<<endl<<endl;
    }
    //Check if there is any itemset that is having count more than threshold in dc. Move it to db
    map<vector<int>,pair<int,int> >temp=dc;
    dc.clear();
    for(map<vector<int>,pair<int,int> >::iterator it=temp.begin();it!=temp.end();)
    {
        if((it->second).first>=threshold)
    	{
    		db[it->first]=it->second;
    		vector<int>res=it->first,tmp=it->first;
    		it=temp.erase(it);
    		//Do the superset thing here.
    		vector<bool>v1(5,false);
    		for(int i=0;i<res.size();i++) v1[res[i]-1]=true;
    		for(int i=0;i<5;i++)
    		{
    		    res=tmp;
    			if(!v1[i])
    			{
    				res.push_back(i+1);//Immediate superset created.
    				sort(res.begin(),res.end());
    				//Check if all subsets of immediate superset is in sb or db
    				bool flag=true;
    				vector<bool>v2(res.size(),false);
    				check(sb,db,res,v2,flag,0);
    				if(flag)//Present in all. So add to dc
    				  dc[res]=make_pair(0,0);
				}
			}
        }
        else
        {
            dc[it->first]=it->second;
            ++it;
        }
	}
	cout<<"After adding the supersets and moving the itemsets from DC to DB"<<endl<<endl;
	cout<<"DC is now: "<<endl;
    for(map<vector<int>,pair<int,int> >::iterator it=dc.begin();it!=dc.end();it++)
    {
         for(int i=0;i<it->first.size();i++) cout<<it->first[i]<<" ";
         cout<<"-> "<<(it->second).first<<" "<<(it->second).second<<endl;
    }


    cout<<endl<<"DB is now: "<<endl;
    for(map<vector<int>,pair<int,int> >::iterator it=db.begin();it!=db.end();it++)
    {
         for(int i=0;i<it->first.size();i++) cout<<it->first[i]<<" ";
         cout<<"-> "<<(it->second).first<<" "<<(it->second).second<<endl;
    }
    cout<<endl<<endl;
    //Check if it reaches where it started in next partition. If so add to solid as counting done.
    move_to_solid(db,sb);
    move_to_solid(dc,sc);

    cout<<"The movements to the solids has been done: "<<endl;
    cout<<"SB is now: "<<endl;
    for(map<vector<int>,pair<int,int> >::iterator it=sb.begin();it!=sb.end();it++)
    {
         for(int i=0;i<it->first.size();i++) cout<<it->first[i]<<" ";
         cout<<"-> "<<(it->second).first<<" "<<(it->second).second<<endl;
    }


    cout<<endl<<"SC is now: "<<endl;
    for(map<vector<int>,pair<int,int> >::iterator it=sc.begin();it!=sc.end();it++)
    {
        for(int i=0;i<it->first.size();i++) cout<<it->first[i]<<" ";
        cout<<"-> "<<(it->second).first<<" "<<(it->second).second<<endl;
    }
    cout<<endl<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

    pos=(pos+1)%n_of;
  }
  cout<<"Frequent itemsets are: "<<endl;
  map_loop(it,sb)
  {
  	for(int i=0;i<it->first.size();i++) cout<<it->first[i]<<" ";
  	cout<<"-> "<<(it->second).first<<endl;
  }
  fin.close();
  return 0;
}
