#ifndef DBOPERA_H_
#define DBOPERA_H_

#include <windows.h>
#include <string>
#include "mysql.h"
#include "Record.h"
#include "Matcher.h"

class CDBOpera
{
private:
	MYSQL * m_pMysqlCon;
	MYSQL_RES * m_pResultSet;
	MYSQL_ROW m_OneRow;
	std::string m_Host = "127.0.0.1";
	std::string m_User = "root";
	std::string m_Password = "";
	std::string m_DBName = "test";

public:
	CDBOpera();
	CDBOpera(char * szHost, char * szUser, char * szPassword, char * szDBName);
	~CDBOpera();
	bool Connect();
	void Close();
	bool HasUnhandleJob();
	CRecord GetAJob();
	bool WriteComplierResultToDB(int id, int result, std::string & compliermsg);

	bool CDBOpera::GetRandAnswerByPID(int pid, int * timelimit, int * memorylimit, std::string & input, std::string & output);

};


#endif