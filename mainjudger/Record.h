#ifndef RECORD_H_
#define RECORD_H_
#include <string>

class CRecord
{
private:

	

	
public:
	//���ݿ��ֶ�
	int m_id;
	int m_uid;
	int m_pid;
	int m_language;
	std::string m_source;

	int m_result;
	int m_memorycost;
	int m_timecost;
	int m_codelength;
	int m_postdate;
	
	bool m_bIsNull;

	//���ɵ��ļ���Ŀ¼
	std::string m_SourceFilePath;
	std::string m_ExeFilePath;
	std::string m_complierMsg;


	//�����ļ������뼰����ļ�
	std::string m_RunInputFilePath;
	std::string m_RunOutputFilePath;



	static enum language{C, CPP, JAVA};
	CRecord();
	~CRecord();
	//CRecord & operator=(const CRecord & record);


	bool GenSourceFile();

};

#endif