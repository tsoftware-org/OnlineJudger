#ifndef COMPLIER_H_
#define COMPLIER_H_
#include "Record.h"
#include "DBOpera.h"

class CComplier
{
private:
	CRecord * m_pRecord;
	CDBOpera * m_pDBOpera;
	std::string m_complierCmd;
	std::string m_complierMsgFilePath;


	bool DoSysCall();
	bool GetComplierResult();
	bool WriteResultBacktoDB();

public:
	CComplier(CRecord & record, CDBOpera & dbopera);
	~CComplier();
	bool Complie();
	

};
#endif