#include<bits/stdc++.h>
using namespace std;

string to_string(int x)
{
  string p="";
  for(int i=x;i>0;i=i/10)  	p+=('0'+(i%10));
  reverse(p.begin(),p.end());
  return p;
}

int main()
{
	fstream f1,f2;
	f1.open("DirtyInput.txt");
	int sum[3],rows[3];
	memset(sum,0,sizeof(sum));
	memset(rows,0,sizeof(rows));
	string s;
	while(f1)
	{
		stringstream ss;
		getline(f1,s);
		ss<<s; int cnt=0;
		string x="";
		while(ss>>x)
		{		
			if(x!="$" && cnt!=0)
			{
				sum[cnt-1]+=atoi(x.c_str()); rows[cnt-1]++;
			}			
		    ++cnt;
		}		
	}
	for(int i=0;i<3;i++) sum[i]/=rows[i];
	f1.close(); f1.open("DirtyInput.txt"); string write="";
	while(f1)
	{
    	stringstream ss;
		getline(f1,s);
		ss<<s; int cnt=0;
		string x="";
		while(ss>>x)
		{
			if(x=="$")
			{
			    if(cnt==0)	write+="N/A ";
			    else write+=to_string(sum[cnt-1])+" ";			    
			}
			else 	write+=x+" ";		
		    ++cnt;
		}
	    write+="$";
		s="";
	}
	f1.close(); f1.open("DirtyInput.txt"); 
	for(int i=0;i<write.length();i++)
	{
		if(write[i]=='$') f1<<endl;
		else f1<<write[i];
	}
	f1.close(); 
	return 0;
}
