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
std::vector<std::vector<double> >x(0);
std::vector<std::vector<double> >w(0);
FILE *in;
FILE *out;

// ---------------------------------------------------------------------------
void normalize(std::vector<double> &v) {
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
inline double summ(std::vector<double> &x, std::vector<double> &w) {
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
			x.push_back(tmp_vector);
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
void FillVectorRandom(std::vector<std::vector<double> > &v, int &NC, int &HNC) {
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
	int NC, HNC; // neuron counts in first and second levels respectively
	if (x.size() > 0) {
		NC = x[0].size();
		HNC = FormMain->TrackBarNeuronCount->Position;
		FillVectorRandom(w, NC, HNC);
	}
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

