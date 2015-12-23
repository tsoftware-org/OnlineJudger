#include "stdafx.h"
#include "Matcher.h"

CMatcher::CMatcher(CRecord & record, CDBOpera & dbopera)
{
	m_pRecord = &record;
 	m_pDBOpera = &dbopera;
// 	m_InputID = 1;

}

CMatcher::~CMatcher()
{


}

/*
bool CMatcher::FetchInputStr()
{
	m_pDBOpera->GetRandAnswerByPID(m_pRecord->m_id, &m_TimeLimit, &m_MemoryLimit, m_InputStr, m_OutputStr);
	std::cout << "Got Answer";
	std::cout << m_pRecord->m_id << std::endl << m_TimeLimit << std::endl << m_MemoryLimit << m_InputStr << std::endl << m_OutputStr << std::endl;
	return true;
}

bool CMatcher::GenInputFile()
{
	m_InputFilePath = "";
	return true;
}

bool CMatcher::FetchOutputStr()
{
	m_OutputStr = "";
	return true;
}

bool CMatcher::CheckSame()
{
	//use m_pRecord->m_RunOutputFilePath and m_OutputStr to compare
	return true;
}
*/