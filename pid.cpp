#include "pid.h"


PID::PID()
{

}

PID::PID(double kr, double Ti, double Td, double N, double b, double max_u, double min_u, Generator *generator)
{
    try
    {
        if (kr>0 && Ti>0 && Td>0 && N>0 && b>0 && b<=1)
        {
            this->kr = kr;
            this->Ti = Ti;
            this->Td = Td;
            this->N = N;
            this->b = b;
        }
        else
        {
            string ex = "Regulator parameters must be positive!";
            throw ex;
        }
        if (max_u>min_u)
        {
            this->max_u  = max_u;
            this->min_u  = min_u;
        }
        else
        {
            string ex = "Maximum control should be greater than minimum control!";
        }

    }
    catch (string ex)
    {
        this->kr = 1;
        this->Ti = 1;
        this->Td = 1;
        this->N = 1;
        this->b = 1;
        this->max_u = 1;
        this->min_u=0;
    }
    s_generator = generator;
    this->SetTime(0);
    u = 0;
}


PID::~PID()
{
}

//Useless
//void P::SetSP(double SP)
//{
//    this->SP=SP;
//}

double PID::GetU()
{
    return u;
}


void PID::Update(double y)
{
    this->Simulate_step(y);
}

void PID::SetTime(int time)
{
    s_time = time;
}

double PID::Simulate_step(double y)
{
    //Generate SP

    SP=s_generator->CalculateSignal(s_time);

    //Calculate error
    e = SP-y;

    //Calculate control
    u_p = kr*e;

    //Anti wind-up
    Fi = ((u>=max_u)||(u<=min_u)) ? 0.0:kr*Tp*e/Ti;
    u_i = prev_u_i + Fi;
    prev_u_i = u_i;

    u_d = Td/(Td+N*Tp)*prev_u_d - kr*(N*Td)/(Td+N*Tp)*(y - prev_y);
    prev_u_d = u_d;
    u = ((u_p + u_i + u_d) > max_u) ? max_u : (u_p + u_i + u_d);
    prev_y = y;

    return u;

}

