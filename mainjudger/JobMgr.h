#ifndef JOBMGR_H_
#define JOBMGR_H_
#include "DBOpera.h"
class CJobMgr
{
public:
	CJobMgr();
	~CJobMgr();
	static void JobMgrThread(void * pThisObj);
	void Start();

protected:
private:
	CDBOpera * m_pDBOpera;
	bool HasNewJob();
};

#endif
