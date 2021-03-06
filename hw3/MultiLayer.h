#ifndef MULTILAYER_H
#define MULTILAYER_H
#include <vector>


using namespace std;

class MultiLayer
{
private:
   int layer_num;
   double learning_rate;
   double count;
   vector<int> node_num;
   vector<int> check;
	 vector<vector<double> > d_input; //doughnut data input
	 vector<double> d_output; //doughnut data output
   vector<vector<double> > gate_input;
   vector<double> gate_output;
   vector<vector<vector<double> > > weights;
   vector<vector<double> > errors;
   vector<vector<double> > values;
   vector<vector<double> > A;
   vector<vector<double> > bias;

public:
	MultiLayer(int _layer_num, vector<int> _node_num);
	double activation_function(double net);
	void printWeight();
	void forward(vector<double> user_input);
	void backward(vector<double> target_output, int index);
	void weight_update();
	double sigmoid(double net);
	double d_sigmoid(double x);
	int check_learning();
	void init_doughnut();
	void init_gate_input();
	void set_gate_type(int typeNum);
	void learn_gate(int typeNum);
	void learn_doughnut();
	void write_weight();
  void write_error(int input_num);
	void print_A();
};

#endif