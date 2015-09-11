// stdafx.cpp : source file that includes just the standard includes
// NeuralNet.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "NeuralNet.cpp"
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

double genRandomInput()
{
	srand(time(NULL));
	double x = rand() % 21 -10; //random number between -10 and 10?
	double y = rand() % 21 - 10;

	double coord[2] = { x, y }; //xy coord of test point
	return coord;
}

bool checkOutput(bool output)
{

}

int main()
{
	NeuralNet NN;
	myNN.Init(2, 1, 1);

	int trainingEpochs = 10; //number of epochs to run during training
	int testingEpochs = 5;

	for (int i = 0; i < trainingEpochs; i++)
	{
		double coord[2] = genRandomInput();
		NN.SetLinOut(0, coord[0]);
		NN.SetIn
	}
	
}

