#include "stdafx.h"
#include "Record.h"
#include <fstream>

CRecord::CRecord()
{
	m_SourceFilePath = "";
}
CRecord::~CRecord()
{

}
/*
CRecord & CRecord::operator=(const CRecord & record)
{

	
}
*/
bool CRecord::GenSourceFile()
{
	std::ofstream fout;
	std::string fileExt;
	switch (m_language)
	{
	case C:	//0
		break;
	case CPP:		//1
		fileExt = ".cpp";
		break;
	case JAVA:	//2
		break;
	default:
		break;
	}

	char tmp[100];
	sprintf_s(tmp, "D:/tmp/%d", m_id);
	m_SourceFilePath = tmp + fileExt;
	fout.open(m_SourceFilePath);
	fout << m_source;
	return true;
}

