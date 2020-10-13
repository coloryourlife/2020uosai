#ifndef MULTILAYER_H
#define MULTILAYER_H
#include <vector>


using namespace std;

class MultiLayer
{
private:
   int layer_num;
   double learning_rate;
   vector<int> node_num;
   vector<int> check;
   vector<vector<vector<double> > > weights;
   vector<vector<double> > errors;
   vector<vector<double> > values;
   vector<vector<double> > A;
   vector<vector<double> > bias;

public:
   MultiLayer(int _layer_num, vector<int> _node_num);
   double activation_function(double net);
   void set_learning_rate() { learning_rate = 0.8; };
   void printWeight();
   void forward(vector<double> user_input);
   void backward(vector<double> target_output, int index);
   void weight_update();
   double sigmoid(double net);
   double d_sigmoid(double x);
   int check_learning();
};

#endif