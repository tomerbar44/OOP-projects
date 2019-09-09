#include "Log.h"
#include <iostream>

Log* Log::m_pLog = NULL;
string Log::m_sLogFile = "";

Log::Log()
{

}

Log* Log::GetLog()
{
	if (m_pLog == NULL)
	{
		m_pLog = new Log();
	}
	return m_pLog;
}

void Log::SetLogFile(const char* pi_sLogFile)
{
	Log* pLog = GetLog();
	//m_sLogFile.assign(string(pi_sLogFile));
	m_sLogFile = string(pi_sLogFile);

	FILE* pFile = fopen(m_sLogFile.c_str(), "w");
	if (pFile == NULL)
	{
		std::cout << "Failed to create " << m_sLogFile.c_str() << std::endl;
	}
	fclose(pFile);
}

const char* Log::GetLogFile() const
{
	return m_sLogFile.c_str();
}
