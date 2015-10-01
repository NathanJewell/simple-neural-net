// stdafx.cpp : source file that includes just the standard includes
// NeuralNet.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <iostream>
#include <string>
#include "NeuralNet.h"
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

struct point
{
	point(double nx, double ny)
	{
		x = nx;
		y = ny;
	}

	double x, y;
};
point genRandomInput()
{
	
//	double x = (double)rand() % 21 -10; //random number between -10 and 10?
//	double y = (double)rand() % 21 - 10;

//	point coord(x, y);

//	return coord;


	double x = (double)rand() / (RAND_MAX + 1)*(10 + 10) - 10;
	double y = (double)rand() / (RAND_MAX + 1)*(10 + 10) - 10;
	point coord(x, y);
	return coord;
}

int calcDesiredOutput(point coord)
{
	//test equation y=x
	//false = below
	//true = above
	
	point p1(-11, -11); //p1 and p2 define ray fitting equation
	point p2(11, 11);

	double res = ((coord.x - p1.x)*(p2.y - p1.y)) - ((coord.y - p1.y)*(p2.x - p1.x));

	if (res > 0)
	{
		return 1;
	}
	return 0;

}

int main()
{
	//srand(time(NULL));
	//NeuralNet NN;
	//std::vector<int> values;
	//values.push_back(1); //output layer
	//values.push_back(1); //hidden layer
	//values.push_back(2); //input layer
	//NN.Init(values);
	//NN.SetBoolOut(true);
	//NN.SetLinOut(true);
	//NN.SetLearningRate(10);
	//int trainingEpochs = 10000; //number of epochs to run during training
	//int testingEpochs = 5;

	//std::string in;
	//int lastout = 0;
	//for (int i = 0; i < trainingEpochs; i++)
	//{
	//	
	//	std::cout << "Starting generation " << i << ". Press any key to continue...";
	//	//getline(std::cin, in);
	//	point coord = genRandomInput();
	//	while (calcDesiredOutput(coord) == lastout)
	//	{
	//		coord = genRandomInput();
	//	}
	//	lastout = calcDesiredOutput(coord);
	//	std::cout << "   coord = (" << coord.x << ", " << coord.y << ")" << std::endl;
	//	NN.SetIn(0, coord.x);
	//	NN.SetIn(1, coord.y);
	//	NN.SetDesiredOut(0, lastout); //set desired output to calculated output
	//  NN.Process()	
	//	double res = NN.OUT->neuronValues[0];
	//	std::cout << "    expected = " << lastout << std::endl;
	//	std::cout << "    epoch " << i << ": " << res << std::endl;
	//}
	//getline(std::cin, in);

	/*TEMPLATE FOR NN

	NeuralNet NN;
	int trainingEpochs;
	std::vector<int> values;
	//push_back values ouput layer first
	NN.Init(values)
	//SetBoolOut(bool)
	//SetLinOut(bool)
	NN.SetLearningRate();

	for(int ii = 0; ii < trainingEpochs; ii++)
	{
		std::vector<double> input = //gen input
		sd
		NN.SetIn

		
	*/
	
}

