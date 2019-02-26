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
    int GetSize() {return size;}
  private:
    int size;
    std::vector<double_pair> table;
};

double func(double x);

double solve(CData *data, int n, double x);

#endif // APROXYMATION_H
