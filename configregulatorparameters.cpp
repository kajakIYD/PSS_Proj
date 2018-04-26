#include "configregulatorparameters.h"

configRegulatorParameters::configRegulatorParameters(string filePath)
{
    myfile.open (filePath);

}


void configRegulatorParameters::WriteToFile(string str)
{
    myfile << str;
}


configRegulatorParameters::~configRegulatorParameters()
{
    myfile.close();
}


