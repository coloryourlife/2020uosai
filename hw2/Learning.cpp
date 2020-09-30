#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Learning.h"

using namespace std;

void Learning::setDimension(int dim){
	dimension = dim;
}

void Learning::setInput(double** in){
	for(int i = 0; i < input_num ; i++){
		for(int j = 0; j < dimension; j++){
			input[i][j] = in[i][j];
		}
	}
}


void Learning::initWeight(){
	srand((unsigned int)time(NULL));
	for(int i = 0; i < dim+1; i++){
		weight[i] = (double)rand() / RAND_MAX;
	}
}

void Learning::activation_function(){
	if(sigma > threshold){
		output = 1;
	}
	else { output = 0;}
}



void Learning::forward_propagation(){
	for(int i = 0; i < dim+1 ; i++){
		sigma += input[i] * weight[i];
	}
}
