#include <iostream>
#include "Organization.h"
#include "Utils.h"

enum EScreenType
{
	SCREEN_TYPE_MAIN_MENU,
	SCREEN_TYPE_LOGIN,
	SCREEN_TYPE_SIGNUP,
	SCREEN_TYPE_USER_MENU_THERAPIST,
	SCREEN_TYPE_USER_MENU_PATIENT,
	SCREEN_TYPE_USER_MENU_RECEPTION
};

void ScreenHeader(string pi_sHeader)
{
	std::cout << pi_sHeader << std::endl << "========================" << std::endl;
}

int main(int argv, char** argc)
{
	Organization org;
	string sReceiveData;
	bool bEndProgram = false;
	EScreenType eScreenType = SCREEN_TYPE_MAIN_MENU;
	User* pUser = NULL;
	while (!bEndProgram)
	{
		switch (eScreenType)
		{
		case SCREEN_TYPE_MAIN_MENU:
		{
			ScreenHeader("Main Menu");
			std::cout << "1.Login\n2.Sign up\n3.Close the program\n";
			std::cin >> sReceiveData;

			if (sReceiveData == "1")
				eScreenType = SCREEN_TYPE_LOGIN;
			else if (sReceiveData == "2")
					eScreenType = SCREEN_TYPE_SIGNUP;
			else if(sReceiveData == "3")
			{
				bEndProgram = true;

			}
			else
			{
				std::cout << "Wrong Number\n";
			}
				
		}
		break;

		case SCREEN_TYPE_LOGIN:
		{
			ScreenHeader("Login");
			int nTemp;
			std::cout << "Please enter ID to login\n";
			std::cin >> sReceiveData;
			nTemp = atoi(sReceiveData.c_str());
			pUser = org.GetUser(nTemp);
			if (pUser == NULL)
			{
				std::cout << "User not exsit\n";
				eScreenType = SCREEN_TYPE_MAIN_MENU;
			}
			else
			{
				switch (pUser->GetUserType())
				{
				case USER_TYPE_THERAPIST:
				{
					eScreenType = SCREEN_TYPE_USER_MENU_THERAPIST;
				}
				break;

				case USER_TYPE_PATIENT:
				{
					eScreenType = SCREEN_TYPE_USER_MENU_PATIENT;
				}
				break;

				case USER_TYPE_RECEPITIONIST:
				{
					eScreenType = SCREEN_TYPE_USER_MENU_RECEPTION;
				}
				break;
				}
				
			}

		}
		break;

		case SCREEN_TYPE_SIGNUP:
		{
			ScreenHeader("Signup");
			std::cout << "Please enter : user type, age, first name, last name, ID (for example:1,41,Tomer,Bar,123)\n";
			std::cin >> sReceiveData;

			vector<string> vecResults = Utils::split(sReceiveData.c_str());

			if (vecResults.size() != 5)
			{
				std::cout << "Invalid parameter. you missed some values." << std::endl;
			}
			else
			{
				int nUserType;
				int nAge;
				string sFname;
				string sLname;
				int nId;

				nUserType = atoi(vecResults[0].c_str());
				nAge = atoi(vecResults[1].c_str());
				sFname = vecResults[2];
				sLname = vecResults[3];
				nId = atoi(vecResults[4].c_str());

				if (org.GetUser(nId) != NULL)
				{
					std::cout << "Error: User with same ID has already exist" << std::endl;
				}
				else
				{
					std::cout << "Enter Note:\n";
					std::cin >> sReceiveData;

					User* l_pUser = new User((EUserType)nUserType, nAge, sFname, sLname, nId);
					l_pUser->SetNote(sReceiveData);

					if (nUserType == USER_TYPE_PATIENT)
					{
						org.AddNewPatient(l_pUser);
					}
					else if (nUserType == USER_TYPE_THERAPIST)
					{
						org.AddNewTherapist(l_pUser);
					}
					else if (nUserType == USER_TYPE_RECEPITIONIST)
					{
						org.AddNewReception(l_pUser);
					}
					else
					{
						std::cout << "Unknown user type" << std::endl;
						exit(1);
					}

					eScreenType = SCREEN_TYPE_MAIN_MENU;
				}
			}
		}
		break;

		case SCREEN_TYPE_USER_MENU_THERAPIST:
		{
			ScreenHeader("Therapist Menu");
			std::cout << "1.See patients \n2.Viewing queues \n3.Cancel an appointment \n4.Main manu"<< std::endl;
			std::cin >> sReceiveData;
			int nTemp;
			nTemp = atoi(sReceiveData.c_str());
			if (nTemp == 1)
			{
				org.PrintPatients();
			}
			else if (nTemp == 2)
			{
				pUser->ShowAppointments();
			}
			else if (nTemp == 3)
			{
				pUser->ShowAppointments();
				int nIndex = 0;
				std::cout << "Enter index:" << std::endl;
				std::cin >> nIndex;
				pUser->CancelAppointment(nIndex-1);
			}
			else if (nTemp == 4)
			{
				eScreenType = SCREEN_TYPE_MAIN_MENU;
				continue;
			}
		
		}
			break;

		case SCREEN_TYPE_USER_MENU_PATIENT:
		{
			
			ScreenHeader("Patient Menu");
			std::cout << "1.Browse therapist \n2.Request appointment \n3.View my appointments \n4.Cancel an appointment \n5.Main manu" << std::endl;
			std::cin >> sReceiveData;
			int nTemp;
			nTemp = atoi(sReceiveData.c_str());
			if (nTemp == 1)
			{
				org.PrintTherapists();

			}

			else if (nTemp == 2)
			{
				int nTherapistId;
				string sDate;
				string sTime;
				string sNote;
				std::cout << "Enter therapist ID: " << std::endl;
				std::cin >> nTherapistId;
				User* l_pUser = org.GetTherapist(nTherapistId);
				if (l_pUser == NULL)
				{
					std::cout << "Therapist not exsit\n";
					eScreenType = SCREEN_TYPE_MAIN_MENU;
					continue;
				}

				std::cout << "Enter time: " << std::endl;
				std::cin >> sTime;
				std::cout << "Enter date: " << std::endl;
				std::cin >> sDate;
				std::cout << "Enter note: " << std::endl;
				std::cin >> sNote;
				Appointment* pAppointment = new Appointment(*l_pUser, *pUser, sTime, sDate, sNote, APPOINTMENT_STATUS_PENDING);
				pUser->AddAppointment(pAppointment);
				l_pUser->AddAppointment(pAppointment);
				org.AddNewAppointment(pAppointment);
				org.AddAppointmentToReception(pAppointment); /*check the short waiting list of reception*/
				std::cout << "Appoitment sended" << std::endl;
				
			}
				


		
			else if (nTemp == 3)
			{
				pUser->ShowAppointments();
			}
			else if (nTemp == 4)
			{
				pUser->ShowAppointments();
				int nIndex = 0;
				std::cout << "Enter index :" << std::endl;
				std::cin >> nIndex;
				
				pUser->CancelAppointment(nIndex - 1);
				pUser->RemoveAppointmentFromVector(nIndex - 1);
				std::cout << "Appointment canceled" << std::endl;
			}
			else if (nTemp == 5)
			{
				eScreenType = SCREEN_TYPE_MAIN_MENU;
				continue;
			}

			
		}
		break;

		case SCREEN_TYPE_USER_MENU_RECEPTION:
		{
			ScreenHeader("Reception Menu");
			std::cout << "1.Browse therapist \n2.View therapist appointment \n3.Cancel/Required an appointment \n4.Main manu" << std::endl;
			std::cin >> sReceiveData;
			int nTemp;
			nTemp = atoi(sReceiveData.c_str());
			if (nTemp == 1)
			{
				org.PrintTherapists();
			}
			else if (nTemp == 2)
			{
				int nTherpistId;
				std::cout << "Enter therapist ID: " << std::endl;
				std::cin >> nTherpistId;
				User* l_pUser = org.GetTherapist(nTherpistId);

				l_pUser->ShowAppointments();

			}
			else if (nTemp == 3)
			{
				pUser->ShowAppointments();
				int nAppointmentIndex;
				std::cout << "Enter index :" << std::endl;
				std::cin >> nAppointmentIndex;

				nAppointmentIndex--;

				std::cout << "1 for Cancel/ 2 for approve " << std::endl;
				int nOption;
				std::cin >> nOption;
				if (nOption != 1 && nOption != 2)
				{
					std::cout << "Invalid range";
					eScreenType = SCREEN_TYPE_MAIN_MENU;
					continue;
				}
				if (nOption == 1)
				{
					pUser->CancelAppointment(nAppointmentIndex);
					std::cout << "Appointment canceled" << std::endl;

				}
				else
				{
					pUser->ApproveAppointment(nAppointmentIndex);
					std::cout << "Appointment approved" << std::endl;
				}

				pUser->RemoveAppointmentFromVector(nAppointmentIndex);

			}
			else if (nTemp == 4)
			{
				eScreenType = SCREEN_TYPE_MAIN_MENU;
				continue;
			}
			
		}
		break;
	

		}
		
	
	}
	return 0;

}
