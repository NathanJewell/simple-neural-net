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
	void FeedForward();
	void BackPropogate();
	void GetMaxOutID();
	void CalcError();
	void SetLearningRate(double rate);
	void SetLinOut(bool lin);
	//setmomentum()
	DumpData(string filename)
};