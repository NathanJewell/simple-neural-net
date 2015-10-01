#ifndef NEURALNET_H
#define NEURALNET_H

#include "NeuralNetLayer.h"
#include <string.h>
#include <functional>

class NeuralNet
{
public:
	//make this more flexible later plz

	std::vector<NeuralNetLayer> LAYERS;//first layer is input second is output
	NeuralNetLayer * OUT;
	NeuralNetLayer * IN;

	void Init(std::vector<int> layerNodes);

	void addHiddenLayer(int numNodes);//add last layer first b/c ez
	void SetIn(int i, double val);
	void SetIn(std::vector<double> vals);
	double GetOut(int i);
	void SetDesiredOut(int i, double val);
	void SetDesiredOut(std::vector<double> vals);
	void FeedForward(); //calculate neuron values for each layer
	void BackPropogate(); //calculate errors and adjust weights for each layer
	int GetMaxOutID(); //get array index of output layer neuron with highest value
	double CalcError(); //calculate total error
	void SetLearningRate(double rate);
	void SetLinOut(bool lin);
	void SetBoolOut(bool out);

	void Process();//feed forward, calcerror, backprop

	bool inputSet, desiredSet;
	//setmomentum()
	//void DumpData(string filename);
};

#endif