#ifndef LEARNING_H
#define LEARNING_H
#include <vector>
#define M 10
using namespace std;

class Learning
{
private:
	vector<double> input;
	vector<double> weight;
	vector<int> target_output;
	int output;
	double sigma;
	double threshold;
	int input_num;
	int delta;
	double learning_rate;

public:
	void initWeight();
	void setWeight(double* w);
	void setThreshold(){threshold = 1;}
	double forward_propagation();
	void activation_function();
	int calc_delta();
	void backward_propagation();
	void printWeight();
	void printInput();
};

#endif