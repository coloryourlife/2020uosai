#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Neuron.h"

using namespace std;

Neuron::Neuron(int input_num){
	srand((unsigned int)time(NULL));
	for(int i = 0; i < input_num + 1; i++){
		weight.push_back((double)rand() / RAND_MAX);
	}
	threshold = 0;
	check = 0;
	learning_rate = 0.3;
	cout << "constructor" << endl;
}

void Neuron::forward_propagation(vector<double> user_input){
	double net = weight[0] * 1 ;
	for(int i = 0; i < user_input.size(); i++){
		input[i] = user_input[i];
		net += user_input[i] * weight[i+1];
	}
	if(net > threshold){ output = 1;}
	else { output = 0;}
	cout << "forward" << endl;
}

void Neuron::backward_propagation(vector<int> target_output, int index){
	int delta = target_output[index] - output;
	if(delta == 0){
		check++;
	}
	else{
		weight[0] = weight[0] + double(delta);
		for(int i = 1; i < weight.size(); i++){
			weight[i] = weight[i] + input[i-1] * double(delta);
		}
		printWeight();
	}
	cout << "backward" << endl;
}

bool Neuron::check_learning(int input_num){
	if(check == input_num) return false;
	else {
		check = 0;
		return true;
	}
	cout << "check" << endl;
}

void Neuron::printWeight(){
	for(int i = 0; i < weight.size(); i++){
		cout << "weight[" << i << "] : " << weight[i] << endl;
	}
}