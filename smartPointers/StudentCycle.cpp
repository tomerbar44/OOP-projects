#include "StudentCycle.h"



StudentCycle::StudentCycle(int pi_nStartYear, int pi_nNumberOf):m_nStartYear(pi_nStartYear),m_nNumberOfStudents(pi_nNumberOf)
{
}

int StudentCycle::GetYear()const
{
	return m_nStartYear;
}
void StudentCycle::PrintAllStudent(string pi_sNameOfDepatment)
{
		WRITE_LOG("Currnet student: %d \n", m_vecSpStudentCurrent.size());
		WRITE_LOG("%s", "Currnet student list : \n");
		for (int i = 0; i < m_vecSpStudentCurrent.size(); ++i)
		{
			if (m_vecSpStudentCurrent[i]->getDepartmentName() == pi_sNameOfDepatment)
			{
				if (m_vecSpStudentCurrent[i]->GetPoints() == 160)
				{
					AddToFinishedVector(m_vecSpStudentCurrent[i]);
					m_vecSpStudentCurrent.erase(m_vecSpStudentCurrent.begin() + i);
				}
				else {
					WRITE_LOG("%d : ", i + 1);
					m_vecSpStudentCurrent[i]->PrintStudent();
				}
			}

		}
		if (m_vecSpStudentFinish.size()>0)
			WRITE_LOG("%s", "Finished student list : \n");

		for (int i = 0; i < m_vecSpStudentFinish.size(); ++i)
		{
			if (m_vecSpStudentFinish[i]->getDepartmentName() == pi_sNameOfDepatment)
			{
				WRITE_LOG("%d : ", i + 1);
				m_vecSpStudentFinish[i]->PrintStudent();
			}
		}
	
	

}
void StudentCycle::AddToCurrentVector(Shared_ptr<Student> spStudent)
{
	m_vecSpStudentCurrent.push_back(spStudent);
	m_nNumberOfStudents++;
}
void StudentCycle::AddToFinishedVector(Shared_ptr<Student> spStudent)
{
	m_vecSpStudentFinish.push_back(spStudent);
	m_nNumberOfStudents++;
}

int StudentCycle::GetNumberOfStudent()const
{
	return m_nNumberOfStudents;
}



StudentCycle::~StudentCycle()
{
}
