#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;
std::string currentDateTime();

class Database
{
protected:
	const string connectionString;
public:
	Database(string connectionString) : connectionString(connectionString) {}
	virtual bool Connect(string connectionString) = 0;
	virtual void Log(string msg) = 0;
};