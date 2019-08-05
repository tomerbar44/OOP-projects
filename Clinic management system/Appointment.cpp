#include "Appointment.h"
#include "RowDataType.h"


Appointment::Appointment(User& pi_refTherapist, User& pi_refPatient, string pi_sTime, string pi_sDate, string pi_sNotes, EAppointmentStatus pi_eAppointmentStatus) :
	m_refUserTherapist(pi_refTherapist),
	m_refUserPatient(pi_refPatient),
	m_sTime(pi_sTime),
	m_sDate(pi_sDate),
	m_sNotes(pi_sNotes),
	m_eAppointmentStatus(pi_eAppointmentStatus)
{
}

Appointment::~Appointment()
{
}

void Appointment::PrintToFile(FILE* pi_pFile)
{
	/*string sStatusName;
	switch (m_eAppointmentStatus)
	{
	case APPOINTMENT_STATUS_APROVED:
	{
		sStatusName = "Approved";
	}
	break;

	case APPOINTMENT_STATUS_CANCELED:
	{
		sStatusName = "Canceled";
	}
	break;

	case APPOINTMENT_STATUS_PENDING:
	{
		sStatusName = "Pending";
	}
	break;
	}*/
	
	fprintf(pi_pFile, "%d,%d,%d,%s,%s,%s,%d\n",ROW_DATA_TYPE_APPOINTMENT, m_refUserTherapist.GetId(),m_refUserPatient.GetId(),m_sDate.c_str(),m_sTime.c_str(),m_sNotes.c_str(),m_eAppointmentStatus);
}

void Appointment::CancelAppointemt() 
{
	m_eAppointmentStatus = APPOINTMENT_STATUS_CANCELED;
}

void Appointment::ApproveAppointemt()
{
	m_eAppointmentStatus = APPOINTMENT_STATUS_APROVED;
}

int Appointment :: GetIdOfPatient()
{
	return m_refUserPatient.GetId();
}

int Appointment::GetIdOfTherapist()
{
	return m_refUserTherapist.GetId();
}