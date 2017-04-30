#include "Fleet.h"
#include "Ship.h"
#include "GaiaSector.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#define SPEED_OF_LIGHT 299792458L

using namespace std;

Fleet::Fleet(string cn):corName(cn){
	ttlPercentageColonized=0;
}

int Fleet::getWeight() const
{
	return weight;
} // Returns cumulative weight of fleet

int Fleet::getEnergyConsumption() const
{
	return energyConsumption;
} // Returns cumulative energy consumption of fleet

int Fleet::getColonistCount() const
{
	return colonistCount;
} // Returns cumulative colonist count of fleet

int Fleet::getCost() const
{
	return cost;
} // Returns cumulative fleet cost

int Fleet::EnergyProduction() const
{
	return energyProduction;
} // Returns cumulative energy production of fleet

int Fleet::countProtectedShips() const
{
	return protectedShips().size();
} // Returns nr of colony ships protected in fleet

bool Fleet::hasMedic() const
{
	return medicShip>0;
} // Returns True if the fleet has a medic ship, false otherwise

string Fleet::getCorporationName() const
{
	return corName;
} // Returns your chosen name of your corporation.

vector<Ship*> Fleet::protectedShips() const
{
	return allShipList;
} // Returns a vector with ship numbers of protected colony ships

vector<Ship*> Fleet::unprotectedShips() const
{
	return allShipList;
} // Returns a vector with ship numbers of unprotected colony ships

vector<Ship*> Fleet::colonyShips() const
{
	return allShipList;
} // Returns a vector with ship numbers of all ships that are a colony ship

vector<Ship*> Fleet::shipList() const
{
	return allShipList;
} // Returns a vector with all ships in the fleet

void Fleet::destroyShip(Ship* i) {
	allShipList.erase(
		remove(allShipList.begin(), allShipList.end(), i),
		allShipList.end()
	);
} // Removes ship i from the fleet

unsigned int Fleet::speedOfFleet(){
	return ((10*(unsigned int)SPEED_OF_LIGHT)/(sqrt (weight)));
}

void Fleet::increaseColonizedPercentage(double percentage){
	ttlPercentageColonized+=percentage;
}

void Fleet::decreaseColonizedPercentage(double percentage){
	if(ttlPercentageColonized>0){
		ttlPercentageColonized-=percentage;
		if(ttlPercentageColonized<0)
		ttlPercentageColonized=0;
	}
}

vector<GaiaSector*> Fleet::getClonizedAreaList() {
	return colonizedAreaList;
}

void Fleet::addColonizedArea(GaiaSector* sec){
	colonizedAreaList.push_back(sec);
}

void Fleet::addShipIntoList(Ship* i){
	allShipList.push_back(i);
}
