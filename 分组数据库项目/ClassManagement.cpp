
#include <iostream>
#include <string>
#include "CDBMysql.h"
using namespace std;
int main()
{
	string para[3];
	cout<<"[提示]请验证账户名密码及数据库名（空格分隔）："<<endl;//root 123456 tsms
	for(int i=0;i<3;i++)  cin >> para[i];
	const char *sql_para[3] = {para[0].data(),para[1].data(),para[2].data()};
    CDBMysql mysqlDB("localhost", sql_para[0], sql_para[1], sql_para[2], 3306);
	while(1)  mysqlDB.CDBHome();
}

