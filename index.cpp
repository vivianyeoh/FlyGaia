#include <iostream>
#include <vector>
#include "Fleet.h"
#include "Ship.h"
using namespace std;
void splashScreen();
Fleet* userInterfaceCreateFleet(); 
int main(  )
{
	ColonyShip* FerryColony = new ColonyShip(5,10,500,"Ferry",100);
	ColonyShip* LinerColony = new ColonyShip(7,20,1000,"Liner",250);
	ColonyShip* CloudColony = new ColonyShip(9,30,2000,"Cloud",750);
	
	
	SolarSailShip* RadiantSolarSail = new SolarSailShip(5,3,50,"Radient",50);
	SolarSailShip* EbulientSolarSail = new SolarSailShip(5,50,250,"Ebulient",500);
	
	MilitaryEscortShip* CruiserMilitaryEscort = new MilitaryEscortShip(10,2,300,"Cruiser",0);	
	MilitaryEscortShip* FrigateMilitaryEscort = new MilitaryEscortShip(20,7,1000,"Frigate",10);	
	MilitaryEscortShip* DestroyerMilitaryEscort = new MilitaryEscortShip(30,19,2000,"Destroyer",25);
	
	Ship* medicShip = new Ship(1,1,1000,"Medic");
	
	Fleet f;
	f.addShipIntoList(medicShip);
	cout<<"size of ship"<<f.shipList().size();
	splashScreen();
	return 0;
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

Fleet* userInterfaceCreateFleet(){}




