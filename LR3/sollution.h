#ifndef SOLLUTION_H
#define SOLLUTION_H

#include <vector>
#include <utility>
#include <math.h>

struct triple_t {
    double x;
    double y;
    double z;
};

struct pair_t {
    double x;
    double y;
};

typedef std::vector<std::vector<triple_t>> data_t;

double func(double x, double y);
data_t generate(double xFrom, double yFrom, double xTo, double yTo, double xStep, double yStep);
double solve_all(data_t data, double x, double y, int nx, int ny, int &r1, int &c1, int &r2, int &c2);
double solve(std::vector<pair_t> v, double x, int left, int right);
std::vector<pair_t> get_line(data_t data, int i);
std::vector<pair_t> get_col(data_t data, int i);
int bs(std::vector<pair_t> v, double x);
int findNearest(std::vector<pair_t> v, double x);

#endif // SOLLUTION_H
