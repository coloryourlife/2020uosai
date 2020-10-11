#ifndef NEURON_H
#define NEURON_H
#include <vector>
using namespace std;

class Neuron
{
private:
	vector<double> input;
	vector<double> weight;
	int output;
	int check;
	double threshold;
	double learning_rate;

public:
	Neuron(int input_num);
	void forward_propagation(vector<double> user_input);
	void backward_propagation(vector<int> target_output, int index);
	bool check_learning(int input_num);
	void printWeight();
	void printInput();
};

#endif