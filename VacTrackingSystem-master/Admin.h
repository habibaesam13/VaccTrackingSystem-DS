#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <unordered_map>
#include <string.h>
#include "user.h"
using namespace std;
class Admin
{
	//private memebers
	string nationalId;
	string password;
public:
	string FirstName;//Admin FName
	string MiddleName;//Admin MName
	string LastName;//Admin LName
	char gender;// M for male F for female
	unsigned short int age;// age of Admin
	//getters
	string getID();
	string getPass();
	//setters
	void setPass(string Pass);
	void setID(string ID);
	//Delete Methods
	void DeleteAllUsers(unordered_map<string, user>& Users, deque<user>& UserQueue);//delete record 
	void DeleteUser(unordered_map<string, user>& Users, deque<user>& UserQueue, string id);//delete record completely
	void DeleteUserFromQueue(deque<user>& UserQueue, string ID);//delete from queue only
	//display and select methods
	void DisplayStatistics();
	void viewUser(unordered_map<string, user>& User, string id);//return the seleceted user in main
	void displayAllUsers(unordered_map<string, user>& Users);//display records
	void displayQueue(deque<user>& UsersInQueue);//display queue
	void displayByDoses(int doses, unordered_map<string, user>& UserMap);//display by number of doses
	void DisplayByAge(unordered_map<string, user>& UserTable);
	void viewNextInQueue(deque<user>& UserQueue);
	//function to add a new admin
	void addAdmin(unordered_map<string, Admin>& admins);
	//Validators
	bool validateNaID(string str);
	bool validatePassword(string password);
	//constructors
	Admin();
	Admin(string id, string pass, string FName, string MName, string LName, char gender, unsigned short int age);
	//destructors
	~Admin();
};
