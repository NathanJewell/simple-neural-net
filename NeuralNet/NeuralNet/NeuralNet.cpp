#include "NeuralNet.h"

void NeuralNet::Init(int numInNodes, int numHiddenNodes, int numOutNodes)
{
	IN.numNodes = numInNodees;
	IN.numChildNodes = numHiddenNodes;
	IN.numParentNodes = 0;
	IN.Init(numInNodes, NULL &HIDDEN);
	IN.RandomizeWeights();

	HIDDEN.numNodes = numHiddenNodes;
	HIDDEN.numChildNodes = numOutNodes;
	HIDDEN.numParentNodes = numInNodes;
	HIDDEN.Init(numHiddenNodes, &IN, &OUT);
	HIDDEN.RandomizeWeights();

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

void NeuralNet::FeedForward()
{
	IN.CalcNeuronValues();
	HIDDEN.CalcNeuronValues();
	OUT.CalcNeuronValues();
}

void NeuralNet::BackPropogate()
{
	OUT.CalcError();
	HIDDEN.CalcError();

	HIDDEN.AdjustWeights();
	OUT.AdjustWeights();
}

int NeuralNet::GetMaxOutID()
{
	int i, id;
	double maxval;

	maxval = OUT.neuronValues[0];
	id = 0;
	
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

double NeuralNet::CalcError()
{
	double error = 0;

	for (int i = 0; i < OUT.numNodes; i++)
	{
		error += pow(OUT.neuronValues)
	}
}