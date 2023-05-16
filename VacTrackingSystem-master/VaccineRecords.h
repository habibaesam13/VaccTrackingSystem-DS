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
#include "Admin.h"
using namespace std;
class VaccineRecords
{
public:
	user VaccineReciever;
	VaccineRecords();
	VaccineRecords(user NewUserToQueue);
	~VaccineRecords();
};

