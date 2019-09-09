#pragma once
#include <iostream>
using namespace std;
#include<string>
#include<vector>
#include<fstream>
#include "Student.h"
#include "Shared_ptr.h"
#include"Course.h"
#include"Department.h"
#include "Utils.h"
#include"RowDataType.h"
#include"StudentCycle.h"
class College
{
public:
	College(const char* pi_sInitFile);
	~College();

	void AddNewStudnet(Shared_ptr<Student> pi_spStudent);
	void AddStudentToCourse(int pi_nId,int pi_nCourseNumber);
	void FinishCourse(int pi_nCourseNumber);
	void SetStudentAsFinishedCourse(int pi_nCourseNumber,int nStudentId);
	void RemoveStudentFromCourse(int pi_nCourseNumber, int nStudentId);
	void RemoveStudentFromAll(int pi_nCourseNumber, int nStudentId);
	void PrintStudentDetails(int pi_nCourseNumber);
	void PrintStudentCycle(string pi_sDepatmentName, int pi_nYear);
	void AddCycle(int pi_nYear);
	

	
private:
	string m_sNameCollege;
	vector<Shared_ptr<Department>> m_vecDepartments;
	vector<Shared_ptr<Course>> m_vecCourses;
	vector<Shared_ptr<StudentCycle>> m_vecStudentCycle;
};

