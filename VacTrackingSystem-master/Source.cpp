#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <string.h>
#include "user.h"
#include "Admin.h"
#include <fstream>
#include<algorithm>
using namespace std;
float user::FNumber = 0;
float user::MNumber = 0;
float user::TotalNumber = 0;
float user::RecFirstDose = 0;
float user::RecSecondDose = 0;
deque<user>UserQueue;
unordered_map<string, Admin>AdminTable;
unordered_map<string, user>UserTable;
user selectedUser = user();
Admin currentAdmin = Admin();
user currentUser = user();
bool isUser = false;
bool isAdmin = false;
void Register();
void Login(int);
void LogOut();
void LoadUserMap();
void LoadQueue();
void LoadAdminMap();
void SaveUserMap();
void SaveAdminMap();
void SaveQueue();
void main()
{
	LoadQueue();
	LoadUserMap();
	LoadAdminMap();
	cout << "\t\t\t----------------------------------------------------" << endl;
	cout << "\t\t\t\t|WELCOME TO VACCINE TRACKING SYSTEM|" << endl;
	cout << "\t\t\t----------------------------------------------------" << "\n";
	int choice;
	char agree;
	/*cout << "\t\t\tWould you like to log in as an Admin or User?\n";
	cout << "\t\t\tfor Admin please enter 1,and for user please enter 2\n";
	cout << "\t\t\t"; cin >> choice;
	Login(choice);*/
start:while (isUser == false && isAdmin == false)
{

	cout << "\t\t\tWould you like to Register or Try Logging in Again?\n";
	cout << "\t\t\t1 to Register and 2 to Log In!\n";
	cout << "\t\t\t"; cin >> choice;
	switch (choice)
	{
	case 1:
	{
		Register();
		break;
	}
	case 2:
	{
		cout << "\t\t\tWould you like to log in as an Admin or User?\n";
		cout << "\t\t\tfor Admin please enter 1,and for user please enter 2\n";
		cout << "\t\t\t"; cin >> choice;
		Login(choice);

		break;
	}
	default:
		break;
	}
}
while (isUser)
{
	cout << "\t\t\tEnter your choice:\n\t\t\t1)Display or Edit your Data\n\t\t\t2)display position in Queue\n\t\t\t3)Apply for Vaccine\n\t\t\t4)Log Out\n\t\t\t5)to Exit\n";
	cout << "\t\t\t";
	cin >> choice;
	switch (choice)
	{


	case 1:
	{
		cout << "\t\t\tPleaes enter your ID and password again to confirm!\n";
		string tempID, tempPass;
		cout << "\t\t\t"; cin >> tempID;
		cout << "\t\t\t"; cin >> tempPass;
		if (currentUser.getID() == tempID && currentUser.getPass() == tempPass)
		{
			cout << "\t\t\tWhat would you like to do?\n \t\t\t1)Display data\n\t\t\t2)Edit Data\n\t\t\t3)Delete data\n";
			cout << "\t\t\t";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				currentUser.DisplayUser();
				cout << "\t\t\tWould you like to display your Vaccine Status?(y/n)\n";
				cout << "\t\t\t"; cin >> agree;
				if (agree == 'y' || agree == 'Y')
				{
					currentUser.DisplayVaccineStatus();
				}
				break;
			}
			case 2:
			{
				string new_id=currentUser.getID();
				UserTable.at(currentUser.getID()).EditUserData(new_id);
				if (new_id != currentUser.getID())
				{
					user TempUser = UserTable.at(currentUser.getID());
					if (currentUser.GetQueuePosition(UserQueue, currentUser) != -1)
					{
						UserQueue.at(currentUser.GetQueuePosition(UserQueue, currentUser) - 1).setID(new_id);
					}
					UserTable.erase(currentUser.getID());
					UserTable.insert({ new_id ,TempUser });
					currentUser = TempUser;
					cout << "\t\t\tID Change Detected and Updated Successfully!\n";
				}
				else
				{
					currentUser = UserTable.at(currentUser.getID());
				}
					if (UserTable.at(currentUser.getID()).applyForVaccine == true)
				{
					if (UserTable.at(currentUser.getID()).vaccineDosesRecieved != 2)
					{
						UserQueue.at(currentUser.GetQueuePosition(UserQueue, currentUser) - 1) = currentUser;
						cout << "\t\t\tData edited in map and Queue\n";
					}
					else if (UserTable.at(currentUser.getID()).vaccineDosesRecieved == 2)
					{
						UserTable.at(currentUser.getID()).DeleteUserFromQueue(UserQueue, currentUser.getID());
						UserTable.at(currentUser.getID()).applyForVaccine = false;
						currentUser = UserTable.at(currentUser.getID());
						cout << "\t\t\tDropped from queue cuz doses =2\n";
					}

				}
				break;
			}
			case 3:
			{
				cout << "\t\t\tAre you sure you would like to erase your data?\n\t\t\tThis means you will lose your position in queue!\n";
				cin >> agree;
				if (agree == 'y' || agree == 'Y')
				{
					system("cls");
					currentUser.DeleteUser(UserTable, UserQueue, currentUser.getID());
					cout << "\n\n\t\t\tYou Have Logged Out Because you deleted your Record..\n\n";
					LogOut();
					goto start;
				}
				else
				{
					cout << "\t\t\tData Erasing cancelled.\n";
				}
				break;
			}
			default:
				break;
			}

		}
		else
		{
			cout << "\t\t\tData mismatch! Please enter the credentials correctly.\n";
		}

		break;

	}
	case 2:
	{
		if (currentUser.GetQueuePosition(UserQueue, currentUser) != -1)
		{
			cout << "\t\t\tCurrent position in Queue is: " << currentUser.GetQueuePosition(UserQueue, currentUser) << endl;
			break;
		}
		else
		{
			cout << "\t\t\tYou have not applied for vaccine yet.\n";
			break;
		}
	}
	case 3:
	{
		if (currentUser.applyForVaccine == true)
		{
			cout << "\t\t\tYou Already Applied for Vaccine!\n";
		}
		else if (currentUser.vaccineDosesRecieved == 2)
		{
			cout << "\t\t\tYou can't take more doses!\n";
		}
		else
		{
			currentUser.AddToVaccineQueue(currentUser, UserQueue);
			UserQueue.at(currentUser.GetQueuePosition(UserQueue, currentUser) - 1).applyForVaccine = true;
			UserTable.at(currentUser.getID()).applyForVaccine = true;
			currentUser.applyForVaccine = true;
			cout << "\t\t\tApplication successful!\n";
		}
		break;
	}
	case 4:
	{
		LogOut();
		system("cls");
		goto start;
		break;
	}
	case 5:
	{
		SaveQueue();
		SaveAdminMap();
		SaveUserMap();
		exit(0);
	}

	default:
		break;
	}
}
while (isAdmin)
{
	
	cout << "\n\t\t\tPress 1 to display a specific user by ID: \n";
	cout << "\t\t\tPress 2 to display all users\n";
	cout << "\t\t\tPress 3 to Display the Queue(Vaccine Waiting List): \n";
	cout << "\t\t\tPress 4 to display all user by a Filter\n";
	cout << "\t\t\tPress 5 to Log Out\n";
	cout << "\t\t\tPress 6 to add a new Admin \n";
	cout << "\t\t\tPress 7 to View Basic Statistics \n";
	cout << "\t\t\tPress 8 to Exit \n\n";
	cout << "\t\t\t"; cin >> choice;
	switch (choice)
	{
	case 1:
	{	char delUser;
	char searchAgain = 0;
	string id;
	if(!UserTable.empty())
	{
		do {

		cout << "\t\t\tEnter the ID you wanna display its user: ";
		cout << "\t"; cin >> id;
		if (UserTable.find(id) != UserTable.end())
		{
			currentAdmin.viewUser(UserTable, id);
			selectedUser = UserTable.at(id);
			cout << "\n\t\t\tWould you like to erase this user's data?(y/n)";

			cin >> delUser;
			if (delUser == 'y' || delUser == 'Y')
			{
				currentAdmin.DeleteUser(UserTable, UserQueue, selectedUser.getID());
				selectedUser = user();
			}
		}
		else
		{
			cout << "\n\t\t\tUser with ID: " << id << "Does not exist in database files\n\n";
		}
			
			cout << "\t\t\tWould you like to search for another user?\n\t\t\t";
			cin >> searchAgain;
		
		}
		while (searchAgain == 'y' || searchAgain == 'Y');
	}
	else
	{
		
		cout << "\t\t\tUser Map is empty..!\n\t\t\tPlease wait until more users Register.\n\n";
	}
	break;
	}
	case 2:
	{
		if (!UserTable.empty())
		{

			currentAdmin.displayAllUsers(UserTable);
			char delAll;
			cout << "\t\t\tWould you like to Delete all the Database?\n\t\t\t";
			cin >> delAll;
			if (delAll == 'y' || delAll == 'Y')
			{
				cout << "\t\t\tAre you SURE??? This will erase everything!\n\t\t\t";
				cin >> delAll;
				if (delAll == 'Y' || delAll == 'y')
				{
					currentAdmin.DeleteAllUsers(UserTable, UserQueue);
					system("cls");
					cout << "\t\t\tAll Data Deleted..\n";
				}
			}
			else
			{
				cout << "\t\t\tDelete all process was cancelled." << endl;
			}
		}
		else
		{
			cout << "\t\t\tNo Users in database files to show..\n\t\t\tPlease wait until more users Register.\n\n";
		}
		break;
	}
	case 3:
	{
		if (!UserQueue.empty())
		{
			currentAdmin.displayQueue(UserQueue);
		}
		else
		{
			
			cout << "\t\t\tQueue is Empty,Nothing to show! \n\t\t\tPlease Wait until more users apply for Vaccine.\n\n";
		}
		break;
	}
	case 4:
	{
		if (!UserTable.empty())
		{
			cout << "\t\t\tHow would you like to filter the users?" << endl;
			cout << "\t\t\t1)by dose number\t\t\t2)By Age Ascendingly\n\t\t\t";
			cin >> agree;
			if (agree == '1')
			{
				cout << "\t\t\tEnter the dose filter(1/2)" << endl;
				cout << "\t\t\t"; cin >> choice;
				currentAdmin.displayByDoses(choice, UserTable);
				cout << "\n";

			}
			else if (agree == '2')
			{
				currentAdmin.DisplayByAge(UserTable);

			}
		}
		else
		{
		
			cout << "\t\t\tNo Users in database files to show..\n\t\t\tPlease wait until more users Register.\n\n";
		}
		break;
	}
	case 5:
	{
		LogOut();
		system("cls");
		goto start;
		break;
	}
	case 6:
	{
		cout << "Please confirm you are an admin." << endl;
		cout << "Enter your ID and Password\n\t\t\t";
		string id, pass;
		cin >> id >> pass;
		if (currentAdmin.getID() == id && currentAdmin.getPass() == pass)
		{
			currentAdmin.addAdmin(AdminTable);
		}
		else
		{
			cout << "\t\t\tError in entered data\n";
		}
		break;
	}
	case 7:
	{
		if (!UserTable.empty())
		{
			currentAdmin.DisplayStatistics();
		}
		else
		{
			system("cls");
			cout << "\t\t\tNo Users in database files to show..\n\t\t\tPlease wait until more users Register.\n\n";
		}
		break;
	}
	case 8:
	{
		SaveQueue();
		SaveAdminMap();
		SaveUserMap();
		exit(0);
	}
	default:
		break;
	}

	
}
}
void Register()
{
	selectedUser.AddUser(UserTable, UserQueue);
}
void Login(int choice)
{
	system("cls");
	string id, password;
	cout << "\t\t\tPLEASE enter your ID followed by passowrd!\n";
	cout << "\t\t\t"; cin >> id;
	cout << "\t\t\t"; cin >> password;
	if (choice == 1)
	{
		if (AdminTable.find(id) != AdminTable.end())
		{
			if (AdminTable.at(id).getPass() == password)
			{
				currentAdmin = AdminTable.at(id);
				isAdmin = true;
				isUser = false;
			}
			else
			{
				cout << "\t\t\tWrong Password or ID Detected!\n";
			}
		}
	}
	else if (choice == 2) {
		if (UserTable.find(id) != UserTable.end())
		{
			if (UserTable.at(id).getPass() == password)
			{
				currentUser = UserTable.at(id);
				cout << "\t\t\tLogin Successful!\n\n";
				isUser = true;
				isAdmin = false;
			}
			else
			{
				cout << "\t\t\tWrong Password or ID Detected!\n\n";
			}
		}
		else
		{
			cout << "\t\t\tID not detected!\n\t\t\tPlease Register or Try Logging in again.\n\n";
		}

	}
	else
	{
		cout << "\t\t\tPlease Enter a valid choice!\n\n";
	}
}
void LogOut()
{
	isUser = false;
	isAdmin = false;
	currentUser = user();
	currentAdmin = Admin();
}
void LoadUserMap()
{


	// read from file into program
	ifstream UserTableFile; //input file
	UserTableFile.open("UserMap.txt");
	if (!UserTableFile.is_open())
	{
		cout << "\ncan't Load file! ";
	}
	else
	{
		string tempID, tempPass, FirstName, MiddleName, LastName, country, governorate;
		char gender;// M for male F for female
		unsigned short int age;//Age of the user
		unsigned short int vaccineDosesRecieved;// number of vaccine doses the user has taken
		bool isVaccined;// true if user got vaccined | false if user haven't 
		bool applyForVaccine;// true if user is applying for vaccine | false is user isn't applying
		while (UserTableFile >> tempID >> tempPass)
		{


			UserTableFile >> FirstName >>
				MiddleName >> LastName
				>> country >> governorate
				>> gender >> applyForVaccine
				>> isVaccined >> age
				>> vaccineDosesRecieved;

			UserTable.insert({ tempID,user(FirstName, MiddleName, LastName, tempID, tempPass, gender,age,country,governorate,vaccineDosesRecieved, isVaccined, applyForVaccine) });
		}
		cout << "Loading User Map Complete!\n";
	}
	UserTableFile.close(); // closing file
}
void SaveUserMap()
{
	user writingToFile = user();//writes user to file from the unordered map

	/*write from program to file */
	ofstream UserTableFile;
	UserTableFile.open("UserMap.txt"); // open file
	// check if file is open
	if (!UserTableFile.is_open())
	{
		cout << "\ncan't Save file! ";
	}
	else
	{
		unordered_map<string, user>::iterator iter;
		for (auto iter = UserTable.begin(); iter != UserTable.end(); iter++)
		{
			writingToFile = iter->second;
			UserTableFile << writingToFile.getID() << " " << writingToFile.getPass() << " " << writingToFile.FirstName << " "
				<< writingToFile.MiddleName << " " << writingToFile.LastName << " "
				<< writingToFile.country << " " << writingToFile.governorate << " " << writingToFile.gender << " "
				<< writingToFile.applyForVaccine << " " << writingToFile.isVaccined
				<< " " << writingToFile.age << " " << writingToFile.vaccineDosesRecieved << "\n";
		}
		cout << "\nSaving Succesful!";
	}
	UserTableFile.close();


}
void LoadAdminMap()
{
	ifstream AdminTableFile; //input file
	AdminTableFile.open("AdminMap.txt");
	if (!AdminTableFile.is_open())
	{
		cout << "\ncan't Load file! ";
	}
	else
	{
		string tempID, tempPass;
		while (AdminTableFile >> tempID >> tempPass)
		{
			Admin readingFromFile = Admin();
			readingFromFile.setID(tempID);
			readingFromFile.setPass(tempPass);
			AdminTableFile >> readingFromFile.FirstName >> readingFromFile.MiddleName >> readingFromFile.LastName
				>> readingFromFile.gender >> readingFromFile.age;
			AdminTable.insert({ tempID,readingFromFile });
		}
		cout << "Loading Admin Map Complete!\n\n\n\n";
		AdminTableFile.close(); // closing file
	}

}
void SaveAdminMap()
{


	/*write from program to file */
	ofstream AdminTableFile;
	AdminTableFile.open("AdminMap.txt"); // open file
	// check if file is open
	if (!AdminTableFile.is_open())
	{
		cout << "\ncan't Save file! ";
	}
	else
	{

		for (auto iter = AdminTable.begin(); iter != AdminTable.end(); iter++)
		{

			AdminTableFile << iter->second.getID() << " " << iter->second.getPass()
				<< " " << iter->second.FirstName << " " << iter->second.MiddleName << " "
				<< iter->second.LastName << " " << iter->second.gender << " " << iter->second.age << "\n";
		}
		cout << "\nSaving Succesful!";
	}
	AdminTableFile.close();


}
void SaveQueue()
{
	user writingToFile = user();//writes user to file from the unordered map

	/*write from program to file */
	ofstream UserQueueFile;
	UserQueueFile.open("UserQueue.txt"); // open file
	// check if file is open
	if (!UserQueueFile.is_open())
	{
		cout << "\ncan't Save file! ";
	}
	else
	{
		//deque<user>::iterator iter;
		//for (auto iter = UserQueue.begin(); iter != UserQueue.end(); iter++)
		for (const auto& user : UserQueue) {
			writingToFile = user;
			UserQueueFile << writingToFile.getID() << " "
				<< writingToFile.getPass() << " " << writingToFile.FirstName << " "
				<< writingToFile.MiddleName << " " << writingToFile.LastName << " "
				<< writingToFile.country << " " << writingToFile.governorate << " "
				<< writingToFile.gender << " " << writingToFile.applyForVaccine << " "
				<< writingToFile.isVaccined << " " << writingToFile.age << " "
				<< writingToFile.vaccineDosesRecieved << "\n";
		}
		cout << "\nSaving Succesful!";
	}
	UserQueueFile.close();

}
void LoadQueue()
{


	// read from file into program
	ifstream UserQueueFile; //input file
	UserQueueFile.open("UserQueue.txt");
	if (!UserQueueFile.is_open())
	{
		cout << "\ncan't Load file! ";
	}
	else
	{
		string tempID, tempPass;
		while (UserQueueFile >> tempID >> tempPass)
		{
			user readingFromFile = user();//reads user from file to add copy in the user map
			UserQueueFile >> readingFromFile.FirstName >>
				readingFromFile.MiddleName >> readingFromFile.LastName
				>> readingFromFile.country >> readingFromFile.governorate
				>> readingFromFile.gender >> readingFromFile.applyForVaccine
				>> readingFromFile.isVaccined >> readingFromFile.age
				>> readingFromFile.vaccineDosesRecieved;
			readingFromFile.setID(tempID);
			readingFromFile.setPass(tempPass);
			UserQueue.push_back(readingFromFile);
		}
		cout << "Loading User Queue Complete!\n";
	}
	UserQueueFile.close(); // closing file

}
