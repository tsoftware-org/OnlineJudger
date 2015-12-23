#ifndef RUNNER_H_
#define RUNNER_H_
#include "Record.h"
#include "DBOpera.h"

class CRunner
{
private:
	CRecord * m_pRecord;
	CDBOpera * m_pDBOpera;
	std::string m_runCmd;
	std::string m_runInPutParamFilePath;
	std::string m_runOutPutResultFilePath;

	bool DoSysCall();

public:
	CRunner(CRecord & record, CDBOpera & dbopera);
	~CRunner();
	bool Run();
	bool PreGenInputFile();


};
#endif