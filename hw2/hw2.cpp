#include <iostream>
#include <cstdlib>
#include <ctime>
#define M 100
using namespace std;

class Neural_node {
	protected:
		double weight;
		double input;
	public:
		Neural_node(){
			weight = 100;
			input = 100;
		}
		void setWeight(double w){
			weight = w;
		}
		void setInput(double i){
			input = i;
		}
		double getInput(){
			return input;
		}
		double getWeight(){
			return weight;
		}
		void printWeight(){
		 cout << weight << endl;
		}
		void printInput(){ 
			cout << input << endl;
		}
		double net(){
			return weight*input;
		};
};

double PRNG(){
	double num = (double)rand() / RAND_MAX;
	return num;
}

Neural_node* init_weight(Neural_node* nodes, int num){
	srand((unsigned int)time(NULL));
	for(int i = 0; i < num; i++){
		double weight = PRNG();
		nodes[i].setWeight(weight);
		nodes[i].printWeight();
	}
	return nodes;
}

int linear_forward_propagation(Neural_node* nodes, double* input, int dim){
	double net = 0;
	nodes[0].setInput(1);
	for(int i = 1; i < dim+1; i ++){
		nodes[i].setInput(input[i-1]);
	}
	for(int i = 0; i < dim + 1; i++){
		net += nodes[i].net();
	}
	if(net > 0) return 1;
	else return 0;
}

void backward_propagation(Neural_node* nodes, int delta, double learning_rate, int input_num){
	double dw = 0;
	double w = 0;
	for(int i=0; i < input_num; i++){
		dw = nodes[i].getInput() * double(delta);
		w = nodes[i].getWeight() + dw;
		nodes[i].setWeight(w);
		cout << "w" << i << " : " ;
		nodes[i].printWeight();
	}
}

int check(int* delta){
	int cnt = 0;
	for(int i = 0; i < 4; i++){
		if(delta[i] != 0) cnt++;
	}
	return cnt;
}

int main(){
	Neural_node nodes[3];
	double weight[3] = {-1.5, 1, 1};
	double input[4][2] = {{0,0},{0,1},{1,0},{1,1}};
	double output[4];
	int and_target_output[4] = {0,0,0,1};
	int or_target_output[4] = {0,1,1,1};
	int xor_target_output[4] = {0,1,1,0};
	int delta[4];
	int input_num = sizeof(input) / sizeof(input[0]);
	int chk = 1;
	int cnt = 0;
	init_weight(nodes,3);
	while(chk){
		for (int i = 0; i < input_num; i++)
		{
			output[i] = linear_forward_propagation(nodes, input[i], 2);
			delta[i] = xor_target_output[i] - output[i];
			if(delta[i] != 0){
				cout << ++cnt << "번째 수정된 weight값들은" << endl;
				backward_propagation(nodes, delta[i], 0.3, 3);
			}
		}
		chk = check(delta);
	}

	cout << "end" << endl;
	return 0;
}