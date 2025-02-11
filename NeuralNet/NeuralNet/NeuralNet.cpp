#include "stdafx.h"
#include "NeuralNet.h"

//first and last value of layer nodes are in and out layer node #'s respectively
void NeuralNet::Init(std::vector<int> layerNodes)
{
	desiredSet = false;
	inputSet = false;
	//initialize input layer
	NeuralNetLayer in;
	NeuralNetLayer out;

	out.numNodes = layerNodes[layerNodes.size()-1];

	LAYERS.push_back(out); //last layer first

	//initialize hidden layers adding the last layer first
	for (int ii = layerNodes.size()-2; ii > 0; ii--)
	{
		addHiddenLayer(layerNodes[ii]);
	}

	in.numNodes = layerNodes[0];
	in.numChildNodes = LAYERS[1].numNodes;
	in.numParentNodes = 0;

	LAYERS.push_back(in);

	IN = &LAYERS[0];
	OUT = &LAYERS[LAYERS.size() - 1];

	//initialize input layer
	IN->numParentNodes = 0;
	IN->numChildNodes = LAYERS[1].numNodes;
	IN->Init(layerNodes[0], NULL, &LAYERS[0]);
	IN->RandomizeWeights();

	//initialize all hidden layers
	for (int ii = 1; ii < LAYERS.size()-1; ii++)
	{
		LAYERS[ii].numChildNodes = LAYERS[ii+1].numNodes;
		LAYERS[ii].numParentNodes = LAYERS[ii-1].numNodes;
		LAYERS[ii].Init(layerNodes[ii], &LAYERS[ii-1], &LAYERS[ii+1]);
		LAYERS[ii].RandomizeWeights();
	}

	//initialize output layer
	OUT->numChildNodes = 0;
	OUT->numParentNodes = layerNodes[layerNodes.size() - 2];//number of nodes in the last hidden layer
	OUT->Init(layerNodes[layerNodes.size()-1], &LAYERS[LAYERS.size() - 2], NULL);
	OUT->RandomizeWeights();



}

void NeuralNet::addHiddenLayer(int numNodes)
{
	NeuralNetLayer aHidden;
	aHidden.numNodes = numNodes;

	LAYERS.push_back(aHidden);
}

void NeuralNet::SetIn(int i, double val)
{
	if ((i >= 0) && (i < IN->numNodes))
	{
		IN->neuronValues[i] = val;
	}
}

void NeuralNet::SetIn(std::vector<double> vals)
{
	IN->neuronValues = vals;
}

double NeuralNet::GetOut(int i)
{
	if ((i >= 0) && (i < OUT->numNodes))
	{
		return OUT->neuronValues[i];
	}

	return (double)INT_MAX;
}

void NeuralNet::SetDesiredOut(int i, double val)
{
	if ((i >= 0) && (i < OUT->numNodes))
	{
		OUT->desiredValues[i] = val;
	}
}

void NeuralNet::SetDesiredOut(std::vector<double> vals)
{
	OUT->desiredValues = vals;
}

void NeuralNet::FeedForward() //calculate neuron values for each layer
{
	IN->CalcNeuronValues();
	
	for (int i = 1; i < LAYERS.size()-1; i++)//cycle through all hidden layers
	{
		LAYERS[i].CalcNeuronValues();
	}

	OUT->CalcNeuronValues();
}

void NeuralNet::BackPropogate()	//calculate errors and adjust weights for each layer
{
	OUT->CalcError();

	for (int i = LAYERS.size()-2; i < 0; i--)//cycle through all hidden layers backwards
	{
		LAYERS[i].CalcError();
	}
	//no errors for the input layer


	//no weights for the output layer
		for (int i = 1; i < LAYERS.size()-1; i++)//cycle through all hidden layers 
	{
		LAYERS[i].AdjustWeights();
	}

	IN->AdjustWeights();

}

int NeuralNet::GetMaxOutID() //get array index of output layer neuron with highest value
{
	double maxval;

	maxval = OUT->neuronValues[0];
	int id = 0;
	
	for (int i = 1; i < OUT->numNodes; i++)
	{
		if (OUT->neuronValues[i] > maxval)
		{
			maxval = OUT->neuronValues[i];
			id = i;
		}
	}

	return id;
}

double NeuralNet::CalcError() //calculate total error
{
	double error = 0;

	for (int i = 0; i < OUT->numNodes; i++)
	{
		error += pow(OUT->neuronValues[i] - OUT->desiredValues[i], 2);
	}

	error /= OUT->numNodes;

	return error;
}

void NeuralNet::SetLearningRate(double rate)
{
	IN->learningRate = rate;                           
	for (int i = 0; i < LAYERS.size(); i++)
	{
		LAYERS[i].learningRate = rate;
	}
	OUT->learningRate = rate;
}

void NeuralNet::SetLinOut(bool lin)
{
	//IN->linearOut = lin;
	//HIDDEN.linearOut = lin;
	LAYERS[LAYERS.size() - 1].linearOut = true;
	LAYERS[LAYERS.size() - 1].boolOut = true;
}

void NeuralNet::SetBoolOut(bool out)
{
	LAYERS[LAYERS.size() - 1].linearOut = !out;
	LAYERS[LAYERS.size() - 1].boolOut = out;
}
void NeuralNet::Process()
{
	FeedForward();
	CalcError();
	BackPropogate();
}
//void NeuralNet::DumpData(string file)
//{
	//ignore this for now
//}


