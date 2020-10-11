#include <iostream>
using namespace std;

#include "MultiLayer.h"

int main(){
	double train_set_x[][2] = {
		{0.,0.},
		{0.,1.},
		{1.,0.},
		{1.,1.},
		{0.5,1.},
		{1.,0.5},
		{0.,0.5},
		{0.5,0.},
		{0.5,0.5}
	};
	double train_set_y[] = {0,0,0,0,0,0,0,0,1};

	vector<int> v;
	vector<double> input;
	input.push_back(0);
	input.push_back(0);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	v.push_back(1);
	MultiLayer test(4, v);
	test.printWeight();
	test.linear_forward(input);
	return 0;
}