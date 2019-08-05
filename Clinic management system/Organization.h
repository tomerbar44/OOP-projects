#pragma once
#include"User.h"
#include<vector>
#include"Appointment.h"
#include "Utils.h"
#define READ_FROM_FILE "db.txt"

using namespace std;

class Organization
{


public:
	Organization();
	~Organization();

	void AddNewTherapist(User* pi_pTherapist);
	void AddNewPatient(User* pi_pPatient);
	void AddNewReception(User* pi_pReception);
	void AddNewAppointment(Appointment* pi_pAppointment);
	User* GetUser(int pi_nId);
	User* GetTherapist(int pi_nId);
	User* GetPatient(int pi_nId);
	void PrintTherapists();
	void PrintPatients();
	void AddAppointmentToReception(Appointment* pi_pAppointemt);

private:
	vector<User*>m_vecTherapist;
	vector<User*>m_vecPatients;
	vector<User*>m_vecReceptions;
	vector<Appointment*>m_vecAppointments;
};

