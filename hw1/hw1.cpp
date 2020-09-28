#include <iostream>
#include <cstdlib>
#include <ctime>
#define M 1000
using namespace std;
typedef struct{
	double weight;
	double input;
}neural_node;

typedef struct Nodes{
	neural_node data[M];
}Nodes;

int N = 3; //N dimensions, you can put whatever you want.
double PRNG(){
	double num = (double)rand() / RAND_MAX; //random number generator between 0 to 1.
	return num;
}

Nodes* node_initialization(int input_num){
	srand((unsigned int)time(NULL));
	Nodes *nodes;
	nodes->data[0].input = 1;
	for(int i = 0; i < input_num+1; i ++){
		nodes->data[i].weight = PRNG();
	}
	return nodes;
}

int linear_activation(Nodes *nodes, double *input){
	int inputSize = sizeof(input) / sizeof(input[0]);
	cout << "input size " << input[0] << endl;
	double linear;
	for(int i = 1; i < 3; i++){
		nodes->data[i].input = input[i-1];
	}
	for(int i = 0; i < 3; i++){
		double weight = nodes->data[i].weight;
		double input = nodes->data[i].input;
		linear += weight*input;
	}
	if(linear > 0) return 1;
	else return 0;
}


int main(){
	Nodes *nodes = node_initialization(2);
	double input1[2] = {0,0};
	// for(int i=0; i < 3; i++){
	// 	cout << nodes->data[i].weight << endl;
	// }
	//int test = linear_activation(nodes, input1);
	//cout << test << endl;
	cout << "end" << endl;

	return 0;
}