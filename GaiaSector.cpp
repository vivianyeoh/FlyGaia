#include <iostream>
#include "GaiaSector.h"
using namespace std;

GaiaSector::GaiaSector(string cs, double p):colonizeSection(cs),percentage(p){
	population=0;
}

void GaiaSector::growPopulation(){
	*population=(int)(*population*1.05);
}

void GaiaSector::setPopulation(int newPopulation){
	*population = newPopulation;
}