#include <iostream>
#include <cassert>
#include <map>
#ifndef GAIASECTOR_H
#define GAIASECTOR_H
using namespace std;

class GaiaSector
{

public:
	GaiaSector(string colonizeSection, double percentage);
	void growPopulation();
	void setPopulation(int newPopulation);

	
protected:
	string colonizeSection;
	double percentage;
	int* population;
};

#endif