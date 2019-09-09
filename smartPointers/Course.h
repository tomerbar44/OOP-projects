#pragma once
#include <iostream>
using namespace std;
#include<string>
#include<vector>
#include "Student.h"
#include "Shared_ptr.h"
#include"Log.h"

class Course
{
public:
	Course(int pi_nNumOfCourse,int pi_nPointsOfCourse=0,string pi_sNameOfCoures="");
	int getCourseNumber()const;
	void setPointsOfCourse(int pi_nPointsOfCourse);
	void setNameOfCourse(string pi_sNameOfCourse);
	void AddStudentToCourse(Shared_ptr<Student> spStudent);
	void AddPointsForAllStudents();
	bool SetStudentFinish(int nStudentId);
	bool RemoveStudent(int nStudentId);
	void PrintDetails();
	
	~Course();

private:
	int m_nNumOfCourse;
	int m_nPointsOfCourse;
	string m_sNameOfCourse;
	vector<Shared_ptr<Student>> m_vecStudents;

};

