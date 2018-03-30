#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T,item=20;
ofstream f;
	f.open("Transaction.txt");
	cout<<"Enter the number of Transactions "<<endl;
	cin>>T;
	srand(time(NULL));
	set<int>s;
	int j=1;
	f<<"TID    "<<"Items"<<endl;
	while(j<=T)
	{
	  int x=rand()%item+2;
	  f<<"T"<<j*10<<"     "; ++j;
	  for(int i=0;i<x;i++)
	  {
	  	int p=rand()%item;
	  	if(s.find(p)!=s.end());
	  	else s.insert(p);	  	
	  }
	  set<int>:: iterator it;
	  for(it=s.begin();it!=s.end();it++) f<<*it<<" ";
	  f<<endl;
	  s.clear(); 	
	}
	f.close();
	return 0;
}
