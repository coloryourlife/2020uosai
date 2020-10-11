#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Neuron.h"
using namespace std;

int main(){
	vector<vector<double> > input = {
		{0,0},
		{0,1},
		{1,0},
		{1,1}
	};
	vector<int> t_output;
	t_output.push_back(0);
	t_output.push_back(0);
	t_output.push_back(0);
	t_output.push_back(1);
	bool chk = true;
	cout << "shit" << endl;
	Neuron neuron(2);
	while(chk){
		for(int i = 0; i < 4; i++){
			neuron.forward_propagation(input[i]);
			neuron.backward_propagation(t_output, i);
		}
		chk = neuron.check_learning(4);
	}
	return 0;
}