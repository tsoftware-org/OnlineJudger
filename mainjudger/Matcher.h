#ifndef MATCHER_H_
#define MATCHER_H_
#include "DBOpera.h"
#include "Record.h"
class CMatcher
{
private:
	CRecord * m_pRecord;
	CDBOpera * m_pDBOpera; 
	//int m_InputID;
	std::string m_InputStr;
	std::string m_InputFilePath;
	std::string m_OutputStr;

	//int m_TimeLimit;
	//int m_MemoryLimit;

public:
	CMatcher(CRecord & record, CDBOpera & dbopera);
	~CMatcher();
	//bool FetchInputStr();
	//bool GenInputFile();
	//bool FetchOutputStr();
	//bool CheckSame();

};

#endif
