#include<bits/stdc++.h>
using namespace std;

int main()
{
	fstream fin;
	fin.open("Transaction.txt");
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
		cout<<it->first<<"--> ";
		for(vector<string>:: iterator itt=it->second.begin();itt!=it->second.end();itt++) cout<<*itt<<" ";
		cout<<endl;
	}
	fin.close();
    return 0;
}
