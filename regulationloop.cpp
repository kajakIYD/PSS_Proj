#include "regulationloop.h"

RegulationLoop::~RegulationLoop()
{
    //Close file
    s_file.close();

    delete s_reg;
}

RegulationLoop::RegulationLoop(SISO *siso, Regulator *regulator, Generator *generator, QString currentRegType) :
    s_siso(siso),
    s_reg(regulator),
    s_generator(generator),
    s_currentRegType(currentRegType)
{
   //Open file
   s_file.open( "E:\\Qt\\Projects\\PSS_New\\PSS\\Config\\Meas.txt", std::ios::out );
}

double RegulationLoop::Simulate_step(double input)
{
    s_reg->SetTime(this->time);
    s_input = s_reg->Simulate_step(input);
    //s_output instead inout
    s_output = s_siso->Simulate_step(s_input);
    UpdatePlot();
    SaveToFile();
    return s_output;
}

void RegulationLoop::UpdatePlot()
{
    Notify(s_input, s_output);
}

void RegulationLoop::SaveToFile()
{
    //Add new line to opened file
   if( s_file.good() == true )
   {
       s_file << "y=" << s_output << ";" << "u=" << s_input << "\n";
       s_file.flush();
   }
}

//instead of multiple parameters use map, check exceptions
void RegulationLoop::ChangeRegParameters(double kr, double Ti, double Td, double N, double b, double max_u, double min_u, double alpha/*and so on?...*/)
{
    //Determine type of regulator

    if (s_currentRegType=="P")
    {
       delete s_reg;
       s_reg = new P(kr, s_generator);
    }
    if (s_currentRegType=="PID")
    {
       delete s_reg;
       s_reg = new PID(kr, Ti, Td, N, b, max_u, min_u, s_generator);
    }
   //Other regulators in the same way?
}

void RegulationLoop::ChangeRegulator(QString s)
{
    //1. create regulator to temp
    //2. check ifs
    //3. delete old
    Regulator *tempReg;;
    tempReg = nullptr;
    s_currentRegType = s;
    if (s == "P")
    {
        tempReg = new  P;
    }
    if (s == "PI")
    {
        //tempReg = new  PI;
    }
    if (s == "PID")
    {
        //tempReg = new  PID;
    }
    if (s == "GPC")
    {
        //tempReg = new  GPC;
    }
    if (tempReg!=nullptr)
    {
        delete s_reg;
        s_reg = tempReg;
        ChangeRegParameters(0,0,0,0,0,0,0,0);
    }
    else
    {

    }
}


double RegulationLoop::GetOutput()
{
    return s_output;
}
