#ifndef MULTILAYER_H
#define MULTILAYER_H
#include <vector>
#include <map>

using namespace std;

class MultiLayer
{
	private: 
		int layer_num;
		int cost;
		vector<int> output;
		vector<int> node_num;
		vector<int> check;
		vector<int> cache;
		map<string, vector<vector<double> > > weights;
		map<string, vector<double> > bias;
		map<string, vector<vector<double> > > dw;
		map<string, vector<double> > db;

	public:
		MultiLayer(int _layer_num, vector<int> _node_num);
		double linear_forward(vector<double> user_input, int layer);
		int activation_function(double net);
		void backward_propagations(int index);
		void cost_function(double target_output, int index);
		void printWeight();
		void forward_propagation(vector<double> user_input);
		void printCache();
		double dot_product(int layer, vector<double> input, vector<vector<double> > weights)
};

#endif