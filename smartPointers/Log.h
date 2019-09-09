#pragma once
#include <iostream>
using namespace std;

class Log
{
private:
	Log();
	static Log* m_pLog;
	static string m_sLogFile;

public:
	static Log* GetLog();
	static void SetLogFile(const char* pi_sLogFile);
	const char* GetLogFile() const;
};

#define WRITE_LOG(format, args)\
{\
	FILE* pFile = fopen(Log::GetLog()->GetLogFile(), "a");\
	if(pFile)\
	{\
		fprintf(pFile, format,args);\
		fclose(pFile);\
	}\
}
#define WRITE_LOG_LN(args)\
{\
	WRITE_LOG("%s\n", args);\
}