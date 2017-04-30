#include "Fleet.h"
#include "Ship.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#define SPEED_OF_LIGHT_IN_MS 299792458L
#define LIGHT_YEAR_IN_METER 9460730472580000L

using namespace std;

Fleet::Fleet(string cn):corName(cn){
	weight=0;
}

void Fleet::calculateWeight(){
	for(int i=0; i< allShipList.size();i++)
		weight+=(allShipList[i]->getWeight());
}

void Fleet::setTotalCost(int newCost){//must be less than 10,000
	cost = newCost;
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
	for(int i=0; i< allShipList.size();i++)
		if((*allShipList[i]).getTypeName()=="Medic" )
	return true;
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
	vector<Ship*> colonyShipList;
	for(int i=0; i< allShipList.size();i++)
		if((*allShipList[i]).getTypeName()=="Ferry" | (*allShipList[i]).getTypeName()=="Liner" |(*allShipList[i]).getTypeName()=="Cloud" )
			colonyShipList.push_back(allShipList[i]);
	return colonyShipList;
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
	return ((10*(unsigned int)SPEED_OF_LIGHT_IN_MS)/(sqrt (weight)));
}

void Fleet::addShipIntoList(Ship* i){
	allShipList.push_back(i);
	calculateWeight();
}
