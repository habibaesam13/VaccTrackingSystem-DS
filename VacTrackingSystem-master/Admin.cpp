#include "Admin.h"
#include "user.h"
#include <algorithm>
#include<regex>
//Display functions
void Admin::DisplayStatistics()
{
	cout << "\t\t\tWhat Would you like to view?\n\t\t\t1)Percentage of Males and Females Registered\n\t\t\t2)Percentage of First Dose Recievers\n\t\t\t3)Percentage of Second Dose Recievers\n";
	int choice;
	double percentage;
	cout << "\t\t\t"; cin >> choice;
	switch (choice)
	{
	case 1:
	{
		percentage = (user::FNumber / user::TotalNumber) * 100;
		cout << "\n-------------------------------------------------------------------------------";
		cout << "\n-------------------------------------------------------------------------------\n";
		cout << "\t\t\tFemales Registered in the system: " << percentage << "%";
		cout << "\n\t\t\tMales Registered in the system: " << 100 - percentage << "%\n";
		cout << "\n-------------------------------------------------------------------------------";
		cout << "\n-------------------------------------------------------------------------------\n";
		break;
	}
	case 2:
	{
		percentage = (user::RecFirstDose / user::TotalNumber) * 100;
		cout << "\n-------------------------------------------------------------------------------\n";
		cout << "\t\t\tPercentage of First Dose Recievers: " << percentage << "%";
		cout << "\n-------------------------------------------------------------------------------\n";
		break;
	}
	case 3:
	{
		percentage = (user::RecSecondDose / user::TotalNumber) * 100;
		cout << "\n-------------------------------------------------------------------------------\n";
		cout << "\t\t\tPercentage of Second Dose Recievers: " << percentage << "%";
		cout << "\n-------------------------------------------------------------------------------\n";
		break;
	}
	default:
	{
		cout << "\n\n\t\t\tEnter a valid Option!\n";
		break;
	}
	}



}
void Admin::viewUser(unordered_map<string, user>& User, string id)
{
	if (User.find(id) != User.end())
	{
		cout << "\n-------------------------------------------------------------------------------\n";
		User.at(id).DisplayUser();
		cout << "\n-------------------------------------------------------------------------------\n";
		User.at(id).DisplayVaccineStatus();
		cout << "\n-------------------------------------------------------------------------------\n";
	}
	else
	{
		cout << "\n\n\t\t\tUser Not Found! Please enter a Valid ID\n";
	}

}
void Admin::viewNextInQueue(deque<user>& UserQueue)
{
	if (!UserQueue.empty())

	{
		cout << "\n-------------------------------------------------------------------------------\n";
		UserQueue[0].DisplayUser();
		cout << "\n-------------------------------------------------------------------------------\n";
		UserQueue[0].DisplayVaccineStatus();
		cout << "\n-------------------------------------------------------------------------------";
		cout << "\n-------------------------------------------------------------------------------\n";
	}
	else
	{
		cout << "\n\n\t\t\tQueue is empty! nothing to show\n";
	}
}
void Admin::displayQueue(deque<user>& UsersInQueue)
{
	if (!UsersInQueue.empty())
	{
		for (int i = 0; i < UsersInQueue.size(); i++)
		{
			cout << "\n-------------------------------------------------------------------------------";
			cout << "\n-------------------------------------------------------------------------------\n";
			cout << "\t\t\tPosition " << i + 1;
			UsersInQueue[i].DisplayUser();
			cout << "\n-------------------------------------------------------------------------------\n";
			UsersInQueue[i].DisplayVaccineStatus();
			cout << "\n-------------------------------------------------------------------------------";
			cout << "\n-------------------------------------------------------------------------------\n";
		}
	}
	else
	{
		cout << "\n\n\t\t\tQueue is empty! nothing to show\n";
	}

}
void Admin::displayAllUsers(unordered_map<string, user>& Users)
{
	if (Users.empty())
	{
		cout << "\t\t\tEmpty User Map Detected! Nothing to Show\n";
	}
	else
	{
		unordered_map<string, user>::iterator iter;
		for (auto iter = Users.begin(); iter != Users.end(); iter++)
		{
			cout << "\n-------------------------------------------------------------------------------\n";
			iter->second.DisplayUser();
			cout << "\n-------------------------------------------------------------------------------\n";
			iter->second.DisplayVaccineStatus();
			cout << "\n-------------------------------------------------------------------------------";
			cout << "\n-------------------------------------------------------------------------------\n";
		}

	}
}
void Admin::displayByDoses(int doses, unordered_map<string, user>& UserMap)
{
	if (doses == 1)
	{

		for (auto iter = UserMap.begin(); iter != UserMap.end(); iter++)
		{
			if (iter->second.vaccineDosesRecieved == 1)
			{
				cout << "\n-------------------------------------------------------------------------------\n";
				iter->second.DisplayUser();
				cout << "\n-------------------------------------------------------------------------------\n";
				iter->second.DisplayVaccineStatus();
				cout << "\n-------------------------------------------------------------------------------";
				cout << "\n-------------------------------------------------------------------------------\n";

			}
		}
	}
	else if (doses == 2)
	{
		for (auto iter = UserMap.begin(); iter != UserMap.end(); iter++)
		{
			if (iter->second.vaccineDosesRecieved == 2)
			{
				cout << "\n-------------------------------------------------------------------------------\n";
				iter->second.DisplayUser();
				cout << "\n-------------------------------------------------------------------------------\n";
				iter->second.DisplayVaccineStatus();
				cout << "\n-------------------------------------------------------------------------------";
				cout << "\n-------------------------------------------------------------------------------\n";

			}
		}
	}
	else
	{
		cout << "Only those who received one or two doses can be viewed!" << endl;
	}
}
void Admin::DisplayByAge(unordered_map<string, user>& UserTable) {
	vector <pair<string, user>> SortedAgeVector(UserTable.begin(), UserTable.end());
	sort(SortedAgeVector.begin(), SortedAgeVector.end(), [](auto& a, auto& b) {
		return a.second.age < b.second.age;
		});
	for (auto& pair : SortedAgeVector)
	{
		cout << "\n-------------------------------------------------------------------------------\n";
		pair.second.DisplayUser();
		cout << "\n-------------------------------------------------------------------------------\n";
		pair.second.DisplayVaccineStatus();
		cout << "\n-------------------------------------------------------------------------------";
		cout << "\n-------------------------------------------------------------------------------\n";
	}

}
//User Deleting functions
void Admin::DeleteAllUsers(unordered_map<string, user>& Users, deque<user>& UserQueue)
{
	Users.clear();
	UserQueue.clear();
}
void Admin::DeleteUser(unordered_map<string, user>& Users, deque<user>& UserQueue, string id)
{
	unordered_map <string, user>::iterator it;

	it = Users.find(id);
	Users.erase(it);
	DeleteUserFromQueue(UserQueue, id);

}
void Admin::DeleteUserFromQueue(deque<user>& UserQueue, string ID)
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
		cout << "\n\t\t\tQueue is Empty! nothing to delete..\n";
	}
}
//
bool Admin::validateNaID(string nationalId) {
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
bool Admin::validatePassword(string password)
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
//Add Admin
void Admin::addAdmin(unordered_map<string, Admin>& admins)
{
	string Fname, Mname, Lname, pass, id;
	unsigned short int age;
	char gender;
	//id=getID();
	bool rightdata = true;
	cout << "\t\t\tPlease Enter Your First Name:\n\t\t\t";
	cin >> Fname;
	cout << "\t\t\tPlease Enter Your Middle Name:\n\t\t\t";
	cin >> Mname;
	cout << "\t\t\tPlease Enter Your Last Name:\n\t\t\t";
	cin >> Lname;
	cout << "\t\t\tPlease Enter Your ID:\n\t\t\t";
	cin >> id;
	if (validateNaID(id)==false)
	{
		rightdata = false;
		goto addAdminFailure;
	}
	cout << "\t\t\tPlease Enter Your Password:\n\t\t\t";
	cin >> pass;
	if (validatePassword(pass) == false)
	{
		rightdata = false;
		goto addAdminFailure;
	}
	cout << "\t\t\tPlease Enter Your Gender:\n\t\t\t" ;
	cin >> gender;
	if (gender == 'm' || gender == 'f' || gender == 'F' || gender == 'M')
	{
	}
	else
	{
		cout << "\t\t\tPlease enter a valid Gender!(m,M/f,F)\n";
		rightdata = false;
		goto addAdminFailure;
	}
	cout << "\t\t\tPlease Enter Your Age:\n\t\t\t";
	cin >> age;
	if (age < 22)
	{

		cout << "\t\t\tAdmin Must Be More Than 22 Years Old" << endl;
		rightdata = false;
		goto addAdminFailure;
	}

	if (rightdata)
	{
		admins.insert({ id, Admin(id,  pass,  Fname,  Mname,  Lname, gender, age) });
		cout << "\t\t\t Admin Added Successfully! \nID:"<<id
			<<"\n\t\t\tPassword"<<pass<<"\n";
	}
	else
	{
		addAdminFailure:cout << "\t\t\tAdd Admin was not Successfu! Please check the data and try again\n";
	}
}
//setters
void Admin::setPass(string Pass)
{
	this->password = Pass;

}
void Admin::setID(string ID)
{
	this->nationalId = ID;

}
//getters
string Admin::getID()
{
	return nationalId;
}
string Admin::getPass()
{
	return password;
}
//constructors
Admin::Admin(string id, string pass, string FName, string MName, string LName, char gender, unsigned short int age)
{
	this->age = age;
	this->gender = gender;
	this->nationalId = id;
	this->password = pass;
	this->FirstName = FName;
	this->MiddleName = MName;
	this->LastName = LName;
}
Admin::Admin()
{
	nationalId = "";
	password = "";
	FirstName = "";
	MiddleName = "";
	LastName = "";
	gender = 'N';
	age = -1;

}
//destructor
Admin::~Admin()
{}
