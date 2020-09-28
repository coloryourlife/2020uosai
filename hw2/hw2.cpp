#include <iostream>
#include <cstdlib>
#include <ctime>
#define M 100
using namespace std;

class Neural_node {
	private:
		double weight;
		double input;
	public:
		Neural_node(){
			weight = 100;
			input = 100;
		}
		void setWeight(double weight){
			weight = weight;
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
		double net();
};

double PRNG(){
	double num = (double)rand() / RAND_MAX;
	return num;
}

// Neural_node* node_initialization(int num, double *input, double *weight){
// 	Neural_node *nodes[num];

// }

// Nodes* node_initialization(Nodes *nodes, int input_num){
// 	srand((unsigned int)time(NULL));
// 	nodes.node
// }

int main(){
	Neural_node nodes[3];
	double weight[3] = {-1.5, 1, 1};
	double input[3] = {1,2,3};
	for(int i = 0; i < 3; i++){
		nodes[i].setWeight(weight[i]);
		nodes[i].setInput(input[i]);
	}

	cout << "end" << endl;
}