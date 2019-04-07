#ifndef DATAREADER_H
#define DATAREADER_H

#include <QString>
#include <vector>

struct data_t {
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> w;
};

class DataReader
{
public:
    DataReader();
    static data_t readFromFile(QString fileName);
};

#endif // DATAREADER_H
