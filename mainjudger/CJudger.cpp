#include "stdafx.h"
#include "Judger.h"
#include "JobMgr.h"

CJudger::CJudger()
{
	m_pJobMgr = new CJobMgr();
}

CJudger::~CJudger()
{

}

bool CJudger::Start()
{
	std::cout << "Started" << std::endl;
	_beginthread(CJudger::JobMgrThread, 0, this);
	return true;
}

bool CJudger::ShutDown()
{
	return true;
}

void CJudger::JobMgrThread(void * pThisObj)
{
	CJudger *  pThis = (CJudger *)pThisObj;

	std::cout << "i am CJudger::JobMgrThread" << std::endl;
	pThis->m_pJobMgr->Start();
}