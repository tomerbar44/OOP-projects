#pragma once
#include <iostream>
using namespace std;
#include<string>
#include<vector>
#include<fstream>
#include"Log.h"

class Student
{
public:
	Student(string pi_sFirstname, string pi_sLastname, int pi_nId, string pi_sAdress, int pi_nYear, string pi_sDepartment, int pi_nPoints = 0,bool pi_bIfStart = false);
	~Student();
	string getDepartmentName()const;
	int GetId()const;
	void SetPoints(int pi_nPoints);
	void SetIfStart();
	bool GetIfStart();
	int GetPoints()const;
	void PrintStudent();
	int GetYear()const;
	//void PrintStudentToFile(FILE* pi_pFile);



private:
	string m_sFirstname;
	string m_sLastname;
	int m_nId;
	string m_sAdress;
	int m_nYear;
	string m_sDepartment;
	int m_nPoints;
	bool m_bIfStart;
};

