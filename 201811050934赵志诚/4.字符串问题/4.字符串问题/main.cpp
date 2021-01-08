//
//  main.cpp
//  4.字符串问题
//
//  Created by 赵志诚 on 2020/12/21.
//  Copyright © 2020年 赵志诚. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int C,M,N;//N为列数，M为行数
    //cout<<"请输入行数和列数："<<endl;
    cin>>M>>N;
    char b[M][N];
    int a[M][N];
    //cout<<"请输入感染分布情况："<<endl;
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
            cin>>b[i][j];
    }
   // cout<<"请输入几段病毒感染："<<endl;
    cin>>C;
    
    for(int k=0;k<M;k++)
        for(int q=0;q<N;q++)
            if(b[k][q]=='O')
                a[k][q]=1;
            else if(b[k][q]=='X')
                a[k][q]=2;
            else
                a[k][q]=1;
    if(C==0)
    {
        for(int i=0;i<M;i++)
        {
            for(int j=0;j<N;j++)
                cout<<b[i][j];
            cout<<endl;
        }
        return 0;
    }
    else
    {
        for(int k=0;k<C;k++)
        {
            for(int i=0;i<M;i++)
            {
                for(int j=0;j<N;j++)
                {
                    
                    if(b[i][j]=='O'||b[i][j]=='P')
                        continue;
                    else
                    {
                        if(a[i][j]==k+2)
                        {
                            //cout<<"i:"<<i<<"j:"<<j<<endl;
                            //cout<<"k:"<<k<<endl;
                            a[i][j]=k+3;
                            if(i>0)
                            {
                                if(b[i-1][j]!='P'&&b[i-1][j]!='X')
                                {
                                    b[i-1][j]='X';
                                    a[i-1][j]=k+3;
                                    //cout<<"1"<<endl;
                                    //cout<<"i-1:"<<i-1<<"j:"<<j<<endl;
                                }
                            }
                            if(i<M-1)
                            {
                                 if(b[i+1][j]!='P'&&b[i+1][j]!='X')
                                {
                                    b[i+1][j]='X';
                                    a[i+1][j]=k+3;                            //cout<<"i+1:"<<i+1<<"j:"<<j<<endl;

                                }
                            }
                            if(j>0)
                            {
                                 if(b[i][j-1]!='P'&&b[i][j-1]!='X')
                                {
                                    b[i][j-1]='X';
                                    a[i][j-1]=k+3;
                                   // cout<<"i:"<<i<<"j-1:"<<j-1<<endl;

                                }
                            }
                            if(j<N-1)
                            {
                                 if(b[i][j+1]!='P'&&b[i][j+1]!='X')
                                {
                                    b[i][j+1]='X';
                                    a[i][j+1]=k+3;
                                    //cout<<"i:"<<i<<"j+1:"<<j+1<<endl;

                                }
                            }
                        }
                            
                    }
                }
            }
        }
        for(int i=0;i<M;i++)
        {
            for(int j=0;j<N;j++)
                cout<<b[i][j];
            cout<<endl;
        }
    }
     

    return 0;
}
