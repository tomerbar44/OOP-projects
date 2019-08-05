#pragma once
#include <iostream>
using namespace std;
#include<string>
#include<vector>

class Appointment;

enum EUserType
{
	USER_TYPE_THERAPIST = 1,
	USER_TYPE_PATIENT =2 ,
	USER_TYPE_RECEPITIONIST = 3,
	USER_TYPE_UNKNOWN
};

class User
{
	
public:
	User(EUserType pi_eUserType,int pi_nAge,string pi_sFirstname,string pi_sLastname, int pi_nId);
	~User();

	void AddAppointment(Appointment* pi_pAppointment);
	void PrintToFile(FILE* pi_pFile);
	int GetId();
	EUserType GetUserType();
	void SetNote(string pi_sNote);
	void PrintUserOnScreen();
	void ShowAppointments();
	void CancelAppointment(int pi_nIndexInVectorToCancel);
	int CountAppointemnts();
	void ApproveAppointment(int pi_nAppointmentIndex);
	void RemoveAppointmentFromVector(int pi_nAppointmentIndex);


private:
	EUserType m_eUserType;
	int m_nAge;
	string m_sFirstname;
	string m_sLastname;
	int m_nId;
	string m_sNotes;
	vector<Appointment*> m_vecAppointment;
};

