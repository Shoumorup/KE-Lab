#include<bits/stdc++.h>
using namespace std;
int n_of_attr=0;//Stores number of attributes 
map<string,pair<double,double> >classes;//Second Column stores count and probability

int main()
{
	fstream fin;
	fin.open("Database.txt");
	string ch="";
	getline(fin,ch);
	int i=0;
	while(i<ch.length())
	{
		if(ch[i]==' ') ++n_of_attr;
		++i;
	} //Checking to store number of attributes
	double sz=0.0;//Stores size of database
	
	vector<map<pair<string,string>,double> >store(n_of_attr);
	while(fin)
	{
		if(sz==14) break;//Problem with File. Don't know why!
	   	getline(fin,ch); ++sz;
	    ch+=' ';  
		stringstream st; string s="";
	    st<<ch; 
	    while(st>>s);//'s' now stores the class of the tuple
	    stringstream ss;
		ss<<ch; string t=""; int x=0;
		while(x<n_of_attr)
		{
		    ss>>t;
		    //store[x] is a map
		    (store[x])[make_pair(t,s)]++;
		    ++x;
		}
		classes[s].first++; 
	}
	cout<<"Counts stored for each combination as follows: "<<endl;
	for(int j=0;j<n_of_attr;j++)
	{
		for(map<pair<string,string>,double>::iterator it=store[j].begin();it!=store[j].end();it++)
		{
			cout<<(it->first).first<<" "<<(it->first).second<<" "<<it->second<<endl;
		}
		cout<<endl;
	}
	
	for(map<string,pair<double,double> >::iterator it=classes.begin();it!=classes.end();it++) 
	{
	  (it->second).second=(it->second).first/sz;
	  cout<<"Probability of class "<<it->first<<" "<<(it->second).second<<" with count "<<(it->second).first<<endl;	
	}
	
	while(true)//2. Check why this is happening!
	{
		cout<<"Enter a tuple. "<<endl;
		string input;
		cin>>input;
		if(input=="-1") break; 
		double maxi=INT_MIN; string res="";
		for(map<string,pair<double,double> >::iterator it=classes.begin();it!=classes.end();it++) 
		{
			stringstream ss;
		    ss<<input; string a=""; int d=0;  double prod=1.0;
			while(ss>>a)
			{
				prod*=((store[d])[make_pair(a,it->first)]/(classes[it->first]).first);
				++d;
			}
			if(prod>maxi)
			{
				prod=maxi;
				res=it->first;
			}	
		}
		cout<<"Tuple belongs to class "<<res<<endl;
	}	
	fin.close();
	return 0;
}
