#pragma once
#include "Database.h"
class DatabaseReal : public Database
{
private:
	bool isConnect;
public:
	DatabaseReal(string connectionString) : Database(connectionString), isConnect(0) {}
	bool Connect(string connectionString) override
	{
		if (connectionString == this->connectionString)
			isConnect = (rand() % 10) < 6; // immitates 60% good connection, aka. very bad
		else
			isConnect = 0;
		return isConnect;
	}
	void Log(string msg) override
	{
		ofstream fout(connectionString, ios::app);
		fout << msg << " : " << currentDateTime() << endl;
		fout.close();
		isConnect = 0;
	}
};