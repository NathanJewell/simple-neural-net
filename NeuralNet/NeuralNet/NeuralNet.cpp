#include "stdafx.h"
#include "NeuralNet.h"

void NeuralNet::Init(int numInNodes, int numHiddenNodes, int numOutNodes)
{
	//initialize input layer
	IN.numNodes = numInNodes;
	IN.numChildNodes = numHiddenNodes;
	IN.numParentNodes = 0;
	IN.Init(numInNodes, NULL, &HIDDEN);
	IN.RandomizeWeights();

	//initialize hidden layer
	HIDDEN.numNodes = numHiddenNodes;
	HIDDEN.numChildNodes = numOutNodes;
	HIDDEN.numParentNodes = numInNodes;
	HIDDEN.Init(numHiddenNodes, &IN, &OUT);
	HIDDEN.RandomizeWeights();

	//initialize output layer
	OUT.numNodes = numOutNodes;
	OUT.numChildNodes = 0;
	OUT.numParentNodes = numHiddenNodes;
	OUT.Init(numOutNodes, &HIDDEN, NULL);

}

void NeuralNet::SetIn(int i, double val)
{
	if ((i >= 0) && (i < IN.numNodes))
	{
		IN.neuronValues[i] = val;
	}
}

double NeuralNet::GetOut(int i)
{
	if ((i >= 0) && (i < OUT.numNodes))
	{
		return OUT.neuronValues[i];
	}

	return (double)INT_MAX;
}

void NeuralNet::SetDesiredOut(int i, double val)
{
	if ((i >= 0) && (i < OUT.numNodes))
	{
		OUT.desiredValues[i] = val;
	}
}

void NeuralNet::FeedForward() //calculate neuron values for each layer
{
	IN.CalcNeuronValues();
	HIDDEN.CalcNeuronValues();
	OUT.CalcNeuronValues();
}

void NeuralNet::BackPropogate()	//calculate errors and adjust weights for each layer
{
	OUT.CalcError();
	HIDDEN.CalcError();

	HIDDEN.AdjustWeights();
	IN.AdjustWeights();

}

int NeuralNet::GetMaxOutID() //get array index of output layer neuron with highest value
{
	double maxval;

	maxval = OUT.neuronValues[0];
	int id = 0;
	
	for (int i = 1; i < OUT.numNodes; i++)
	{
		if (OUT.neuronValues[i] > maxval)
		{
			maxval = OUT.neuronValues[i];
			id = i;
		}
	}

	return id;
}

double NeuralNet::CalcError() //calculate total error
{
	double error = 0;

	for (int i = 0; i < OUT.numNodes; i++)
	{
		error += pow(OUT.neuronValues[i] - OUT.desiredValues[i], 2);
	}

	error /= OUT.numNodes;

	return error;
}

void NeuralNet::SetLearningRate(double rate)
{
	IN.learningRate = rate;
	HIDDEN.learningRate = rate;
	OUT.learningRate = rate;
}

void NeuralNet::SetLinOut(bool lin)
{
	//IN.linearOut = lin;
	//HIDDEN.linearOut = lin;
	OUT.linearOut = true;
	OUT.boolOut = false;
}

void NeuralNet::SetBoolOut(bool out)
{
	OUT.linearOut = !out;
	OUT.boolOut = out;
}
//void NeuralNet::DumpData(string file)
//{
	//ignore this for now
//}

