#ifndef MULTILAYER_H
#define MULTILAYER_H
#include <vector>
#include <map>

using namespace std;

class MultiLayer
{
	private: 
		int layer_num;
		int output;
		vector<int> node_num;
		map<string, vector<vector<double> > > weights;
		map<string, vector<double> > bias;

	public:
		MultiLayer(int _layer_num, vector<int> _node_num);
		double linear_forward(vector<double> user_input);
		void activation_function(double net);
		void backward_propagations(int index);
		void printWeight();
		void forward_propagation(vector<double> user_input);
};

#endif