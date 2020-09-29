#ifndef MACHINE_LEARNING_H
#define MACHINE_LEARNING_H
#include "Neural_node.h"
#define M 10

class Machine_learning
{
private:
	Neural_node* nodes;

public:
	Neural_node()
	{
		for(int i = 0; i < dim; i++){
			
		}
	}
	void setWeight(double w) { weight = w; }
	void setInput(double i) { input = i; }
	double getInput() { return input; }
	double getWeight() { return weight; }
	void printWeight();
	void printInput();
	double net();
};

#endif