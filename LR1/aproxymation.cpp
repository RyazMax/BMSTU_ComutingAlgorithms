#include "aproxymation.h"

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

double func(double x) {
    return x * x;
}

double solve(CData *data, int n, double x) {
    return x;
}

double_pair CData::GetLine(int i) {
    return this->table[i];
}


