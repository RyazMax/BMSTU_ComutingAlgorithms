#include "aproxymation.h"

#include <QDebug>
#include <iostream>
#include <algorithm>

CData::CData() {
    this->size = 0;
    this->table = std::vector<double_pair>();
}

CData::CData(std::vector<double_pair> table) {
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

double solve(CData *data, double x, double &an, double &bn, double &cn, double &dn, int &line) {
    int n = data->GetSize() - 1;
    std::vector<double> ksi(n+2), eta(n+2);
    std::vector<double> h(n + 1);
    for (int i = 1; i <= n; ++i) {
        h[i] = data->GetLine(i).first - data->GetLine(i - 1).first;
    }
    ksi[2] = 0;
    eta[2] = 0;
    for (int i = 2; i <= n; ++i) {
        double A = h[i-1], B = -2 * (h[i-1] + h[i]), D = h[i], F = -3*((data->GetLine(i).second - data->GetLine(i-1).second)/h[i] - (data->GetLine(i-1).second - data->GetLine(i-2).second)/h[i-1]);
        ksi[i+1] = D / (B - A * ksi[i]);
        eta[i+1] = (A*eta[i] + F) / (B - A * ksi[i]);
    }

    std::vector<double> c(n+2);
    c[n+1] = 0;
    for (int i = n; i > 0; --i) {
        c[i] = ksi[i + 1] * c[i+1] + eta[i+1];
    }

    std::vector<double> a(n+1);
    std::vector<double> b(n+1);
    std::vector<double> d(n+1);
    for (int i = 1; i <= n; ++i) {
        a[i] = data->GetLine(i-1).second;
        d[i] = (c[i+1] - c[i]) / (3 * h[i]);
        b[i] = (data->GetLine(i).second - data->GetLine(i-1).second)/h[i] - (h[i] * (c[i+1] + 2 * c[i])) / 3;
    }

    double res = 0;
    double sub = x - data->GetLine(1).first;
    if (x < data->GetLine(0).first) {
        res = a[1] + b[1] * sub + c[1] * sub * sub + d[1] * sub * sub * sub;
        an = a[1];
        bn = b[1];
        cn = c[1];
        dn = d[1];
        line = 0;
    }
    sub = x - data->GetLine(n - 1).first;
    if (x >= data->GetLine(n).first) {
        res = a[n] + b[n] * sub + c[n] * sub * sub + d[n] * sub * sub * sub;
        an = a[n];
        bn = b[n];
        cn = c[n];
        dn = d[n];
        line = n - 1;
    }
    for (int i = 1; i <= n; ++i) {
        double sub = x - data->GetLine(i - 1).first;
        if (x >= data->GetLine(i - 1).first && x < data->GetLine(i).first) {
            res = a[i] + b[i] * sub + c[i] * sub * sub + d[i] * sub * sub * sub;
            an = a[i];
            bn = b[i];
            cn = c[i];
            dn = d[i];
            line = i -1;
            break;
        }
    }
    return res;
}

double_pair CData::GetLine(int i) {
    return this->table[i];
}
