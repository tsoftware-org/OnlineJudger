#include "stdafx.h"
#include "Runner.h"
#include <windows.h>
#include <winbase.h>
#include <Psapi.h>

CRunner::CRunner(CRecord & record, CDBOpera & dbopera)
{
	m_pRecord = &record;
	m_pDBOpera = &dbopera;
}
CRunner::~CRunner()
{

}

bool CRunner::Run()
{
	//char tmp[100];
	//sprintf_s(tmp, "%d", m_pRecord->m_id);

	switch (m_pRecord->m_language)
	{
	case CRecord::C:
		break;
	case CRecord::JAVA:
		break;
	case CRecord::CPP:
		m_runCmd = m_pRecord->m_ExeFilePath + ".exe";

		break;
	default:
		break;
	}

	std::cout << "Run Cmd is: " << m_runCmd << std::endl;
	//Sleep(20000);
	DoSysCall();
	return true;
}

bool CRunner::PreGenInputFile()
{
	
	return true;

}


bool CRunner::DoSysCall()
{
	STARTUPINFOA si;
	memset(&si, 0, sizeof(STARTUPINFO));//初始化si在内存块中的值（详见memset函数）
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_SHOW;
	SECURITY_ATTRIBUTES sa = { sizeof(sa),
		NULL,
		TRUE
	};

	char tmp[100];
	sprintf_s(tmp, "D:/tmp/%d.inp", m_pRecord->m_id);		//注意必须有这个文件夹,程序的输入参数
	m_runInPutParamFilePath = tmp;
	
	sprintf_s(tmp, "D:/tmp/%d.oup", m_pRecord->m_id);		//程序的输出都放到这个文件里
	m_runOutPutResultFilePath = tmp;

	LPSTR runInPutParamFilePath = (LPSTR)m_runInPutParamFilePath.c_str();
	LPSTR runOutPutResultFilePath = (LPSTR)m_runOutPutResultFilePath.c_str();
	HANDLE hInPutFile = CreateFileA(runInPutParamFilePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hOutPutFile = CreateFileA(runOutPutResultFilePath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	si.hStdInput = hInPutFile;
	si.hStdOutput = hOutPutFile;
	si.hStdError = hOutPutFile;

	PROCESS_INFORMATION pi;				//必备参数设置结束
	LPSTR cmd = (LPSTR)m_runCmd.c_str();


	SIZE_T maxMemory = 0;
	SIZE_T minMemory = 0;
	PROCESS_MEMORY_COUNTERS pmc;

	if (!CreateProcessA(NULL,
		cmd,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
		)){
		std::cout << "Run Fail!" << std::endl;
		exit(1);
	}
	else{
		
		/*while (true)
		{
			GetProcessMemoryInfo(pi.hProcess, &pmc, sizeof(pmc));
			if (pmc.PeakWorkingSetSize > maxMemory)
			{
				maxMemory = pmc.PeakPagefileUsage;
			}

			if (WaitForSingleObject(pi.hProcess, 0) == WAIT_OBJECT_0)
			{
				break;
			}
			

		}
		
		*/
		
		
		WaitForSingleObject(pi.hProcess, INFINITE);
		GetProcessMemoryInfo(pi.hProcess, &pmc, sizeof(pmc));
		GetProcessWorkingSetSize(pi.hProcess, &minMemory, &maxMemory);
		std::cout << minMemory << "----"<< maxMemory<< std::endl;
		std::cout <<"----" << pmc.PeakWorkingSetSize << std::endl;

		CloseHandle(hInPutFile);
		CloseHandle(hOutPutFile);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		std::cout << "Run Success!" << std::endl;
		
	}
	return true;
}

