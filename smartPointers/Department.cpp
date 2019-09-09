#include "Department.h"



Department::Department(string pi_sNameDepartment):m_sNameDepartment(pi_sNameDepartment)
{
}

string Department::GetName()const
{
	return m_sNameDepartment;
}

void Department::addCourseToDepartment(Shared_ptr<Course> spCourse)
{
	m_vecCourses.push_back(spCourse);
}

void Department::addStudentToDepartment(Shared_ptr<Student> spStudent) 
{
	
	m_vecStudents.push_back(spStudent);
	
}

bool Department::SearchStudent(int pi_nId)
{
	for (int i = 0; i < m_vecStudents.size(); ++i)
	{
		if (pi_nId == m_vecStudents[i]->GetId())
		{
			return true;
		}

	}
	return false;
}
Shared_ptr<Student> Department::GetStudent(int pi_nId)
{

	for (int i = 0; i < m_vecStudents.size(); ++i)
	{
		if (pi_nId == m_vecStudents[i]->GetId())
		{
			return m_vecStudents[i];
		}

	}
	
}
bool Department::RemoveStudentFromDepatment(int pi_nId)
{
	for (int i = 0; i < m_vecStudents.size(); ++i)
	{
		if (pi_nId == m_vecStudents[i]->GetId())
		{
			m_vecStudents.erase(m_vecStudents.begin() + i);
		
			return true;
		}

	}
	return false;
}

Department::~Department()
{

	m_vecCourses.clear();
	m_vecStudents.clear();

}
