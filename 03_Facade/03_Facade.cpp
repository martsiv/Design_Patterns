#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Hotel
{
private:
	const int price1Person = 800;
	const int price2Person = 1500;
	const int priceFamily = 2000;
public:
	int BookHote1Person(int days = 1) const { return price1Person * days; }
	int BookHote2Person(int days = 1) const { return price2Person * days; }
	int BookHoteFamily(int days = 1) const { return priceFamily * days; }
};

class Pool
{
private:
	const int pricePerHourForAdult = 200;
	const int pricePerHourForChild = 100;
public:
	int BuyTicketForAdult(int person = 1, int hours = 1) { return pricePerHourForAdult * hours * person; }
	int BuyTicketForChild(int person = 1, int hours = 1) { return pricePerHourForChild * hours * person; }
};

class Bar
{
private:
	const int PriceStrongMensAlcohol = 350;
	const int PriceWeakWomensAlcohol = 500;
public:
	int BuyStrongMensAlcohol(int person = 1) const
	{
		return PriceStrongMensAlcohol * person;
	}
	int BuyWeakWomensAlcohol(int person = 1) const
	{
		return PriceWeakWomensAlcohol * person;
	}
};

class Restaurant
{
private:
	const int BudgetFoodPerOnePerson = 400;
	const int MiddlePriceFoodPerOnePerson = 800;
	const int OverPriceFoodPerOnePerson = 2000;
	const int FoodForChildren = 500;
public:
	int OrderBudgetFood(int person = 1) const { return BudgetFoodPerOnePerson * person; }
	int OrderMiddlePriceFood(int person = 1) { return MiddlePriceFoodPerOnePerson * person; }
	int OrderOverPriceFood(int person = 1) { return OverPriceFoodPerOnePerson * person; }
	int OrderFoodForChildren(int person = 1) { return FoodForChildren * person; }
};

class Billiard
{
private:
	const int pricePerHour = 50;
	const int priceEvening = 200;
	const int priceNight = 300;
	const int priceHolidays = 1000;
public:
	int BuyTicketPerHour() const { return pricePerHour; }
	int BuyTicketPerEvening() const { return priceEvening; }
	int BuyTicketPerNight() const { return priceNight; }
	int BuyTicketPerHolidays() const { return priceHolidays; }
};

class Massage
{
private:
	const int pricePerOneSession = 400;
public:
	int BuyMassageSession(int person = 1) { return pricePerOneSession * person; }
};

class ObarivResort
{
private:
	Hotel* hotel;
	Pool* pool;
	Bar* bar;
	Restaurant* rest;
	Billiard* billiard;
	Massage* massage;
	bool servicesWereCreatedInternally;
	int totalPrice = 0;
public:
	ObarivResort(Hotel* hotel, Pool* pool, Bar* bar, Restaurant* rest, Billiard* billiard, Massage* massage)
		: hotel(hotel), pool(pool), bar(bar), rest(rest), billiard(billiard), massage(massage), servicesWereCreatedInternally(false) {}
	ObarivResort() : servicesWereCreatedInternally(true)
	{
		hotel = new Hotel;
		pool = new Pool;
		bar = new Bar;
		rest = new Restaurant;
		billiard = new Billiard;
		massage = new Massage;
	}
	virtual	~ObarivResort()
	{
		if (servicesWereCreatedInternally)
		{
			delete hotel;
			delete pool;
			delete bar;
			delete rest;
			delete billiard;
			delete massage;
		}
	}
	int OneHourPleasure(int adultPerson, int children, int men, int women, bool alcohol, bool discountCard)
	{
		if (children)
			totalPrice += pool->BuyTicketForChild(children);
		totalPrice += pool->BuyTicketForAdult(adultPerson);
		totalPrice += massage->BuyMassageSession(adultPerson);
		totalPrice += bar->BuyStrongMensAlcohol(men);
		totalPrice += bar->BuyWeakWomensAlcohol(women);
		totalPrice += billiard->BuyTicketPerHour();
		if (discountCard)
			totalPrice *= 0.8;
		return totalPrice;
	}
	int OneEveningPleasure(int adultPerson, int children, int men, int women, bool alcohol, bool discountCard)
	{
		if (children)
		{
			totalPrice += pool->BuyTicketForChild(children);
			totalPrice += rest->OrderFoodForChildren(children);
		}
		totalPrice += pool->BuyTicketForAdult(adultPerson);
		totalPrice += massage->BuyMassageSession(adultPerson);
		totalPrice += bar->BuyStrongMensAlcohol(men);
		totalPrice += bar->BuyWeakWomensAlcohol(women);
		totalPrice += billiard->BuyTicketPerEvening();
		totalPrice += rest->OrderMiddlePriceFood(adultPerson);
		if (discountCard)
			totalPrice *= 0.8;
		return totalPrice;
	}
	int OneNightPleasure(int adultPerson, int children, int men, int women, bool alcohol, bool discountCard)
	{
		if (children)
		{
			totalPrice += pool->BuyTicketForChild(children);
			totalPrice += rest->OrderFoodForChildren(children);
		}
		totalPrice += pool->BuyTicketForAdult(adultPerson);
		totalPrice += massage->BuyMassageSession(adultPerson);
		totalPrice += bar->BuyStrongMensAlcohol(men);
		totalPrice += bar->BuyWeakWomensAlcohol(women);
		totalPrice += billiard->BuyTicketPerNight();
		totalPrice += rest->OrderMiddlePriceFood(adultPerson);
		if (children)
			totalPrice += hotel->BookHoteFamily();
		else if (adultPerson == 1)
			totalPrice += hotel->BookHote1Person();
		else
			totalPrice += hotel->BookHote2Person();
		if (discountCard)
			totalPrice *= 0.8;
		return totalPrice;
	}
	int HolidaysPleasure(int adultPerson, int children, int men, int women, bool alcohol, bool discountCard)
	{
		for (int i = 0; i < 3; i++)
		{
			if (children)
			{
				totalPrice += pool->BuyTicketForChild(children);
				for (int i = 0; i < 3; i++)
					totalPrice += rest->OrderFoodForChildren(children);
			}
			totalPrice += pool->BuyTicketForAdult(adultPerson);
			totalPrice += massage->BuyMassageSession(adultPerson);
			totalPrice += bar->BuyStrongMensAlcohol(men);
			totalPrice += bar->BuyWeakWomensAlcohol(women);
			for (int i = 0; i < 3; i++)
				totalPrice += rest->OrderMiddlePriceFood(adultPerson);
		}
		totalPrice += billiard->BuyTicketPerHolidays();
		if (children)
			totalPrice += hotel->BookHoteFamily(3);
		else if (adultPerson == 1)
			totalPrice += hotel->BookHote1Person(3);
		else
			totalPrice += hotel->BookHote2Person(3);
		if (discountCard)
			totalPrice *= 0.8;
		return totalPrice;
	}
};

int main()
{
	ObarivResort resort;
	cout << "One hour - " << resort.OneHourPleasure(2, 0, 1, 1, 0, 0) << "UAH\n";
	cout << "One evening - " <<  resort.OneEveningPleasure(2, 0, 1, 1, 0, 0) << "UAH\n";
	cout << "One night - " <<  resort.OneNightPleasure(2, 0, 1, 1, 0, 0) << "UAH\n";
	cout << "Holidays - " <<  resort.HolidaysPleasure(2, 0, 1, 1, 0, 0) << "UAH\n";
}