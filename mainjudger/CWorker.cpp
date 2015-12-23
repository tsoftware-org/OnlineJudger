#include "stdafx.h"
#include "Worker.h"
CWorker::CWorker()
{
	m_pDBOpera = new CDBOpera;
	m_pRecord = new CRecord;
	m_pComplier = new CComplier(*m_pRecord, *m_pDBOpera);
	m_pRunner = new CRunner(*m_pRecord, *m_pDBOpera);
	m_pMatcher = new CMatcher(*m_pRecord, *m_pDBOpera);
}
CWorker::~CWorker()
{
	delete m_pDBOpera;
	delete m_pRecord;
}

void CWorker::WorkFlowThread(void * pThisObj)
{
	CWorker * pThis = (CWorker *)pThisObj;
	std::cout << "i am now in WorkFlowThread!" << std::endl;
	//Sleep(20000);
	*(pThis->m_pRecord) = pThis->m_pDBOpera->GetAJob();
	//std::cout << pThis->m_pRecord->m_source << std::endl;
	pThis->m_pRecord->GenSourceFile();
	pThis->m_pComplier->Complie();
	pThis->m_pMatcher->FetchInputStr();
	pThis->m_pRunner->Run();

}