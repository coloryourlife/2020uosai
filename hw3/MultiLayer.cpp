#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include "MultiLayer.h"

using namespace std;

MultiLayer::MultiLayer(int _layer_num, vector<int> _node_num)
{
   srand((unsigned int)time(NULL));
   layer_num = _layer_num;
   for (int i = 0; i < layer_num; i++) {
      node_num.push_back(_node_num[i]);
   }
   weights.push_back(vector<vector<double> >());
   for (int l = 1; l < layer_num  ; l++) {
      weights.push_back(vector<vector<double> >());
      for (int j = 0; j < node_num[l]; j++) {
         weights[l].push_back(vector<double>());
         for (int k = 0; k < node_num[l - 1]; k++) {
            weights[l][j].push_back(round(((double)rand() / RAND_MAX)*100)/100);
         }
      }
   }
   for (int l = 0; l < layer_num; l++) {
      values.push_back(vector<double>());
      A.push_back(vector<double>());
      errors.push_back(vector<double>());
      bias.push_back(vector<double>());
      for (int i = 0; i < node_num[l]; i++) {
         values[l].push_back(0);
         A[l].push_back(0);
         errors[l].push_back(0);
         bias[l].push_back(0);
      }
   }
   printWeight();
   count = 0;
   learning_rate = 0.5;
   cout << "init complete" << endl;
};

void MultiLayer::printWeight() {
   for (int i = 1; i < layer_num; i++) {
      cout << "layer : " << i << endl;
      for (int j = 0; j < node_num[i]; j++) {
         cout << j + 1 << "번째 노드로 가는 weight, bias" << endl;
         cout << "bias : " << round(bias[i][j] * 100) / 100 << endl;
				 cout << "weight : [";
         for (int k = 0; k < node_num[i - 1]; k++) {
            cout << round(weights[i][j][k] * 100) / 100 << " ";
         }
				 cout << "]" << endl;
      }
   }
}

// double MultiLayer::activation_function(double net) {
//    if (net > 0.5) { return 1; }
//    else { return 0; }
// }

double MultiLayer::sigmoid(double net) {
   return 1 / (1 + exp(-net));
}

double MultiLayer::d_sigmoid(double x) {
   return x*(1 - x);
}

void MultiLayer::forward(vector<double> user_input) {
	for (int i = 0; i < user_input.size(); i++) {
		values[0][i] = user_input[i];
		A[0][i] = values[0][i];
	}
	for (int l = 1; l < layer_num; l++) {
		for (int j = 0; j < node_num[l]; j++) {
				values[l][j] = bias[l][j];
				for (int k = 0; k < node_num[l - 1]; k++) {
					values[l][j] += A[l-1][k] * weights[l][j][k];
				}
				A[l][j] = sigmoid(values[l][j]);
		}
	}
}

void MultiLayer::backward(vector<double> target_output, int index) {
   double err;
   double error;
   error = 0.5 * pow((target_output[index] - A[layer_num - 1][0]), 2);
   errors[layer_num - 1][0] = (-target_output[index] + A[layer_num - 1][0]) * d_sigmoid(A[layer_num-1][0]);
   if (error < 0.01) { check.push_back(0); }
   else { 
      //cout << error << endl;
      check.push_back(1);
   }
   for (int l = layer_num - 2; l >= 0; l--) {
      for (int j = 0; j < node_num[l]; j++) {
				err = 0;
				for (int k = 0; k < node_num[l + 1]; k++) {
					err += errors[l + 1][k] * weights[l + 1][k][j];
				}
				errors[l][j] = err * d_sigmoid(A[l][j]);
      }
   }
}

void MultiLayer::weight_update() {
   for (int l = 1; l < layer_num; l++) {
      for (int j = 0; j < node_num[l]; j++) {
				for (int k = 0; k < node_num[l - 1]; k++) {
					weights[l][j][k] -= learning_rate * A[l - 1][k] * errors[l][j];
				}
				bias[l][j] -= learning_rate * errors[l][j];
      }
   }
   //printWeight();
}

int MultiLayer::check_learning() {
   int check_size = check.size();
   int cnt = 0;
   for (int i = 0; i < check_size; i++) {
      if (check[i] == 0) {
         cnt++;
      }
   }
   if(count < cnt){
      cout << "Error 감소 weight changed" << endl;
      printWeight();
      count = cnt;
   }
   if (cnt == check_size) { return 0; }
   else {
      check.clear();
      return 1; 
   }
}

void MultiLayer::init_gate_input(){
	vector<double> v;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			v.clear();
			v.push_back(i);
			v.push_back(j);
			gate_input.push_back(v);
		}
	}
	cout << "gate_init complete" << endl;
}

void MultiLayer::set_gate_type(int typeNum){
	double and_output[4] = {0,0,0,1};
	double or_output[4] = {0,1,1,1};
	double xor_output[4] = {0, 1, 1, 0};

	switch(typeNum){
		case 1: 
				for(int i = 0; i < 4; i++){
					gate_output.push_back(and_output[i]);
				}
		case 2:
				for (int i = 0; i < 4; i++){
					gate_output.push_back(or_output[i]);
				}
		case 3:
				for (int i = 0; i < 4; i++){
					gate_output.push_back(xor_output[i]);
				}
	}
	cout << "gate_type complete" << endl;
}

void MultiLayer::learn_gate(int typeNum)
{  
	int a = 1;
	int epoch = 0;
	init_gate_input();
	set_gate_type(typeNum);
	while (a != 0)
	{  
      if(epoch > 20000){
         cout << "Learning failed. Pleas try again" << endl;
         break;
      }
		for (int i = 0; i < 4; i++)
		{
			forward(gate_input[i]);
			backward(gate_output, i);
			weight_update();
		}
		a = check_learning();
		epoch++;
	}
	cout << "epoch : " << epoch << endl;
}

void MultiLayer::write_weight(){
   string fileName = "weight.txt";
   ofstream writeFile(fileName.data());
   if(writeFile.is_open()){
      for (int i = 1; i < layer_num; i++) {
         writeFile << "layer : " << i << endl;
         for (int j = 0; j < node_num[i]; j++) {
            writeFile << j + 1 << "번째 노드로 가는 weight, bias" << endl;
            writeFile << "bias : " << bias[i][j] << endl;
            writeFile << "weight : [";
            for (int k = 0; k < node_num[i - 1]; k++) {
               writeFile << weights[i][j][k] << " ";
            }
            writeFile << "]" << endl;
         }
      } 
      writeFile.close(); 
   }
}

void MultiLayer::print_A(){
	for (int l = 1; l < layer_num; l++) {
		cout << "layer : " << l << "  A" << endl;
		for (int j = 0; j < node_num[l]; j++) {
			cout << j << "번째 : ";
			cout << A[l][j] << endl;
		}
	}
}