#include "stdafx.h"
#include "DBOpera.h"
#include "Record.h"
#include <cstdlib>
#include <ctime>

CDBOpera::CDBOpera()
{
	m_pMysqlCon = mysql_init(NULL);
	if (!Connect())
	{
		Sleep(100000000);
		exit(EXIT_FAILURE);
	}
	
}
CDBOpera::CDBOpera(char * szHost, char * szUser, char * szPassword, char * szDBName)
{
	m_Host = szHost;
	m_User = szUser;
	m_Password = szPassword;
	m_DBName = szDBName;

	m_pMysqlCon = mysql_init(NULL);
	if (!Connect())
	{
		Sleep(100000000);
		exit(EXIT_FAILURE);
	}
}

CDBOpera::~CDBOpera()
{
	Close();
}

bool CDBOpera::Connect()
{
	if (!mysql_real_connect(m_pMysqlCon, m_Host.c_str(), m_User.c_str(), m_Password.c_str(), m_DBName.c_str(), 3306, NULL, 0))
	{
		std::cerr << "Connection Failed" << std::endl;
		if (mysql_errno(m_pMysqlCon))
		{
			std::cerr << "Connection error " << mysql_errno(m_pMysqlCon) << ":" << mysql_error(m_pMysqlCon);
		}
		return false;
	}
	std::cout << "Connection success" << std::endl;
	return true;
}

void CDBOpera::Close()
{
	mysql_close(m_pMysqlCon);
}

bool CDBOpera::HasUnhandleJob()
{
	char szSql[] = "SELECT COUNT(id) FROM oj_submitedrecord WHERE result=0 LIMIT 1";
	int res;
	res = mysql_query(m_pMysqlCon, szSql);
	if (res)	//0 means OK, other not ok
	{
		std::cerr << "SELECT error " << mysql_errno(m_pMysqlCon) << ":" << mysql_error(m_pMysqlCon);
		return false;
	}else{
		m_pResultSet = mysql_store_result(m_pMysqlCon);	//若遇到错误则返回NULL
		if (m_pResultSet)
		{
			m_OneRow = mysql_fetch_row(m_pResultSet);
			int unHandleRecordsCount = atoi(m_OneRow[0]);

			//释放结果集
			mysql_free_result(m_pResultSet);
			
			//返回是否有未处理的记录
			if (unHandleRecordsCount > 0)
			{
				return true;
			}else{
				return false;
			}


		}
		else
		{
			std::cerr << "Store result error " << mysql_errno(m_pMysqlCon) << ":" << mysql_error(m_pMysqlCon);
			return false;
		}
	}
}

CRecord CDBOpera::GetAJob()
{
	/*
	int m_id;
	int m_uid;
	int m_pid;
	int m_language;
	std::string m_source;
	int m_result;
	std::string m_compliermsg;
	int m_memorycost;
	int m_timecost;
	int m_codelength;
	int m_postdate;
	*/
	CRecord record;
	char szSql[] = "SELECT id,uid,pid,language,source FROM oj_submitedrecord WHERE result=0 LIMIT 1";
	int res;
	res = mysql_query(m_pMysqlCon, szSql);
	if (res)	//0 means OK, other not ok
	{
		std::cerr << "GetAJob error " << mysql_errno(m_pMysqlCon) << ":" << mysql_error(m_pMysqlCon);
		record.m_bIsNull = true;
	}
	else{
		m_pResultSet = mysql_store_result(m_pMysqlCon);	//若遇到错误则返回NULL
		if (m_pResultSet)
		{
			m_OneRow = mysql_fetch_row(m_pResultSet);
			record.m_bIsNull = false;
			record.m_id = atoi(m_OneRow[0]);
			record.m_uid = atoi(m_OneRow[1]);
			record.m_pid = atoi(m_OneRow[2]);
			record.m_language = atoi(m_OneRow[3]);
			record.m_source = m_OneRow[4];
			record.m_result = 0;

			//释放结果集
			mysql_free_result(m_pResultSet);

		}
		else
		{
			std::cerr << "Store result error " << mysql_errno(m_pMysqlCon) << ":" << mysql_error(m_pMysqlCon);
		}
	}

	return record;

}

bool CDBOpera::WriteComplierResultToDB(int id, int result, std::string & compliermsg)
{
	char szSqlBuffer[2000];
	char szEscStr[2000];
	mysql_escape_string(szEscStr, compliermsg.c_str(), compliermsg.length());

	sprintf_s(szSqlBuffer, "UPDATE oj_submitedrecord SET result='%d',compliermsg='%s' WHERE id='%d' LIMIT 1", result, szEscStr, id);
	std::cout << "szSqlBuffer = \n" << szSqlBuffer << std::endl;
	int res;
	res = mysql_query(m_pMysqlCon, szSqlBuffer);
	if (res)	//0 means OK, other not ok
	{
		std::cerr << "UPDATE error " << mysql_errno(m_pMysqlCon) << ":" << mysql_error(m_pMysqlCon);
		return false;
	}
	else{
		return true;
	}


}


bool CDBOpera::GetRandAnswerByPID(int pid, int * timelimit, int * memorylimit, std::string & input, std::string & output)
{
	
	char szSql[200];
	//std::srand((int)time(0));
	int iRand = 1;//rand() % 10;
	
	sprintf_s(szSql, "SELECT timelimit,memorylimit,input%d,output%d FROM oj_problem WHERE id=%d LIMIT 1", iRand, iRand, pid);
	
	int res;
	res = mysql_query(m_pMysqlCon, szSql);
	if (res)	//0 means OK, other not ok
	{
		std::cerr << "GetRandAnswer error " << mysql_errno(m_pMysqlCon) << ":" << mysql_error(m_pMysqlCon);
		return false;
	}
	else
	{
		m_pResultSet = mysql_store_result(m_pMysqlCon);	//若遇到错误则返回NULL
		if (m_pResultSet)
		{
			m_OneRow = mysql_fetch_row(m_pResultSet);
			
			*timelimit = atoi(m_OneRow[0]);
			*memorylimit = atoi(m_OneRow[1]);
			input = m_OneRow[2];
			output = m_OneRow[3];
			
			//释放结果集
			mysql_free_result(m_pResultSet);
			return true;

		}
		else
		{
			std::cerr << "Store result error " << mysql_errno(m_pMysqlCon) << ":" << mysql_error(m_pMysqlCon);
			return false;
		}
	}
}