#include <iostream>
#include <vector>
#include "Ship.h"
#ifndef FLEET_H
#define FLEET_H
using namespace std;

class Fleet
{

public:
	Fleet(string corName);
	
	void addWeight(Ship* s);
	
	void addEnergyConsumption(Ship* s);
	
	void addCost(Ship* s);
	
	void addEnergyProduction(SolarSailShip* s);
	
	void countColonists();

	void setColonists(int colonists);
	
	int getWeight() const; // Returns cumulative weight of fleet

	int getEnergyConsumption() const; // Returns cumulative energy consumption of fleet

	int getColonistCount() const; // Returns cumulative colonist count of fleet

	int getCost() const; // Returns cumulative fleet cost

	int EnergyProduction() const; // Returns cumulative energy production of fleet

	int countProtectedShips() const; // Returns nr of colony ships protected in fleet

	bool hasMedic() const; // Returns True if the fleet has a medic ship, false otherwise ( If the fleet does not have a medic ship, all colonists on that ship die after disease but its weight is unmodified by the event.)

	string getCorporationName() const; // Returns your chosen name of your corporation.

	vector<Ship*> protectedShips() const;// Returns a vector with ship numbers of protected colony ships

	vector<Ship*> unprotectedShips() const; // Returns a vector with ship numbers of unprotected colony ships (A random 25% of colony ships (rounded up) not protected by a military escort is destroyed, and the remains are left behind by the fleet)

	vector<Ship*> colonyShips() const; // Returns a vector with ship numbers of all ships that are a colony ship

	vector<Ship*> shipList() const; // Returns a vector with all ships in the fleet

	void destroyShip(Ship* s); // Removes ship i from the fleet

	unsigned int speedOfFleet();
	
	void addShipIntoList(Ship* i);
	
protected:
	int weight; // Returns cumulative weight of fleet

	int energyConsumption; // Returns cumulative energy consumption of fleet

	int colonistCount; // Returns cumulative colonist count of fleet

	int cost; // Returns cumulative fleet cost (must less than 10,000)

	int eneProduction; // Returns cumulative energy production of fleet

	bool medicShip;//has medic ship

	string corName; // Returns your chosen name of your corporation.

	vector<Ship*> allShipList;// Returns a vector with all ships in the fleet	
	
	int numOfColonyShipProtected;
	
	int numOfFighters;
};

#endif