#include "Log.h"
#include "College.h"
#include "Course.h"
#include "Department.h"


void StartSimulation(College oCollege, const char* pi_sSimulationFile)
{
	FILE* pFile = fopen(pi_sSimulationFile, "r");
	if (pFile == NULL)
	{
		WRITE_LOG("%s", "Cant open file \n");
		exit(1);
	}

	std::ifstream infile(pFile);
	std::string line;
	while (std::getline(infile, line))
	{
		vector<string> vecResults = Utils::split(line.c_str());
		if (line[0] == '#')
		{
			continue;
		}

		else if (line[0] - 48 == 1)
		{
			if (vecResults.size() != 7)
			{
				WRITE_LOG("%s", "DB corruped \n");
				exit(1);
			}
			string sFirstName = vecResults[1];
			string sLastName = vecResults[2];
			int nId = atoi(vecResults[3].c_str());
			string sAdress = vecResults[4];
			int nYear = atoi(vecResults[5].c_str());
			string sDepartment = vecResults[6];
			Shared_ptr<Student> spStudent(new Student(sFirstName, sLastName, nId, sAdress, nYear, sDepartment));
			oCollege.AddCycle(nYear);
			oCollege.AddNewStudnet(spStudent);
		}

		else if (line[0] - 48 == 2)
		{
			if (vecResults.size() != 3)
			{
				WRITE_LOG("%s", "DB corruped \n");
				exit(1);
			}
			int nId = atoi(vecResults[1].c_str());
			int nCourseNumer = atoi(vecResults[2].c_str());
			oCollege.AddStudentToCourse(nId, nCourseNumer);
		}

		else if (line[0] - 48 == 3)
		{
			if (vecResults.size() != 2)
			{
				WRITE_LOG("%s", "DB corruped \n");
				exit(1);
			}
			int nCourseNumer = atoi(vecResults[1].c_str());
			oCollege.FinishCourse(nCourseNumer);
		
		}
		else if (line[0] - 48 == 4)
		{
			if (vecResults.size() != 3)
			{
				WRITE_LOG("%s", "DB corruped \n");
				exit(1);
			}

			int nId = atoi(vecResults[1].c_str());
			int nCourseNumber = atoi(vecResults[2].c_str());
			oCollege.SetStudentAsFinishedCourse(nCourseNumber, nId);
		
		}

		else if (line[0] - 48 == 5)
		{
			if (vecResults.size() != 3)
			{
				WRITE_LOG("%s", "DB corruped \n");
				exit(1);
			}
			int nId = atoi(vecResults[1].c_str());
			int nCourseNumber = atoi(vecResults[2].c_str());
			oCollege.RemoveStudentFromCourse(nCourseNumber, nId);
		}

		else if (line[0] - 48 == 6)
		{
			if (vecResults.size() != 3)
			{
				WRITE_LOG("%s", "DB corruped \n");
				exit(1);
			}
			int nId = atoi(vecResults[1].c_str());
			int nYearStart = atoi(vecResults[2].c_str());
			oCollege.RemoveStudentFromAll(nYearStart, nId);
		}
		else if (line[0] - 48 == 7)
		{
			if (vecResults.size() != 3)
			{
				WRITE_LOG("%s", "DB corruped \n");
				exit(1);
			}
			string sDepatmentName = vecResults[1];
			int nYear = atoi(vecResults[2].c_str());
			oCollege.PrintStudentCycle(sDepatmentName, nYear);
			
		}
		else if (line[0] - 48 == 8)
		{
			if (vecResults.size() != 2)
			{
				WRITE_LOG("%s", "DB corruped \n");
				exit(1);
			}
			int nCourseNumber = atoi(vecResults[1].c_str());
			oCollege.PrintStudentDetails(nCourseNumber);
		}
	

		else if (line == "")
		{

		}
		else
		{
			WRITE_LOG("%s", "DB corruped \n");
			exit(1);
		}


		
	}
	fclose(pFile);
}

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		std::cout << "error. please insert path to file" << std::endl;
	}

	//output file
	Log::SetLogFile(argv[3]);

	

	// init
	College college(argv[1]);
	
	// simulation
	StartSimulation(college,argv[2]);



	return 0;
}