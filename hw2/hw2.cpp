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

double linear_forward(Neural_node* nodes, double* input, int dim){
	double output = 0;
	nodes[0].setInput(1);
	for(int i = 1; i < dim+1; i ++){
		nodes[i].setInput(input[i-1]);
	}
	for(int i = 0; i < dim + 1; i++){
		output += nodes[i].net();
	}
	return output;
}

int main(){
	Neural_node nodes[3];
	double weight[3] = {-1.5, 1, 1};
	double input[4][2] = {{0,0},{0,1},{1,0},{1,1}};
	double output[4];
	int input_num = sizeof(input) / sizeof(input[0]);
	init_weight(nodes,3);
	for (int i = 0; i < input_num; i++)
	{
		output[i] = linear_forward(nodes, input[i], 2);
		cout << output[i] << endl;
	}
	cout << "end" << endl;
	return 0;
}