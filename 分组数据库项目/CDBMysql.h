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
	MYSQL		*	m_hMysql;		// 定义数据库连接的句柄，它被用于几乎所有的 MySQL函数
	MYSQL_RES	*	m_result;		// 查询结果集，结构类型
	MYSQL_FIELD	*	m_fd;			// 包含字段信息的结构
	MYSQL_ROW		m_row;			// 存放一行查询结果的字符串数组
	char			m_sqlBuf[1024];	// 存放查询sql语句字符串
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