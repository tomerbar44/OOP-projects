#include "College.h"
#include "Log.h"


College::College(const char* pi_sInitFile) 
	
{
	std::ifstream infile(pi_sInitFile);
	std::string line;
	while (std::getline(infile, line))
	{
		vector<string> vecResults = Utils::split(line.c_str());
		if (line[0] == '#')
		{
			continue;
		}

		else if (line[0] - 48 == ROW_DATA_TYPE_COLLEGE_NAME)
		{
			if (vecResults.size() != 3)
			{
				std::cout << "DB corrupted" << std::endl;
				exit(1);
			}
			string sNameCollege;
			sNameCollege = vecResults[2];
		}

		else if (line[0] - 48 == ROW_DATA_TYPE_DEPARTMENTS)
		{

			string sNameDepartment;
			for (int i = 2; i < vecResults.size(); ++i)
			{
				sNameDepartment = vecResults[i];
				Shared_ptr<Department> pDepartment(new Department(sNameDepartment));
				m_vecDepartments.push_back(pDepartment);
			}

		}
		else if (line[0] - 48 == ROW_DATA_TYPE_COURSES)
		{
			int nNumOfCourse;
			for (int i = 2; i < vecResults.size(); ++i)
			{
				nNumOfCourse = atoi(vecResults[i].c_str());
				Shared_ptr<Course> pCourse(new Course(nNumOfCourse));
				m_vecCourses.push_back(pCourse);
			}


		}
		else if (line[0] - 48 == ROW_DATA_TYPE_COURSES_DETAILS)
		{
			int nNumOfCourse;
			int nPointsOfCourse;
			string sNameOfDepartment;
			string sNameOfCourse;
			Shared_ptr<Course> spCourse;

			nNumOfCourse = atoi(vecResults[2].c_str());
			sNameOfDepartment = vecResults[3];
			nPointsOfCourse = atoi(vecResults[4].c_str());
			sNameOfCourse = vecResults[5];

			bool bCourseFound = false;
			bool bDepartmentFound = false;
			for (int i = 0; i <  m_vecCourses.size(); ++i)
			{
				spCourse = m_vecCourses[i];
				
				if (spCourse->getCourseNumber() == nNumOfCourse)
				{
					bCourseFound = true;
					spCourse->setNameOfCourse(sNameOfCourse);
					spCourse->setPointsOfCourse(nPointsOfCourse);
					for (int j = 0; j < m_vecDepartments.size(); ++j)
					{
						if (sNameOfDepartment == m_vecDepartments[j]->GetName())
						{
							bDepartmentFound = true;
							m_vecDepartments[j]->addCourseToDepartment(spCourse);
							break;
						}
					}

					if (bDepartmentFound == false)
					{
						WRITE_LOG("Deprtmant %s not found.\n", sNameOfDepartment.c_str());
					}
				}
				if (bCourseFound == true)
					break;
			}

			if (bCourseFound == false)
			{
				WRITE_LOG("Course %s not found.\n", sNameOfCourse);
			}

		}

		else if (line == "")
		{

		}
		else
		{
			std::cout << "DB corrupted" << std::endl;
			exit(1);
		}
	}
	m_vecStudentCycle.clear();
	WRITE_LOG("%s","Init sucsses\n");
	WRITE_LOG("%s", "----------------\n");
}

void College::AddNewStudnet(Shared_ptr<Student> pi_spStudent)
{

	string sNameOfDepartment = pi_spStudent->getDepartmentName();
	bool bDepartmentFound = false;
	for (int j = 0; j < m_vecDepartments.size(); ++j)
	{
		if (sNameOfDepartment == m_vecDepartments[j]->GetName())
		{
			bDepartmentFound = true;
			m_vecDepartments[j]->addStudentToDepartment(pi_spStudent);
		

			for (int i = 0; i < m_vecStudentCycle.size(); ++i)
			{
				if (m_vecStudentCycle[i]->GetYear() == pi_spStudent->GetYear())
				{
					m_vecStudentCycle[i]->AddToCurrentVector(pi_spStudent);
				}
			}
		
			
		}
	}

	if (bDepartmentFound == false)
	{
		WRITE_LOG("Deprtmant %s not found.\n", sNameOfDepartment);
		WRITE_LOG("%s", "----------------\n");
	}
	else
	{
		WRITE_LOG("Student %d added to depatrment\n", pi_spStudent->GetId());
		WRITE_LOG("%s", "----------------\n");
	}
	
}

void College::AddStudentToCourse(int pi_nId, int pi_nCourseNumber)
{
	bool bStudentFound = false;
	bool bCourseFound = false;
	for (int j = 0; j < m_vecDepartments.size(); ++j)
	{
		if (m_vecDepartments[j]->SearchStudent(pi_nId) == true)
		{
			bStudentFound = true;
			Shared_ptr<Student> spStudent( m_vecDepartments[j]->GetStudent(pi_nId));
		
			for (int i = 0; i < m_vecCourses.size(); ++i)
			{
				if (m_vecCourses[i]->getCourseNumber() == pi_nCourseNumber)
				{
					bCourseFound = true;
					m_vecCourses[i]->AddStudentToCourse(spStudent);
					WRITE_LOG("Student added %d ", pi_nId);
					WRITE_LOG("to course %d \n ", pi_nCourseNumber);
					WRITE_LOG("%s", "----------------\n");		
					break;
				}
			}
			
		}
	}

	if (bStudentFound == false)
	{
		WRITE_LOG("Student %s not found.\n", pi_nId);
		WRITE_LOG("%s", "----------------\n");
	}

	if (bStudentFound == false)
	{
		WRITE_LOG("Course %s not found.\n", pi_nCourseNumber);
		WRITE_LOG("%s", "----------------\n");
	}
	

}
void College::FinishCourse(int pi_nCourseNumber)
{
	bool bCourseFound = false;
	for (int i = 0; i < m_vecCourses.size(); ++i)
	{
		if (m_vecCourses[i]->getCourseNumber() == pi_nCourseNumber)
		{
			bCourseFound = true;
			m_vecCourses[i]->AddPointsForAllStudents();
			break;

		}
	}

	if (bCourseFound == false)
	{
		WRITE_LOG("Course %d not found.\n", pi_nCourseNumber);
		WRITE_LOG("%s", "----------------\n");
	}
	else
	{
		WRITE_LOG("Course %d finish\n", pi_nCourseNumber);
		WRITE_LOG("%s", "----------------\n");
	}
	
}

void College::SetStudentAsFinishedCourse(int pi_nCourseNumber, int nStudentId)
{
	bool bCourseFound = false;
	for (int i = 0; i < m_vecCourses.size(); ++i)
	{
		if (m_vecCourses[i]->getCourseNumber() == pi_nCourseNumber)
		{
			bCourseFound = true;
			if (m_vecCourses[i]->SetStudentFinish(nStudentId) == true)
			{
				WRITE_LOG("Student %d", nStudentId);
				WRITE_LOG("finish course %d \n", pi_nCourseNumber);
				WRITE_LOG("%s", "----------------\n");
			}
				
			else
			{
				WRITE_LOG("Student %d dont found in this course\n ", nStudentId);
				WRITE_LOG("%s", "----------------\n");
			}
		}
	}
	if (bCourseFound == false)
	{
		WRITE_LOG("Course %s not found.\n", pi_nCourseNumber);
		WRITE_LOG("%s", "----------------\n");
	}

}

void College::RemoveStudentFromCourse(int pi_nCourseNumber, int nStudentId)
{
	bool bCourseFound = false;
	for (int i = 0; i < m_vecCourses.size(); ++i)
	{
		if (m_vecCourses[i]->getCourseNumber() == pi_nCourseNumber)
		{
			bCourseFound = true;
			if (m_vecCourses[i]->RemoveStudent(nStudentId) == true)
			{
				WRITE_LOG("Student %d", nStudentId);
				WRITE_LOG("remove from course %d \n", pi_nCourseNumber);
				WRITE_LOG("%s", "----------------\n");
			}
			else
			{
				WRITE_LOG("Student %d dont found\n ", nStudentId);
				WRITE_LOG("%s", "----------------\n");
			}
		}
		
	}
	if (bCourseFound == false)
	{
		WRITE_LOG("Course %s not found.\n", pi_nCourseNumber);
		WRITE_LOG("%s", "----------------\n");
	}
}

void College::RemoveStudentFromAll(int pi_nYearStart, int nStudentId)
{
	bool bStudentFoundInDepartment = false;
	bool bStudentFoundInCourses = false;
	Shared_ptr<Student> sp = m_vecDepartments[0]->GetStudent(nStudentId);;
	for (int i = 0; i < m_vecDepartments.size(); ++i)
	{
		if (m_vecDepartments[i]->SearchStudent(nStudentId) == true)
		{
			sp = m_vecDepartments[i]->GetStudent(nStudentId);
		}
		if (m_vecDepartments[i]->RemoveStudentFromDepatment(nStudentId) == true)
		{ 
			bStudentFoundInDepartment = true;
			WRITE_LOG("Student %d remove from departmemt \n", nStudentId);
			WRITE_LOG("%s", "----------------\n");

		}
	}
	for (int j = 0; j < m_vecCourses.size(); ++j)
	{
		if (m_vecCourses[j]->RemoveStudent(nStudentId) == true)
		{
			bStudentFoundInCourses = true;
			WRITE_LOG("Student %d ", nStudentId);
			WRITE_LOG("remove from course - %d \n", m_vecCourses[j]->getCourseNumber());
			WRITE_LOG("%s", "----------------\n");
		}
	}


	if (bStudentFoundInDepartment == false)
	{
		WRITE_LOG("%s","Student not found in all departments.\n");
		WRITE_LOG("%s", "----------------\n");
	}
	if (bStudentFoundInCourses == false)
	{
		WRITE_LOG("%s","Student not found in any course.\n");
		WRITE_LOG("%s", "----------------\n");
	}
	

}

void College::PrintStudentDetails(int pi_nCourseNumber)
{
	bool bCourseFound = false;
	for (int i = 0; i < m_vecCourses.size(); ++i)
	{
		if (m_vecCourses[i]->getCourseNumber() == pi_nCourseNumber)
		{
			bCourseFound = true;
			m_vecCourses[i]->PrintDetails();
		}
	}
	if (bCourseFound == false)
	{
		WRITE_LOG("Course %d not found.\n", pi_nCourseNumber);
		WRITE_LOG("%s", "----------------\n");
	}
}
void College::PrintStudentCycle(string pi_sDepatmentName, int pi_nYear)
{
	bool bYearFound = false;
	
	for (int i = 0; i < m_vecStudentCycle.size(); ++i)
	{
		if (m_vecStudentCycle[i]->GetYear() == pi_nYear)
		{
			bYearFound = true;
			WRITE_LOG("Student cycle year: %d \n", pi_nYear);
			WRITE_LOG("%s", "----------------\n");
			m_vecStudentCycle[i]->PrintAllStudent(pi_sDepatmentName);
		}
	}
	if (bYearFound == false)
	{
		WRITE_LOG("Student cycle year: %n not found.\n", pi_nYear);
		WRITE_LOG("%s", "----------------\n");
	}
	
}

void College::AddCycle(int pi_nYear)
{
	bool bYearFound = false;
	for (int i = 0; i < m_vecStudentCycle.size(); ++i)
	{
		if (m_vecStudentCycle[i]->GetYear() == pi_nYear)
		{
			bYearFound = true;
		}
	}
	if (bYearFound == false)
	{
		Shared_ptr<StudentCycle> spCycle(new StudentCycle(pi_nYear));
		m_vecStudentCycle.push_back(spCycle);
		WRITE_LOG("New cycle create: %d \n", pi_nYear);
		WRITE_LOG("%s", "----------------\n");

	}
	
}


College::~College()
{
	m_vecCourses.clear();
	m_vecDepartments.clear();
	m_vecStudentCycle.clear();
}
