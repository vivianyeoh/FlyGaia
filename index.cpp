#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "Fleet.h"
#include "GaiaSector.h"
#include "Ship.h"

#define NUM_THREADS 5

using namespace std;

void *compareFleet(void *threadid);
void *diseaseAttack(void *threadid);
void *alienAttack(void *threadid);
void *setFleetandPopulation(void *threadid);
void splashScreen();
void displayGaiaCurrentData();
void *timePassingYear(void *threadid);
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
Fleet* corporation1;
Fleet* userCor;
Fleet* settlerGaia;
Fleet* settlerRival;
Ship* medicShip;
GaiaSector* gaia;
int year=1;
bool settlerGaiaChanged=false;
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
	
	cout<<"Existing competitors:\n";
	cout<<"\nCorporation under: 025280"<<endl;
	corporation1 = displayCorporationDetails("025280-fleet.dat");
	/*
	cout<<"\nCorporation under: 023330"<<endl;
	Fleet* corporation2 = displayCorporationDetails("023330-fleet.dat");
	
	cout<<"\nCorporation under: 019785"<<endl;
	Fleet* corporation3 = displayCorporationDetails("019785-fleet.dat");
	
	cout<<"\nCorporation under: 018957"<<endl;
	Fleet* corporation4 = displayCorporationDetails("018957-fleet.dat");
	*/
	
	userCor = userInterfaceCreateFleet();
	
	/*cout<<"\nTime to launch the fleet!"<<endl;
	cout<<"3"<<endl;
	Sleep(500);
	cout<<"2"<<endl;
	Sleep(500);
	cout<<"1"<<endl;
	Sleep(500);
	for(int i=0;i<10; i++){
		cout<<"-";	
		Sleep(200);
	}
	cout<<">"<<endl;
	*/
	
	pthread_t threads[NUM_THREADS];
	int rc;
	int i=0;//thread 0
	
	rc = pthread_create(&threads[i], NULL, compareFleet, (void *)i);
	
	if (rc){
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
	
	i=1;//thread 1
	rc = pthread_create(&threads[i], NULL, setFleetandPopulation, (void *)i);
	
	if (rc){
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
	
	i=2;//thread 2
	rc = pthread_create(&threads[i], NULL, timePassingYear, (void *)i);
	
	if (rc){
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
	
	pthread_exit(NULL);	
	
	i=3;//thread 2
	rc = pthread_create(&threads[i], NULL, diseaseAttack, (void *)i);
	
	if (rc){
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
	
	pthread_exit(NULL);	
	
	i=4;//thread 2
	rc = pthread_create(&threads[i], NULL, alienAttack, (void *)i);
	
	if (rc){
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
	
	pthread_exit(NULL);	

	return 0;
}

void *diseaseAttack(void *threadid){
	
}

void *alienAttack(void *threadid){
	
}

void *timePassingYear(void *threadid)
{
	while(true){		
		if(year>10){
			break;
		}
		Sleep(2000);//one year is 5 second
		gaia->growPopulation();
		settlerGaia->setColonists(gaia->getPopulation());
		year++;

	}pthread_exit(NULL);
}

void *compareFleet(void *threadid) {	
	int tempYear = 0;
	int speedOfCor1 = corporation1->speedOfFleet();
	int speedOfCor2 = userCor->speedOfFleet();
	
	if(speedOfCor1>speedOfCor2){//faster fleet will reach first
		settlerGaia = corporation1;
		settlerRival= userCor;		
	}else{
		settlerGaia = userCor;
		settlerRival= corporation1;
	}
	
	while(true){
		if(year>10){
			break;
		}
		if(tempYear<year){//to ensure this thread runs after another year
			if(year==3){//assume another fleet reached after 3 years
				if((*settlerGaia).getColonistCount()<(*settlerRival).getColonistCount()){//compare number of colonist
					Fleet * temp = settlerGaia;
					settlerGaia = settlerRival;
					settlerRival = temp;
					settlerGaiaChanged = true;
					gaia->setFleet(settlerGaia);
					gaia->setPopulation((*settlerGaia).getColonistCount());
				}
			}
			tempYear=year;
		}
		
	}
	pthread_exit(NULL);
}

void *setFleetandPopulation(void *threadid) {
	int tempYear = 0;
	while(true){
		if(year>10){
			break;
		}
		if(tempYear<year){//to ensure this thread runs after another year
			gaia->setFleet(settlerGaia);
			gaia->setPopulation((*settlerGaia).getColonistCount());
			displayGaiaCurrentData();
			tempYear=year;
		}		
	}
	pthread_exit(NULL);
}

void displayGaiaCurrentData(){
	cout<<"\n";
	cout<<"\nYear: "<<year<<" in Gaia"<<endl;
	
	if(year==4){
		if(settlerGaiaChanged){
			cout<<"The new settler in Gaia is: "<<(*settlerGaia).getCorporationName()<<endl;
			settlerGaiaChanged=false;
		}else{
			cout<<"The rival of corporation "<<(*settlerRival).getCorporationName()<<" has failed to take over Gaia with population of "<<(*settlerRival).getColonistCount()<<endl;
		}
	}
	
	cout<<"Current Population in Gaia: "<<(*gaia).getPopulation()<<endl;
	cout<<"Corporation Code "<<(*settlerGaia).getCorporationName()<<" with a population of "<<(*settlerGaia).getColonistCount()<<" is colonising Gaia!";
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
	
	string ShiptypeAmt[40][2];//store ship type and amount of each ship

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
				if((costOfShips+(*FerryColony).getCost())<=10000){
					costOfShips+=(*FerryColony).getCost();
					newfleet->addShipIntoList(FerryColony);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Liner"){
				if((costOfShips+(*LinerColony).getCost())<=10000){
					costOfShips+=(*LinerColony).getCost();
					newfleet->addShipIntoList(LinerColony);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Cloud"){
				if((costOfShips+(*CloudColony).getCost())<=10000){
					costOfShips+=(*CloudColony).getCost();
					newfleet->addShipIntoList(CloudColony);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Radiant"){
				if((costOfShips+(*RadiantSolarSail).getCost())<=10000){
					costOfShips+=(*RadiantSolarSail).getCost();
					newfleet->addShipIntoList(RadiantSolarSail);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Ebulient"){
				if((costOfShips+(*EbulientSolarSail).getCost())<=10000){
					costOfShips+=(*EbulientSolarSail).getCost();
					newfleet->addShipIntoList(EbulientSolarSail);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Cruiser"){
				if((costOfShips+(*CruiserMilitaryEscort).getCost())<=10000){
					costOfShips+=(*CruiserMilitaryEscort).getCost();
					newfleet->addShipIntoList(CruiserMilitaryEscort);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Frigate"){
				if((costOfShips+(*FrigateMilitaryEscort).getCost())<=10000){
					costOfShips+=(*FrigateMilitaryEscort).getCost();
					newfleet->addShipIntoList(FrigateMilitaryEscort);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Destroyer"){
				if((costOfShips+(*DestroyerMilitaryEscort).getCost())<=10000){
					costOfShips+=(*DestroyerMilitaryEscort).getCost();
					newfleet->addShipIntoList(DestroyerMilitaryEscort);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}else if(ShiptypeAmt[i][0]=="Medic"){
				if((costOfShips+(*medicShip).getCost())<=10000){
					costOfShips+=(*medicShip).getCost();
					newfleet->addShipIntoList(medicShip);
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<ShiptypeAmt[i][0]<<" are not purchased!"<<endl;
					break;
				}
			}
			amount++;
		}
	}
	
	for(int i=0; i<((*newfleet).shipList()).size();i++){
		cout<<(i+1)<<". "<<((*newfleet).shipList())[i]->getTypeName()<<endl;
	}
	
	return newfleet;
}

Fleet* userInterfaceCreateFleet(){
	cout<<"\n\n";
	
	for(int i=0; i<105; i++)
	{
		cout<<"x";
	}
	
	
	cout<<"\n\nShip Purchasing Panel"<<endl;
	cout<<"Corporation code(5 digits) (Same corporation code to overwrite previous data): ";
	string corName;
	while(std::getline(std::cin,corName) && corName.size() != 5) {
		cout << "Please enter a valid Corporation code(5 digits): ";
	}
	
	cout<<"\n\n";
	cout<<"\t------------+-----------+------+--------+--------------+----------------------"<<endl;
	cout<<"\t| Ship Code | Ship Type | Cost | Weight | Consumption* | Other               |"<<endl;
	cout<<"\t------------+-----------+------+--------+--------------+----------------------"<<endl;
	cout<<"\t|   10000   |   Ferry   |  500 |   10   |      5       |    100 Colonists    |"<<endl;
	cout<<"\t|   10001   |   Liner   | 1000 |   20   |      7       |    250 Colonists    |"<<endl;
	cout<<"\t|   10002   |   Cloud   | 2000 |   30   |      9       |    750 Colonists    |"<<endl;
	cout<<"\t------------+-----------+------+--------+--------------+----------------------"<<endl;
	cout<<"\t|   10003   |   Radiant |   50 |    3   |      5       |  *Generate 50 Energy|"<<endl;
	cout<<"\t|   10004   |  Ebulient |  250 |   50   |      5       | *Generate 500 Energy|"<<endl;
	cout<<"\t------------+-----------+------+--------+--------------+----------------------"<<endl;
	cout<<"\t|   10005   |   Cruiser |  300 |    2   |     10       |      0 Fighters     |"<<endl;
	cout<<"\t|   10006   |   Frigate | 1000 |    7   |     20       |     10 Fighters     |"<<endl;
	cout<<"\t|   10007   | Destroyer | 2000 |   19   |     30       |     25 Fighters     |"<<endl;
	cout<<"\t------------+-----------+------+--------+--------------+----------------------"<<endl;
	cout<<"\t|   10008   |   Medic   | 1000 |    1   |      1       |                     |"<<endl;
	cout<<"\t------------+-----------+------+--------+--------------+----------------------"<<endl;
	cout<<"\n\n*Consumption as in Energy Consumption\n";
	cout<<"*Generate as in Generate Energy for ship\n";
	cout<<"Each corporation has only 10,000 UNP to spend on ships. \n\n\n";
	
	Fleet* newfleet = new Fleet(corName);
	string inputShipType;
	ofstream outputFile;
	string fname = corName+ "-fleet.dat";
	outputFile.open(fname.c_str());
	
	int costOfShips=0;
	char moreShip = 'N';
	
	do{
		int shipCode=0;
		cout<<"\n\nType of ship (Please key in the ship code): ";	
		while (!(std::cin >> shipCode)| (shipCode<10000|shipCode>10008)) {
			cout << "Type of ship (Please key in the ship code): ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
		cout<<"Number of ships: ";
		int purAmount=0;
		while (!(std::cin >> purAmount)|purAmount<0) {
			cout << "Please enter a valid number of ships: \n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
		int amount = 0;
		
		while(amount!=purAmount){
			boolean overSpent = false;
			switch(shipCode){
			case 10000:
				if((costOfShips+(*FerryColony).getCost())<=10000){
					costOfShips+=(*FerryColony).getCost();
					newfleet->addShipIntoList(FerryColony);
					inputShipType = (*FerryColony).getTypeName();
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<(*FerryColony).getTypeName()<<" are not purchased!"<<endl;
					overSpent=true;
				}
				break;
			case 10001:
				if((costOfShips+(*LinerColony).getCost())<=10000){
					costOfShips+=(*LinerColony).getCost();
					newfleet->addShipIntoList(LinerColony);
					inputShipType = (*LinerColony).getTypeName();
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<(*LinerColony).getTypeName()<<" are not purchased!"<<endl;
					overSpent=true;
				}
				break;
			case 10002:
				if((costOfShips+(*CloudColony).getCost())<=10000){
					costOfShips+=(*CloudColony).getCost();
					newfleet->addShipIntoList(CloudColony);
					inputShipType = (*CloudColony).getTypeName();
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<(*CloudColony).getTypeName()<<" are not purchased!"<<endl;
					overSpent=true;
				}
				break;
			case 10003:
				if((costOfShips+(*RadiantSolarSail).getCost())<=10000){
					costOfShips+=(*RadiantSolarSail).getCost();
					newfleet->addShipIntoList(RadiantSolarSail);
					inputShipType = (*RadiantSolarSail).getTypeName();
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<(*RadiantSolarSail).getTypeName()<<" are not purchased!"<<endl;
					overSpent=true;
				}
				break;
			case 10004:
				if((costOfShips+(*EbulientSolarSail).getCost())<=10000){
					costOfShips+=(*EbulientSolarSail).getCost();
					newfleet->addShipIntoList(EbulientSolarSail);
					inputShipType = (*EbulientSolarSail).getTypeName();
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<(*EbulientSolarSail).getTypeName()<<" are not purchased!"<<endl;
					overSpent=true;
				}
				break;
			case 10005:
				if((costOfShips+(*CruiserMilitaryEscort).getCost())<=10000){
					costOfShips+=(*CruiserMilitaryEscort).getCost();
					newfleet->addShipIntoList(CruiserMilitaryEscort);
					inputShipType = (*CruiserMilitaryEscort).getTypeName();
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<(*CruiserMilitaryEscort).getTypeName()<<" are not purchased!"<<endl;
					overSpent=true;
				}
				break;
			case 10006:
				if((costOfShips+(*FrigateMilitaryEscort).getCost())<=10000){
					costOfShips+=(*FrigateMilitaryEscort).getCost();
					newfleet->addShipIntoList(FrigateMilitaryEscort);
					inputShipType = (*FrigateMilitaryEscort).getTypeName();
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<(*FrigateMilitaryEscort).getTypeName()<<" are not purchased!"<<endl;
					overSpent=true;
				}
				break;
			case 10007:
				if((costOfShips+(*DestroyerMilitaryEscort).getCost())<=10000){
					costOfShips+=(*DestroyerMilitaryEscort).getCost();
					newfleet->addShipIntoList(DestroyerMilitaryEscort);
					inputShipType = (*DestroyerMilitaryEscort).getTypeName();
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<(*DestroyerMilitaryEscort).getTypeName()<<" are not purchased!"<<endl;
					overSpent=true;
				}
				break;
			case 10008:
				if((costOfShips+(*medicShip).getCost())<=10000){
					costOfShips+=(*medicShip).getCost();
					newfleet->addShipIntoList(medicShip);
					inputShipType = (*medicShip).getTypeName();
				}else{
					cout<<"Cost more than 10,000! Ships after "<<amount<<" "<<(*medicShip).getTypeName()<<" are not purchased!"<<endl;
					overSpent=true;
				}
				break;	
			}
			if(overSpent==true)
			break;
			amount++;
		}
		
		outputFile <<inputShipType<<" "<<amount<<endl;
		
		if(costOfShips<10000){
			cout<<"Total Cost: "<<newfleet->getCost()<<endl;
			cout<<"Total energy consumpted: "<<newfleet->getEnergyConsumption()<<endl;
			cout<<"Total energy generated: "<<newfleet->EnergyProduction()<<endl;
			cout<<"Total weight: "<<newfleet->getWeight()<<endl;
			cout<<"Total colonists: "<<newfleet->getColonistCount()<<endl;
			cout<<"Total colony ship protected: "<<newfleet->countProtectedShips()<<endl;
			cout<<"Has medic: "<<(newfleet->hasMedic()?"Yes":"No")<<endl;
			cout<<"Add more ships? (Y/N):  ";
			while (!(std::cin >> moreShip)|!toupper(moreShip)=='Y'|!toupper(moreShip)=='N') {
				cout << "Please enter a response (Y/N): \n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}else{
			toupper(moreShip)=='N';
			break;
		}
	}while(toupper(moreShip)=='Y');
	
	cout<<"Total ship purchased: \n";
	for(int i=0; i<((*newfleet).shipList()).size();i++){
		cout<<(i+1)<<". "<<((*newfleet).shipList())[i]->getTypeName()<<endl;
	}
	cout<<"\n\n";
	
	for(int i=0; i<105; i++)
	{
		cout<<"x";
	}
	
	
	cout<<"\n\n";

	return newfleet;
}
