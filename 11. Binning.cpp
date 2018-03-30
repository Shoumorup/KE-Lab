#include<bits/stdc++.h>
using namespace std;

int main()
{
	fstream fin;
	fin.open("File.txt"); 
	string s;
	int bin_size;
	cout<<"Enter bin size: "<<endl;
	cin>>bin_size;
	vector<vector<int> >res;
	while(fin)
	{
		getline(fin,s);
		stringstream ss;
		ss<<s; string x=""; int i=0; vector<int>bin;
		vector<int>lump;
		while(ss>>x) 	lump.push_back(atoi(x.c_str()));
		sort(lump.begin(),lump.end());
		for(int d=0;d<lump.size();d++)
		{
		    bin.push_back(lump[d]);
		  	i=(i+1)%bin_size;
		  	if(i==0) 
			{
		  		res.push_back(bin);
		  		bin.clear();
    		}	
		}  	
	}
	int arr[res.size()],first[res.size()],last[res.size()],middle[res.size()];
	memset(arr,0,sizeof(arr));
	cout<<"Partitioned into: "<<endl;
	for(int i=0;i<res.size();i++)
	{
		cout<<"Bin "<<i<<" : ";
		first[i]=res[i][0];
		last[i]=res[i][res[i].size()-1];
		middle[i]=res[i][(res[i].size()-1)/2];
		for(int j=0;j<res[i].size();j++) 
		{
			cout<<res[i][j]<<" ";
			arr[i]+=res[i][j];
		}
		arr[i]/=bin_size;
		cout<<endl;
	}
	cout<<endl<<"Binning by means: "<<endl;
	for(int i=0;i<res.size();i++) 
	{
		cout<<"Bin "<<i<<" : ";
		for(int j=0;j<res[i].size();j++) cout<<arr[i]<<" ";
		cout<<endl;
	}
	
    cout<<endl<<"Binning with Boundaries: "<<endl;
    for(int i=0;i<res.size();i++)
    {
       cout<<"Bin "<<i<<" : ";
	   for(int j=0;j<res[i].size();j++) 
	   {
	   	if(j<=(res[i].size())/2) cout<<first[i]<<" ";
	   	else cout<<last[i]<<" ";
	   }
	   cout<<endl;
    }
    
    cout<<endl<<"Binning with Median: "<<endl;
    for(int i=0;i<res.size();i++)
    {
       cout<<"Bin "<<i<<" : ";
	   for(int j=0;j<res[i].size();j++) cout<<middle[i]<<" ";
	   cout<<endl;
    }
    
	fin.close();
}
