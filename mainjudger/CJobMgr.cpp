#include "stdafx.h"
#include "JobMgr.h"
#include "Worker.h"

#include <process.h>
CJobMgr::CJobMgr()
{
	m_pDBOpera = new CDBOpera();

}
CJobMgr::~CJobMgr()
{
	delete m_pDBOpera;
}

void CJobMgr::Start()
{
	_beginthread(CJobMgr::JobMgrThread, 0, this);
}

void CJobMgr::JobMgrThread(void * pThisObj)
{
	CJobMgr * pThis = (CJobMgr*)pThisObj;
	while (true)
	{
		if (pThis->HasNewJob())
		{
			std::cout << "has new job" << std::endl;
			CWorker * pNewWorker = new CWorker();
			_beginthread(CWorker::WorkFlowThread, 0, pNewWorker);
			Sleep(10000);
		}
		else
		{
			std::cout << "don't has new job" << std::endl;
			Sleep(20000);
		}

	}
}

bool CJobMgr::HasNewJob()
{
	if (m_pDBOpera->HasUnhandleJob())
	{
		return true;
	}
	
	return false;
}