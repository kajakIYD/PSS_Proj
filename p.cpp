#include "p.h"

P::P(double kr, Generator *generator)
{
    this->kr = kr;
    s_generator = generator;
}


P::~P()
{
}

//Useless
//void P::SetSP(double SP)
//{
//    this->SP=SP;
//}

double P::GetU()
{
    return u;
}

double P::GetSP()
{
    return this->SP;
}


void P::Update(double y)
{
    this->Simulate_step(y);
}


double P::Simulate_step(double y) //Wlasnie tu ma byc zero, bo wart zadana ma byc w regulatorze ogarniana a z kolei regulator ma byc powiadamiany z arx'a?
{
    //Generate SP
    SP=s_generator->CalculateSignal(time);

    //Calculate error
    e = SP-y;

    //Calculate control
    u = kr*e;

    return u;

}
