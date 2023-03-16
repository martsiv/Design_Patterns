#pragma once
#include "Database.h"

std::string currentDateTime() {
	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);

	char buffer[128];
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %X", now);
	return buffer;
}
void ClientCode(Database* database)
{
	while (true)
	{
		cout << "Enter some message (Q - to quit): ";
		string msg;
		getline(cin, msg);
		if (msg == "Q" || msg == "q")
			return;
		database->Log(msg);
	}
	cout << "Goodbeye!\n";
}