#include "user.h"
#include<iostream>
#include<regex>
using namespace std;
//Delete user's Record
void user::DeleteUserFromQueue(deque<user>& UserQueue, string ID)
{
	bool UserExists=false;
	if (!UserQueue.empty())
	{

		for (auto& user : UserQueue)
		{
			if (user.getID() == ID)
			{
				UserExists = true;
				break;
			}

		}
		if (UserExists==true)
		{
			stack<user>UserStack;
			for (auto& user : UserQueue)
			{
				if (user.getID() == ID)
				{
					UserQueue.pop_front();
					break;
				}
				else
				{

					UserStack.push(user);
					UserQueue.pop_front();

				}
			}
			while (!UserStack.empty())
			{
				UserQueue.push_front(UserStack.top());
				UserStack.pop();
			}
		}
		else
		{
		cout << "\t\t\tUser Not In waiting list for vaccination,thus no changes were made to the Queue!\n";
		}
	}
	else
	{
		cout << "\t\t\tQueue is Empty! nothing to show\n";
	}
	
}
void user::DeleteUser(unordered_map<string, user>& Users, deque<user>& UserQueue, string id)
{
	unordered_map <string, user>::iterator it;

	it = Users.find(id);
	Users.erase(it);
	DeleteUserFromQueue(UserQueue, id);

}
//Add a new user
void user::AddUser(unordered_map<string, user>& Users, deque<user>& UserQueue)
{
	char wasVaccinated, gender, applyForvac, confirmRegistration;
	int dosesRecieved, age;
	bool correctData = true, applyForVaccine = false, isFULLYVaccined;
	unordered_map <string, user>::iterator it;
	string nationalId, password, FName, MName, LName, country, governorate;
	cout << "\t\t\tEnter ID\t";
	cin >> nationalId;
	if (validateNaID(nationalId) == false)
	{
		correctData = false;
		goto RegistrationFailure;
	}
	it = Users.find(nationalId);
	if (it == Users.end())
	{
		cout << "\t\t\tEnter Password\t";
		cin >> password;
		if (validatePassword(password) == false)
		{
			correctData = false;
			goto RegistrationFailure;
		}
		cout << "\t\t\tEnter First Name \t";
		cin >> FName;
		cout << "\t\t\tEnter Middle Name\t";
		cin >> MName;
		cout << "\t\t\tEnter Last Name  \t";
		cin >> LName;
		cout << "\t\t\tAge\t              ";
		cin >> age;
		if (age < 17)
		{
			cout << "\t\t\tAge invalid!\n\t\t\tOnly Citizens of 17 years or above can register.\n";
			correctData = false;
			goto RegistrationFailure;
		}
		cout << "\t\t\tGender\t\t\t";
		cin >> gender;
		if (gender == 'm' || gender == 'f' || gender == 'F' || gender == 'M')
		{


		}
		else
		{
			cout << "\t\t\tGender incorrect,Please enter a valid character(M/m/f/F)\n";
			correctData = false;
			goto RegistrationFailure;
		}
		cout << "\t\t\tCountry\t\t\t";
		cin >> country;
		if (country != "Egypt")
		{
			cout << "\t\t\tplease Enter correct data\n";
			correctData = false;
			goto RegistrationFailure;
		}
		cout << "\t\t\tGovernorate\t\t";
		cin >> governorate;//use enum function


		if (correctData) {
			cout << "\t\t\tHave you been Vaccinated before?(y/n)\t\t\t";
			cin >> wasVaccinated;
			if (wasVaccinated == 'y' || wasVaccinated == 'Y')
			{
				cout << "\t\t\tHow many doses of the vaccine did you recieve?\n\t\t\t";
				cin >> dosesRecieved;
				if (dosesRecieved == 2)
				{
					cout << "\n\t\t\tYou Got All Doses..\n";
					isFULLYVaccined = true;
					applyForVaccine = false;
				}
				else
				{
					isFULLYVaccined = false;
					cout << "\t\t\tWould you like to apply for vaccination?\t\t\t";
					cin >> applyForvac;
					if (applyForvac == 'y' || applyForvac == 'Y')
					{
						applyForVaccine = true;
					}
					else {
						applyForVaccine = false;
						/*correctData = false;
						cout << "You must apply for Vaccine in order to register!";*/
					}

				}
			}
			else
			{

				dosesRecieved = 0;
				isFULLYVaccined = false;
				cout << "\t\t\tWould you like to apply for vaccination?\t\t\t";
				cin >> applyForvac;
				if (applyForvac == 'y' || applyForvac == 'Y')
				{
					applyForVaccine = true;
				}
				else {
					applyForVaccine = false;
					/*correctData = false;
					cout << "You must apply for Vaccine in order to register!";*/
				}
			}
		}
		if (correctData)
		{
			cout << "\n\t\t\tConfirm Registration?('y' or 'Y' to confirm)\t\t\t";
			cin >> confirmRegistration;
			if (confirmRegistration != 'y' && confirmRegistration != 'Y')
			{
				correctData = false;
				applyForVaccine = false;
				cout << "\t\t\tRegistration Cancelled! \n";
			}
		}
		if (correctData)
		{
			Users.insert({ nationalId, user(FName,MName,LName, nationalId, password, gender, age, country, governorate,dosesRecieved,isFULLYVaccined,applyForVaccine) });
			cout << "\t\t\tWould you like to Edit your data?\t\t\t";
			cin >> confirmRegistration;
			if (confirmRegistration == 'Y' || confirmRegistration == 'y')
			{
				Users.at(nationalId).EditUserData(nationalId);
			}
		}
		if (applyForVaccine && correctData)
		{
			AddToVaccineQueue(nationalId, Users, UserQueue);
		}
	}
	else
	{
		cout << "\t\t\tUser is already found..\n\n";
		correctData = false;
	}
RegistrationFailure:	if (!correctData)
{
	cout << "\t\t\tRegistration was unsuccesful!\n";
}
}
//Edit User
void user::EditUserData(string &new_id)
{
	char editAgain = 'y';
	while (editAgain == 'y' || editAgain == 'Y')
	{
		int EditChoice;
		string toEditString;
		unsigned short int ToEditNumbers;
		cout << "Please Select what would you like to edit: \n1)Name\n2)Password\n3)age\n4)Gender\n5)Vaccine Doses Recieved\n6)Governorate\n7)Country\n8)National ID\n";
		cin >> EditChoice;
		switch (EditChoice)
		{
		case 1:
		{
			cout << "Enter the Name Correctly(First,then Middle,then Last): \t";
			cin >> toEditString;
			this->FirstName = toEditString;
			cin >> toEditString;
			this->MiddleName = toEditString;
			cin >> toEditString;
			this->LastName = toEditString;
			cout << "Name was successfully changed!\n";
			cout << "Want to Edit  something else?(y/n)\n";
			cin >> editAgain;
			break;
		}
		case 2:
		{
			cout << "Please enter your Password correctly: \n";
			cin >> toEditString;
			if (toEditString == this->password)
			{
				cout << "Password cannot be the same!\n";
			}
			else
			{
				if (validatePassword(toEditString) == true)
				{
					this->password = toEditString;
					cout << "Password successfully changed!\n";
				}
				else
				{
					cout << "Unable to change Password!\nPlease try again.\n";
				}
			}
			cout << "Want to Edit  something else?(y/n)\n";
			cin >> editAgain;
			break;
		}
		case 3:
		{
			cout << "\t\t\tEnter the Age Correctly: \t";
			cin >> ToEditNumbers;
			if (ToEditNumbers > 17)
			{
				cout << "\t\t\tAge changed from: " << this->age << " To: " << ToEditNumbers << endl;
				this->age = ToEditNumbers;

			}
			else
			{
				cout << "\t\t\tAge must be above 17!\n";
			}
			cout << "\t\t\tWant to Edit  something else?(y/n)\n";
			cin >> editAgain;
			break;
		}
		case 4:
		{
			cout << "\t\t\tEnter the Gender Correctly(M/F): \t";
			cin >> toEditString;
			if (toEditString[0] == 'm' || toEditString[0] == 'M' || toEditString[0] == 'F' || toEditString[0] == 'f')
			{
				this->gender = toEditString[0];
			}
			else
			{
				cout << "enter a valid Gender input (M/m,F/f)!";
			}
			cout << "\t\t\tWant to Edit  something else?(y/n)\n";
			cin >> editAgain;
			break;
		}
		case 5:
		{
			cout << "\t\t\tEnter how many Vaccine doses you recieved: \t";
			cin >> ToEditNumbers;
			if (ToEditNumbers <= 2 && ToEditNumbers >= 0)
			{
				if (vaccineDosesRecieved != ToEditNumbers)
				{
					if (vaccineDosesRecieved == 0 && ToEditNumbers == 1)
					{
						user::RecFirstDose++;
						vaccineDosesRecieved = 1;
					}
					else if (vaccineDosesRecieved == 0 && ToEditNumbers == 2)
					{
						user::RecSecondDose++;
						vaccineDosesRecieved = 2;
						isVaccined = true;
					}
					else if (vaccineDosesRecieved == 1 && ToEditNumbers == 2)
					{
						user::RecFirstDose--;
						user::RecSecondDose++;
						vaccineDosesRecieved = 2;
						isVaccined = true;
					}
					else if (vaccineDosesRecieved == 2 && ToEditNumbers == 1)
					{
						user::RecFirstDose++;
						user::RecSecondDose--;
						vaccineDosesRecieved = 1;
					}
					else if (vaccineDosesRecieved == 2 && ToEditNumbers == 0)
					{
						user::RecSecondDose--;
						vaccineDosesRecieved = 0;
					}
					else if (vaccineDosesRecieved == 1 && ToEditNumbers == 0)
					{
						user::RecFirstDose--;
						vaccineDosesRecieved = 0;
					}

				}
			}
			else if (vaccineDosesRecieved == ToEditNumbers)
			{
				cout << "\t\t\tYou entered the same number of doses..Nothing changed.\n";
			}
			else
			{
				cout << "\t\t\tPlease enter a valid value (0,1,2)!" << endl;
			}
			cout << "\t\t\tWant to Edit  something else?(y/n)\n";
			cout << "\t\t\t"; cin >> editAgain;
			break;
		}
		case 6:
		{

			cout << "\t\t\tEnter Your Governorate Correctly:  \t";
			cin >> toEditString;
			this->governorate = toEditString;
			cout << "\t\t\tWant to Edit  something else?(y/n)\n";
			cin >> editAgain;
			break;
		}
		case 7:
		{
			cout << "\t\t\tEnter Your Country Correctly:  \t";
			cin >> toEditString;
			if (toEditString == "Egypt")
			{
				this->country = toEditString;
			}
			else
			{
				cout << "\t\t\tYour Country must be Egypt!" << endl;
			}
			cout << "\t\t\tWant to Edit  something else?(y/n)\n";
			cin >> editAgain;

			break;
		}
		case 8:
		{
			cout << "\t\t\tPlease enter the National ID\n";
			cin >> toEditString;
			if (validateNaID(toEditString) == true)
			{
				if (nationalId!=toEditString) 
				{
					this->nationalId = toEditString;
					new_id= nationalId;
					cout << "\t\t\tNational ID Changed Successfully!\n";
				}
				else
				{
					cout << "\t\t\tCan't use the same ID,please try again with a different ID\n";
				}
			}
			else
			{
				cout << "\t\t\tError changing your ID,please try again.\n";
			}
			cout << "\t\t\tWant to Edit  something else?(y/n)\n\t\t\t";
			cin >> editAgain;
		}
		default:
			break;
		}
	}
}
//Display functions
void user::DisplayUser()
{
	cout << "\n-------------------------------------------------------------------------------\n";
	cout << "\t\t\tID: " << getID()<<"\n\t\t\tPassWord: "<<getPass()<< "\n\t\t\tName: " << FirstName << " " << MiddleName << " " << LastName << "\n\t\t\tGender: " << gender << "\n\t\t\tAge: " << age;
	cout << "\n-------------------------------------------------------------------------------\n";
}
void user::DisplayVaccineStatus()
{
	string applyForVac, fullyVac;
	if (isVaccined)
	{
		fullyVac = "Fully Vaccinated.";
	}
	else
	{
		fullyVac = "Not Fully Vaccinated";
	}
	if (applyForVaccine)
	{
		applyForVac = "Applied";
	}
	else
	{
		applyForVac = "Not Applied";
	}
	cout << "\n-------------------------------------------------------------------------------\n";
	cout << "\t\t\tNumber of Doses Left: " << 2 - vaccineDosesRecieved << "\n\t\t\tApplication for vaccine: " << applyForVac << "\n\t\t\tVaccination Status:" << fullyVac ;
	cout << "\n-------------------------------------------------------------------------------\n";
}
//Queue Functions
int user::GetQueuePosition(deque<user>& UserQueue, user& currentUser)
{
	
		for (int i = 0; i < UserQueue.size(); i++)
		{
			if (UserQueue[i].getID() == currentUser.getID() && UserQueue[i].getPass() == currentUser.getPass())
			{
				return i + 1;
			}
		}

		return -1;
}
void user::AddToVaccineQueue(user IntoQueue, deque<user>& UserQueue)
{
	UserQueue.push_back(IntoQueue);
}
void user::AddToVaccineQueue(string id, unordered_map<string, user>& UserTable, deque<user>& UserQueue)
{




	UserQueue.push_back(UserTable.at(id));
}
//Test validate NID , PASSWORD
bool user::validateNaID(string nationalId) {
	const regex pattern("^[0-9]{3}[0-9]{7}[0-9]{3}$");
	if (nationalId.empty()) {
		cout << "\n\t\t\tNo Input Detected!\n";
	}

	// Return true if the str
	// matched the ReGex
	if (regex_match(nationalId, pattern)) {
		return true;
	}
	else {
		cout << "\n\t\t\tPlease enter a valid ID,consisting of 13 numbers only and exactly.\n";
		return false;

	}


}
bool user::validatePassword(string password)
{
	// regex pattern for password validation  
	regex pattern("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@#$%*^&+=]).{8,}");

	// check if the password matches the pattern  
	if (regex_match(password, pattern))
	{
		return true;
	}
	else
	{

		cout << "\n\t\t\tPlease enter a valid Password that includes at  least:\n\t\t\t1 Capital and 1 Small letters\n\t\t\tat least 1 number and 1 symbol \n\t\t\tand is 8 characters long.\n";
		return false;

	}

}
//setters
void user::setID(string ID)
{
	this->nationalId = ID;
}
void user::setPass(string Pass)
{
	this->password = Pass;
}
//getters
string user::getID()
{
	return nationalId;
}
string user::getPass()
{
	return password;
}
//constructors
user::user(string Firstname, string MiddleName, string LastName, string nationalIdNEW, string passwordNEW, char genderNEW, unsigned short int ageNEW, string countryNEW, string governorateNEW, unsigned short int timesVaccinatedNew, bool isVaccined, bool applyForVaccine)
{
	this->FirstName = Firstname;
	this->MiddleName = MiddleName;
	this->LastName = LastName;
	nationalId = nationalIdNEW;
	password = passwordNEW;
	gender = genderNEW;
	age = ageNEW;
	country = countryNEW;
	governorate = governorateNEW;
	vaccineDosesRecieved = timesVaccinatedNew;
	this->isVaccined = isVaccined;
	this->applyForVaccine = applyForVaccine;
	if (gender == 'M' || gender == 'm')
	{
		MNumber++;
		TotalNumber++;
	}
	else
	{
		FNumber++;
		TotalNumber++;
	}
	if (vaccineDosesRecieved == 1)
	{
		RecFirstDose++;
	}
	else if (vaccineDosesRecieved == 2)
	{
		RecSecondDose++;
	}
}
user::user()
{
	FirstName = "-1";
	MiddleName = "-1";
	LastName = "-1";
	nationalId = "-1";
	password = "-1";
	gender = 'N';
	age = -1;
	country = "-1";
	governorate = "-1";
	vaccineDosesRecieved = -1;
	this->isVaccined = false;
	this->applyForVaccine = false;
}
//destructor
user::~user()
{

}
