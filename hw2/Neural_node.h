#ifndef NEURAL_NODE_H
#define NEURAL_NODE_H

class Neural_node
{
	private:
		double weight;
		double input;

	public:
		Neural_node()
		{
			weight = 100;
			input = 100;
		}
		void setWeight(double w){ weight = w; }
		void setInput(double i){ input = i; }
		double getInput(){ return input; }
		double getWeight(){ return weight; }
		void printWeight();
		void printInput();
		double net();
};