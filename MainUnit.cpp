//#include "ANN.h"
#include "MainUnit.h"

int main (void)
{
	printf("hi\n");
	ANNFile input;
	input.ReadInputFile("in.txt");
	ANN net(input.GetInputVector()[0].size(), 0.5, 0.01, 4);
	std::vector<double> y, xo;//create temp vectors
	net.FillWeightsRandom(net.w);
	net.x = input.GetInputVector();
	net.Train(net.x);	
	net.xout.clear();
	//fill xout with network output
	for(unsigned int i = 0; i < net.x.size(); ++i)
	{
		net.Network(net.x[i], xo, y);
		net.xout.push_back(xo);
		net.PrintVector(xo);
	}	
	//net.xout[0]=xo;
	//printf("\nsize = %d\n", net.xout[0].size());
	input.SaveWeights(net.w, "w.txt");
	input.SaveOutputFile(net.xout, "out.txt");
	getchar();
}