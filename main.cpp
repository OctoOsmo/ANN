#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

void normalize(vector <int> &v)
{
    int max = INT_MIN;
    int min = INT_MAX;
    for(unsigned int i = 0; i < v.size(); ++i)
        if(v[i] < min)
        {
            min = v[i];
        }else
        {
            if(v[i] > max) max = v[i];
        }
    for(unsigned int i = 0; i < v.size(); ++i)
        v[i] = (v[i] - min) - (max - min);

}

int summ(vector <int> &x, vector <int> &w)
{
    int sum = 0;
    for(unsigned int i = 0; i < x.size(); ++i)
        for(unsigned int j = 0; j < w.size(); ++j)
            sum += x[i]*w[j];
    return sum;
}

int main()
{
    vector <int> x;
    vector <vector <int> > w;
    cout << "Hello World1" << endl;
    return 0;
}

