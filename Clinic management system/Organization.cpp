#include "Organization.h"
#include <iostream>
#include <string>
#include<fstream>
#include "RowDataType.h"
#include"Utils.h"

Organization::Organization()
{
	std::ifstream infile(READ_FROM_FILE);
	std::string line;
	while (std::getline(infile, line))
	{
		vector<string> vecResults = Utils::split(line.c_str());
		if (line[0] == '#')
		{
			continue;
		}
		else if (line[0] - 48 == ROW_DATA_TYPE_USER)
		{
			if (vecResults.size() != 7)
			{
				std::cout << "DB corrupted" << std::endl;
				exit(1);
			}
			int nUserType;
			int nAge;
			string sFname;
			string sLname;
			int nId;
			string sNote;

			nUserType = atoi(vecResults[1].c_str());
			nAge = atoi(vecResults[2].c_str());
			sFname = vecResults[3];
			sLname = vecResults[4];
			nId = atoi(vecResults[5].c_str());
			sNote = vecResults[6];

			EUserType eUserType = USER_TYPE_UNKNOWN;

			switch (nUserType)
			{
				case USER_TYPE_THERAPIST:
					eUserType = USER_TYPE_THERAPIST;
					break;
				case USER_TYPE_PATIENT:
					eUserType = USER_TYPE_PATIENT;
					break;
				case USER_TYPE_RECEPITIONIST:
					eUserType = USER_TYPE_RECEPITIONIST;
					break;
				default:
					eUserType = USER_TYPE_UNKNOWN;
			}

			User* pUser = new User(eUserType, nAge, sFname, sLname, nId);
			pUser->SetNote(sNote);

			if (nUserType == USER_TYPE_PATIENT)
			{
				AddNewPatient(pUser);
			}
			else if (nUserType == USER_TYPE_THERAPIST)
			{
				AddNewTherapist(pUser);
			}
			else if (nUserType == USER_TYPE_RECEPITIONIST)
			{
				AddNewReception(pUser);
			}
			else
			{
				std::cout << "Unknown type of user: " << nUserType << std::endl;
				exit(1);
			}
			
		}
		else if (line[0]-48 == ROW_DATA_TYPE_APPOINTMENT)
		{
			int nTherapistId;
			int nPatientId;
			string sDate;
			string sTime;
			string sNote;
			int nAppointmentStatus = 0;
			EAppointmentStatus eAppointmentStatus;

			nTherapistId = atoi(vecResults[1].c_str());
			nPatientId = atoi(vecResults[2].c_str());

			sDate = vecResults[3];
			sTime = vecResults[4];
			sNote = vecResults[5];
			nAppointmentStatus = atoi(vecResults[6].c_str());

			if (nAppointmentStatus == APPOINTMENT_STATUS_APROVED)
			{
				eAppointmentStatus = APPOINTMENT_STATUS_APROVED;
			}
			else if (nAppointmentStatus == APPOINTMENT_STATUS_CANCELED)
			{
				eAppointmentStatus = APPOINTMENT_STATUS_CANCELED;
			}
			else if (nAppointmentStatus == APPOINTMENT_STATUS_PENDING)
			{
				eAppointmentStatus = APPOINTMENT_STATUS_PENDING;
			}
			else
			{
				std::cout << "Unknown type of appointment: " << nAppointmentStatus << std::endl;
				exit(1);
			}

			User* pTherapist = GetTherapist(nTherapistId);

			User* pPatient = GetPatient(nPatientId);

			
			if (pTherapist == NULL || pPatient == NULL)
			{
				std::cout << "Unknown user " << std::endl;
				exit(1);
			}
			Appointment* pAppointment = new Appointment(*pTherapist, *pPatient, sTime, sDate, sNote, eAppointmentStatus);

			AddNewAppointment(pAppointment);
			pTherapist->AddAppointment(pAppointment);
			pPatient->AddAppointment(pAppointment);

			if (eAppointmentStatus == APPOINTMENT_STATUS_PENDING)
			{
				AddAppointmentToReception(pAppointment);
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


}

Organization::~Organization()
{
	FILE* pFile = fopen(READ_FROM_FILE, "w"); 
	if (pFile == NULL)
	{
		printf("Error, cant open file: %s", READ_FROM_FILE);
		exit(1);
	}

	fprintf(pFile, "# Therapists list:\n");
	for (size_t i = 0; i < m_vecTherapist.size(); ++i)
	{
		m_vecTherapist[i]->PrintToFile(pFile);
		/*delete(m_vecTherapist[i]);*/
	}
	fprintf(pFile, "# Patients list:\n");
	for (size_t i = 0; i < m_vecPatients.size(); ++i)
	{
		m_vecPatients[i]->PrintToFile(pFile);
		/*delete(m_vecPatients[i]);*/
	}

	fprintf(pFile, "# Receptions list:\n");
	for (size_t i = 0; i < m_vecReceptions.size(); ++i)
	{
		m_vecReceptions[i]->PrintToFile(pFile);
		/*delete(m_vecReceptions[i]);*/
	}
	fprintf(pFile, "# Appointments list:\n");
	for (size_t i = 0; i < m_vecAppointments.size(); ++i)
	{
		m_vecAppointments[i]->PrintToFile(pFile);
		/*delete(m_vecAppointments[i]);*/
	}




	for (size_t i = 0; i < m_vecTherapist.size(); ++i)
	{
		
		delete(m_vecTherapist[i]);
	}

	for (size_t i = 0; i < m_vecPatients.size(); ++i)
	{
		
		delete(m_vecPatients[i]);
	}

	for (size_t i = 0; i < m_vecReceptions.size(); ++i)
	{
	
		delete(m_vecReceptions[i]);
	}
	for (size_t i = 0; i < m_vecAppointments.size(); ++i)
	{
		
		delete(m_vecAppointments[i]);
	}
	
	fclose(pFile);
}

void Organization::AddNewTherapist(User* pi_pTherapist)
{
	m_vecTherapist.push_back(pi_pTherapist);
}

void Organization::AddNewPatient(User* pi_pPatient)
{
	m_vecPatients.push_back(pi_pPatient);
}

void Organization::AddNewReception(User* pi_pReception)
{
	m_vecReceptions.push_back(pi_pReception);
}

void Organization::AddNewAppointment(Appointment* pi_pAppointment)
{
	m_vecAppointments.push_back(pi_pAppointment);
}

User* Organization::GetUser(int pi_nId) 
{
	for (size_t i = 0; i < m_vecTherapist.size(); ++i)
	{
		if (pi_nId == m_vecTherapist[i]->GetId())
		{
			return m_vecTherapist[i];
		}
	}
	for (size_t i = 0; i < m_vecPatients.size(); ++i)
	{
		if (pi_nId == m_vecPatients[i]->GetId())
		{
			return m_vecPatients[i];
		}
	}
	for (size_t i = 0; i < m_vecReceptions.size(); ++i)
	{
		if (pi_nId == m_vecReceptions[i]->GetId())
		{
			return m_vecReceptions[i];
		}
	}

	return NULL;
}

void Organization::PrintTherapists()
{
	for (size_t i = 0; i < m_vecTherapist.size(); ++i)
	{
		m_vecTherapist[i]->PrintUserOnScreen();
	}
}

void Organization::PrintPatients()
{
	for (size_t i = 0; i < m_vecPatients.size(); ++i)
	{
		std::cout << (i + 1) << ". ";
		m_vecPatients[i]->PrintUserOnScreen();
	}
}

User* Organization::GetTherapist(int pi_nId)
{
	for (size_t i = 0; i < m_vecTherapist.size(); ++i)
	{
		if (pi_nId == m_vecTherapist[i]->GetId())
		{
			return m_vecTherapist[i];
		}
	}
	return NULL;
}

User* Organization::GetPatient(int pi_nId)
{
	for (size_t i = 0; i < m_vecPatients.size(); ++i)
	{
		if (pi_nId == m_vecPatients[i]->GetId())
		{
			return m_vecPatients[i];
		}
	}
	return NULL;
}

void Organization::AddAppointmentToReception(Appointment* pi_pAppointemt)
{
	if (m_vecReceptions.size() == 0)
	{
		std::cout << "Can't alloate appointemnt to reception because there are no reception at all" << std::endl;
	}

	User* pReception = m_vecReceptions[0];
	for (size_t i = 0; i < m_vecReceptions.size(); i++)
	{
		if (pReception->CountAppointemnts() > m_vecReceptions[i]->CountAppointemnts())
		{
			pReception = m_vecReceptions[i];
		}
	}

	pReception->AddAppointment(pi_pAppointemt);
}