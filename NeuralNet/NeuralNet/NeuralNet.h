#include "NeuralNetLayer.h"
#include <string.h>

class NeuralNet
{
public:
	//make this more flexible later plz
	NeuralNetLayer IN;
	NeuralNetLayer HIDDEN;
	NeuralNetLayer OUT;

	void Init(int numInNodes, int numHiddenNodes, int numOutNodes)

	void SetIn(int i, double val);
	double GetOut(int i);
	void SetDesiredOut(int i, double val);
	void FeedForward(); //calculate neuron values for each layer
	void BackPropogate(); //calculate errors and adjust weights for each layer
	void GetMaxOutID(); //get array index of output layer neuron with highest value
	void CalcError(); //calculate total error
	void SetLearningRate(double rate);
	void SetLinOut(bool lin);
	//setmomentum()
	void DumpData(string filename)
};