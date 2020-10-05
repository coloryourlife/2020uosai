#ifndef MULTILAYER_H
#define MULTILAYER_H
#include <vector>
#include <map>

using namespace std;

class MultiLayer
{
	private: 
		int layer_num;
		vector<int> node_num;
		map<string, vector<vector<double> > > parameters;

	public:
		MultiLayer(int _layer_num, vector<int> _node_num);
		void forward_propagations(vector<double> user_input);
		void backward_propagations(int index);
		void printWeight();
};

#endif