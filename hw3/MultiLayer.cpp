#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include "MultiLayer.h"

using namespace std;

/* MultiLayer constructor 
   Init weights with random numbers between 0 to 1.
   Init number of layer.
   Init number of nude number of each layers
   Init learning rate with 0.5
   When you finish initialize weights. Print out init weights.
 */
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

/* Printing weight on console */
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

/* I used sigmoid as activation function */
double MultiLayer::sigmoid(double net) {
   return 1 / (1 + exp(-net));
}

/* derivative of sigmoid */
double MultiLayer::d_sigmoid(double x) {
   return x*(1 - x);
}

/* forward propagation 
   Save every net values at values.
   Save every g(net) at A
   forward prop : Z = AW + b 
   A is a value from last layer nodes, W is Weight, b is bias
 */
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

/* backward propagation
   caculate error with target_output and output which we calc at forward propagation.
   using mse for error calc
   since target output is 0 or 1 the output with sigmoid as activation function couldn't reach exact value.
   so we decide if error is less than 0.01 then the learning is done with success.
 */
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

/* weight update(bias update either)
   weight update with errors(delta)
   w = -learning_rate * A * delta
   b = -learning_rate * delta
 */
void MultiLayer::weight_update() {
   for (int l = 1; l < layer_num; l++) {
      for (int j = 0; j < node_num[l]; j++) {
         for (int k = 0; k < node_num[l - 1]; k++) {
            weights[l][j][k] -= learning_rate * A[l - 1][k] * errors[l][j];
         }
         bias[l][j] -= learning_rate * errors[l][j];
      }
   }
}

/* check learning
   if all the output matches to target output 
   then it'll return 1
   else it'll return 0 
   if we get 1 for the return value.
   we can break the while loop
 */
int MultiLayer::check_learning() {
   double check_size = check.size();
   double cnt = 0;
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

/* init gate input
   initialize gate input with (0,0),(0,1),(1,0),(1,1)
 */
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

/* set gate type
   get type number from user
   1 : and gate
   2 : or gate
   3 : xor gate
   initialize target output
 */
void MultiLayer::set_gate_type(int typeNum){
	double and_output[4] = {0,0,0,1};
	double or_output[4] = {0,1,1,1};
	double xor_output[4] = {0, 1, 1, 0};

	switch(typeNum){
		case 1: 
         for(int i = 0; i < 4; i++){
            gate_output.push_back(and_output[i]);
         }
         break;
		case 2:
         for (int i = 0; i < 4; i++){
            gate_output.push_back(or_output[i]);
         }
         break;
		case 3:
         for (int i = 0; i < 4; i++){
            gate_output.push_back(xor_output[i]);
         }
         break;
      default:
         cout << "잘못 입력하셨습니다." << endl;
	}
	cout << "gate_type complete" << endl;
}

/* Learning gate
   if epoch is greater than 20000 there is some problem with setting init weights
   and it falls to local minimum so learning got failed.
   else it printed out the epoch and whenever the weight got changed with error % changed
   we print out the changed weight.
 */
void MultiLayer::learn_gate(int typeNum)
{  
	int a = 1;
	int epoch = 0;
	init_gate_input();
	set_gate_type(typeNum);
	while (a != 0)
	{  
      epoch++;
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
      write_error(4);
   }
	cout << "epoch : " << epoch << endl;
}

/* init doughnut data
   initialize doughnut data's input and target output
 */
void MultiLayer::init_doughnut(){
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
	}; //given doughnut inputs
   double train_set_y[] = { 0,0,0,0,0,0,0,0,1 }; //given doughnut output set
   vector<double> input;
   for(int i = 0; i < 9; i++){
      input.clear();
      for(int j = 0; j < 2; j++){
         input.push_back(train_set_x[i][j]);
      }
      d_input.push_back(input);
      d_output.push_back(train_set_y[i]);
   }
}

/* Learning with doughnut datas */
void MultiLayer::learn_doughnut(){
   int a = 1;
   int epoch = 0;
   init_doughnut();
   while(a != 0){
      for(int i = 0; i < 9; i++){
         forward(d_input[i]);
         backward(d_output, i);
         weight_update();
      }
      a = check_learning();
      epoch++;
      write_error(9);
   }
   cout << "epoch : " << epoch << endl;
   cout << "학습이 완료되었습니다." << endl;
}

/* write a final weight in weight.txt file */
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

/* write a error with every epoch */
void MultiLayer::write_error(int input_num){
	string fileName = "error.txt";
   ofstream writeFile(fileName.data(),ios::app);
   if(writeFile.is_open()){
      writeFile << double((input_num - count)) / input_num * 100 << endl;
      writeFile.close();
   }
}