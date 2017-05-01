#include "Fleet.h"
#include "Ship.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#define SPEED_OF_LIGHT_IN_KMS 299792L


using namespace std;

Fleet::Fleet(string cn):corName(cn){
	cost=0;
	weight=0;
	colonistCount=0;
	numOfColonyShipProtected=0;
	medicShip=false;
	energyConsumption=0;
	eneProduction=0;
}

void Fleet::addWeight(Ship* s){
	weight+=(s->getWeight());
}

void Fleet::addEnergyConsumption(Ship* s){
	energyConsumption+=(s->getEnergyConsumption());
}

void Fleet::addColonists(ColonyShip* s){
	colonistCount+=s->getColonistCount();
}

void Fleet::addEnergyProduction(SolarSailShip* s){
	eneProduction+=s->getEnergyProduction();
}

void Fleet::addCost(Ship* s){//must be less than 10,000
	cost += s->getCost();
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
	return eneProduction;
} // Returns cumulative energy production of fleet

int Fleet::countProtectedShips() const
{
	return protectedShips().size();
} // Returns nr of colony ships protected in fleet

bool Fleet::hasMedic() const
{
	return medicShip;
} // Returns True if the fleet has a medic ship, false otherwise

string Fleet::getCorporationName() const
{
	return corName;
} // Returns your chosen name of your corporation.

vector<Ship*> Fleet::protectedShips() const
{
	vector<Ship*> protectedList;
	int tempAmtOfProt=numOfColonyShipProtected;//temporary amount of colony ship protected
	for(int i=0; i< colonyShips().size();i++){
		if(tempAmtOfProt>0){
			if((*(colonyShips()[i])).getTypeName()=="Cloud"){
				tempAmtOfProt--;
				protectedList.push_back(colonyShips()[i]);
			}
		}
	}
	return protectedList;
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
	return ((10*(unsigned int)SPEED_OF_LIGHT_IN_KMS)/(sqrt (weight)));
}

void Fleet::addShipIntoList(Ship* i){
	allShipList.push_back(i);
	addWeight(i);
	addEnergyConsumption(i);
	addCost(i);
	
	if((*i).getTypeName()=="Ferry" | (*i).getTypeName()=="Liner" |(*i).getTypeName()=="Cloud" )
		addColonists((ColonyShip*)i);
	else if((*i).getTypeName()=="Radiant" | (*i).getTypeName()=="Ebulient")
		addEnergyProduction((SolarSailShip*)i);
	else if((*i).getTypeName()=="Medic")
		medicShip = true;
	else if((*i).getTypeName()=="Cruiser" | (*i).getTypeName()=="Frigate" |(*i).getTypeName()=="Frigate" ){
		numOfColonyShipProtected+=1;
		numOfColonyShipProtected+=((((MilitaryEscortShip*)i)->getNrProtected())/2);
	}
}

void Fleet::setColonists(int colonists){
	colonistCount = colonists;
}