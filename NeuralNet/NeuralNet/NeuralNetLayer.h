// NeuralNet.cpp : Defines the entry point for the console application.
//
#ifndef NEURALNETLAYER_H
#define NEURALNETLAYER_H
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
	bool linearOut;
	
	NeuralNetLayer* parentLayer;
	NeuralNetLayer* childLayer;

	NeuralNetLayer();

	void Init(int nodes, NeuralNetLayer* parent, NeuralNetLayer* child);
	void RandomizeWeights();
	void CalcError();
	void AdjustWeights();
	void CalcNeuronValues();

};

#endif


