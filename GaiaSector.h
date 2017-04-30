#include <iostream>
#include <cassert>
#include <map>
#include "Fleet.h"
#ifndef GAIASECTOR_H
#define GAIASECTOR_H
using namespace std;

class GaiaSector
{

public:
	GaiaSector();
	void growPopulation();
	void setPopulation(int newPopulation);
	int getPopulation();
	void setFleet(Fleet* f);
	
protected:
	string colonizeSection;
	int population;
	Fleet* settler; 
};

#endif