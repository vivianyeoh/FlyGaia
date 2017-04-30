#include <iostream>
#include "Ship.h"
using namespace std;

Ship::Ship(int e,int sw,int sc,string st):energyConsump(e),shipWeight(sw),shipCost(sc),shipType(st){
	*status = true; // Original status is true
	
}

int Ship::getEnergyConsumption() const
{
	return energyConsump;
} // Returns energy consumption of a ship

int Ship::getWeight() const
{
	return shipWeight;
} // Returns weight of a ship

int Ship::getCost() const
{
	return shipCost;
} // Returns cost of a ship

string Ship::getTypeName() const
{
	return shipType;
} // Returns the ship type, e.g. Ferry, Cruiser, or Ebulient. Note that spelling mistakes may effect your grade!

bool Ship::isDestroyed() const
{
	return (*status)==true;
} // Returns true if the ship is destroyed, false otherwise

void Ship::destroyShip() const
{
	*status = false;
} //The ship is destroyed, status of ship = FALSE

ColonyShip::ColonyShip(int e,int sw,int sc,string st,int nr):Ship(e,sw,sc,st),nrOfColonists(nr){
	*infectedStatus = false;// Original status is false
}

int ColonyShip::getColonistCount() const{
	return nrOfColonists;
} // Returns nr of colonists of a ship

void ColonyShip::infect(){
	
} // Infects a colony ship

bool ColonyShip::isInfected() const{
	return *infectedStatus==true;
} // Returns True if the ship is infected with a disease, False otherwise

SolarSailShip::SolarSailShip(int e,int sw,int sc,string st, int ep):Ship(e,sw,sc,st),energyProduction(ep){}

int SolarSailShip::getEnergyProduction() const{
	return energyProduction;
} // Returns energy production of Solar Sail Ship

MilitaryEscortShip::MilitaryEscortShip(int e,int sw,int sc,string st, int cs):Ship(e,sw,sc,st),fighters(cs){}

int MilitaryEscortShip::getNrProtected() const{
	return nrOfColonyShip;
} // Returns nr of colony ships protected by this ship