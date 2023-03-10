#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

enum class MessageType { INFO = 1, WARNING, ERROR };

std::string GetNameOfType(MessageType type)
{
	switch (MessageType(type))
	{
	case MessageType::INFO:
		return "INFO";
	case MessageType::WARNING:
		return "WARNING";
	case MessageType::ERROR:
		return "ERROR";
	default:
		return " ";
	}
}
int ReturnTypeToInt(std::string tmp)
{
	if (tmp.find("INFO") != std::string::npos)
		return 1;

	if (tmp.find("WARNING") != std::string::npos)
		return 2;

	if (tmp.find("ERROR") != std::string::npos)
		return 3;

	return 0;
}
std::string currentDateTime() {
	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);

	char buffer[128];
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %X", now);
	return buffer;
}

class Singleton
{
	Singleton() { }
	int _logCount = 0;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(Singleton&) = delete;

public:
	static Singleton& GetInstance()
	{
		static Singleton instance;
		return instance;
	}
	void Log(MessageType type, std::string message)
	{
		std::ofstream fout("log.txt", std::ios::app);

		fout << GetNameOfType(type) << ":" << _logCount << " at " << currentDateTime() << " - " << message << std::endl;
		_logCount++;
		fout.close();
	}
	void ReadAllMessages()
	{
		std::ifstream fin("log.txt");

		if (!fin)
			return;
		std::string input_str;
		while (fin >> input_str)
		{
			if (ReturnTypeToInt(input_str))
				std::cout << std::endl;
			std::cout << input_str << ' ';
		}
		fin.close();
	}
	void ReadMessagesByType(MessageType type)
	{
		std::ifstream fin("log.txt");

		if (!fin)
			return;
		std::string input_str;
		bool trueType = 0;
		int int_type = 0;
		while (fin >> input_str)
		{
			int_type = ReturnTypeToInt(input_str);
			if (int_type)
			{
				if (MessageType(int_type) == type)
				{
					std::cout << std::endl;
					trueType = 1;
				}
				else
					trueType = 0;
			}
			if (trueType)
				std::cout << input_str << ' ';
		}
		fin.close();
	}
};

int main()
{
	Singleton::GetInstance().Log(MessageType::ERROR, "First message in the log");
	Singleton::GetInstance().Log(MessageType::WARNING, "Second message in the log");
	Singleton::GetInstance().ReadAllMessages();
	Singleton::GetInstance().ReadMessagesByType(MessageType::ERROR);
}