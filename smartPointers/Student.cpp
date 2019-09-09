#include "Student.h"



Student::Student(string pi_sFirstname, string pi_sLastname, int pi_nId, string pi_sAdress, int pi_nYear, string pi_sDepartment, int pi_nPoints,bool pi_bIfStart):
	m_sFirstname(pi_sFirstname),
	m_sLastname(pi_sLastname),
	m_nId(pi_nId),
	m_sAdress(pi_sAdress),
	m_nYear(pi_nYear),
	m_sDepartment(pi_sDepartment),
	m_nPoints(pi_nPoints),
	m_bIfStart(pi_bIfStart)
{
}

string Student::getDepartmentName()const
{
	return m_sDepartment;
}
int Student::GetId()const
{
	return m_nId;
}

void Student::SetPoints(int pi_nPoints)
{
	m_nPoints = m_nPoints + pi_nPoints;
}
int Student::GetPoints()const
{
	return m_nPoints;
}

void Student::SetIfStart()
{
	m_bIfStart = true;
}

bool Student::GetIfStart()
{
	return m_bIfStart;
}
int Student::GetYear()const
{
	return m_nYear;
}
void Student::PrintStudent()
{
	WRITE_LOG("First name: %s | ",m_sFirstname.c_str());
	WRITE_LOG("Last name: %s | ",m_sLastname.c_str());
	WRITE_LOG("ID: %d | ",m_nId);
	WRITE_LOG("Adress :%s | ",m_sAdress.c_str());
	WRITE_LOG("Start: %d | ",m_nYear);
	WRITE_LOG("Depatrment: %s | ",m_sDepartment.c_str());
	WRITE_LOG("Points: %d \n ",m_nPoints);
}

Student::~Student()
{
}

