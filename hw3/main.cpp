#include <iostream>
using namespace std;

#include "MultiLayer.h"

int main() {
	double train_set_x[][2] = {
		{ 0.,0. },
		{ 0.,1. },
		{ 1.,0. },
		{ 1.,1. },
		{ 0.5,1. },
		{ 1.,0.5 },
		{ 0.,0.5 },
		{ 0.5,0. },
		{ 0.5,0.5 }
	};
	double train_set_y[] = { 0,0,0,0,0,0,0,0,1 };
	vector<int> v;
	vector<double> input;
	vector<vector<double> > inputs;
	vector<double> t_output;
int epoch = 0;
	int a = 1; 
	for (int i = 0; i < 9; i++) {
		input.clear();
		for (int j = 0; j < 2; j++) {
				input.push_back(train_set_x[i][j]);
		}
		inputs.push_back(input);
		t_output.push_back(train_set_y[i]);
	}
	v.push_back(2);
	v.push_back(2);
	v.push_back(1);
	MultiLayer test(3, v);
	test.learn_gate(3);
	while (a !=0 ) {
	   for (int i = 0; i < 9; i++) {
	      test.forward(inputs[i]);
	      test.backward(t_output, i);
	      test.weight_update();
	   }
	   a = test.check_learning();
		epoch++;
	}
	cout << "epoch : " << epoch << endl;
	test.write_weight();
	cout << "end" << endl;
  return 0;
}

