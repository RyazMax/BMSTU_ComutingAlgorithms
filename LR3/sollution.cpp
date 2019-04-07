#include "sollution.h"

double func(double x, double y)
{
    return x*x + y*y;
}

data_t generate(double xFrom, double yFrom, double xTo, double yTo, double xStep, double yStep) {
    double x = xFrom;
    double y = yFrom;
    data_t res;

    while (x < xTo) {
        std::vector<triple_t> line;
        y = yFrom;
        while (y < yTo) {
            line.push_back(triple_t{x, y, func(x, y)});
            y += yStep;
        }
        res.push_back(line);
        x += xStep;
    }
    return res;

}

double solve_all(data_t data, double x, double y, int nx, int ny, int &r1, int &c1, int &r2, int &c2)
{
    int left = 0, right = 0;
    int bsFound = bs(get_line(data, 0), y);
    int nearest = findNearest(get_line(data, 0), y);
    ny++;
    if (ny & 1) {
        left = std::max(0, nearest - (ny / 2));
        right = std::min(int(data[0].size()) - 1, nearest + std::max(ny / 2, ny - (nearest - left + 1)));
        if (right - left + 1 < ny) {
            left = right - ny + 1;
        }
    } else {
        left = std::max(0, bsFound - (ny / 2) + 1);
        right = std::min(int(data[0].size()) - 1, bsFound + std::max(ny / 2, ny - (bsFound - left + 1)));
        if (right - left + 1     < ny) {
            left = right - ny + 1;
        }
    }
    c1 = left;
    c2 = right;

    int up = 0, bottom = 0;
    bsFound = bs(get_col(data, 0), x);
    nearest = findNearest(get_col(data, 0), x);
    nx++;
    if (nx & 1) {
        up = std::max(0, nearest - (nx / 2));
        bottom = std::min(int(data.size()) - 1, nearest + std::max(nx / 2, nx - (nearest - up + 1)));
        if (bottom - up + 1 < nx) {
            up = bottom - nx + 1;
        }
    } else {
        up = std::max(0, bsFound - (nx / 2) + 1);
        bottom = std::min(int(data.size()) - 1, bsFound + std::max(nx / 2, nx - (bsFound - up + 1)));
        if (bottom - up + 1 < nx) {
            up = bottom - nx + 1;
        }
    }
    r1 = up;
    r2 = bottom;

    std::vector<pair_t> toRes;
    for (int i = up; i <= bottom; ++i) {
        toRes.push_back(pair_t{data[i][0].x, solve(get_line(data, i), y, left, right)});
    }

    return solve(toRes, x, 0, toRes.size() - 1);
}

double solve(std::vector<pair_t> v, double x, int left, int right)
{
    std::vector<std::vector<double>> sumTable(v.size());
    for (int i = left; i <= right; ++i) {
        sumTable[i - left] = std::vector<double>(right - left + 2);
        sumTable[i - left][0] = v[i].x;
        sumTable[i - left][1] = v[i].y;
    }

    for (int i = 2; i < right - left + 2; ++i) {
        for (int j = 0; j < (right - left) - (i - 2); ++j) {
            sumTable[j][i] = (sumTable[j][i - 1] - sumTable[j+1][i-1]) / (sumTable[j][0] - sumTable[j + (i-1)][0]);
        }
    }

    double result = 0;
    double mulPart = 1;
    for (int i = 1; i < right - left + 2; ++i) {
        result += mulPart * sumTable[0][i];
        mulPart *= (x - sumTable[i - 1][0]);
    }
    return result;
}

std::vector<pair_t> get_line(data_t data, int i)
{
    std::vector<pair_t> res;
    for (int j = 0; j < data[i].size(); ++j) {
        res.push_back(pair_t{data[i][j].y, data[i][j].z});
    }
    return res;
}

std::vector<pair_t> get_col(data_t data, int i)
{
    std::vector<pair_t> res;
    for (int j = 0; j < data.size(); ++j) {
        res.push_back(pair_t{data[j][i].x, data[j][i].z});
    }
    return res;
}

int bs(std::vector<pair_t> v, double val)
{
    int right = v.size();
    int left = 0;
    while (right - left > 1) {
        int m = (right + left) / 2;
        if (v[m].x > val) {
            right = m;
        } else  {
            left = m;
        }
    }
    return left;
}

int findNearest(std::vector<pair_t> v, double val)
{
    int ind = bs(v, val);
    if (ind + 1 < v.size()) {
        if (fabs(v[ind].x - val) > fabs(v[ind + 1].x - val)) {
            return ind + 1;
        }
    }
    return ind;
}

