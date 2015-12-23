// mainjudger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Judger.h"
#include <windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	CJudger * pJudger = new CJudger();
	std::cout << "Program Now Starting..." << std::endl;
	pJudger->Start();

	//wait for shut down event
	HANDLE hEvent = ::CreateEvent(NULL, FALSE, FALSE, _T("ShutDownEvent"));
	::WaitForSingleObject(hEvent, INFINITE);
	::CloseHandle(hEvent);
	//shut down the program
	pJudger->ShutDown();
	delete pJudger;
	std::cout << "CwnuJudger Stoped! Thx For Your Support!" << std::endl;
	return 0;
}

