#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

enum class CarBodyType { Sedan, Coupe, SportCar, Hatchback, SUV, Minivan };
enum class EngineType { Diesel, Gas, Electric, Hybrid };
enum class InteriorUpholstery { Wood, Plastic, Leather, EcoLeather, Alcantara, Vinyl, Velour };
string GetCarBodyTypeName(CarBodyType carBodyType)
{
	switch (carBodyType)
	{
	case CarBodyType::Sedan:
		return "Sedan";
	case CarBodyType::Coupe:
		return "Coupe";
	case CarBodyType::SportCar:
		return "Sport Car";
	case CarBodyType::Hatchback:
		return "Hatchback";
	case CarBodyType::SUV:
		return "SUV";
	case CarBodyType::Minivan:
		return "Minivan";
	default:
		return " ";
	}
}
string GetEngineTypeName(EngineType engineType)
{
	switch (engineType)
	{
	case EngineType::Diesel:
		return "Diesel";
	case EngineType::Gas:
		return "Gas";
	case EngineType::Electric:
		return "Electric";
	case EngineType::Hybrid:
		return "Hybrid";
	default:
		return " ";
	}
}
string GetInteriorUpholsteryName(InteriorUpholstery interiorUpholstery)
{
	switch (interiorUpholstery)
	{
	case InteriorUpholstery::Wood:
		return "Wood";
	case InteriorUpholstery::Plastic:
		return "Plastic";
	case InteriorUpholstery::Leather:
		return "Leather";
	case InteriorUpholstery::EcoLeather:
		return "Eco Leather";
	case InteriorUpholstery::Alcantara:
		return "Alcantara";
	case InteriorUpholstery::Vinyl:
		return "Vinyl";
	case InteriorUpholstery::Velour:
		return "Velour";
	default:
		return " ";
	}
}

class Engine
{
	EngineType engineType;
	float volume;
public:
	Engine(EngineType engineType = EngineType::Gas, float volume = 2.0) : engineType(engineType), volume(volume) {}
	friend std::ostream& operator<< (std::ostream& out, const Engine& engine)
	{
		out << "Engine: " << GetEngineTypeName(engine.engineType) << endl;
		if (engine.engineType == EngineType::Electric || engine.engineType == EngineType::Hybrid)
			out << "Power: " << engine.volume << endl;
		else
			out << "Engine capacity: " << engine.volume << endl;
		return out;
	}
};

class Auto
{
private:
	string model = "ZAZ";
	CarBodyType carBody = CarBodyType::Sedan;
	Engine engine;
	string wheels[4] = {"Michelin 19'", "Michelin 19'", "Michelin 19'", "Michelin 19'" };
	string color= "Black";
	InteriorUpholstery interiorUpholstery = InteriorUpholstery::Vinyl;

public:
	Auto() {}
	void SetModel(string value) { model = value; }
	void SetCarBodyType(CarBodyType value) { carBody = value; }
	void SetEngine(Engine value) { engine = value; }
	void SetWheels(string value[4])
	{
		for (int i = 0; i < 4; i++)
			wheels[i] = value[i];
	}
	void SetColor(string value) { color = value; }
	void SetInteriorUpholstery(InteriorUpholstery value) { interiorUpholstery = value; }

	void Show() const
	{
		cout << "Model: " << model << endl;
		cout << "Car body type: " << GetCarBodyTypeName(carBody) << endl;
		cout << engine;
		cout << "Wheels: \n";
		for (size_t i = 0; i < 4; i++)
			cout << wheels[i] << endl;
		cout << "Color: " << color << endl;
		cout << "Interior upholstery: " << GetInteriorUpholsteryName(interiorUpholstery) << endl;
	}
};

class AutoBuilder
{
protected:
	Auto* car;
public:
	void CreateNewCar()	{ car = new Auto();	}
	Auto* GetMyCar() const { return car; }
	virtual void SetModel() = 0;
	virtual void SetCarBodyType() = 0;
	virtual void SetEngine() = 0;
	virtual void SetWheels() = 0;
	virtual void SetColor() = 0;
	virtual void SetInteriorUpholstery() = 0;
};

class MiniAutoBuilder : public AutoBuilder
{
	void SetModel() override
	{
		car->SetModel("Mini Cooper");
	}
	void SetCarBodyType() override
	{
		car->SetCarBodyType(CarBodyType::Coupe);
	}
	void SetEngine() override
	{
		car->SetEngine({ EngineType::Gas, 1.5 });
	}
	void SetWheels() override
	{
		string wheels[4]{
			"Michelin 17'", "Michelin 17'", "Michelin 17'", "Michelin 17'"
		};
		car->SetWheels(wheels);
	}
	void SetColor() override
	{
		car->SetColor("Black");
	}
	void SetInteriorUpholstery() override
	{
		car->SetInteriorUpholstery(InteriorUpholstery::Wood);
	}
};

class SportAutoBuilder : public AutoBuilder
{
	void SetModel() override
	{
		car->SetModel("Ferrari");
	}
	void SetCarBodyType() override
	{
		car->SetCarBodyType(CarBodyType::SportCar);
	}
	void SetEngine() override
	{
		car->SetEngine({ EngineType::Hybrid, 3.2 });
	}
	void SetWheels() override
	{
		string wheels[4]{
			"Michelin 19'", "Michelin 19'", "Michelin 19'", "Michelin 19'"
		};
		car->SetWheels(wheels);
	}
	void SetColor() override
	{
		car->SetColor("Red");
	}
	void SetInteriorUpholstery() override
	{
		car->SetInteriorUpholstery(InteriorUpholstery::Plastic);
	}
};

class SUVAutoBuilder : public AutoBuilder
{
	void SetModel() override
	{
		car->SetModel("Mitsubisi");
	}
	void SetCarBodyType() override
	{
		car->SetCarBodyType(CarBodyType::SUV);
	}
	void SetEngine() override
	{
		car->SetEngine({ EngineType::Diesel, 4.0 });
	}
	void SetWheels() override
	{
		string wheels[4]{
			"Continental 16'", "Continental 16'", "Continental 16'", "Continental 16'"
		};
		car->SetWheels(wheels);
	}
	void SetColor() override
	{
		car->SetColor("Green");
	}
	void SetInteriorUpholstery() override
	{
		car->SetInteriorUpholstery(InteriorUpholstery::Vinyl);
	}
};

class AutoDirector
{
	AutoBuilder* builder;
	void ClearBuilder()
	{
		if (builder != nullptr) delete builder;
	}
public:
	AutoDirector(AutoBuilder* builder = nullptr) : builder(builder) { }
	~AutoDirector()
	{
		ClearBuilder();
	}
	void SetBuilder(AutoBuilder* b)
	{
		ClearBuilder();
		builder = b;
	}
	Auto* Configurate()
	{
		builder->CreateNewCar();
		builder->SetModel();
		builder->SetCarBodyType();
		builder->SetEngine();
		builder->SetWheels();
		builder->SetColor();
		builder->SetInteriorUpholstery();
		return builder->GetMyCar();
	}
};

void main()
{
	AutoDirector dir;
	dir.SetBuilder(new MiniAutoBuilder);
	Auto* car = dir.Configurate();
	car->Show();
	delete car;

	dir.SetBuilder(new SUVAutoBuilder);
	car = dir.Configurate();
	car->Show();
	delete car;

	dir.SetBuilder(new SportAutoBuilder);
	car = dir.Configurate();
	car->Show();
	delete car;
}