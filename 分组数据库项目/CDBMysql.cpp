#include "CDBMysql.h"
#include "iostream"
#include "string"
#include "mystring.h"
#pragma comment(lib,"libmysql.lib")
using namespace std;

extern CDBMysql mysqlDB;

int CDBMysql::CDBHome()
{
	int choice;
		system("cls");
		cout << "------------------------------------------------" << endl;
		cout << "-------------欢迎使用教师工资管理系统-----------" << endl;
		cout << "-----------------0.退出管理程序-----------------" << endl;
		cout << "-----------------1.增加教师记录-----------------" << endl;
		cout << "-----------------2.增加工资记录-----------------" << endl;
		cout << "-----------------3.删除教师记录-----------------" << endl;
		cout << "-----------------4.删除工资信息-----------------" << endl;
		cout << "-----------------5.综合查询---------------------" << endl;
		cout << "-----------------6.简单查询---------------------" << endl;
		cout << "-----------------7.统计信息---------------------" << endl;
		cout << "-----------------8.修改教师信息-----------------" << endl;
		cout << "-----------------9.修改工资信息-----------------" << endl;
		cout << "------------------------------------------------" << endl;
		cin>>choice;
		switch (choice) {
			case 0:   //退出管理系统
				cout<<"[提示]请等待片刻，即将关闭数据库..."<<endl;
				cout<<"[提示]欢迎您下次使用"<<endl;
				system("net stop mysql");
				break;
			case 1:   //增加教师记录
				insertTeacherInfo();
				break;
			case 2:   //增加工资记录
				insertSalaryInfo();
				break;
			case 3:   //删除教师记录
				deleteTeacherInfo();
				break;
			case 4:   //删除工资信息
				deleteSalaryInfo();
				break;
			case 5:  
				selectInfo();
				break;
			case 6:   
				select_All();
				break;
			case 7:   //统计信息
				selectStatistic();
				break;
			case 8:   //修改教师信息
				ModifyTeacherInfo();
				break;
			case 9:   //修改工资信息
				ModifySalaryInfo();
				break;
			default:
				system("cls");//清空、刷新屏幕
				break;
			}
		return 0;
}
CDBMysql::CDBMysql(const char* host, const char* user, const char* passwd, const char* dbname, unsigned int port)
{
	system("net start mysql");
	mysql_init(&m_mysql); 
	if (!(m_hMysql = mysql_real_connect(&m_mysql, host, user, passwd, dbname, port, NULL, 0)))
	{
		fprintf(stderr, "Couldn't connect to engine!\n%s\n", mysql_error(&m_mysql));
		exit(1);
	}


	mysql_query(m_hMysql, "set names 'utf8'");

	m_result = NULL;
	m_fd = NULL;
	memset(m_sqlBuf, 0, 1024);
	mysql_query(m_hMysql,"set names gbk");
}

CDBMysql::~CDBMysql(void)
{
	if (m_hMysql) {
		mysql_close(m_hMysql);
	}
}


int CDBMysql::selectOneStudent(int id, StudnetInfo * stuInfo)
{
	mysql_query(m_hMysql, "SET NAMES 'GBK'");

	sprintf_s(m_sqlBuf, 1024, "select id, name, sex from student where id=%d", id);
	if (mysql_query(m_hMysql, m_sqlBuf) == 0)
	{
		m_result = mysql_store_result(m_hMysql);
		if (m_result->row_count <= 0)
		{
			return 0;
		}
	}
	else
	{
		return -1;
	}

	if (m_row = mysql_fetch_row(m_result))
	{
		stuInfo->id = atoi(m_row[0]);
		sprintf_s(stuInfo->name, 20, m_row[1]);
		stuInfo->sex = atoi(m_row[2]);
	}
	mysql_free_result(m_result);

	return 0;
}

int CDBMysql::selectAllStudent(StudnetInfo** stuInfoList,int * stuNumber)
{
	*stuNumber = 0;
	*stuInfoList = 0;

	mysql_query(m_hMysql, "SET NAMES 'GBK'");

	sprintf_s(m_sqlBuf, 1024, "select 教师号, 性别, from teachears");
	if (mysql_query(m_hMysql, m_sqlBuf) == 0)
	{
		m_result = mysql_store_result(m_hMysql);
		if (m_result->row_count <= 0)
		{
			return 0;
		}
	}
	else
	{
		return -1;
	}

	*stuNumber = m_result->row_count;
	*stuInfoList = (StudnetInfo*) malloc(m_result->row_count * sizeof(StudnetInfo));

	int index = 0;
	while (m_row = mysql_fetch_row(m_result))
	{
		(*stuInfoList + index)->id = atoi(m_row[0]);
		sprintf_s((*stuInfoList + index)->name, 20, m_row[1]);
		(*stuInfoList + index)->sex = atoi(m_row[2]);
		index++;
	}
	mysql_free_result(m_result);

	return 0;
}

int CDBMysql::insertStudentInfo(int id, const char * name, bool sex)
{
	sprintf_s(m_sqlBuf, 1024, "insert into student (id, name, sex) values (%d, '%s', %d)", id, name, sex);

	mysql_query(m_hMysql, "SET NAMES 'GBK'");
	if (mysql_query(m_hMysql, m_sqlBuf) == 0)
	{
		return 0;
	}
	return -1;
}

//int CDBMysql::SplitString(const CString str, char split, std::vector<CString>& strList)
//{
//	strList.clear();
//	CString strTemp = str;
//	int iIndex = 0;
//	while (1)
//	{
//		iIndex = strTemp.Find(split);
//		if (iIndex >= 0)
//		{
//			strList.push_back(strTemp.Left(iIndex));
//			strTemp = strTemp.Right(strTemp.GetLength() - iIndex - 1);
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	if (!strTemp.IsEmpty())
//	{
//		strList.push_back(strTemp);
//	}
//
//	return strList.size();
//}

//int CDBMysql::insertTeacherInfo(int id, const char* name, const char* sex, const char* company, const char* address, const char* tel)
//{
//	sprintf_s(m_sqlBuf, 1024, "insert into teachers (教师号, 姓名, 性别, 单位名称, 家庭住址, 联系电话) values (%d, '%s', '%s', '%s', '%s', '%s')", id, name, sex, company, address, tel);
//
//	mysql_query(m_hMysql, "SET NAMES 'GBK'");
//	if (mysql_query(m_hMysql, m_sqlBuf) == 0)
//	{
//		return 0;
//	}
//	return -1;
//}
//
//int CDBMysql::insertSalaryInfo(int id, int baseSalary, int subsidy, int assistance, int telCharge, int cost, int roomCharge, int tax, int healthCost, int funds)
//{
//	sprintf_s(m_sqlBuf, 1024, "insert into salaries (教师号, 基本工资, 津贴, 生活补贴, 电话费, 水电费, 房租, 所得税, 卫生费, 公积金) values (%d, %d, %d, %d, %d, %d, %d, %d, %d, %d)", id, baseSalary, subsidy, assistance, telCharge, cost, roomCharge, tax, healthCost, funds);
//
//	mysql_query(m_hMysql, "SET NAMES 'GBK'");
//	if (mysql_query(m_hMysql, m_sqlBuf) == 0)
//	{
//		return 0;
//	}
//	return -1;
//}

void CDBMysql::TipInsertTeacher()
{
	cout<<"[提示]您正在添加一名新教师..."<<endl<<endl;
	cout<<"[提示]请以空格分隔输入教师编号、姓名、性别、单位名称、家庭住址、联系电话："<<endl;
	cout<<"[提示]若暂未知晓某些信息，请用“NULL”代替，您可以尝试这样输入："<<endl;
	cout<<"[示例]001 王五 NULL 青岛理工大学 嘉陵江东路777号 18888888888"<<endl;
}

void CDBMysql::TipInsertSalary()
{
	cout<<"[提示]您正在添加一名新教师工资..."<<endl<<endl;
	cout<<"[提示]请以空格分隔输入教师编号、基本工资、津贴、生活补贴、电话费、水电费、房租、所得税、卫生费、公积金："<<endl;
	cout<<"[示例]001 11 22 33 44 55 66 77 88 99"<<endl;
	cout<<"[提示]若暂未知晓某些信息，请用“NULL”代替："<<endl;
}

void CDBMysql::TipDeleteTeacher()
{
	cout<<"[提示]您正在删除一名教师..."<<endl<<endl;
	cout<<"[提示]请输入删除教师的特征条件："<<endl;
	cout<<"[提示]教师信息表中可供索引的条件包含：教师号、姓名、性别、单位名称、家庭住址、联系电话"<<endl<<endl;
	cout<<"[提示]您可以尝试输入便于您表达的语言："<<endl;
	cout<<"[示例]教师号=0001"<<endl;
	cout<<"[示例]删除男教师"<<endl;
	cout<<"[示例]删掉姓王的"<<endl;
	cout<<"[示例]去除姓李的女教师"<<endl;
	cout<<"[示例]这个人的电话是18888888888"<<endl<<endl;
	cout<<"[提示]如您删除单位或住址，只可按以下格式输入："<<endl;
	cout<<"[示例]单位名称=青岛理工大学"<<endl;
	cout<<"[示例]家庭住址=嘉陵江东路777号"<<endl;
}

void CDBMysql::TipDeleteSalary()
{
	cout<<"[提示]您正在删除一名教师工资..."<<endl<<endl;
	cout<<"[提示]请输入删除教师工资的特征条件："<<endl;
	cout<<"[提示]教师工资表中可供索引的条件包含：教师号、基本工资、津贴、生活补贴、电话费、水电费、房租、所得税、卫生费、公积金"<<endl;
	cout<<"[提示]您可以试试这样输入："<<endl;
	cout<<"[示例]教师号=0001"<<endl;
	cout<<"[示例]基本工资<0"<<endl;
	cout<<"[示例]基本工资<0 and 教师号=0001"<<endl;
	cout<<"[示例]基本工资<0 or 教师号=0001"<<endl;
}

void CDBMysql::TipSelect()
{
	cout<<"[提示]您正在查询教师信息..."<<endl<<endl;
	cout<<"[提示]请输入查询教师的特征条件："<<endl;
	cout<<"[提示]综合信息表中可供索引的条件包含：教师号、姓名、性别、单位名称、家庭住址、联系电话"<<endl;
	cout<<"      基本工资、津贴、生活补贴、电话费、水电费、房租、所得税、卫生费、公积金"<<endl;
	cout<<"[提示]您可以尝试输入便于您表达的语言："<<endl;
	cout<<"[示例]教师号=0001"<<endl;
	cout<<"[示例]教师号是0003"<<endl;
	cout<<"[示例]男的"<<endl;
	cout<<"[示例]找男人"<<endl;
	cout<<"[示例]姓王的"<<endl;
	cout<<"[示例]姓李的女的"<<endl;
	cout<<"[示例]Ta电话是18888888888"<<endl<<endl;
	cout<<"[提示]如您查询单位或住址，只可按以下格式输入："<<endl;
	cout<<"[示例]单位名称=青岛理工大学"<<endl;
	cout<<"[示例]家庭住址=嘉陵江东路777号"<<endl;
}
	
void CDBMysql::TipStatis()
{
	cout<<"[提示]您正在统计教师工资..."<<endl<<endl;
	cout<<"[提示]请输入查询的教师号："<<endl;
}

void CDBMysql::TipModifyTeacher()
{
	cout<<"[提示]您正在修改教师信息..."<<endl<<endl;
	cout<<"[提示]教师信息表中可供索引的特征包含：教师号、姓名、性别、单位名称、家庭住址、联系电话"<<endl<<endl;
	cout<<"[提示]若您需要将姓名为“马递归”的性别修改为女，可以这样输入："<<endl;
	cout<<"[示例]姓名=马递归 性别 女"<<endl;
	cout<<"[提示]请输入："<<endl;
}

void CDBMysql::TipModifySalary()
{
	cout<<"[提示]您正在修改教师工资..."<<endl<<endl;
	cout<<"[提示]教师工资表中可供索引的条件包含：教师号、基本工资、津贴、生活补贴、电话费、水电费、房租、所得税、卫生费、公积金"<<endl;
	cout<<"[提示]若您需要将教师号为002的基本工资修改为100，可以这样输入："<<endl;
	cout<<"[示例]教师号=002 基本工资 100"<<endl;
	cout<<"[提示]请输入："<<endl;
}

void CDBMysql::TipSelectAll()
{
	cout<<"[提示]您正在进行简单查询..."<<endl<<endl;
	cout<<"[提示]若您想查询工资表中教师号为001的基本工资和公积金，可以按如下输入："<<endl<<endl;
	cout<<"[示例]工资表 基本工资,公积金 教师号=001"<<endl;
	cout<<"[提示]请输入："<<endl;
}
int CDBMysql::insertTeacherInfo()
{
	system("cls");
	string para[6];
	TipInsertTeacher();
	for(int i=0;i<6;i++) cin >> para[i];
	const char *sql_para[6] = {para[0].data(),para[1].data(),para[2].data(),para[3].data(),para[4].data(),para[5].data()};
	sprintf_s(m_sqlBuf, 1024, "insert into teachers values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\");",
					sql_para[0],sql_para[1],sql_para[2],sql_para[3],sql_para[4],sql_para[5]);
	if(mysql_query(m_hMysql, m_sqlBuf))
	{
		printf("插入失败 (%s)\n",mysql_error(m_hMysql));
		system("pause");
		return false;
	}
	else
	{
		printf("插入成功\n");
		return true;
	}
}

int CDBMysql::insertSalaryInfo()
{
	system("cls");
	string para[10];
	TipInsertSalary();
	for(int i=0;i<10;i++) cin >> para[i];
	const char *sql_para[10] = {para[0].data(),para[1].data(),para[2].data(),para[3].data(),para[4].data(),para[5].data(),para[6].data(),para[7].data(),para[8].data(),para[9].data()};
	sprintf_s(m_sqlBuf, 1024, "insert into salaries values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\");",
					sql_para[0],sql_para[1],sql_para[2],sql_para[3],sql_para[4],sql_para[5],
					sql_para[6],sql_para[7],sql_para[8],sql_para[9]);
	if(mysql_query(m_hMysql, m_sqlBuf))
	{
		printf("插入失败 (%s)\n",mysql_error(m_hMysql));
		system("pause");
		return false;
	}
	else
	{
		printf("插入成功\n");
		return true;
	}
}

int CDBMysql::deleteTeacherInfo()
{
	system("cls");
	string para,temp;
	string::size_type position;
	TipDeleteTeacher();
	cin >> para;
	temp = para;
	if(para.find("=") == para.npos) //未找到=
	{
		if(para.find("男") == para.npos)	//未找到男
		{
			if(para.find("女") == para.npos) temp ="NULL";//未找到女
			else  temp = "性别='女'";      //找到女
		}
		else if(para.find("女") == para.npos)  temp = "性别='男'"; //找到男未找到女
		else temp = "性别='男' or 性别='女'";

		position = para.find("姓");
		if(position != para.npos)//找到了姓
		{
			if(temp=="NULL") temp="姓名 like '"+ChineseStringSubstr(para,position+2,position+4)+"%';";
			else temp=temp+" and "+"姓名 like '"+ChineseStringSubstr(para,position+2,position+4)+"%';";
		}
		
		if(para.find("电话") != para.npos) //找到了电话 
		{
			if((temp=="NULL")) temp = "联系电话="+to_String(to_int(para));
			else temp=temp+" and "+"联系电话="+to_String(to_int(para));
		}

		if(para.find("教师号") != para.npos) //找到了教师号 
		{
			if((temp=="NULL")) temp = "教师号="+to_String(to_int(para));
			else temp=temp+" and "+"教师号="+to_String(to_int(para));
		}
	}
	else//找到=  自动加引号
	{
		position = para.find("=");
		temp.insert(position+1,"'");
		temp = temp + "';";
	}

	para = temp;
	const char *sql_para = para.data();
	sprintf_s(m_sqlBuf, 1024, "delete from teachers where %s;",sql_para);
    if(mysql_query(m_hMysql, m_sqlBuf))        //执行SQL语句
    {
        printf("执行失败 (%s)\n",mysql_error(m_hMysql));
		system("pause");
        return false;
    }
    else
    {
        printf("执行成功\n");
        return true;
    }

}

int CDBMysql::deleteSalaryInfo()
{
	system("cls");
	string para;
	TipDeleteSalary();
	cin >> para;
	const char *sql_para = para.data();
	sprintf_s(m_sqlBuf, 1024, "delete from salaries where %s;",sql_para);
    if(mysql_query(m_hMysql, m_sqlBuf))        //执行SQL语句
    {
        printf("执行失败 (%s)\n",mysql_error(m_hMysql));
		system("pause");
        return false;
    }
    else
    {
        printf("执行成功\n");
        return true;
    }

}

int CDBMysql::selectInfo()
{
	system("cls");
	string para,temp;
	string::size_type position;
	TipSelect();
	cin >> para;
	temp = para;
	if(para.find("=") == para.npos) //未找到=
	{
		if(para.find("男") == para.npos)	//未找到男
		{
			if(para.find("女") == para.npos) temp ="NULL";//未找到女
			else  temp = "性别='女'";      //找到女
		}
		else if(para.find("女") == para.npos)  temp = "性别='男'"; //找到男未找到女
		else temp = "性别='男' or 性别='女'";

		position = para.find("姓");
		if(position != para.npos)//找到了姓
		{
			if(temp=="NULL") temp="姓名 like '"+ChineseStringSubstr(para,position+2,position+4)+"%';";
			else temp=temp+" and "+"姓名 like '"+ChineseStringSubstr(para,position+2,position+4)+"%';";
		}
		
		if(para.find("电话") != para.npos) //找到了电话 
		{
			if((temp=="NULL")) temp = "联系电话="+to_String(to_int(para));
			else temp=temp+" and "+"联系电话="+to_String(to_int(para));
		}

		if(para.find("教师号") != para.npos) //找到了教师号 
		{
			if((temp=="NULL")) temp = "教师号="+to_String(to_int(para));
			else temp=temp+" and "+"教师号="+to_String(to_int(para));
		}
	}
	else//找到=  自动加引号
	{
		position = para.find("=");
		temp.insert(position+1,"'");
		temp = temp + "';";
	}
	//para = subreplace(temp, "教师号","teachers.教师号");
	para = temp;
	const char *sql_para = para.data();
	sprintf_s(m_sqlBuf, 1024, "select * from teachers inner join salaries using (教师号) where %s",sql_para);
    if(mysql_query(m_hMysql, m_sqlBuf))        //执行SQL语句
    {
        printf("执行失败 (%s)\n",mysql_error(m_hMysql));
		system("pause");
        return false;
    }
    else
    {
        printf("查询成功\n");
    }

	//获取结果集
    if (!(m_result=mysql_store_result(m_hMysql)))    //获得sql语句结束后返回的结果集
    {
        printf("无法获取结果从： %s\n", mysql_error(m_hMysql));
        return false;
    }
 
    //打印数据行数
	system("cls");
    printf("结果总行数: %d\n",mysql_affected_rows(m_hMysql));
	printf("结果总列数: %d\n\n\n",mysql_field_count(m_hMysql));
    //获取字段的信息
    char *str_field[32];  //定义一个字符串数组存储字段信息
    for(int i=0;i<mysql_field_count(m_hMysql);i++)   //在已知字段数量的情况下获取字段名
    {
        str_field[i]=mysql_fetch_field(m_result)->name;
    }
    for(int i=0;i<(int)mysql_field_count(m_hMysql);i++)   //打印字段
        printf("%10s\t",str_field[i]);
    printf("\n");
    //打印获取的数据
    while (m_row = mysql_fetch_row(m_result))   //在已知字段数量情况下，获取并打印下一行
    {
        //printf("%10s\t%10s\t%10s\t%10s\n", column[0], column[1], column[2],column[3]);  //column是列数组
		for(int i=0;i<(int)mysql_field_count(m_hMysql);i++) printf("%10s\t", m_row[i]); 
		printf("\n"); 
    }
	system("pause");
	system("cls");
}


int CDBMysql::select_All()
{
	system("cls");
	string::size_type position;
	string para[3];
	TipSelectAll();
	cin >> para[0];
	cin >> para[1];
	cin >> para[2];
	if(para[2]=="NULL") para[2]="";
	else 
	{
		para[2]=" where "+para[2];
		position = para[2].find("=");
		para[2].insert(position+1,"'");
		para[2] = para[2] + "';";
	}
	if(para[0]=="信息表") para[0]="teachers";
	else if(para[0]=="工资表") para[0]="salaries";
	const char *sql_para[3] = {para[0].data(),para[1].data(),para[2].data()};

    sprintf(m_sqlBuf, "select %s from %s%s",sql_para[1],sql_para[0],sql_para[2]); //执行查询语句，这里是查询所有，user是表名，不用加引号，用strcpy也可以
    mysql_query(m_hMysql,"set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
    //返回0 查询成功，返回1查询失败
    if(mysql_query(m_hMysql, m_sqlBuf))        //执行SQL语句
    {
        printf("[警告]执行失败 (%s)\n",mysql_error(m_hMysql));
		system("pause");
        return false;
    }
    else
    {
        printf("[提示]执行成功\n");
    }
    //获取结果集
    if (!(m_result=mysql_store_result(m_hMysql)))    //获得sql语句结束后返回的结果集
    {
        printf("无法获取结果从： %s\n", mysql_error(m_hMysql));
        return false;
    }
 
    //打印数据行数
	system("cls");
    printf("结果总行数: %d\n",mysql_affected_rows(m_hMysql));
	printf("结果总列数: %d\n\n\n",mysql_field_count(m_hMysql));
    //获取字段的信息
    char *str_field[32];  //定义一个字符串数组存储字段信息
    for(int i=0;i<mysql_field_count(m_hMysql);i++)   //在已知字段数量的情况下获取字段名
    {
        str_field[i]=mysql_fetch_field(m_result)->name;
    }
    for(int i=0;i<mysql_field_count(m_hMysql);i++)   //打印字段
        printf("%10s\t",str_field[i]);
    printf("\n");
    //打印获取的数据
    while (m_row = mysql_fetch_row(m_result))   //在已知字段数量情况下，获取并打印下一行
    {
        //printf("%10s\t%10s\t%10s\t%10s\n", column[0], column[1], column[2],column[3]);  //column是列数组
		for(int i=0;i<mysql_field_count(m_hMysql);i++) printf("%10s\t", m_row[i]); 
		printf("\n"); 
    }
	system("pause");
    return true;
}

int CDBMysql::selectStatistic()
{
	system("cls");
	string para;
	TipStatis();
	cin >> para;
	const char *sql_para = para.data();
	
    sprintf_s(m_sqlBuf, 1024, "select 教师号,基本工资+津贴+生活补贴 as '应发工资',电话费+水电费+房租+所得税+卫生费+公积金 as 合计扣款,基本工资+津贴+生活补贴-电话费-水电费-房租-所得税-卫生费-公积金 as '实发工资' from salaries where 教师号=%s",sql_para); 
    //返回0 查询成功，返回1查询失败
    if(mysql_query(m_hMysql, m_sqlBuf))        //执行SQL语句
    {
        printf("[警告]执行失败 (%s)\n",mysql_error(m_hMysql));
		system("pause");
        return false;
    }
    else
    {
        printf("[提示]执行成功\n");
    }
    //获取结果集
    if (!(m_result=mysql_store_result(m_hMysql)))    //获得sql语句结束后返回的结果集
    {
        printf("无法获取结果从： %s\n", mysql_error(m_hMysql));
		system("pause");
        return false;
    }
 
    //打印数据行数
	system("cls");
    printf("结果总行数: %d\n",mysql_affected_rows(m_hMysql));
	printf("结果总列数: %d\n\n\n",mysql_field_count(m_hMysql));
    //获取字段的信息
    char *str_field[32];  //定义一个字符串数组存储字段信息
    for(int i=0;i<mysql_field_count(m_hMysql);i++)   //在已知字段数量的情况下获取字段名
    {
        str_field[i]=mysql_fetch_field(m_result)->name;
    }
    for(int i=0;i<mysql_field_count(m_hMysql);i++)   //打印字段
        printf("%10s\t",str_field[i]);
    printf("\n");
    //打印获取的数据
    while (m_row = mysql_fetch_row(m_result))   //在已知字段数量情况下，获取并打印下一行
    {
        //printf("%10s\t%10s\t%10s\t%10s\n", column[0], column[1], column[2],column[3]);  //column是列数组
		for(int i=0;i<mysql_field_count(m_hMysql);i++) printf("%10s\t", m_row[i]); 
		printf("\n"); 
    }
	system("pause");
}

int CDBMysql::ModifyTeacherInfo()
{
	system("cls");
	string para[3];
	string::size_type position;
	TipModifyTeacher();
	cin >> para[2];
	if(para[2]=="NULL") para[2]="";
	else para[2]=" where "+para[2];
	cin >> para[0];
	cin >> para[1];
	position = para[2].find("=");
	para[2].insert(position+1,"'");
	para[2] = para[2] + "';";
	const char *sql_para[3] = {para[0].data(),para[1].data(),para[2].data()};
    sprintf_s(m_sqlBuf, 1024, "update teachers set %s='%s'%s",sql_para[0],sql_para[1],sql_para[2]);
    if(mysql_query(m_hMysql, m_sqlBuf))        //执行SQL语句
    {
        printf("修改失败 (%s)\n",mysql_error(m_hMysql));
        return false;
    }
    else
    {
        printf("修改成功\n");
        return true;
    }
}

int CDBMysql::ModifySalaryInfo()
{
	system("cls");
	string para[3];
	string::size_type position;
	TipModifySalary();
	cin >> para[2];
	if(para[2]=="NULL") para[2]="";
	else para[2]=" where "+para[2];
	cin >> para[0];
	cin >> para[1];
	position = para[2].find("=");
	para[2].insert(position+1,"'");
	para[2] = para[2] + "';";
	const char *sql_para[3] = {para[0].data(),para[1].data(),para[2].data()};
    sprintf(m_sqlBuf, "update salaries set %s='%s'%s",sql_para[0],sql_para[1],sql_para[2]);
    if(mysql_query(m_hMysql, m_sqlBuf))         //执行SQL语句
    {
        printf("修改失败 (%s)\n",mysql_error(m_hMysql));
        return false;
    }
    else
    {
        printf("修改成功\n");
        return true;
    }
}

