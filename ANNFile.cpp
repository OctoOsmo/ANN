//#pragma once
#include "ANNClass.cpp"

class ANNFile
{
private:
	std::vector<std::vector<double> >x; // all training sequense

public:
	std::vector<std::vector<double> >GetInputVector(void)
	{
		return x;
	}

	int ReadInputFile(wchar_t *file_name) 
	{
		FILE *in; // input file
		if ((in = _wfopen(file_name, L"r")) == NULL) 
		{
			fprintf(stderr, "Cannot open input file.\n");
			return 1;
		}
		// open input vectors
		int input_size;
		fscanf(in, "%d", &input_size); // read  size of input vector
		double tmp;
		std::vector<double>tmp_vector;
		int j = 1;
		while (fscanf(in, "%lf", &tmp) != EOF)
		{
			tmp_vector.push_back(tmp);
			if (j == input_size)
			{
				ANN::Normalize(tmp_vector);
				x.push_back(tmp_vector);
				tmp_vector.clear();
				j = 0;
			}
			++j;
		}
		fclose(in);
		return 0;
	}

	int SaveWeights(std::vector<std::vector<double> > &w, wchar_t *file_name) 
	{
		FILE *out; // output file
		if ((out = _wfopen(file_name, L"w+")) == NULL)
		{
			fprintf(stderr, "Cannot open weights output file.\n");
			return 1;
		}
		int inputs_count, neurons_count;
		inputs_count = w.size();
		neurons_count = w[0].size();
		fprintf(out, "%d %d\n", inputs_count, neurons_count);
		// TODO: out of bounds exception
		for (int i = 0; i < inputs_count; ++i) {
			for (int j = 0; j < neurons_count; ++j) {
				fprintf(out, "%lf ", w[i][j]);
			}
			fprintf(out, "\n");
		}
		fclose(out);
		return 0;
	}

	int OpenWeights(std::vector<std::vector<double> > &w, wchar_t *file_name)
	{
		FILE *in; // input file
		if ((in = _wfopen(file_name, L"r")) == NULL) 
		{
			fprintf(stderr, "Cannot open weights file.\n");
			return 1;
		}
		unsigned int inputs_count, neurons_count;
		fscanf(in, "%d %d", &inputs_count, &neurons_count);
		double tmp;
		std::vector<double>tmp_vector;
		int j = 1;
		while (fscanf(in, "%lf", &tmp) != EOF) 
		{
			tmp_vector.push_back(tmp);
			if (j == neurons_count)
			{
				x.push_back(tmp_vector);
				tmp_vector.clear();
				j = 0;
			}
			++j;
		}
		fclose(in);
		return 0;
	}

	int SaveOutputFile(std::vector<std::vector<double> >&v, wchar_t *file_name)
	{
		FILE *out; // output file
		if ((out = _wfopen(file_name, L"w+")) == NULL)
		{
			fprintf(stderr, "Cannot open output file.\n");
			return 1;
		}
		int inputs_count, neurons_count;
		inputs_count = v.size();
		neurons_count = v[0].size();
		// TODO: out of bounds exception
		for (int i = 0; i < inputs_count; ++i) 
		{
			for (int j = 0; j < neurons_count; ++j) 
				fprintf(out, "%lf ", v[i][j]);			
			fprintf(out, "\n");
		}
		fclose(out);
		return 0;
	}
};
