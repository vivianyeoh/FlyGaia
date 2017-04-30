#include <iostream>
#include "GaiaSector.h"
#include "Fleet.h"
using namespace std;

GaiaSector::GaiaSector(){
	population=0;
}

void GaiaSector::growPopulation(){
	population=(int)(population*1.05);
}

void GaiaSector::setPopulation(int newPopulation){
	population = newPopulation;
}

int GaiaSector::getPopulation(){
	return population;
}

void GaiaSector::setFleet(Fleet* f){
	settler = f;
}