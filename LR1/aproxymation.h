#ifndef APROXYMATION_H
#define APROXYMATION_H

#include <math.h>
#include <utility>
#include <vector>
#include <algorithm>

typedef std::pair<double, double> double_pair;

class CData {
  public:
    CData();
    CData(std::vector<double_pair> table);

    void Swap();
    void Sort();

    double_pair GetLine(int i);
    int FindNearest(double val);
    int GetSize() {return size;}
    int Bs(double val);
  private:
    int size;
    std::vector<double_pair> table;
};

double func(double x);

double solve(CData *data, int n, double x, int& left, int& right);

int bs(std::vector<double_pair> v, double val);

#endif // APROXYMATION_H
