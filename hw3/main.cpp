#include <iostream>
using namespace std;

#include "MultiLayer.h"

int main() {
	int type;
	int gateType;
	vector<int> v;
	//vector for node number of each layer
	v.push_back(2);
	v.push_back(2);
	v.push_back(1);
	MultiLayer test(3, v); //make a mlp model with layer 3 and nodes upon.
	cout << "어떤 러닝을 할지 고르세요.(1: Gate학습, 2: 도넛데이터학습)" << endl;
	cin >> type;
	switch(type){
		case 1:
			cout <<"학습시킬 게이트를 입력하세요.(1:AND, 2:OR, 3:XOR)" << endl;
			cin >> gateType;
			test.learn_gate(gateType);
			break;
		case 2: 
			test.learn_doughnut();
			break;
		default:
			cout << "잘못입력하셨습니다." << endl;
			break;
	}	
	test.write_weight();
	cout << "프로그램이 끝났습니다." << endl;
  return 0;
}

