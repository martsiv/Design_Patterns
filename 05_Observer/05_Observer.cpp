#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <set>
#include <vector>
#include <deque>

const int Xtime = 5;
const int swingError = 10;

class Coin
{
	std::string name;
	int priceOfBuy;
	int value;
	std::deque<int> history;
	int numOfHistory;
public:
	Coin(std::string name) : name(name), priceOfBuy(0), value(100), numOfHistory(Xtime) {}
	friend std::ostream& operator<< (std::ostream& out, const Coin& coin)
	{
		out << coin.name << " " << coin.value;
		return out;
	}
	friend bool operator< (const Coin& c1, const Coin& c2)
	{
		return c1.name < c2.name;
	}
	/*friend bool operator== (const Coin& c1, const Coin& c2)
	{
		return 
	}*/
	operator std::string() { return name; }
	void UpdateHistory(int newPrice)
	{
		history.push_back(newPrice);
		while (numOfHistory < history.size())
			history.pop_front();
	}
	void Buy(int value) 
	{ 
		this->value += value; 
	}
	int Sell(int currentPrice) 
	{
		std::cout << "Sell. New price = " << currentPrice << " all coins (" << value << "). Total summ = " << currentPrice * value << "\n";
		return currentPrice * value;
	}
	int GetValue() const { return value; }
	int GetAvegareLastHistory() const
	{
		if (history.size() < numOfHistory)
			return 0;
		int result = 0;
		for (auto i : history)
			result += i;
		result /= history.size();
		return result;
	}
	std::string GetName() const { return name; }
};

class Client
{
	std::string fullname;
	long long money;
	std::set<Coin> coins;
	//int CalculateTrend(std::string coinName)
	//{
	//	for (auto i : coins)
	//		if (i.GetName() == coinName)
	//			return i.GetAvegareLastHistory();
	//	return 0;
	//}
public:
	Client(std::string fullname) : fullname(fullname), money(100000) {}
	void Update(std::string coinName, int newPrice)
	{
		if (coins.find(coinName) == coins.end())
			coins.emplace(Coin(coinName));
		std::cout << "Client " << fullname << ":\n";
		for (auto i : coins)
		{
			if (i.GetName() == coinName)
			{
				i.UpdateHistory(newPrice);
				int average = i.GetAvegareLastHistory();
				if (average)
				{
					if (((average + swingError * 2) < newPrice) && i.GetValue()) // if down trend && 0 < value == SELL
					{
						money += i.Sell(newPrice);
					}
					else if (newPrice < ((average - swingError * 2)) && (1000 < money)) // if up trend && newPrice < money == BUY (~1000$)
					{
						int val = 0 < (1000 / newPrice) ? (1000 / newPrice) : (newPrice <= money ? 1 : 0);
						std::cout << "Buy " << val << " coins, " << val * newPrice << "$\n";
						i.Buy(val);
						money -= val * newPrice;
					}
				}
				return;
			}
		}
	}
	std::string GetFullname() { return fullname; }
};

class Exchange
{
	struct Coin
	{
		std::string name;
		int currentPrice;
		Coin(std::string name, int currentPrice) : name(name), currentPrice(currentPrice){}
		friend bool operator< (const Coin& c1, const Coin& c2)
		{
			return c1.name < c2.name;
		}
	};
	std::map<std::string, Client&> map_clients;
	std::set<Coin> coins;
public:
	Exchange()
	{
		coins.emplace(Coin{ "BTC", 324 });
		coins.emplace(Coin{ "ETH", 423 });
		coins.emplace(Coin{ "BCH", 23 });
		coins.emplace(Coin{ "XRP", 132 });
		coins.emplace(Coin{ "LTC", 731 });
	}
	void Subscribe(Client& client)
	{
		map_clients.insert({ client.GetFullname(), client });
	}
	void Unsubscribe(Client& client)
	{
		map_clients.erase(client.GetFullname());
	}
	void Notify(std::string coinName, int newPrice)
	{
		for (auto i : map_clients)
			i.second.Update(coinName, newPrice);
	}
	void ChangePrice()
	{
		for (auto i : coins)
		{
			i.currentPrice += -10 + rand() % (10 - (-10) + 1);
			Notify(i.name, i.currentPrice);
		}
		system("PAUSE");
	}

};

int main()
{
	Client* Max = new Client("Max Semkiv");
	Client* Ivan = new Client("Ivan Petruk");
	Exchange exchange;
	exchange.Subscribe(*Max);
	exchange.Subscribe(*Ivan);
	for (int i = 0; i < 20; i++)
		exchange.ChangePrice();
	delete Max;
	delete Ivan;

}