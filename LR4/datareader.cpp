#include "datareader.h"

DataReader::DataReader()
{
}

data_t DataReader::readFromFile(QString fileName) {
    data_t res;
    res.x.push_back(100);
    res.y.push_back(200);
    res.w.push_back(300);
    return res;
}
