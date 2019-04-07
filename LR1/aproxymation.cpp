#include "aproxymation.h"

#include <QDebug>
#include <iostream>
#include <algorithm>

CData::CData() {
    this->size = 0;
    this->table = std::vector<double_pair>();
}

CData::CData(std::vector<double_pair> table) {
    // Возможно здесь неправильно
    this->table = table;
    this->size = table.size();
}

void CData::Sort() {
    std::sort(this->table.begin(), this->table.end());
}

void CData::Swap() {
    for (auto it = this->table.begin(); it < this->table.end(); ++it) {
        double tmp = it->first;
        it->first = it->second;
        it->second = tmp;
    }
}

int CData::FindNearest(double val) {
    int ind = bs(this->table, val);
    if (ind + 1 < this->table.size()) {
        if (fabs(this->table[ind].first - val) > fabs(this->table[ind + 1].first - val)) {
            return ind + 1;
        }
    }
    return ind;
}

double func(double x) {
    return x * x;
}

double solve(CData *data, int n, double x, int &left, int &right) {
    left = 0;
    right = 0;
    int bsFound = data->Bs(x);
    int nearest = data->FindNearest(x);
    n++;
    if (n & 1) {
        left = std::max(0, nearest - (n / 2));
        right = std::min(data->GetSize() - 1, nearest + std::max(n / 2, n - (nearest - left + 1)));
        if (right - left + 1 < n) {
            left = right - n + 1;
        }
    } else {
        left = std::max(0, bsFound - (n / 2) + 1);
        right = std::min(data->GetSize() - 1, bsFound + std::max(n / 2, n - (bsFound - left + 1)));
        if (right - left + 1 < n) {
            left = right - n + 1;
        }
    }

    std::vector<std::vector<double>> sumTable(data->GetSize());
    for (int i = left; i <= right; ++i) {
        sumTable[i - left] = std::vector<double>(n + 1);
        double_pair pair = data->GetLine(i);
        sumTable[i - left][0] = pair.first;
        sumTable[i - left][1] = pair.second;
    }

    for (int i = 2; i < n + 1; ++i) {
        for (int j = 0; j < (right - left) - (i - 2); ++j) {
            sumTable[j][i] = (sumTable[j][i - 1] - sumTable[j+1][i-1]) / (sumTable[j][0] - sumTable[j + (i-1)][0]);
        }
    }

    double result = 0;
    double mulPart = 1;
    for (int i = 1; i < n + 1; ++i) {
        result += mulPart * sumTable[0][i];
        mulPart *= (x - sumTable[i - 1][0]);
    }
    return result;
}

double_pair CData::GetLine(int i) {
    return this->table[i];
}

int CData::Bs(double val) {
    return bs(this->table, val);
}

int bs(std::vector<double_pair> v, double val) {
    int right = v.size();
    int left = 0;
    while (right - left > 1) {
        int m = (right + left) / 2;
        if (v[m].first > val) {
            right = m;
        } else  {
            left = m;
        }
    }
    return left;
}


