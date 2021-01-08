#include<iostream>
using namespace std;
int main()
{
   int m,n; 
   char *column;
   char **p;  
   int i,gen;
   while(1)
   {
	   cin>>n;
	   cin>>m;
	   column=new char[m]; 
	   p=new char*[m]; 
	   for(i=0;i<m;i++)
	   { 
		   column[i]=n;
		   p[i]=new char[n];
	   }
	   for(i=0;i<m;i++) 
	   {
		   for(int j=0;j<column[i];j++)
			 cin>>p[i][j];
	   }
	   cin>>gen;
		for(int k=0;k<gen;k++)
		{
		   for(i=0;i<m;i++)
		   {
			   for(int j=0;j<column[i];j++)
			   {
					if(p[i][j]=='X')
					{
						if((j!=0)&&(p[i][j-1]!='P')&&(p[i][j-1]!='X'))     p[i][j-1]='Z';
						if((j!=n-1)&&(p[i][j+1]!='P')&&(p[i][j+1]!='X'))   p[i][j+1]='Z';
						if((i!=m-1)&&(p[i+1][j]!='P')&&(p[i+1][j]!='X'))   p[i+1][j]='Y';
						if((i!=0)&&(p[i-1][j]!='P')&&(p[i-1][j]!='X'))     p[i-1][j]='Y';
					}
			   }
		   }
		   for(i=0;i<m;i++) 
		   {
			 for(int j=0;j<column[i];j++)  if(p[i][j]=='Y'||p[i][j]=='Z') p[i][j]='X';
			 
		   }
		}
	   cout<<"---------输出每行元素-----------\n";
	   for(i=0;i<m;i++)
	   {
		   for(int j=0;j<column[i];j++)
			 cout<<p[i][j]<<"";
		   cout<<endl;
	   }

	   for(i=0;i<m;i++)  
		   delete []p[i];
	   delete []p;  
	   cout<<"指针p的地址："<<p; 
	}
   return 0;
}