#include <iostream>
#include <vector>
#include <cstdlib>
#include <pthread.h>
#include <fstream>
#include<cstring>
#include<stdlib.h>
#include<string>
#include "Fleet.h"
#include "Ship.h"
#include "GaiaSector.h"
#define NUM_THREADS 5

using namespace std;

void *gaiaExist(void *threadid);
void *displayYearPopulation(void *threadid);
void splashScreen();
void waitOneYear();
Fleet* displayCorporationDetails(const char *filename);
Fleet* userInterfaceCreateFleet(); 

ColonyShip* FerryColony;
ColonyShip* LinerColony;
ColonyShip* CloudColony;
SolarSailShip* RadiantSolarSail;
SolarSailShip* EbulientSolarSail;
MilitaryEscortShip* CruiserMilitaryEscort;
MilitaryEscortShip* FrigateMilitaryEscort;
MilitaryEscortShip* DestroyerMilitaryEscort;
Ship* medicShip;
GaiaSector* gaia;
int year=1;

int main(  )
{
	FerryColony = new ColonyShip(5,10,500,"Ferry",100);
	LinerColony = new ColonyShip(7,20,1000,"Liner",250);
	CloudColony = new ColonyShip(9,30,2000,"Cloud",750);

	RadiantSolarSail = new SolarSailShip(5,3,50,"Radiant",50);
	EbulientSolarSail = new SolarSailShip(5,50,250,"Ebulient",500);
	
	CruiserMilitaryEscort = new MilitaryEscortShip(10,2,300,"Cruiser",0);	
	FrigateMilitaryEscort = new MilitaryEscortShip(20,7,1000,"Frigate",10);	
	DestroyerMilitaryEscort = new MilitaryEscortShip(30,19,2000,"Destroyer",25);

	medicShip = new Ship(1,1,1000,"Medic");
	gaia = new GaiaSector();
	
	splashScreen();
	
	cout<<"Existing competitors:\n\n";
	cout<<"\nCorporation under: 025280\n"<<endl;
	Fleet* corporation1 = displayCorporationDetails("025280-fleet.dat");
	
	cout<<"\nCorporation under: 023330\n"<<endl;
	Fleet* corporation2 = displayCorporationDetails("023330-fleet.dat");
	
	cout<<"\nCorporation under: 019785\n"<<endl;
	Fleet* corporation3 = displayCorporationDetails("019785-fleet.dat");
	
	cout<<"\nCorporation under: 018957\n"<<endl;
	Fleet* corporation4 = displayCorporationDetails("018957-fleet.dat");
	
	pthread_t threads[NUM_THREADS];
	int rc;
	int i=0;//thread 0
	
	rc = pthread_create(&threads[i], NULL, gaiaExist, (void *)i);
	
	if (rc){
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
	
	i=1;//thread 1
	rc = pthread_create(&threads[i], NULL, displayYearPopulation, (void *)i);
	
	if (rc){
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
	
	
	pthread_exit(NULL);	

	return 0;
}

void waitOneYear()
{
	Sleep(5000);//one year is 5 second
}

void *gaiaExist(void *threadid) {
	int tempYear = 0;
	while(true){
		if(tempYear<year){//to ensure this thread runs after the other threads have finished their job and time
			
			
			tempYear=year;
		}
		if(year>10)
		break;
	}
	pthread_exit(NULL);
}

void *displayYearPopulation(void *threadid) {
	while(true){
		cout<<"\n--------------------------------";
		cout<<"\nCurrent Population: "<<(*gaia).getPopulation();
		cout<<"\nYear: "<<year;
		waitOneYear();
		gaia->growPopulation();
		year++;
		if(year>10)
		break;
	}
	pthread_exit(NULL);
}


void splashScreen()
{
	
	cout<<"\n\n";
	
	for(int i=0; i<105; i++)
	{
		cout<<"x";
	}
	
	cout<<"\n\n";
	cout<<"\n\t\t\t\t      _____ _        _____     _    ";
	cout<<"\n\t\t\t\t     |   __| |_ _   |   __|___|_|___ ";
	cout<<"\n\t\t\t\t     |   __| | | |  |  |  | .'| | .'|";
	cout<<"\n\t\t\t\t     |__|  |_|_  |  |_____|__,|_|__,|";
	cout<<"\n\t\t\t\t             |___|         ";
	cout<<"\n\n";

	for(int i=0; i<105; i++)
	{
		cout<<"-";
	}

	cout<<"\n";

	cout<<"\n\t\t\t\t        The more people in your fleet,";
	cout<<"\n\t\t\t\tThe greater the chance you win the planet Gaia!";

	cout<<"\n\n";
	for(int i=0; i<105; i++)
	{
		cout<<"-";
	}

	cout<<"\n";
	cout<<"\n\n";

	for(int i=0; i<105; i++)
	{
		cout<<"x";
	}

	cout<<"\n\n";
}


Fleet* displayCorporationDetails(const char *filename){
	
	int num;                //store number of students
	string ShiptypeAmt[40][2];      //store students ID

	ifstream file(filename); // pass file name as argument
	if(!file)
	{
		cout << "Cannot open input file.\n";
	}
	int linecount = 0 ;

	if ( file )
	{
		while ( !file.eof() )
		{
			file>>ShiptypeAmt[linecount][0];
			file>>ShiptypeAmt[linecount][1];
			cout<<"Ship type: "<<ShiptypeAmt[linecount][0]<<" amount: "<<ShiptypeAmt[linecount][1]<<endl;
			linecount++ ;
		}
	}
	file.close();
	
	string fleetname =  string (filename, 5);
	Fleet* newfleet = new Fleet(fleetname);
	int costOfShips=0;
	for(int i=0; i<linecount;i++){
		int purAmount = atoi(ShiptypeAmt[i][1].c_str());
		int amount = 0;
		while(amount!=purAmount){
			if(ShiptypeAmt[i][0]=="Ferry") {
				if((costOfShips+(*FerryColony).getCost())<10000){
					costOfShips+=(*FerryColony).getCost();
					cout<<"cost of colony ship"<<costOfShips<<endl;
					newfleet->addShipIntoList(FerryColony);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Liner"){
				if((costOfShips+(*LinerColony).getCost())<10000){
					costOfShips+=(*LinerColony).getCost();
					cout<<"cost of colony ship"<<costOfShips<<endl;
					newfleet->addShipIntoList(LinerColony);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Cloud"){
				if((costOfShips+(*CloudColony).getCost())<10000){
					costOfShips+=(*CloudColony).getCost();
					cout<<"cost of colony ship"<<costOfShips<<endl;
					newfleet->addShipIntoList(CloudColony);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Radiant"){
				if((costOfShips+(*RadiantSolarSail).getCost())<10000){
					costOfShips+=(*RadiantSolarSail).getCost();
					cout<<"cost of colony ship"<<costOfShips<<endl;
					newfleet->addShipIntoList(RadiantSolarSail);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Ebulient"){
				if((costOfShips+(*EbulientSolarSail).getCost())<10000){
					costOfShips+=(*EbulientSolarSail).getCost();
					cout<<"cost of colony ship"<<costOfShips<<endl;
					newfleet->addShipIntoList(EbulientSolarSail);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Cruiser"){
				if((costOfShips+(*CruiserMilitaryEscort).getCost())<10000){
					costOfShips+=(*CruiserMilitaryEscort).getCost();
					cout<<"cost of colony ship"<<costOfShips<<endl;
					newfleet->addShipIntoList(CruiserMilitaryEscort);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Frigate"){
				if((costOfShips+(*FrigateMilitaryEscort).getCost())<10000){
					costOfShips+=(*FrigateMilitaryEscort).getCost();
					cout<<"cost of colony ship"<<costOfShips<<endl;
					newfleet->addShipIntoList(FrigateMilitaryEscort);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Destroyer"){
				if((costOfShips+(*DestroyerMilitaryEscort).getCost())<10000){
					costOfShips+=(*DestroyerMilitaryEscort).getCost();
					cout<<"cost of colony ship"<<costOfShips<<endl;
					newfleet->addShipIntoList(DestroyerMilitaryEscort);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Medic"){
				if((costOfShips+(*medicShip).getCost())<10000){
					costOfShips+=(*medicShip).getCost();
					cout<<"cost of colony ship"<<costOfShips<<endl;
					newfleet->addShipIntoList(medicShip);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}
			amount++;
		}
	}
	
	cout<<"Size of colony ship"<<((*newfleet).colonyShips()).size()<<endl;	
	cout<<"speedOfFleet of colony ship"<<(*newfleet).speedOfFleet()<<endl;
	cout<<"cost of colony ship"<<costOfShips<<endl;
}

Fleet* userInterfaceCreateFleet(){
	
}




