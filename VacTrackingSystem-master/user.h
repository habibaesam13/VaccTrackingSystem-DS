#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <deque>
#include <unordered_map>
#include <string.h>
using namespace std;
class user
{
	//Private members
	string nationalId;
	string password;
public:
	string FirstName, MiddleName, LastName, country, governorate;
	char gender;// M for male F for female
	unsigned short int age;//Age of the user
	unsigned short int vaccineDosesRecieved;// number of vaccine doses the user has taken
	bool isVaccined;// true if user got vaccined 
	bool applyForVaccine;// true if user is applying for vaccine | false is user isn't applying
	static float TotalNumber,//Total number of users
		FNumber,// number of female users
		MNumber,// number of male users
		RecFirstDose,//number of first dose recievers
		RecSecondDose;//number of second dose recievers
	//Getters
	string getID();
	string getPass();
	//Setters
	void setPass(string Pass);
	void setID(string ID);
	//Display Methods
	void DisplayUser();
	void  DisplayVaccineStatus();
	int GetQueuePosition(deque<user>& UserQueue, user& currentUser);
	//Methods to Add user to the database
	void AddUser(unordered_map<string, user>& Users, deque<user>& UserQueue);
	void AddToVaccineQueue(string id, unordered_map<string, user>& Users, deque<user>& UserQueue);//Called when the user is registering and wants to apply for vaccine
	void AddToVaccineQueue(user IntoQueue, deque<user>& UserQueue);//Called when the user is already registered and wants to apply for vaccine
	//Edit Method
	bool validateNaID(string str);
	bool validatePassword(string password);
	void EditUserData(string &new_id);
	//Delete methods
	void DeleteUser(unordered_map<string, user>& Users, deque<user>& UserQueue, string id);
	void DeleteUserFromQueue(deque<user>& UserQueue, string ID);
	//Constructors
	user();
	user(string Fisrtname, string MiddleName, string LastName, string nationalIdNEW, string passwordNEW, char genderNEW, unsigned short int ageNEW, string countryNEW, string governorateNEW, unsigned short int timesVaccinatedNew, bool isVaccined, bool applyForVaccine);
	//Destructors
	~user();
};
