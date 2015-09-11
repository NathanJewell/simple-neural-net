#include "NeuralNetLayer.h"

NeuralNetLayer::NeuralNetLayer()
{
	parentLayer = NULL;
	childLayer = NULL;
	boolOut = false;
}

void NeuralNetLayer::Init(int NumNodes, NeuralNetLayer* parent, NeuralNetLayer* child)
{
	for (int i = 0; i < numNodes; i++)
	{
		neuronValues.push_back(0);
		desiredValues.push_back(0);
		errors.push_back(0);
	}

	//initializing everything with 0's
	parentLayer = parent;
	childLayer = child;

	if (child != NULL)
	{
		for (int i = 0; i < numNodes; i++)
		{
			std::vector<double> tmp;
			for (int j = 0; j < numChildNodes; j++)
			{
				tmp.push_back(0);
			}
			weights.push_back(tmp);
			deltaWeights.push_back(tmp);
		}

		for (int i; i < numChildNodes)
		{
			biasValues.push_back(0);
			biasWeights.push_back(0);
		}

		for (int i = 0; i < NumNodes; i++)
		{
			weights.push_back(0);
			deltaWeights.push_back(0);
		}
	}
	else {
		//this stuff only matters if something is feeding into the layer (ie. not input layer)
		weights = NULL;
		biasValues = NULL;
		biasWeights = NULL;
		deltaWeights = NULL;

	}
	
	if (childLayer != NULL) //all biases start at the same value
	{
		for (int i; i < numChildNodes; i++)
		{
			biasValues[i] = -1;
			biasWeights[i] = 0;
		}
	}
}

void NeuralNetLayer::RandomizeWeights()
{
	int min = 0;
	int max = 200;
	int number;

	srand(time(NULL));

	for (int i = 0; i < numNodes; i++)
	{
		for (int j = 0; j < numChildNodes; j++)
		{
			number = (((abs(rand()) % max - min + 1)) + min);

			if (number > max)
				number = max;
			if (number < min)
				number = min;

			weights[i][j] = number / 100.0f - 1;
		}
	}
	
	for (i = 0; i < numChildNodes; i++)
	{
		number = (((abs(rand()) % max - min + 1)) + min);

		if (number > max)
			number = max;

		if (number < min)
			number = min;

		biasWeights[i] = number / 100.0f - 1;
	}

}

void NeuralNetLayer::CalcNeuronValues()
{
	if (parentLayer != NULL)
	{
		//do this for all nodes in layer
		for (i = 0; i < numNodes; i++)
		{
			x = 0;
			//add the values for all child nodes (j) times their respective weights together to recieve the total
			for (j = 0; j < numParentNodes; j++)
			{
				x += parentLayer->neuronValues[j] * parentLayer->weights[i][j]; 
			}

			x += parentLayer->biasValues[i] * parentLayer->biasWeights[i]; //add weighted bias to total

			if ((childLayer == NULL && linOut))
				neuronValues[i] = x; //if the activation is linu
			else // HARDCODED FUNCTION HERE BEWARNED !! <<---- should change that
				neuronValues[j] = 1.0f / (1 + exp(-x));	//use the activation function to produce a final value

		}
	}
}

void NeuralNetLayer::CalcError()
{
	double sum;

	if (childLayer == NULL) //output layer errors
	{
		for (i = 0; i < numNodes; i++) //calculate an error for each node (expected-desired) 
		{
			errors[i] = (desiredValues[i] - neuronValues[i]) * neuronValues[i] * (1.0f - neuronValues[i]);
		}
	}
	else if (parentLayer == NULL) //no errors for input layer
	{
		for (int i = 0; i < numNodes; i++)
		{
			errors[i] = 0;
		}
	}
	else //calculate errors for all hidden layers
	{
		//cycling through all possible combinations of one node and one child node to produce errors for each connection
		for (int i = 0; i < numNodes; i++)
		{
			sum = 0;
			for (j = 0; j < numChildNodes; j++)
			{
				sum += childLayer->errors[j] * weights[i][j];
			}
			errors[i] = sum * neuronValues[i] * (1.0f - neuronValues[i]); //i need to look up/find out why this needs to happen
		}
	}
}

void NeuralNetLayer::AdjustWeights()
{
	double dw; //delta weight

	if (childLayer != NULL) //isn't output layer
	{
		//for each neuron i, cycle through all of the child neurons j
		//find a delta weight dw and then apply that change to the weight corresponding to [i][j] 
		for (int i = 0; i < numNodes; i++)
		{
			for (j = 0; j < numChildNodes; j++) 
			{
				dw = learningRate * childLayer->errors[j] * neuronValues[i];

				//momentum here

				//else
				weights[i][j] += dw;
			}
		}

		//similarly apply a change to the weighting of each bias based on the error
		for (int i = 0; i < numChildNodes; i++)
		{
			biasWeights[j] += learningRate * childLayer->errors[j] * biasValues[j];

		}
	}

	


}