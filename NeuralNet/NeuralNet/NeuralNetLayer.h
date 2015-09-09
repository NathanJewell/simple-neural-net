// NeuralNet.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <time.h>

class NeuralNetLayer
{
public:
	int numNodes;
	int numChildNodes;
	int numParentNodes;
	std::vector<std::vector<double> > weights;
	std::vector<std::vector<double> > deltaWeights;
	std::vector<double>  neuronValues;
	std::vector<double> desiredValues;
	std::vector<double> errors;
	std::vector<double> biasWeights;
	std::vector<double> biasValues;
	double learningRate;

	bool boolOut;

	NeuralNetLayer* parentLayer;
	NeuralNetLayer* childLayer;

	NeuralNetLayer();

	void Init();
	void RandomizeWeights();
	void CalcError();
	void AdjustWeights();
	void CalcNeuronValues();

};



