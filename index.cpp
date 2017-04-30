#include <iostream>
#include <vector>
#include <cstdlib>
#include <pthread.h>
#include <fstream>
#include <string>
#include "Fleet.h"
#include "Ship.h"
#include "GaiaSector.h"
#define NUM_THREADS 5

using namespace std;

void *gaiaExist(void *threadid);
void *displayYearPopulation(void *threadid);
void splashScreen();
void waitOneYear();
Fleet* displayCorporationDetails(string fileName);
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

	RadiantSolarSail = new SolarSailShip(5,3,50,"Radient",50);
	EbulientSolarSail = new SolarSailShip(5,50,250,"Ebulient",500);
	
	CruiserMilitaryEscort = new MilitaryEscortShip(10,2,300,"Cruiser",0);	
	FrigateMilitaryEscort = new MilitaryEscortShip(20,7,1000,"Frigate",10);	
	DestroyerMilitaryEscort = new MilitaryEscortShip(30,19,2000,"Destroyer",25);

	medicShip = new Ship(1,1,1000,"Medic");
	gaia = new GaiaSector();
	
	splashScreen();
	
	cout<<"Corporation under: 025280\n"<<endl;
	Fleet* corporation1 = displayCorporationDetails("025280-fleet.dat");
	
	cout<<"Corporation under: 023330\n"<<endl;
	Fleet* corporation2 = displayCorporationDetails("023330-fleet");
	
	cout<<"Corporation under: 019785\n"<<endl;
	Fleet* corporation3 = displayCorporationDetails("019785-fleet");
	
	cout<<"Corporation under: 018957\n"<<endl;
	Fleet* corporation4 = displayCorporationDetails("018957-fleet");
	
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


Fleet* displayCorporationDetails(string fileName){
	
	int num;                //store number of students
	string ShiptypeAmt[40][2];      //store students ID

	ifstream file(fileName); // pass file name as argment
Fleet* newfleet = new Fleet(fileName.substr(0, 4));
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
	
	for(int i=0; i<linecount;i++){
		
			if(ShiptypeAmt[i][0]=="Ferry") 
				newfleet->addShipIntoList(FerryColony);
				else if(ShiptypeAmt[i][0]=="Liner")
				newfleet->addShipIntoList(LinerColony);
				else if(ShiptypeAmt[i][0]=="Cloud")
				newfleet->addShipIntoList(CloudColony);
				else if(ShiptypeAmt[i][0]=="Radient")
				newfleet->addShipIntoList(RadiantSolarSail);
				else if(ShiptypeAmt[i][0]=="Ebulient")
				newfleet->addShipIntoList(EbulientSolarSail);
				else if(ShiptypeAmt[i][0]=="Cruiser")
				newfleet->addShipIntoList(CruiserMilitaryEscort);
				else if(ShiptypeAmt[i][0]=="Frigate")
				newfleet->addShipIntoList(FrigateMilitaryEscort);
				else if(ShiptypeAmt[i][0]=="Destroyer")
				newfleet->addShipIntoList(DestroyerMilitaryEscort);
				else if(ShiptypeAmt[i][0]=="Medic")
				newfleet->addShipIntoList(medicShip);
				
		}
	}
	
	cout<<"Size of colony ship"<<(newfleet->colonyShips()).size();
}

Fleet* userInterfaceCreateFleet(){
	
}




