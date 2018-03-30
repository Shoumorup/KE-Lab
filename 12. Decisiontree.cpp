#include<bits/stdc++.h>
using namespace std;
bool check[4];
string best[]={"age","income","student","credit"};
map<int,set<string> >dict;

typedef
struct node
{
	string name;
	string edge[3];
	node* child[3];	
}*Tptr;

bool allsame(vector<vector<string> >& db)
{
  if(db.size()==0) return false;
  string test=db[0][db[0].size()-1];	
  for(int i=1;i<db.size();i++)
  {
  	if(db[i][db[0].size()-1].compare(test)!=0) return false; 
  }	
  return true;
}

string findmaj(vector<vector<string> >& db)
{
	int yes=0,no=0;
	for(int i=0;i<db.size();i++)
	{
		 if(db[i][db[0].size()-1].compare("yes")==0) ++yes;
		 else ++no; 
	}
	return (yes>=no?"yes":"no");
}

int splitting(vector<vector<string> >& db)
{
	double sz=db.size(); 
	double yes=0.0,no=0.0;
	for(int i=0;i<db.size();i++)
	{
		 if(db[i][db[i].size()-1]=="yes") ++yes;
		 else ++no; 		 
	}
	double y=yes/sz, n=no/sz;	
	double infoD=0.0;
	if(n==0) infoD=-1*(y*log2(y)); 
	else if(y==0) infoD=-1*(n*log2(n)); 
	else infoD=-1*(y*log2(y)+n*log2(n)); 
	double maxi=INT_MIN; int pos=0; 
	cout<<"Info(D) "<<infoD<<endl; 
	for(int i=0;i<4;i++) //Checking the Attribute list
	{
		if(check[i]) continue;
		double sum=0; 
		for(set<string>::iterator it=dict[i+1].begin();it!=dict[i+1].end();it++)
		{
			double c=0.0,p=0.0,q=0.0;
			for(int j=0;j<db.size();j++) //Iterating through the database
			{
				if(db[j][i]==*it)
				{
				  ++c;
				  if(db[j][db[0].size()-1].compare("yes")==0)++p;
				  else  ++q;	
				}
			}
			double a=p/c,b=q/c,info; 
			if(a==0) info=-1*(b*log2(b));
			else if(b==0) info=-1*(a*log2(a));
			else info=-1*(a*log2(a)+b*log2(b));
			double x=((double)c/(double)sz)*info; 
			sum+=x;
		} 
		if(best[i]!="income")		cout<<"For "<<best[i]<<" "<<sum<<endl; 
		if((infoD-sum)>maxi)
		{
			maxi=infoD-sum;
			pos=i;
		}		
	}
	return pos;
}

void printtree(Tptr& T)
{
	if(!T) return;
	cout<<T->name<<" "<<endl;
	for(int i=0;i<3;i++)
	{
		if(T->edge[i].compare("")!=0) 
		{
			cout<<T->edge[i]<<endl;
			printtree(T->child[i]);
		}
	}
}

Tptr recur(Tptr& T,vector<vector<string> >& db)
{
	T=new node();
	for(int i=0;i<3;i++) 
	{
		T->child[i]=NULL;
		T->edge[i]="";
	}
	
	if(allsame(db))//All belonging to the same class
	{
		T->name=db[0][db[0].size()-1];
		return T;
	}
	int cld=0;
	for(int i=0;i<3;i++) 
	{
		if(check[i]) ++cld;
	}
	
	if(cld==3) //attribute list empty
	{
	   string maj=findmaj(db);
	   T->name=maj;	   
	   return T;
    } 
	int j=splitting(db); //splitting Criterion Obtained and it's check value made true
	check[j]=true; //cout<<j<<endl;
	cout<<"Splitting Criterion now is: "<<best[j]<<endl; //return T;
	T->name=best[j];
	int chil=0;
	for(set<string>::iterator it=dict[j+1].begin();it!=dict[j+1].end();it++)
	{
		vector<vector<string> >res; res.clear();
		for(int k=0;k<db.size();k++)
		{
			if(db[k][j].compare(*it)==0) res.push_back(db[k]);//Tuple with matching attribute
		}
		cout<<"Calling for "<<*it<<endl;
		T->child[chil]=recur(T->child[chil],res);
		T->edge[chil]=*it;
		++chil;
	}
	return T;
}

int main()
{
	fstream fin;
	fin.open("Database.txt");//contains Training Dataset
	string ch="";
	getline(fin,ch);
	vector<vector<string> >db;
    db.clear();
    dict.clear();
    memset(check,false,sizeof(check));
   	while(fin)
	{
		getline(fin,ch);
		ch+=' ';
		int i=0,cnt=0; 
		string t=""; 
		vector<string>p;
		while(i<ch.length())
		{
		  if(ch[i]!=' ') t+=ch[i];
		  else
		  {
		  	++cnt;
		  	if(dict[cnt].find(t)==dict[cnt].end()) dict[cnt].insert(t);
		  	p.push_back(t); t="";
		  }	
		  ++i;	  
		}
		db.push_back(p);//1. Check here
	}
	db.pop_back();
	dict[1].clear();//2. Check here
	dict[1].insert("youth");
	dict[1].insert("middle");
	dict[1].insert("senior");
	for(map<int,set<string> >::iterator it=dict.begin();it!=dict.end();it++)
	{
		cout<<it->first<<" ";
		for(set<string>::iterator ip=it->second.begin();ip!=it->second.end();ip++) cout<<*ip<<" ";
		cout<<endl;
	}
	Tptr T=NULL;
	T=recur(T,db); return 0;
	fin.close();
	return 0;
}
