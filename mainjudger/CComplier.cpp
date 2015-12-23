#include "stdafx.h"
#include "Complier.h"
#include <windows.h>
#include <winbase.h>
#include <Psapi.h>
#include <fstream>
#include <regex>

CComplier::CComplier(CRecord & record, CDBOpera & dbopera)
{
	m_pRecord = &record;	//注意是引用
	m_pDBOpera = &dbopera;
}

CComplier::~CComplier()
{

}

bool CComplier::Complie()
{
	char tmp[100];
	sprintf_s(tmp, "%d", m_pRecord->m_id);
	SetCurrentDirectory(TEXT("D:/tmp/"));
	switch (m_pRecord->m_language)
	{
	case CRecord::C:
		break;
	case CRecord::CPP:
		m_complierCmd = "g++ -Wall " + m_pRecord->m_SourceFilePath + " -o " + tmp;
		m_pRecord->m_ExeFilePath = tmp;
		break;
	case CRecord::JAVA:
		break;
	default:
		break;
	}

	std::cout << m_complierCmd << std::endl;
	DoSysCall();
	return true;
}

bool CComplier::DoSysCall()
{
	STARTUPINFOA si;
	memset(&si, 0, sizeof(STARTUPINFO));//初始化si在内存块中的值（详见memset函数）
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	
	SECURITY_ATTRIBUTES sa = { sizeof(sa),
		NULL,
		TRUE
	};

	char tmp[100];
	sprintf_s(tmp, "D:/tmp/%d.jcm", m_pRecord->m_id);		//注意必须有这个文件夹
	m_complierMsgFilePath = tmp;
	LPSTR complierMsgFilePath = (LPSTR)m_complierMsgFilePath.c_str();
	HANDLE hOutPutFile = CreateFileA(complierMsgFilePath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	si.hStdOutput = hOutPutFile;
	si.hStdError = hOutPutFile;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;				//必备参数设置结束
	LPSTR cmd = (LPSTR)m_complierCmd.c_str();
	if (!CreateProcessA(NULL,
		cmd,
		NULL,
		NULL,
		TRUE,		//need set to TRUE
		0,
		NULL,
		NULL,
		&si,
		&pi
		))
	{
		std::cout << "CreateFail!" << std::endl;
		exit(1);
	}
	else{
		std::cout << "Success!" << std::endl;
		
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		CloseHandle(hOutPutFile);

	}
	//不使用的句柄最好关掉
	
	
	/*PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(pi.hProcess, &pmc, sizeof(pmc));

	std::cout << pmc.WorkingSetSize << std::endl;
	*/
	
	GetComplierResult();
	std::cout << "ComplierResult = " << m_pRecord->m_result << std::endl;
	WriteResultBacktoDB();
	return true;
}

bool CComplier::GetComplierResult()
{
	std::ifstream fin;
	fin.open(m_complierMsgFilePath.c_str());
	
	if (!fin.is_open())		//打开编译消息文件失败
	{
		m_pRecord->m_result = 10;		//未知错误
		return false;
	}
	else{
		int countByte = 0;
		char ch;
		while (fin.get(ch))
		{
			countByte++;
			m_pRecord->m_complierMsg = m_pRecord->m_complierMsg + ch;
		}

		fin.close();

		if (countByte == 0)				//编译没有出任何提示,直接就说明编译成功
		{
			m_pRecord->m_result = 30;	//complier passed
		}
		else{
			if (std::regex_search(m_pRecord->m_complierMsg, std::regex(" error: ")))
			{
				std::cout << "complier error matched\n";
				m_pRecord->m_result = 10;		//means failed,编译遇到error
			}
			else
			{
				std::cout << "not match error" << std::endl;
				m_pRecord->m_result = 999;
			}
		}

	
	}
	return true;

}

bool CComplier::WriteResultBacktoDB()
{
	m_pDBOpera->WriteComplierResultToDB(m_pRecord->m_id, m_pRecord->m_result, m_pRecord->m_complierMsg);
	return true;
}