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
	vector<double> v3;
	for(int i = 0 ; i < layer_num; i++){
		node_num.push_back(_node_num[i]);
	}
	for(int i = 1; i < layer_num; i++){
		for(int j = 0; j < node_num[i]; j++){
			for(int k = 0; k < node_num[i-1]; k++){
				v1.push_back(round(((double)rand() / RAND_MAX) * 100) / 10000);
			}
			v2.push_back(v1);
			v3.push_back(1);
			v1.clear();
		}
		weights['W'+to_string(i)] = v2;
		bias['b'+to_string(i)] = v3;
		v3.clear();
		v2.clear();
	}
	
	cout << "init complete" << endl;
};

void MultiLayer::printWeight(){
	for(int i = 1; i < layer_num; i++){
		cout << "layer : " << i << endl;
		for(int j = 0; j < node_num[i]; j++){
			cout << j+1 << "번째 노드로 가는 weight" << endl;
			for(int k = 0; k < node_num[i-1]; k++){
				cout << k+1 << "번째 weight : " << weights['W' + to_string(i)][j][k] << endl;
			}
		}
	}
}

double MultiLayer::linear_forward(vector<double> user_input)
{
	 vector<double> input;
	 vector<double> net;
	 double sig;
	 for(int i = 0; i < user_input.size(); i++){
		 input.push_back(user_input[i]);
	 }
	 for(int i = 1; i < layer_num; i++){
		 for(int j = 0; j < node_num[i] ; j++){
			 for(int k = 0; k < node_num[i-1]; k++){
				 sig += input[k] * weights["W"+to_string(i)][j][k];
			 }
			 sig += bias['b'+to_string(i)][j];
			 net.push_back(sig);
		 }
		 input.clear();
		 for(int n = 0; n < net.size(); n++){
			 input.push_back(net[n]);
		 }
		 net.clear();
	 }
	 cout << "net 값 : " << input[0] << endl;
	 return input[0];
};

void MultiLayer::activation_function(double net){
	if(net > 0) {output = 1;}
	else { output = 0;}
	cout << "output : " << output << endl;
}

void MultiLayer::forward_propagation(vector<double> user_input){
	double net = linear_forward(user_input);
	activation_function(net);
}