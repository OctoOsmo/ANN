//#pragma once
#include "ANN.h"

class ANN
{
private:
	int inputs_count; // size of input vector
	int NC; // neurons count

	double a; // learning speed parameter
	double eps; // learning parameter

	// std::vector<double>y; // hidden layer output;

	inline double Summ(std::vector<double> &v)
	{
		double s = 0;
		for (unsigned int i = 0; i < v.size(); ++i)
			s += v[i];
		return (s);
	}

	inline double LogisticNeuron(std::vector<double> &in, std::vector<double>&w)
	{
		double y;
		y = 1 / (1 + exp(-Summ(in, w)));
		return (y);
	}

	inline double Summ(std::vector<double>&x, std::vector<double>&w) 
	{
		double sum = 0;
		for (unsigned int i = 0; i < x.size(); ++i)
			for (unsigned int j = 0; j < w.size(); ++j)
				sum += x[i] * w[j];
		return (sum);
	}

	inline void FillRandom(std::vector<double> &v) 
	{
		//randomize();
		srand(time(NULL));
		//printf("\n%d\n", time(NULL));
		for (unsigned int i = 0; i < v.size(); ++i)
			v[i] = ((double) (rand()%100)) / 100;
	}

public:
	std::vector<std::vector<double> >w; // weights matrix
	std::vector<std::vector<double> >x; // all input vectors
	std::vector<std::vector<double> >xout; // output of neural network

	ANN(int ic, double ac = 0.01, double epsc = 0.01, int NCc = 2) // constructor
	{ 
		a = ac; // learning speed parameter
		eps = epsc; // learning parameter
		NC =NCc; // number of neurons in hidden layer
		inputs_count = ic;
	}

	inline void FillWeightsRandom(std::vector<std::vector<double> > &v) 
	{
		v.resize(inputs_count);
		for (int i = 0; i < inputs_count; ++i) 
		{
			v[i].resize(NC);
			FillRandom(v[i]);
		}
	}

	static void PrintVector(std::vector<double> &v) // debug function
	{ 
		printf("\n");
		for (unsigned int i = 0; i < v.size(); ++i)
			printf("%lf ", v[i]);
		printf("\n");
	}

	void Network(std::vector<double> &in, std::vector<double> &out, std::vector<double> &y) 
	{
		// TODO: check for x and w non empty;
		// std::vector<double>y; // hidden layer output;
		y.clear();
		out.clear();
		out.resize(inputs_count);
		//printf("\nnet inputs count = %d\n", inputs_count);
		for (int i = 0; i < NC; ++i) 
		{
			y.push_back(LogisticNeuron(in, w[i]));
			for (int j = 0; j < inputs_count; ++j)
				out[j] += w[j][i] * y[i];
		}
	}

	double TrainVector(std::vector<double> &tr) 
	{
		double ay, dx = 0, e = 0;
		// alpha*y, difference betwen in and out values, epsilon(deviation)
		std::vector<double>y; // output of hidden layer
		std::vector<double>out; // network output
		Network(tr, out, y);
		for (int i = 0; i < NC; ++i) 
		{
			ay = a * y[i];
			for (unsigned int j = 0; j < tr.size(); ++j) 
			{
				dx = tr[j] - out[j];
				w[j][i] += ay * dx;
				e += fabs(dx);
			}
		}
		return e / tr.size();
	}

	void Train(std::vector<std::vector<double> >tr)
	{
		double tmp_e = 2;//, alpha = a;
		int count = 0;
		xout.resize(x.size());
		while ((tmp_e > eps) && (count < 20000)) 
		{
			tmp_e = 0;
			for (unsigned int i = 0; i < tr.size(); ++i) 			
				tmp_e += TrainVector(tr[i]);			
			++count;
			//a = 1/count;
			tmp_e /= (double) tr.size();
		}
		printf("\ncount =%d", count);
		//a = alpha;
	}

	static void Normalize(std::vector<double>&v) 
	{
		double min, max;
		min = max = v[0];
		// search for max and min values in vector
		for (unsigned int i = 1; i < v.size(); ++i)
			if (v[i] < min)
				min = v[i];
			else 
			{
				if (v[i] > max)
					max = v[i];
			}
			// normalization
			double div = max - min;
			for (unsigned int i = 0; i < v.size(); ++i) 
			{
				v[i] = ((v[i] - min) / div);
			}	
			ANN::PrintVector(v);
	}

	char* GetName()
	{
		return ("John Doe");
	}
};
