#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <math.h>
#include "Neuron.h"

using namespace std;

Neuron::Neuron(int input_num)
{
	srand((unsigned int)time(NULL)); //√ ±‚ weight ∞™¿∏∑Œ 0~1∞™ ¡ﬂ random«œ∞‘ √ ±‚»≠
	for (int i = 0; i < input_num + 1; i++)
	{
		weight.push_back(round(((double)rand() / RAND_MAX) * 100) / 100);
		input.push_back(0); // input ∞™¿ª 0¿∏∑Œ √ ±‚»≠
	}
	learning_rate = 0.3; // learning_rate 0.3¿∏∑Œ √ ±‚»≠
	cout << "Learning_rate =" << learning_rate << endl;
	cout << "--------init weight---------" << endl;
	printWeight();
	threshold = 0; // threshold ∞™¿∫ 0¿∏∑Œ √ ±‚»≠
	check = 0;
}

void Neuron::forward_propagation(vector<double> user_input)
{
	double net = weight[0] * 1; //∞Ì¡§∞™ 1∞˙ ±◊¿« weight∏¶ ∞ˆ«— ∞™¿∏∑Œ net∞™ √ ±‚»≠
	for (int i = 0; i < user_input.size(); i++)
	{
		input[i] = user_input[i];
		net += user_input[i] * weight[i + 1]; // net = sigma(xi*wi)
	}
	if (net > threshold)
	{
		output = 1;
	} // activation «‘ºˆ∑Œ ∞Ë¥‹«‘ºˆ∏¶ ªÁøÎ, threshold ∞™∫∏¥Ÿ ≈©∏È 1, ¿€¿∏∏È 0 return
	else
	{
		output = 0;
	}
}

void Neuron::backward_propagation(int index)
{
	int delta = t_output[index] - output; //target output - output = delta
	if (delta == 0)
	{
		check++; //delta ∞™¿Ã 0¿Ã∏È target output¿Ã ≥™ø¬ ∞Õ¿Ãπ«∑Œ check ∞™¿ª ¡ı∞°
	}
	else
	{
		weight[0] = weight[0] + double(delta) * learning_rate;
		for (int i = 1; i < weight.size(); i++)
		{
			weight[i] = weight[i] + input[i - 1] * double(delta) * learning_rate; // w  = w + dw, dw = xi*delta*c
		}
		cout << "--------weight changed--------" << endl;
		printWeight(); //weight¿« ∫Ø»≠∞° ¿œæÓ≥Ø ∂ß∏∂¥Ÿ √‚∑¬¿∏∑Œ weight ∞™¿« ∫Ø»≠∏¶ æÀ∑¡¡ÿ¥Ÿ.
	}
}

bool Neuron::check_learning(int input_num)
{
	if (check == input_num)
	{
		cout << "Error after iterations" << endl;
		cout << "Error : 0%" << endl;
		return false;
	} //user¿« input set¿Ã ∏µŒ µÈæÓø‘¿ª ∂ß, ∏µÁ output¿Ã target output∞˙ ∞∞¿∏∏È whileπÆ ¡æ∑·
	else
	{
		cout << "Error after iterations" << endl;
		cout << "Error : " << double(100 - (double(check) / double(input_num)) * 100) << "%" << endl;
		check = 0; //«œ≥™∂Ûµµ ¥Ÿ∏£∏È check ∞™ ¥ŸΩ√ 0¿∏∑Œ √ ±‚»≠ »ƒ π›∫ππÆ Ω««‡
		return true;
	}
}

void Neuron::printWeight()
{
	for (int i = 0; i < weight.size(); i++)
	{
		cout << "weight[" << i << "] : " << weight[i] << endl; //weight∞™ √‚∑¬
	}
}

void Neuron::setType(int type)
{
	vector<int> and_output = {0, 0, 0, 1}; //AND gate's target output
	vector<int> or_output = {0, 1, 1, 1};	 //OR gate's target output
	vector<int> xor_output = {0, 1, 1, 0}; //XOR gate's target output
	t_output.push_back(0);
	t_output.push_back(0);
	t_output.push_back(0);
	t_output.push_back(0);
	switch (type)
	{
	case 1:
		for (int i = 0; i < 4; i++)
		{
			t_output[i] = and_output[i];
		}
		break;
	case 2:
		for (int i = 0; i < 4; i++)
		{
			t_output[i] = or_output[i];
		}
		break;
	case 3:
		for (int i = 0; i < 4; i++)
		{
			t_output[i] = xor_output[i];
		}
		break;
	}
}
