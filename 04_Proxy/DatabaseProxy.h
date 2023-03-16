#pragma once
#include "Database.h"
#include "DatabaseReal.h"
class DatabaseProxy : public Database
{
private:
	DatabaseReal* database;
	string localTempDatabase;
	bool isInsideCreatedDB;
	bool CheckLocal()
	{
		ifstream fin(localTempDatabase);
		if (fin.get())
		{
			fin.close();
			return true;
		}
		else
		{
			fin.close();
			return false;
		}
	}
	void DeleteLocalDB()
	{
		ofstream deleteLocalFile(localTempDatabase, ios::trunc);
		deleteLocalFile.close();
	}
public:
	DatabaseProxy(DatabaseReal* database, string connectionString)
		: Database(connectionString), database(database), localTempDatabase("localTempDatabase.txt"), isInsideCreatedDB(false) {}
	~DatabaseProxy()
	{
		DeleteLocalDB();
		if (isInsideCreatedDB)
			delete database;
	}
	bool Connect(string connectionString) override
	{
		return database->Connect(connectionString);
	}
	void Log(string msg) override
	{
		if (!Connect(connectionString))
		{
			fstream fout(localTempDatabase, ios::app);
			fout << msg << " : " << currentDateTime() << endl;
			fout.close();
		}
		else
		{
			if (CheckLocal())
			{
				ifstream fin(localTempDatabase);
				string input;
				while (getline(fin, input))
				{
					database->Log("From Local: " + input);
				}
				fin.close();
				DeleteLocalDB();
			}
			database->Log(msg);
		}
	}
};