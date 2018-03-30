#include<bits/stdc++.h>
using namespace std;
int main()
{
	fstream fin,fin2;
	int threshold=0;
	cout<<"Enter minimum Threshold count"<<endl;
	cin>>threshold;
	fin.open("Pairs.txt");
	fin2.open("L2pairs.txt");
	string s="";
	while(fin)
	{
	  getline(fin,s);
	  string str="";
	  for(int i=s.length()-1;i>=0 && s.at(i)>='0' && s.at(i)<='9';i--) str+=s.at(i);
	  reverse(str.begin(),str.end());
	  char tmp[100];
	  int num=atoi(str.c_str());
	  if(num>threshold) fin2<<s<<endl;
    }
	fin2.close();
	fin.close();
    return 0;
}
