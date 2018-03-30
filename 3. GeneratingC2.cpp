#include<bits/stdc++.h>
using namespace std;

int main()
{
	fstream fin,fin2;
	fin.open("Transaction.txt");
	fin2.open("Pairs.txt");
	string s="";
	map<int,vector<string> >m;
	m.clear();
	while(fin)
	{
	  getline(fin,s);
	  string tmp="",tmp1="";	
	  for(int i=0;i<s.length();i++)
	  {
	  	char c=s.at(i);
	  	if(c=='T')
	  	{
	  		while(c!=' ')
	  		{
	  		  tmp=tmp+c;	
	  		  ++i;
	  		  c=s.at(i); 
			}
			while(s.at(i)==' ')++i;
		}
		else if(c!=' ') tmp1+=c;
		else 
		{
			tmp1.erase(tmp1.begin(),tmp1.begin()+1);
			int x=atoi(tmp1.c_str());
			m[x].push_back(tmp);
			tmp1="";
		}		
	  }
	  s.clear();	 
	}
	
	for(map<int,vector<string> >:: iterator it=m.begin();it!=m.end();it++)
	{
		map<int,vector<string> >:: iterator itt=it; itt++;
		set<string>s1;
		for(vector<string>:: iterator it1=it->second.begin();it1!=it->second.end();it1++) s1.insert(*it1);
		for(;itt!=m.end();itt++)
		{
			fin2<<" I"<<it->first<<" , "<<"I"<<itt->first<<" ";  int cnt=0;
		    for(vector<string>:: iterator it1=itt->second.begin();it1!=itt->second.end();it1++)
		    {
		    	if(s1.find(*it1)!=s1.end()) ++cnt;		    
			}		   
		    fin2<<cnt<<endl;
		}
		s1.clear();	
	}
	fin2.close();
	fin.close();
    return 0;
}
