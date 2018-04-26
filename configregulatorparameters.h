#ifndef CONFIGREGULATORPARAMETERS_H
#define CONFIGREGULATORPARAMETERS_H
#include <QVector>
#include <QFile>
#include <QXmlStreamWriter>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class configRegulatorParameters
{
public:
    configRegulatorParameters(string filePath);
    ~configRegulatorParameters();
    void WriteToFile(string str);
private:
    ofstream myfile;

};

#endif // CONFIGREGULATORPARAMETERS_H
