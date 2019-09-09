#pragma once
#include "Student.h"
#include"Shared_ptr.h"
#include"Log.h"
class StudentCycle
{
public:
	StudentCycle(int pi_nStartYear,int pi_nNumberOf=0);
	~StudentCycle();
	int GetYear()const;
	void PrintAllStudent(string pi_sNameOfDepatment);
	void AddToCurrentVector(Shared_ptr<Student> spStudent);
	void AddToFinishedVector(Shared_ptr<Student> spStudent);
	int GetNumberOfStudent()const;


private:
	int m_nStartYear;
	int m_nNumberOfStudents;
	vector<Shared_ptr<Student>> m_vecSpStudentCurrent;
	vector<Shared_ptr<Student>> m_vecSpStudentFinish;
};

