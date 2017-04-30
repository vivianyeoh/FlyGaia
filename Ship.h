#include <iostream>
#ifndef SHIP_H
#define SHIP_H
using namespace std;

class Ship
{

public:
	
	Ship(int energyConsump,int shipWeight,int shipCost,string shipType);

	int getEnergyConsumption() const; // Returns energy consumption of a ship

	int getWeight() const; // Returns weight of a ship ( Military escort ships prioritise bigger ships)

	int getCost() const; // Returns cost of a ship

	string getTypeName() const; // Returns the ship type, e.g. Ferry, Cruiser, or Ebulient. Note that spelling mistakes may effect your grade!

	bool isDestroyed() const; // Returns true if the ship is destroyed, false otherwise

	void destroyShip() const;//The ship is destroyed, status of ship = FALSE
	
protected:
	int energyConsump; // Returns energy consumption of a ship

	int shipWeight; // Returns weight of a ship

	int shipCost; // Returns cost of a ship

	string shipType; // Returns the ship type, e.g. Ferry, Cruiser, or Ebulient. Note that spelling mistakes may effect your grade!

	bool* status; //whether the ship is destroyed
};

class ColonyShip:public Ship{
	
public:
	
	ColonyShip(int energyConsump,int shipWeight,int shipCost,string shipType,int nrOfColonists);

	int getColonistCount() const; // Returns nr of colonists of a ship
	
	void infect(); // Infects a colony ship
	
	bool isInfected() const; // Returns True if the ship is infected with a disease, False otherwise

protected:
	
	int nrOfColonists;// nr of colonists of a ship
	
	bool* infectedStatus;
};

class SolarSailShip:public Ship{
	
public:
	
	SolarSailShip(int energyConsump,int shipWeight,int shipCost,string shipType,int energyProduction);
	
	int getEnergyProduction() const; // Returns energy production of Solar Sail Ship
	
protected:

	int energyProduction;
	
};

class MilitaryEscortShip:public Ship{
	
public:
	
	MilitaryEscortShip(int energyConsump,int shipWeight,int shipCost,string shipType,int fighters);
	
	int getNrProtected() const;// Returns nr of colony ships protected by this ship
	
protected:

	int nrOfColonyShip;
	
	int fighters;
};

#endif
