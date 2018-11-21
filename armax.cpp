#include "armax.h"

ARMAX::ARMAX()
{
    //destrctor and make it aggregation(outside of that class, in mw)
    this->conf = new Config("C:\\PSS\\PSS_Config.xml");

    s_parA = conf->A;
    s_parB = conf->B;
    s_parC = conf->C;

    s_k = conf->delay;
    s_switchTime = conf->switchTime;
    s_switchTimePeriod = conf->switchTimePeriod;

    // stopnie wielomianów
    s_dA = s_parA.size();
    s_dB = s_parB.size()-1;
    s_dC = s_parC.size();

    // wstępne zerowanie wektorów
    for(int i=0; i < s_dA;i++)
        y.push_back(0);

    for(int i=0;i < s_dB + s_k + 1; i++)
        u.push_back(0);

    for(int i=0;i < s_dC + 1; i++)
        e.push_back(0);


    //Licz zmiane
    CalculateParamChanges();

}

void ARMAX::CalculateParamChanges()
{
    for(int i=0; i<s_dA; i++)
    {
        auto tmp = (conf->A_N.at(i) - s_parA.at(i))/s_switchTimePeriod;
        s_changes_parA.push_back((conf->A_N.at(i) - s_parA.at(i))/s_switchTimePeriod);
    }
    for(int i=0; i<=s_dB; i++)
    {
        auto tmp = (conf->B_N.at(i) - s_parB.at(i))/s_switchTimePeriod;
        s_changes_parB.push_back((conf->B_N.at(i) - s_parB.at(i))/s_switchTimePeriod);
    }
    for(int i=0; i<s_dC; i++)
    {
        auto tmp = (conf->C_N.at(i) - s_parC.at(i))/s_switchTimePeriod;
        s_changes_parC.push_back((conf->C_N.at(i) - s_parC.at(i))/s_switchTimePeriod);
    }
}

ARMAX::~ARMAX()
{

}


void ARMAX::UpdateParameters()
{
    for(int i=0; i<s_dA; i++)
    {
        s_parA.at(i) = s_parA.at(i) + s_changes_parA.at(i);
    }
    for(int i=0; i<=s_dB; i++)
    {
        s_parB.at(i) = s_parB.at(i) + s_changes_parB.at(i);
    }
    for(int i=0; i<s_dC; i++)
    {
        s_parC.at(i) = s_parC.at(i) + s_changes_parC.at(i);
    }
}

void ARMAX::ResetParameters()
{
    s_parA = conf->A;
    s_parB = conf->B;
    s_parC = conf->C;
}

std::vector<double> ARMAX::GetA()
{
    return s_parA;
}

std::vector<double> ARMAX::GetB()
{
    return s_parB;
}

std::vector<double> ARMAX::GetC()
{
    return s_parC;
}

int ARMAX::GetAdegree()
{
    return s_dA;
}

int ARMAX::GetBdegree()
{
    return s_dB;
}

int ARMAX::GetCdegree()
{
    return s_dC;
}

int ARMAX::Getk()
{
    return s_k;
}

int ARMAX::GetSwitchTime()
{
    return this->s_switchTime;
}

int ARMAX::GetSwitchPeriod()
{
    return this->s_switchTimePeriod;
}

double ARMAX::Simulate_step(double input)
{
    //make it static (optimal)
//    static std::deque<double> subU(s_k+s_dB);
    static std::deque<double> subY;

    static std::deque<double> subU;

    static std::deque<double> subE;

    // generate random e value
    std::normal_distribution<double> distribution(0, s_var);
    e.pop_back();
    e.push_front(distribution(generator));


    // delete oldest value and push newest
    u.pop_back();
    u.push_front(input);

    // copy u vector with k offset
    auto it = u.begin();
    advance(it, this->s_k);
    std::copy(it, u.end(), std::front_inserter(subU));//std::back_inserter(subU));

    // copy y vector to dA, no offset
    it = y.begin();
    advance(it, this->s_dA);
    std::copy(y.begin(), it, std::front_inserter(subY));

    // copy e vector to dC, no offset
    it = e.begin();
    advance(it, this->s_dC);
    std::copy(e.begin(), it, std::front_inserter(subE));

    double output1, output2, output3;//dist;
    // generate new output
//    auto it_subU = subU.end();
//    advance(it_subU, -this->s_dB);
//    auto it_subY = subY.end();
//    advance(it_subY, -this->s_dA);
    output1 = inner_product(s_parB.begin(), s_parB.end(), subU.begin(), 0.0);
    output2 = - inner_product(s_parA.begin(), s_parA.end(), subY.begin(), 0.0);
    output3 = inner_product(s_parC.begin(), s_parC.end(), subE.begin(), 0.0);
    /*for (int i = 0; i <= s_dC; ++i)
    {
        dist -= s_parC * e.at(i);
    }*/




    this->y.pop_back();
    this->y.push_front(output1 + output2 + output3);
    double output = output1 + output2 + output3;

    //Powiadom wykres
//    Notify(input, output);

    //Powiadom regulator
    //Notify(output);

    this->yFromBeginning.push_back(output);
    return output;
}

std::deque<double> ARMAX::GetNewestY()
{
    return y;
}


std::deque<double> ARMAX::GetY()
{
    return yFromBeginning;
}


std::deque<double> ARMAX::GetU()
{
    return u;
}

void ARMAX::SetY(std::deque<double> yNew)
{
    this->y = yNew;
}


void ARMAX::SetU(std::deque<double> uNew)
{
    this->u = uNew;
}
