#pragma once

#include <mysql.h>
#include <locale.h>
#include <vector>

typedef struct tagStudentInfo{
	int		id;
	char	name[20];
	bool	sex;
} StudnetInfo;

class CDBMysql
{
public:
	CDBMysql(const char* host,const char* user,const char* passwd,const char* db,unsigned int port);
	virtual ~CDBMysql();

private:
	MYSQL			m_mysql;
	MYSQL		*	m_hMysql;		// �������ݿ����ӵľ�����������ڼ������е� MySQL����
	MYSQL_RES	*	m_result;		// ��ѯ��������ṹ����
	MYSQL_FIELD	*	m_fd;			// �����ֶ���Ϣ�Ľṹ
	MYSQL_ROW		m_row;			// ���һ�в�ѯ������ַ�������
	char			m_sqlBuf[1024];	// ��Ų�ѯsql����ַ���
	/////////////////////////////////////////////////////////////
	void TipInsertTeacher();
	void TipInsertSalary();
	void TipDeleteTeacher();
	void TipDeleteSalary();
	void TipSelect();
	void TipStatis();
	void TipSelectAll();
	void TipModifyTeacher();
	void TipModifySalary();
public:
	
	int selectOneStudent(int id, StudnetInfo* stuInfo);
	int selectAllStudent(StudnetInfo** stuInfoList, int* stuNumber);
	int insertStudentInfo(int id, const char* name, bool sex);
	int CDBHome();
	/////////////////////////////////////////////////////////////
	int insertTeacherInfo();
	int insertSalaryInfo();
	int deleteTeacherInfo();
	int deleteSalaryInfo();
	int selectInfo();
	int selectStatistic();
	int select_All();
	int ModifyTeacherInfo();
	int ModifySalaryInfo();
	
	//int SplitString(const const char *  str, char split, std::vector<const char * >& strList);
};

void ShowMenu();