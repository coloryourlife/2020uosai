#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Neuron.h"
using namespace std;

int main()
{
	cout << "«–Ω¿Ω√≈≥ ∞‘¿Ã∆Æ π¯»£∏¶ ¿‘∑¬«œººø‰.(AND : 1, OR : 2, XOR : 3) " << endl;
	vector<vector<double>> input = {
			{0, 0},
			{0, 1},
			{1, 0},
			{1, 1}};
	bool chk = true;
	int type = 0;
	cin >> type;
	Neuron neuron(2);
	neuron.setType(type);
	while (chk)
	{
		for (int i = 0; i < 4; i++)
		{
			neuron.forward_propagation(input[i]);
			neuron.backward_propagation(i);
		}
		chk = neuron.check_learning(4);
	}
	system("pause");
	return 0;
}