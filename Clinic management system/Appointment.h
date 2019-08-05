#pragma once
#include"User.h"
#include <string>

using namespace std;

enum EAppointmentStatus
{
	APPOINTMENT_STATUS_APROVED = 1,
	APPOINTMENT_STATUS_CANCELED,
	APPOINTMENT_STATUS_PENDING,
	APPOINTMENT_STATUS_UNKNOWN
};

class Appointment
{

public:
	Appointment(User& pi_refTherapist, User& pi_refPatient,string pi_sTime,string pi_sDate, string pi_sNotes,EAppointmentStatus pi_eAppointmentStatus= APPOINTMENT_STATUS_PENDING);
	~Appointment();
	void PrintToFile(FILE* pi_pFile);
	int GetIdOfPatient();
	int GetIdOfTherapist();
	void CancelAppointemt();
	void ApproveAppointemt();
private:
	User& m_refUserTherapist;
	User& m_refUserPatient;
	string m_sTime;
	string m_sDate;
	string m_sNotes;
	EAppointmentStatus m_eAppointmentStatus;
};


