#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
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

double MultiLayer::dot_product(int layer, vector<double> input, vector<vector <double> > weight){
	double net;
	for(int i = 0; i < node_num[layer]; i++){
		for(int j = 0; j < node_num[layer_num-1]; j++){
			net += input[j] * weight[i][j];
		}
	}
	return net;
}
double linear_forward(vector<double> user_input, int layer)
{
	double Z;
	vector<vector <double> > weight = weights['W'+to_string(layer)];
	Z = dot_product(layer, user_input, weights['W'+to_string(layer)]
}
// double MultiLayer::linear_forward(vector<double> user_input)
// {
// 	 vector<double> input;
// 	 vector<int> outputs;
// 	 double net;
// 	 double sig;
// 	 for(int i = 0; i < user_input.size(); i++){
// 		 input.push_back(user_input[i]);
// 	 }
// 	 for(int i = 1; i < layer_num; i++){
// 		 for(int j = 0; j < node_num[i] ; j++){
// 			 for(int k = 0; k < node_num[i-1]; k++){
// 				net += input[k] * weights["W"+to_string(i)][j][k];
// 			 }
// 			 net += bias['b'+to_string(i)][j];
// 			 outputs.push_back(activation_function(net));
// 			 cache.push_back(activation_function(net));
// 		 }
// 		 input.clear();
// 		 for(int n = 0; n < outputs.size(); n++){
// 			 input.push_back(double(outputs[n]));
// 		 }
// 		 outputs.clear();
// 	 }
// 	 output.push_back((input[0]));
// 	 cout << "output 값 : " << input[0] << endl;
// 	 printCache();
// 	 return input[0];
// };
double linear_forward(vector<double> user_input, vector<double> weights, vector<double> bias){

}

int MultiLayer::activation_function(double net){
	if(net > 0) {return 1;}
	else { return 0;}
}

void MultiLayer::forward_propagation(vector<double> user_input){
	double net = linear_forward(user_input);
}

void MultiLayer::cost_function(double target_output, int index){
	cost = 1/2*pow((target_output - output[index]),2);
}

void backward_propagations(int index){

}

void MultiLayer::printCache(){
	for(int i = 0; i < cache.size(); i++){
		cout << "cache" << cache[i] << endl;
	}
}