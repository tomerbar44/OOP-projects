#include "User.h"
#include "Appointment.h"
#include "RowDataType.h"


User::User(EUserType pi_eUserType, int pi_nAge, string pi_sFirstname, string pi_sLastname, int pi_nId) :
	m_eUserType(pi_eUserType),
	m_nAge(pi_nAge),
	m_sFirstname(pi_sFirstname),
	m_sLastname(pi_sLastname),
	m_nId(pi_nId)
{
}

User::~User()
{
}

void User::AddAppointment(Appointment* pi_pAppointment)
{
	m_vecAppointment.push_back(pi_pAppointment);
}

void User::PrintToFile(FILE* pi_pFile)
{
	fprintf(pi_pFile, "%d,%d,%d,%s,%s,%d,%s\n", ROW_DATA_TYPE_USER, m_eUserType, m_nAge, m_sFirstname.c_str(), m_sLastname.c_str(), m_nId, m_sNotes.c_str());
}

int User::GetId()
{
	return m_nId;
}

EUserType User::GetUserType()
{
	return m_eUserType;
}

void User::SetNote(string pi_sNote)
{
	m_sNotes = pi_sNote;
}

void User::PrintUserOnScreen()
{
	std::cout << "Id:" << m_nId <<  " First name: " <<m_sFirstname.c_str() <<  "Last name: " << m_sLastname.c_str() << 
	" Age: " << m_nAge << "Note: " << m_sNotes.c_str() << ".\n";
}

void User::ShowAppointments()
{
	for (size_t i = 0; i < m_vecAppointment.size(); ++i)
	{
		std::cout << (i + 1) << ". ";
		m_vecAppointment[i]->PrintToFile(stdout);//
	}
}

void User::CancelAppointment(int pi_nIndexInVectorToCancel)
{
	m_vecAppointment[pi_nIndexInVectorToCancel]->CancelAppointemt();
}

int User::CountAppointemnts()
{
	return m_vecAppointment.size();
}

void User::ApproveAppointment(int pi_nAppointmentIndex)
{
	m_vecAppointment[pi_nAppointmentIndex]->ApproveAppointemt();
}

void User::RemoveAppointmentFromVector(int pi_nAppointmentIndex)
{
	m_vecAppointment.erase(m_vecAppointment.begin() + pi_nAppointmentIndex);
}

