#include<bits/stdc++.h>
using namespace std;

map<int,int>prio;

typedef
struct node
{
	int item;
	int cnt;
	node* child[5];
	node* next;
	node* parent;
}*Tptr;

struct arr
{
	int item;
	int supp;
	node* node_link;
};

Tptr array1[5];

bool mycomp(arr a1,arr a2)
{
	return (a1.supp>a2.supp);
}

bool hascomp(int a,int b)
{
	return (prio[a]>prio[b]);
}

void create(Tptr& head,vector<int>& p,int n,int count)
{
  if(n<0) return;
  Tptr T=head;
  if(!T->child[p[n]-1])
  {
  	T->child[p[n]-1]=new node();
  	for(int i=0;i<5;i++) T->child[p[n]-1]->child[i]=NULL;
  	T->child[p[n]-1]->next=NULL;
  	T->child[p[n]-1]->item=p[n];
  	T->child[p[n]-1]->parent=T;

	array1[p[n]-1]->next=T->child[p[n]-1];
	array1[p[n]-1]=T->child[p[n]-1];
  }
  T->child[p[n]-1]->cnt+=count;
  create(T->child[p[n]-1],p,n-1,count);
}

void subsets(vector<int>& row,vector<bool>& sub,vector<vector<int> >&all1,int i)
{
	if(i==row.size())
	{
		vector<int>p;
		for(int j=0;j<row.size();j++)
		{
			if(sub[j]==true)  p.push_back(row[j]); 
		}
		all1.push_back(p);
		return;
	}
	sub[i]=true;
	subsets(row,sub,all1,i+1);
	sub[i]=false;
	subsets(row,sub,all1,i+1);
}

void printtree(Tptr& head)
{
	if(!head) return;
	Tptr T=head;
	cout<<T->item<<" "<<T->cnt<<endl;
	for(int i=0;i<5;i++) printtree(T->child[i]);
}

bool checkSingle(Tptr& head)
{
	if(!head) return true;
	int cld=0;
	for(int i=0;i<5;i++)
	{
		if(head->child[i]) cld++;
	}
	if(cld>1)  return false;
	for(int i=0;i<5;i++) 
	{
		bool b=checkSingle(head->child[i]);
		if(!b) return false;
	}
	return true;
}

void storeSingle(Tptr& T,vector<int>& all)
{
	if(!T) return;
	if(T->item!=-1)all.push_back(T->item);
	for(int i=0;i<5;i++) storeSingle(T->child[i],all);
}

void recur(vector<pair<vector<int>,int> >&support,vector<int>& parent,int count,int threshold,Tptr head1,vector<vector<int> >&global,bool& flag)
{
    //Writing the single path Base case
    if(checkSingle(head1))
    {
    	vector<int>row;
    	storeSingle(head1,row);
      	vector<bool>sub(row.size(),false);
    	vector<vector<int> >all; // all subsets of row
    	subsets(row,sub,all,0);
    	for(int i=0;i<all.size();i++)
        {
        	for(int j=0;j<parent.size()-1;j++) 	all[i].push_back(parent[j]);	
			global.push_back(all[i]);			
        }
        flag=true;
        return;
    }
	if(support.size()==0) return;
    //support is my new database.
	vector<arr>res; int i=0;
	//Create the Table again
	for(int i=0;i<support.size();i++)
	{
	  for(int j=0;j<support[i].first.size();j++)
	  {
	  	int f=0;
	  	for(f=0;f<res.size();f++)
	  	{
	  		if((support[i].first)[j]==res[f].item) { res[f].supp+=count; break; }
	  	}
	  	if(f==res.size())
        {
            arr a;
            a.item=(support[i].first)[j];
            a.supp=count;
            a.node_link=NULL;
            res.push_back(a);
        }
	  }
	}
	for(i=0;i<res.size();)
    {
        if(res[i].supp<threshold)  res.erase(res.begin()+i);
        else ++i;
    }

	for(i=0;i<res.size();i++)
    {
        res[i].node_link=new node();
        Tptr T=res[i].node_link;
        T->item=res[i].item;
        T->cnt=0;
        for(int k=0;k<5;k++) T->child[k]=NULL;
        T->next=NULL;
        T->parent=NULL;
        array1[res[i].item-1]=T;
    }
	sort(res.begin(),res.end(),mycomp);
    //New Table is now ready.

	cout<<"This is for parent ";
	for(int i=0;i<parent.size();i++) cout<<parent[i]; cout<<endl;
	
    for(int i=0;i<res.size();i++) cout<<res[i].item<<" "<<res[i].supp<<endl;
	cout<<endl;

	prio.clear();
	i=1;
	for(vector<arr>::iterator it=res.begin();it!=res.end();it++)
	{
	    prio[it->item]=i;//Setting Priorities
	    ++i;
	}

    Tptr head=new node();
	head->item=-1;
	head->cnt=0;
	for(int i=0;i<5;i++) head->child[i]=NULL;
	head->next=NULL;
	int k=0;
	vector<int>p;
	for(int z=0;z<support.size();z++)
	{
		p=support[z].first;
		vector<int>pm;
		for(int b=0;b<p.size();b++)
		{
			if(prio.find(p[b])!=prio.end()) pm.push_back(p[b]);
		}
		sort(pm.begin(),pm.end(),hascomp);
		//for(int d=0;d<pm.size();d++) cout<<pm[d]<<" "; cout<<endl;
    	create(head,pm,pm.size()-1,count);
	    p.clear();
	}
	cout<<"Tree has been created for parent ";
	for(int i=0;i<parent.size();i++) cout<<parent[i]; cout<<endl;
	printtree(head);
	cout<<endl<<endl;

	cout<<endl<<"Printing the Links "<<endl;
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i].item<<" : ";
		Tptr L=res[i].node_link;
		while(L)
		{
			cout<<"( "<<L->item<<","<<L->cnt<<" ) ";
			L=L->next;
		}
		cout<<endl;
	}

	//Make a pattern base of the generated Tree
	cout<<endl<<endl;
	vector<pair<int,vector<pair<vector<int>,int> > > >cpb;//conditional_pattern_base
	for(int i=res.size()-1;i>0;i--)
	{
       Tptr T=res[i].node_link;
       vector<pair<vector<int>,int> >cp; cp.clear();
       while(T->next)
	   {
	   	 T=T->next;
	   	 vector<int>st; st.clear();
	   	 int x=T->cnt;
	   	 Tptr K=T; K=K->parent;
	   	 while(K->parent)
	   	 {
	   	 	st.push_back(K->item);
	   	 	K=K->parent;
	   	 }
	   	 reverse(st.begin(),st.end());
	   	 if(!st.empty())
         {
             pair<vector<int>,int>  z=make_pair(st,x);
	   	     cp.push_back(z);
         }
	   }
	   cpb.push_back(make_pair(T->item,cp));
	}
	if(cpb.empty())
	{	
	 if(res.empty()) global.push_back(parent);
	 else 
	 {
		parent.push_back(res[0].item);
		global.push_back(parent);
		parent.pop_back();
		global.push_back(parent);
	 }
	 return;
    }
	cout<<"Conditional Pattern Base for ";
	for(int i=0;i<parent.size();i++) cout<<parent[i]; cout<<endl;
	//Printing the conditional Pattern Base
	for(int q=0;q<cpb.size();q++)
	{
		cout<<cpb[q].first<<endl;
		for(int r=0;r<(cpb[q].second).size();r++)
		{
			for(vector<int>::iterator it=((cpb[q].second[r]).first).begin();it!=((cpb[q].second[r]).first).end();it++)
		    {
		    	cout<<*it<<" ";
		    }
		    cout<<"-> "<<(cpb[q].second[r]).second<<endl;
		}
	}
	cout<<endl<<endl;	
	for(int q=0;q<cpb.size();q++)
	{
		parent.push_back(cpb[q].first);
		recur(cpb[q].second,parent,(cpb[q].second)[0].second,threshold,head,global,flag);
		parent.pop_back();
	}
	
	if(!flag) //Since single path not found
	{
		parent.push_back(res[0].item);
		global.push_back(parent);
		parent.pop_back();
		global.push_back(parent);		
	}
}

int main()
{
    fstream fin;
	fin.open("Transaction.txt");
	vector<arr>res(5);
	map<int,vector<int> >support;
	for(int i=0;i<5;i++)
	{
		res[i].item=i+1;
		res[i].supp=0;

		res[i].node_link=new node();
		Tptr T=res[i].node_link;
		T->item=res[i].item;
		T->cnt=0;
		for(int k=0;k<5;k++) T->child[k]=NULL;
		T->next=NULL;
		T->parent=NULL;
		array1[i]=T;
	}
	int threshold=2;//Support Count for my Entire Program
	string ch="";
	getline(fin,ch);
	while(fin)
	{
		ch="";

		getline(fin,ch); ch+=' ';
		string tmp="",t="";
		int i=1;
		while(i<ch.length() && ch.at(i)!=' ')
		{
			tmp+=ch.at(i);
			++i;
		}
		i=i+5;
		for(;i<ch.length();i++)
		{
			char c=ch.at(i);
			if(c!=' ') t+=c;
			else
			{
				support[atoi(tmp.c_str())].push_back(atoi(t.c_str()));
				res[atoi(t.c_str())-1].supp++;//Stores the initial unsorted table
				t="";
			}
		}
	} 
	//for(int i=0;i<res.size();i++) cout<<res[i].item<<" "<<res[i].supp<<endl;
	for(vector<arr>::iterator it=res.begin();it!=res.end();)
	{
		if(it->supp<threshold) it=res.erase(it);
		else ++it;
	}
	sort(res.begin(),res.end(),mycomp);
	//Eliminate the ones whose support is below the threshold
	for(int i=0;i<res.size();i++) cout<<res[i].item<<" "<<res[i].supp<<endl; //Table has been Created
	prio.clear();
	int i=1;
	for(vector<arr>::iterator it=res.begin();it!=res.end();it++)
	{
	    prio[it->item]=i;//Setting Priorities
	    ++i;
	}

	Tptr head=new node();
	head->item=-1;
	head->cnt=0;
	for(int i=0;i<5;i++) head->child[i]=NULL;
	head->next=NULL;
	int k=0;
	vector<int>p;
	
	for(map<int,vector<int> >::iterator it=support.begin();it!=support.end();it++)
	{
		p=it->second;
		//Sort it accordingly.
		sort(p.begin(),p.end(),hascomp);
		create(head,p,p.size()-1,1);
	    p.clear();	    
	}
	cout<<"Tree has been created "<<endl;
	printtree(head);

	cout<<endl<<"Printing the Links "<<endl;
	for(int i=0;i<5;i++)
	{
		cout<<res[i].item<<" : ";
		Tptr L=res[i].node_link;
		while(L)
		{
			cout<<"( "<<L->item<<","<<L->cnt<<" ) ";
			L=L->next;
		}
		cout<<endl;
	}
	vector<pair<int,vector<pair<vector<int>,int> > > >cpb;//conditional_pattern_base
	for(int i=res.size()-1;i>0;i--)
	{
       Tptr T=res[i].node_link;
       vector<pair<vector<int>,int> >cp; cp.clear();
       while(T->next)
	   {
	   	 T=T->next;
	   	 vector<int>st; st.clear();
	   	 int x=T->cnt;
	   	 Tptr K=T; K=K->parent;
	   	 while(K->parent)
	   	 {
	   	 	st.push_back(K->item);
	   	 	K=K->parent;
	   	 }
	   	 reverse(st.begin(),st.end());
	   	 if(!st.empty())
         {
             pair<vector<int>,int>  z=make_pair(st,x);
	   	     cp.push_back(z);
         }
	   }
	   cpb.push_back(make_pair(T->item,cp));
	}
	//Printing the conditional Pattern Base
	for(int q=0;q<cpb.size();q++)
	{
		cout<<cpb[q].first<<endl;
		for(int r=0;r<(cpb[q].second).size();r++)
		{
			for(vector<int>::iterator it=((cpb[q].second[r]).first).begin();it!=((cpb[q].second[r]).first).end();it++)
		    {
		    	cout<<*it<<" ";
		    }
		    cout<<"-> "<<(cpb[q].second[r]).second<<endl;
		}
	}
	//Recursion for the Conditional Fp Tree
	for(int q=0;q<cpb.size();q++)
	{
	   vector<int>parent;
	   vector<vector<int> >global;
	   parent.push_back(cpb[q].first);
	   bool flag=false;
       recur(cpb[q].second,parent,(cpb[q].second)[0].second,threshold,head,global,flag);
       //vector<int>z; z.push_back(cpb[q].first);
       //global.push_back(z);
       cout<<"Frequent Itemsets for"<<cpb[q].first<<endl;    
	   for(int i=0;i<global.size();i++)
	   {
		  for(int j=0;j<global[i].size();j++) 	cout<<global[i][j]<<" "; cout<<endl;
	   }    
    }
    if(!res.empty()) cout<<"Frequent Itemset "<<endl<<res[0].item;
	return 0;
}
