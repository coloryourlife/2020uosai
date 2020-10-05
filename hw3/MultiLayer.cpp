#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <math.h>
#include <string>
#include "MultiLayer.h"

using namespace std;

MultiLayer::MultiLayer(int _layer_num, vector<int> _node_num)
{
	srand((unsigned int)time(NULL)); 
	layer_num = _layer_num;
	vector<double> v1;
	vector<vector<double> > v2;
	for(int i = 0 ; i < layer_num; i++){
		node_num.push_back(_node_num[i]);
	}
	for(int i = 1; i < layer_num; i++){
		for(int j = 0; j < node_num[i]; j++){
			for(int k = 0; k < node_num[i-1]; k++){
				v1.push_back(round(((double)rand() / RAND_MAX) * 100) / 100);
			}
			v2.push_back(v1);
			v1.clear();
		}
		parameters['W'+to_string(i)] = v2;
		v2.clear();
	}
	cout << "init complete" << endl;
};

void MultiLayer::printWeight(){
	cout << "start" << endl;
	for(int i = 1; i < layer_num; i++){
		for(int j = 0; j < node_num[i]; j++){
			for(int k = 0; k < node_num[i-1]; k++){
				cout << parameters['W' + to_string(i)][j][k] << endl;
			}
		}
	}
	cout << "end" << endl;
}

void MultiLayer::forward_propagations(vector<double> user_input)
{
	
};