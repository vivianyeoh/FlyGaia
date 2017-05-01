#include "Fleet.h"
#include "Ship.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#define SPEED_OF_LIGHT_IN_MS 299792458L


using namespace std;

Fleet::Fleet(string cn):corName(cn){
	cost=0;
	weight=0;
	colonistCount=0;
	numOfFighters=0;
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

void Fleet::countColonists(){
	colonistCount=0;
	for(int i=0; i< colonyShips().size();i++){
		if(!(((ColonyShip*)((colonyShips())[i]))->isInfected()))
		colonistCount+=(((ColonyShip*)((colonyShips())[i]))->getColonistCount());
	}
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
	return numOfColonyShipProtected+(int)(numOfFighters/2);
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
	
	int tempAmtOfProt=countProtectedShips();//temporary amount of colony ship protected
	
	for(int i=0; i< colonyShips().size();i++){
		if(tempAmtOfProt>0){
			if((*(colonyShips()[i])).getTypeName()=="Cloud"){//bigger ship will be prioritized
				tempAmtOfProt--;
				protectedList.push_back(colonyShips()[i]);
			}
		}else{
			break;
		}
	}
	
	for(int i=0; i< colonyShips().size();i++){
		if(tempAmtOfProt>0){
			if((*(colonyShips()[i])).getTypeName()=="Liner"){
				tempAmtOfProt--;
				protectedList.push_back(colonyShips()[i]);
			}
		}else{
			break;
		}
	}
	for(int i=0; i< colonyShips().size();i++){
		if(tempAmtOfProt>0){
			if((*(colonyShips()[i])).getTypeName()=="Ferry"){
				tempAmtOfProt--;
				protectedList.push_back(colonyShips()[i]);
			}
		}else{
			break;
		}
	}
	
	return protectedList;
} // Returns a vector with ship numbers of protected colony ships

vector<Ship*> Fleet::unprotectedShips() const
{
	vector<Ship*> unProtectedList;
	vector<Ship*> cloudList;
	vector<Ship*> linerList;
	vector<Ship*> ferryList;
	
	for(int i=0; i< colonyShips().size();i++){
		if((*(colonyShips()[i])).getTypeName()=="Cloud"){
			cloudList.push_back(colonyShips()[i]);
		}else if((*(colonyShips()[i])).getTypeName()=="Liner"){
			linerList.push_back(colonyShips()[i]);
		}else if((*(colonyShips()[i])).getTypeName()=="Ferry"){
			ferryList.push_back(colonyShips()[i]);
		}
	}
	
	for(int i=0; i< protectedShips().size();i++){
		if((*(protectedShips()[i])).getTypeName()=="Cloud"){//bigger ship will be prioritized
			cloudList.erase(cloudList.begin());
		}else if((*(protectedShips()[i])).getTypeName()=="Liner"){
			linerList.erase(linerList.begin());
		}else if((*(protectedShips()[i])).getTypeName()=="Ferry"){
			ferryList.erase(ferryList.begin());
		}
	}
	

	if(cloudList.size()>0){
		for(int i=0; i<cloudList.size(); i++){
			unProtectedList.push_back(cloudList[i]);
		}
	}
	
	if(linerList.size()>0){
		for(int i=0; i<linerList.size(); i++){
			unProtectedList.push_back(linerList[i]);
		}
	}
	
	if(ferryList.size()>0){
		
		for(int i=0; i<ferryList.size(); i++){
			unProtectedList.push_back(ferryList[i]);
		}
		
	}
	
	return unProtectedList;
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

void Fleet::destroyShip(Ship* s) {
	for(int i=0; i<allShipList.size(); i++){
		if(allShipList[i]==s){
			allShipList.erase(allShipList.begin() + i);
			break;
		}			
	}
} // Removes ship i from the fleet

unsigned int Fleet::speedOfFleet(){
	return ((10*(unsigned int)SPEED_OF_LIGHT_IN_MS)/(sqrt (weight)));
}

void Fleet::addShipIntoList(Ship* i){
	allShipList.push_back(i);
	addWeight(i);
	addEnergyConsumption(i);
	addCost(i);
	countColonists();
	if((*i).getTypeName()=="Radiant" | (*i).getTypeName()=="Ebulient")
	addEnergyProduction((SolarSailShip*)i);
	else if((*i).getTypeName()=="Medic")
	medicShip = true;
	else if((*i).getTypeName()=="Cruiser" | (*i).getTypeName()=="Frigate" |(*i).getTypeName()=="Destroyer" ){
		numOfColonyShipProtected++;
		numOfFighters+=((MilitaryEscortShip*)i)->getNrProtected();
	}
}

void Fleet::setColonists(int colonists){
	colonistCount = colonists;
}