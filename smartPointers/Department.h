#pragma once
#include <iostream>
using namespace std;
#include<string>
#include<vector>
#include "Student.h"
#include "Shared_ptr.h"
#include"Course.h"

class Department
{
public:
	Department(string pi_sNameDepartment);
	~Department();

	string GetName()const;
	void addCourseToDepartment(Shared_ptr<Course> spCourse);
	void addStudentToDepartment(Shared_ptr<Student> spStudent);
	bool SearchStudent(int pi_nId);
	bool RemoveStudentFromDepatment(int pi_nId);
	Shared_ptr<Student> GetStudent(int pi_nId);

private:
	string m_sNameDepartment;
	vector<Shared_ptr<Course>> m_vecCourses;
	vector<Shared_ptr<Student>> m_vecStudents;
};

