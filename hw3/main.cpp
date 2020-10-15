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
	int type = 0;
	int gateType = 0;
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
	cout << "어떤 러닝을 할지 고르세요.(1: Gate학습, 2: 도넛데이터학습)" << endl;
	cin >> type;
	switch(type){
		case 1:
			cout <<"학습시킬 게이트를 입력하세요.(1:AND, 2:OR, 3:XOR)" << endl;
			cin >> gateType;
			test.learn_gate(gateType);
		case 2: 
			int a = 1; 
			int epoch = 0;
			while (a !=0 ) {
				for (int i = 0; i < 9; i++) {
						test.forward(inputs[i]);
						test.backward(t_output, i);
						test.weight_update();
				}
				a = test.check_learning();
				test.write_error();
				epoch++;
			}
			cout << "epoch : " << epoch << endl;
	}	
	test.write_weight();
	cout << "프로그램이 끝났습니다." << endl;
  return 0;
}

