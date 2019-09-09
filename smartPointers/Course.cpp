#include "Course.h"



Course::Course(int pi_nNumOfCourse, int pi_nPointsOfCourse/* = 0*/,string pi_sNameOfCoures/*=""*/):m_nNumOfCourse(pi_nNumOfCourse),m_nPointsOfCourse(pi_nPointsOfCourse), m_sNameOfCourse(pi_sNameOfCoures)
{
}


int Course::getCourseNumber()const
{
	return m_nNumOfCourse;
}

void Course::setPointsOfCourse(int pi_nPointsOfCourse)
{
	m_nPointsOfCourse = pi_nPointsOfCourse;
}
void Course::setNameOfCourse(string pi_sNameOfCourse)
{
	m_sNameOfCourse = pi_sNameOfCourse;
}

void  Course::AddStudentToCourse(Shared_ptr<Student> spStudent)
{

	m_vecStudents.push_back(spStudent);
	spStudent->SetIfStart();
	WRITE_LOG("Student %d start\n", spStudent->GetId());
	WRITE_LOG("%s", "----------------\n");

}

void Course::AddPointsForAllStudents()
{
	for (int i = 0; i < m_vecStudents.size(); ++i)
	{
		m_vecStudents[i]->SetPoints(m_nPointsOfCourse);

	}
	m_vecStudents.clear();
}

bool Course::SetStudentFinish(int nStudentId)
{
	for (int i = 0; i < m_vecStudents.size(); ++i)
	{
		if (m_vecStudents[i]->GetId() == nStudentId)
		{
			m_vecStudents[i]->SetPoints(m_nPointsOfCourse);
			m_vecStudents.erase(m_vecStudents.begin() + i);
			return true;
		
		}
	}
	return false;
	
}

bool Course::RemoveStudent(int nStudentId)
{
	for (int i = 0; i < m_vecStudents.size(); ++i)
	{
		if (m_vecStudents[i]->GetId() == nStudentId)
		{
			m_vecStudents.erase(m_vecStudents.begin() + i);
			return true;
		}
	}
	return false;

}
void Course::PrintDetails()
{
	WRITE_LOG("Course number: %d |",m_nNumOfCourse);
	WRITE_LOG("Course points: %d |",m_nPointsOfCourse);
	WRITE_LOG("Course name: %s \n",m_sNameOfCourse.c_str());
	if (m_vecStudents.size() <= 0)
	{
		WRITE_LOG("%s", "Student list : empty  \n");
		WRITE_LOG("%s", "----------------\n");
	}
	else 
	{
		WRITE_LOG("%s", "Student list : \n");
		for (int i = 0; i < m_vecStudents.size(); ++i)
		{
			WRITE_LOG("%d : ", i + 1);
			m_vecStudents[i]->PrintStudent();

		}
	}

}

Course::~Course()
{

	m_vecStudents.clear();
}
