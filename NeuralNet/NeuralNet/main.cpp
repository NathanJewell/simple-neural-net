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
	
	double x = rand() % 21 -10; //random number between -10 and 10?
	double y = rand() % 21 - 10;

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

	//double res = ((coord.x - p1.x)*(p2.y - p1.y)) - ((coord.y - p1.y)*(p2.x - p1.x));

	if (coord.y > coord.x)
	{
		if (coord.x > 0)
			return 1;
		else
			return 0;
	}
	else if (coord.y < coord.x)
	{
		if (coord.x > 0)
			return 0;
		else
			return 1;
	}
	else
	{
		return 1; //return true if the point is on the line
	}

}

int main()
{
	srand(time(NULL));
	NeuralNet NN;
	NN.Init(2, 1, 1);
	NN.SetBoolOut(true);

	int trainingEpochs = 10; //number of epochs to run during training
	int testingEpochs = 5;

	std::string in;

	for (int i = 0; i < trainingEpochs; i++)
	{
		
		std::cout << "Starting generation " << i << ". Press any key to continue...";
		//getline(std::cin, in);
		point coord = genRandomInput();
		std::cout << "   coord = (" << coord.x << ", " << coord.y << ")" << std::endl;
		NN.SetIn(0, coord.x);
		NN.SetIn(1, coord.y);
		NN.SetDesiredOut(0, calcDesiredOutput(coord)); //set desired output to calculated output
		NN.FeedForward(); //calculate neuron values
		NN.CalcError(); //calculate errors
		NN.BackPropogate(); //use errors to adjust weights
		double res = NN.GetOut(NN.GetMaxOutID());
		std::cout << "    expected = " << calcDesiredOutput(coord) << std::endl;
		std::cout << "    epoch " << i << ": " << res << std::endl;
	}
	getline(std::cin, in);
	
}

