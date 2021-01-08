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
		cout << "-------------��ӭʹ�ý�ʦ���ʹ���ϵͳ-----------" << endl;
		cout << "-----------------0.�˳��������-----------------" << endl;
		cout << "-----------------1.���ӽ�ʦ��¼-----------------" << endl;
		cout << "-----------------2.���ӹ��ʼ�¼-----------------" << endl;
		cout << "-----------------3.ɾ����ʦ��¼-----------------" << endl;
		cout << "-----------------4.ɾ��������Ϣ-----------------" << endl;
		cout << "-----------------5.�ۺϲ�ѯ---------------------" << endl;
		cout << "-----------------6.�򵥲�ѯ---------------------" << endl;
		cout << "-----------------7.ͳ����Ϣ---------------------" << endl;
		cout << "-----------------8.�޸Ľ�ʦ��Ϣ-----------------" << endl;
		cout << "-----------------9.�޸Ĺ�����Ϣ-----------------" << endl;
		cout << "------------------------------------------------" << endl;
		cin>>choice;
		switch (choice) {
			case 0:   //�˳�����ϵͳ
				cout<<"[��ʾ]��ȴ�Ƭ�̣������ر����ݿ�..."<<endl;
				cout<<"[��ʾ]��ӭ���´�ʹ��"<<endl;
				system("net stop mysql");
				break;
			case 1:   //���ӽ�ʦ��¼
				insertTeacherInfo();
				break;
			case 2:   //���ӹ��ʼ�¼
				insertSalaryInfo();
				break;
			case 3:   //ɾ����ʦ��¼
				deleteTeacherInfo();
				break;
			case 4:   //ɾ��������Ϣ
				deleteSalaryInfo();
				break;
			case 5:  
				selectInfo();
				break;
			case 6:   
				select_All();
				break;
			case 7:   //ͳ����Ϣ
				selectStatistic();
				break;
			case 8:   //�޸Ľ�ʦ��Ϣ
				ModifyTeacherInfo();
				break;
			case 9:   //�޸Ĺ�����Ϣ
				ModifySalaryInfo();
				break;
			default:
				system("cls");//��ա�ˢ����Ļ
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

	sprintf_s(m_sqlBuf, 1024, "select ��ʦ��, �Ա�, from teachears");
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
//	sprintf_s(m_sqlBuf, 1024, "insert into teachers (��ʦ��, ����, �Ա�, ��λ����, ��ͥסַ, ��ϵ�绰) values (%d, '%s', '%s', '%s', '%s', '%s')", id, name, sex, company, address, tel);
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
//	sprintf_s(m_sqlBuf, 1024, "insert into salaries (��ʦ��, ��������, ����, �����, �绰��, ˮ���, ����, ����˰, ������, ������) values (%d, %d, %d, %d, %d, %d, %d, %d, %d, %d)", id, baseSalary, subsidy, assistance, telCharge, cost, roomCharge, tax, healthCost, funds);
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
	cout<<"[��ʾ]���������һ���½�ʦ..."<<endl<<endl;
	cout<<"[��ʾ]���Կո�ָ������ʦ��š��������Ա𡢵�λ���ơ���ͥסַ����ϵ�绰��"<<endl;
	cout<<"[��ʾ]����δ֪��ĳЩ��Ϣ�����á�NULL�����棬�����Գ����������룺"<<endl;
	cout<<"[ʾ��]001 ���� NULL �ൺ����ѧ ���꽭��·777�� 18888888888"<<endl;
}

void CDBMysql::TipInsertSalary()
{
	cout<<"[��ʾ]���������һ���½�ʦ����..."<<endl<<endl;
	cout<<"[��ʾ]���Կո�ָ������ʦ��š��������ʡ���������������绰�ѡ�ˮ��ѡ����⡢����˰�������ѡ�������"<<endl;
	cout<<"[ʾ��]001 11 22 33 44 55 66 77 88 99"<<endl;
	cout<<"[��ʾ]����δ֪��ĳЩ��Ϣ�����á�NULL�����棺"<<endl;
}

void CDBMysql::TipDeleteTeacher()
{
	cout<<"[��ʾ]������ɾ��һ����ʦ..."<<endl<<endl;
	cout<<"[��ʾ]������ɾ����ʦ������������"<<endl;
	cout<<"[��ʾ]��ʦ��Ϣ���пɹ�������������������ʦ�š��������Ա𡢵�λ���ơ���ͥסַ����ϵ�绰"<<endl<<endl;
	cout<<"[��ʾ]�����Գ�������������������ԣ�"<<endl;
	cout<<"[ʾ��]��ʦ��=0001"<<endl;
	cout<<"[ʾ��]ɾ���н�ʦ"<<endl;
	cout<<"[ʾ��]ɾ��������"<<endl;
	cout<<"[ʾ��]ȥ�������Ů��ʦ"<<endl;
	cout<<"[ʾ��]����˵ĵ绰��18888888888"<<endl<<endl;
	cout<<"[��ʾ]����ɾ����λ��סַ��ֻ�ɰ����¸�ʽ���룺"<<endl;
	cout<<"[ʾ��]��λ����=�ൺ����ѧ"<<endl;
	cout<<"[ʾ��]��ͥסַ=���꽭��·777��"<<endl;
}

void CDBMysql::TipDeleteSalary()
{
	cout<<"[��ʾ]������ɾ��һ����ʦ����..."<<endl<<endl;
	cout<<"[��ʾ]������ɾ����ʦ���ʵ�����������"<<endl;
	cout<<"[��ʾ]��ʦ���ʱ��пɹ�������������������ʦ�š��������ʡ���������������绰�ѡ�ˮ��ѡ����⡢����˰�������ѡ�������"<<endl;
	cout<<"[��ʾ]�����������������룺"<<endl;
	cout<<"[ʾ��]��ʦ��=0001"<<endl;
	cout<<"[ʾ��]��������<0"<<endl;
	cout<<"[ʾ��]��������<0 and ��ʦ��=0001"<<endl;
	cout<<"[ʾ��]��������<0 or ��ʦ��=0001"<<endl;
}

void CDBMysql::TipSelect()
{
	cout<<"[��ʾ]�����ڲ�ѯ��ʦ��Ϣ..."<<endl<<endl;
	cout<<"[��ʾ]�������ѯ��ʦ������������"<<endl;
	cout<<"[��ʾ]�ۺ���Ϣ���пɹ�������������������ʦ�š��������Ա𡢵�λ���ơ���ͥסַ����ϵ�绰"<<endl;
	cout<<"      �������ʡ���������������绰�ѡ�ˮ��ѡ����⡢����˰�������ѡ�������"<<endl;
	cout<<"[��ʾ]�����Գ�������������������ԣ�"<<endl;
	cout<<"[ʾ��]��ʦ��=0001"<<endl;
	cout<<"[ʾ��]��ʦ����0003"<<endl;
	cout<<"[ʾ��]�е�"<<endl;
	cout<<"[ʾ��]������"<<endl;
	cout<<"[ʾ��]������"<<endl;
	cout<<"[ʾ��]�����Ů��"<<endl;
	cout<<"[ʾ��]Ta�绰��18888888888"<<endl<<endl;
	cout<<"[��ʾ]������ѯ��λ��סַ��ֻ�ɰ����¸�ʽ���룺"<<endl;
	cout<<"[ʾ��]��λ����=�ൺ����ѧ"<<endl;
	cout<<"[ʾ��]��ͥסַ=���꽭��·777��"<<endl;
}
	
void CDBMysql::TipStatis()
{
	cout<<"[��ʾ]������ͳ�ƽ�ʦ����..."<<endl<<endl;
	cout<<"[��ʾ]�������ѯ�Ľ�ʦ�ţ�"<<endl;
}

void CDBMysql::TipModifyTeacher()
{
	cout<<"[��ʾ]�������޸Ľ�ʦ��Ϣ..."<<endl<<endl;
	cout<<"[��ʾ]��ʦ��Ϣ���пɹ�������������������ʦ�š��������Ա𡢵�λ���ơ���ͥסַ����ϵ�绰"<<endl<<endl;
	cout<<"[��ʾ]������Ҫ������Ϊ����ݹ顱���Ա��޸�ΪŮ�������������룺"<<endl;
	cout<<"[ʾ��]����=��ݹ� �Ա� Ů"<<endl;
	cout<<"[��ʾ]�����룺"<<endl;
}

void CDBMysql::TipModifySalary()
{
	cout<<"[��ʾ]�������޸Ľ�ʦ����..."<<endl<<endl;
	cout<<"[��ʾ]��ʦ���ʱ��пɹ�������������������ʦ�š��������ʡ���������������绰�ѡ�ˮ��ѡ����⡢����˰�������ѡ�������"<<endl;
	cout<<"[��ʾ]������Ҫ����ʦ��Ϊ002�Ļ��������޸�Ϊ100�������������룺"<<endl;
	cout<<"[ʾ��]��ʦ��=002 �������� 100"<<endl;
	cout<<"[��ʾ]�����룺"<<endl;
}

void CDBMysql::TipSelectAll()
{
	cout<<"[��ʾ]�����ڽ��м򵥲�ѯ..."<<endl<<endl;
	cout<<"[��ʾ]�������ѯ���ʱ��н�ʦ��Ϊ001�Ļ������ʺ͹����𣬿��԰��������룺"<<endl<<endl;
	cout<<"[ʾ��]���ʱ� ��������,������ ��ʦ��=001"<<endl;
	cout<<"[��ʾ]�����룺"<<endl;
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
		printf("����ʧ�� (%s)\n",mysql_error(m_hMysql));
		system("pause");
		return false;
	}
	else
	{
		printf("����ɹ�\n");
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
		printf("����ʧ�� (%s)\n",mysql_error(m_hMysql));
		system("pause");
		return false;
	}
	else
	{
		printf("����ɹ�\n");
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
	if(para.find("=") == para.npos) //δ�ҵ�=
	{
		if(para.find("��") == para.npos)	//δ�ҵ���
		{
			if(para.find("Ů") == para.npos) temp ="NULL";//δ�ҵ�Ů
			else  temp = "�Ա�='Ů'";      //�ҵ�Ů
		}
		else if(para.find("Ů") == para.npos)  temp = "�Ա�='��'"; //�ҵ���δ�ҵ�Ů
		else temp = "�Ա�='��' or �Ա�='Ů'";

		position = para.find("��");
		if(position != para.npos)//�ҵ�����
		{
			if(temp=="NULL") temp="���� like '"+ChineseStringSubstr(para,position+2,position+4)+"%';";
			else temp=temp+" and "+"���� like '"+ChineseStringSubstr(para,position+2,position+4)+"%';";
		}
		
		if(para.find("�绰") != para.npos) //�ҵ��˵绰 
		{
			if((temp=="NULL")) temp = "��ϵ�绰="+to_String(to_int(para));
			else temp=temp+" and "+"��ϵ�绰="+to_String(to_int(para));
		}

		if(para.find("��ʦ��") != para.npos) //�ҵ��˽�ʦ�� 
		{
			if((temp=="NULL")) temp = "��ʦ��="+to_String(to_int(para));
			else temp=temp+" and "+"��ʦ��="+to_String(to_int(para));
		}
	}
	else//�ҵ�=  �Զ�������
	{
		position = para.find("=");
		temp.insert(position+1,"'");
		temp = temp + "';";
	}

	para = temp;
	const char *sql_para = para.data();
	sprintf_s(m_sqlBuf, 1024, "delete from teachers where %s;",sql_para);
    if(mysql_query(m_hMysql, m_sqlBuf))        //ִ��SQL���
    {
        printf("ִ��ʧ�� (%s)\n",mysql_error(m_hMysql));
		system("pause");
        return false;
    }
    else
    {
        printf("ִ�гɹ�\n");
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
    if(mysql_query(m_hMysql, m_sqlBuf))        //ִ��SQL���
    {
        printf("ִ��ʧ�� (%s)\n",mysql_error(m_hMysql));
		system("pause");
        return false;
    }
    else
    {
        printf("ִ�гɹ�\n");
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
	if(para.find("=") == para.npos) //δ�ҵ�=
	{
		if(para.find("��") == para.npos)	//δ�ҵ���
		{
			if(para.find("Ů") == para.npos) temp ="NULL";//δ�ҵ�Ů
			else  temp = "�Ա�='Ů'";      //�ҵ�Ů
		}
		else if(para.find("Ů") == para.npos)  temp = "�Ա�='��'"; //�ҵ���δ�ҵ�Ů
		else temp = "�Ա�='��' or �Ա�='Ů'";

		position = para.find("��");
		if(position != para.npos)//�ҵ�����
		{
			if(temp=="NULL") temp="���� like '"+ChineseStringSubstr(para,position+2,position+4)+"%';";
			else temp=temp+" and "+"���� like '"+ChineseStringSubstr(para,position+2,position+4)+"%';";
		}
		
		if(para.find("�绰") != para.npos) //�ҵ��˵绰 
		{
			if((temp=="NULL")) temp = "��ϵ�绰="+to_String(to_int(para));
			else temp=temp+" and "+"��ϵ�绰="+to_String(to_int(para));
		}

		if(para.find("��ʦ��") != para.npos) //�ҵ��˽�ʦ�� 
		{
			if((temp=="NULL")) temp = "��ʦ��="+to_String(to_int(para));
			else temp=temp+" and "+"��ʦ��="+to_String(to_int(para));
		}
	}
	else//�ҵ�=  �Զ�������
	{
		position = para.find("=");
		temp.insert(position+1,"'");
		temp = temp + "';";
	}
	//para = subreplace(temp, "��ʦ��","teachers.��ʦ��");
	para = temp;
	const char *sql_para = para.data();
	sprintf_s(m_sqlBuf, 1024, "select * from teachers inner join salaries using (��ʦ��) where %s",sql_para);
    if(mysql_query(m_hMysql, m_sqlBuf))        //ִ��SQL���
    {
        printf("ִ��ʧ�� (%s)\n",mysql_error(m_hMysql));
		system("pause");
        return false;
    }
    else
    {
        printf("��ѯ�ɹ�\n");
    }

	//��ȡ�����
    if (!(m_result=mysql_store_result(m_hMysql)))    //���sql�������󷵻صĽ����
    {
        printf("�޷���ȡ����ӣ� %s\n", mysql_error(m_hMysql));
        return false;
    }
 
    //��ӡ��������
	system("cls");
    printf("���������: %d\n",mysql_affected_rows(m_hMysql));
	printf("���������: %d\n\n\n",mysql_field_count(m_hMysql));
    //��ȡ�ֶε���Ϣ
    char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ
    for(int i=0;i<mysql_field_count(m_hMysql);i++)   //����֪�ֶ�����������»�ȡ�ֶ���
    {
        str_field[i]=mysql_fetch_field(m_result)->name;
    }
    for(int i=0;i<(int)mysql_field_count(m_hMysql);i++)   //��ӡ�ֶ�
        printf("%10s\t",str_field[i]);
    printf("\n");
    //��ӡ��ȡ������
    while (m_row = mysql_fetch_row(m_result))   //����֪�ֶ���������£���ȡ����ӡ��һ��
    {
        //printf("%10s\t%10s\t%10s\t%10s\n", column[0], column[1], column[2],column[3]);  //column��������
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
	if(para[0]=="��Ϣ��") para[0]="teachers";
	else if(para[0]=="���ʱ�") para[0]="salaries";
	const char *sql_para[3] = {para[0].data(),para[1].data(),para[2].data()};

    sprintf(m_sqlBuf, "select %s from %s%s",sql_para[1],sql_para[0],sql_para[2]); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����
    mysql_query(m_hMysql,"set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������
    //����0 ��ѯ�ɹ�������1��ѯʧ��
    if(mysql_query(m_hMysql, m_sqlBuf))        //ִ��SQL���
    {
        printf("[����]ִ��ʧ�� (%s)\n",mysql_error(m_hMysql));
		system("pause");
        return false;
    }
    else
    {
        printf("[��ʾ]ִ�гɹ�\n");
    }
    //��ȡ�����
    if (!(m_result=mysql_store_result(m_hMysql)))    //���sql�������󷵻صĽ����
    {
        printf("�޷���ȡ����ӣ� %s\n", mysql_error(m_hMysql));
        return false;
    }
 
    //��ӡ��������
	system("cls");
    printf("���������: %d\n",mysql_affected_rows(m_hMysql));
	printf("���������: %d\n\n\n",mysql_field_count(m_hMysql));
    //��ȡ�ֶε���Ϣ
    char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ
    for(int i=0;i<mysql_field_count(m_hMysql);i++)   //����֪�ֶ�����������»�ȡ�ֶ���
    {
        str_field[i]=mysql_fetch_field(m_result)->name;
    }
    for(int i=0;i<mysql_field_count(m_hMysql);i++)   //��ӡ�ֶ�
        printf("%10s\t",str_field[i]);
    printf("\n");
    //��ӡ��ȡ������
    while (m_row = mysql_fetch_row(m_result))   //����֪�ֶ���������£���ȡ����ӡ��һ��
    {
        //printf("%10s\t%10s\t%10s\t%10s\n", column[0], column[1], column[2],column[3]);  //column��������
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
	
    sprintf_s(m_sqlBuf, 1024, "select ��ʦ��,��������+����+����� as 'Ӧ������',�绰��+ˮ���+����+����˰+������+������ as �ϼƿۿ�,��������+����+�����-�绰��-ˮ���-����-����˰-������-������ as 'ʵ������' from salaries where ��ʦ��=%s",sql_para); 
    //����0 ��ѯ�ɹ�������1��ѯʧ��
    if(mysql_query(m_hMysql, m_sqlBuf))        //ִ��SQL���
    {
        printf("[����]ִ��ʧ�� (%s)\n",mysql_error(m_hMysql));
		system("pause");
        return false;
    }
    else
    {
        printf("[��ʾ]ִ�гɹ�\n");
    }
    //��ȡ�����
    if (!(m_result=mysql_store_result(m_hMysql)))    //���sql�������󷵻صĽ����
    {
        printf("�޷���ȡ����ӣ� %s\n", mysql_error(m_hMysql));
		system("pause");
        return false;
    }
 
    //��ӡ��������
	system("cls");
    printf("���������: %d\n",mysql_affected_rows(m_hMysql));
	printf("���������: %d\n\n\n",mysql_field_count(m_hMysql));
    //��ȡ�ֶε���Ϣ
    char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ
    for(int i=0;i<mysql_field_count(m_hMysql);i++)   //����֪�ֶ�����������»�ȡ�ֶ���
    {
        str_field[i]=mysql_fetch_field(m_result)->name;
    }
    for(int i=0;i<mysql_field_count(m_hMysql);i++)   //��ӡ�ֶ�
        printf("%10s\t",str_field[i]);
    printf("\n");
    //��ӡ��ȡ������
    while (m_row = mysql_fetch_row(m_result))   //����֪�ֶ���������£���ȡ����ӡ��һ��
    {
        //printf("%10s\t%10s\t%10s\t%10s\n", column[0], column[1], column[2],column[3]);  //column��������
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
    if(mysql_query(m_hMysql, m_sqlBuf))        //ִ��SQL���
    {
        printf("�޸�ʧ�� (%s)\n",mysql_error(m_hMysql));
        return false;
    }
    else
    {
        printf("�޸ĳɹ�\n");
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
    if(mysql_query(m_hMysql, m_sqlBuf))         //ִ��SQL���
    {
        printf("�޸�ʧ�� (%s)\n",mysql_error(m_hMysql));
        return false;
    }
    else
    {
        printf("�޸ĳɹ�\n");
        return true;
    }
}

