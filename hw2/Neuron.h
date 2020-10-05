#ifndef NEURON_H
#define NEURON_H
#include <vector>
using namespace std;

class Neuron
{
private:
	vector<double> input;	 //input ∞™¿ª ¿˙¿Â«œ¥¬ ∫Øºˆ
	vector<double> weight; // weight ∞™¿ª ¿˙¿Â«œ¥¬ ∫Øºˆ
	vector<int> t_output;	 // target output ∞™¿ª ¿˙¿Â«œ¥¬ ∫Øºˆ
	int output;						 // output ∞™¿ª ¿˙¿Â«œ¥¬ ∫Øºˆ
	int check;						 // ø√πŸ∏• √‚∑¬¿Ã ¿Ã∑ÁæÓ¡≥¥¬µ• check«œ±‚ ¿ß«— ∫Øºˆ
	double threshold;			 // threshold∏¶ ¿˙¿Â«œ¥¬ ∫Øºˆ
	double learning_rate;	 // learning_rate¿ª ¿˙¿Â«œ¥¬ ∫Øºˆ

public:
	Neuron(int input_num);															 //constructor «‘ºˆ
	void forward_propagation(vector<double> user_input); // user input¿ª πﬁæ∆ forward propagation «œ¥¬ «‘ºˆ
	void backward_propagation(int index);								 // backward propagation «‘ºˆ
	void setType(int type);															 // userø°∞‘ and,or,xor¿« type¿ª ¿‘∑¬πﬁ¥¬ «‘ºˆ
	bool check_learning(int input_num);									 //learning¿Ã ¿ﬂ ¿Ã∑ÁæÓ¡≥¥¬¡ˆ check«œ¥¬ «‘ºˆ
	void printWeight();																	 //weight¿« ∫Ø»≠∞° ¿÷¿ª ∂ß weight∏¶ √‚∑¬«ÿ¡÷¥¬ «‘ºˆ
};

#endif