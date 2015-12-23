#ifndef JUDGER_H_
#define JUDGER_H_

#include <windows.h>
#include <process.h>
#include "JobMgr.h"

class CJudger
{
private:
	CJobMgr * m_pJobMgr;

	static void JobMgrThread(void * pThisObj);
public:
	CJudger();
	~CJudger();
	bool Start();
	bool ShutDown();


protected:
private:

};

#endif