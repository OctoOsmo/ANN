// ---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#pragma hdrstop

#include "MainUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;

// ---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------
int NC, HNC;//input neurons count and hidden neurons count respectively
std::vector<std::vector<double> >x(0);//all training sequense
std::vector<std::vector<double> >w(0);//weights matrix
std::vector<double> y1;//first logistic layer output
std::vector<double> y2;//second logistic layer output
std::vector<double> yh;//hidden layer output;
FILE *in;//input file
FILE *out;//output file

// ---------------------------------------------------------------------------
void Normalize(std::vector<double> &v) {
	int max = INT_MIN;
	int min = INT_MAX;
	for (unsigned int i = 0; i < v.size(); ++i)
		if (v[i] < min) {
			min = v[i];
		}
		else {
			if (v[i] > max)
				max = v[i];
		}
	for (unsigned int i = 0; i < v.size(); ++i)
		v[i] = (v[i] - min) - (max - min);
	double div = max - min;
	for (unsigned int i = 0; i < v.size(); ++i) {
		v[i] = (v[i] - min) / div;
	}
}
// ---------------------------------------------------------------------------
inline double Summ(std::vector<double> &v)
{
	double s = 0;
	for(unsigned int i = 0; i < v.size(); ++i)
		s += v[i];
	return(s);
}
// ---------------------------------------------------------------------------
inline double Summ(std::vector<double> &x, std::vector<double> &w) {
	double sum = 0;
	for (unsigned int i = 0; i < x.size(); ++i)
		for (unsigned int j = 0; j < w.size(); ++j)
			sum += x[i] * w[j];
	return (sum);
}

// ---------------------------------------------------------------------------
inline double LogisticNeuron(double &sum) {
	double y;
	y = 1 / (1 + exp(-sum));
	return (y);
}

// ---------------------------------------------------------------------------
inline double CompressNeuron(int &k, int &L, int &m, double &sum) {
	double tanh_sum = 0;
	for (int i = 1; i < L; ++i) {
		tanh_sum += tanh(k * sum - i / L);
	}
	double f;
	f = 1 / 2 + 1 / (2 * (m - 1)) * tanh_sum;
	return (f);
}

// ---------------------------------------------------------------------------
void ReadInputFile(const wchar_t *file_name) {
	in = _wfopen(file_name, L"r");
	// open input vectors
	int input_size;
	fscanf(in, "%d", &input_size);
	double tmp;
	std::vector<double>tmp_vector;
	int j = 1;
	while (fscanf(in, "%lf", &tmp) != EOF) {
		tmp_vector.push_back(tmp);
		if (j == input_size) {
			Normalize(tmp_vector);
			x.push_back(tmp_vector);
			tmp_vector.clear();
			j = 0;
		}
		++j;
	}

	FormMain->TrackBarNeuronCount->Max = input_size;
	FormMain->TrackBarNeuronCount->Min = 1;
	FormMain->TrackBarNeuronCount->Position = (input_size - 1) / 2;
}

// ---------------------------------------------------------------------------
void FillRandom(std::vector<double> &v) {
	Randomize();
	for (unsigned int i = 0; i < v.size(); ++i)
		v[i] = ((double) random(64)) / 64;
}

// ---------------------------------------------------------------------------
void FillVectorRandom(std::vector<std::vector<double> > &v) {
	Randomize();
	v.resize(NC);
	for (int i = 0; i < NC; ++i) {
		v[i].resize(HNC);
		for (int j = 0; j < HNC; ++j)
			v[i][j] = ((double) random(64)) / 64;
	}
}

// ---------------------------------------------------------------------------
void InitializeWeights(void) {
	if (x.size() > 0) {
		NC = x[0].size();//first level neuron count
		HNC = FormMain->TrackBarNeuronCount->Position;//Hidden layer neuron count
		FillVectorRandom(w);
	}
}

// ---------------------------------------------------------------------------
void Network()
{
	y1.clear();
	y2.clear();
	yh.clear();
	//compute first level output
	double s;
	for(int i = 0; i < NC; ++i)
	{
		s = Summ(x[i]);
//		s = LogisticNeuron(Summ(x[i]));
//		y1.push_back(LogisticNeuron(Summ(x[i])));

	}
}
// ---------------------------------------------------------------------------
void Train(void)
{

}
// ---------------------------------------------------------------------------
void __fastcall TFormMain::NOpenClick(TObject *Sender) {
	if (FormMain->OpenInputDialog->Execute()) {
		ReadInputFile(OpenInputDialog->FileName.w_str());
	}
	InitializeWeights();
}

// ---------------------------------------------------------------------------
void __fastcall TFormMain::TrackBarNeuronCountChange(TObject *Sender) {
	LabelNeuronCount->Caption = "Количество нейронов скрытого слоя = " +
		IntToStr(FormMain->TrackBarNeuronCount->Position);
	InitializeWeights();
}
// ---------------------------------------------------------------------------
void __fastcall TFormMain::NExitClick(TObject *Sender)
{
FormMain->Close();
}
//---------------------------------------------------------------------------

