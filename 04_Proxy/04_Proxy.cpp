#include "DatabaseProxy.h"
#include "DatabaseReal.h"
#include "func.h"

int main()
{
	string DBpath = "database.txt";
	DatabaseReal* realDB = new DatabaseReal(DBpath);
	DatabaseProxy* proxyDB = new DatabaseProxy(realDB, DBpath);
	ClientCode(proxyDB);
	delete proxyDB;
	delete realDB;
}