#ifndef WORKER_H_
#define WORKER_H_
#include "DBOpera.h"
#include "Record.h"
#include "Complier.h"
#include "Runner.h"
#include "Matcher.h"

class CWorker
{
private:
	CDBOpera * m_pDBOpera;
	CRecord * m_pRecord;
	CComplier * m_pComplier;
	CRunner * m_pRunner;
	CMatcher * m_pMatcher;

public:
	CWorker();
	~CWorker();
	static void WorkFlowThread(void * pThisObj);



};
#endif