#include "arx.h"

ARX::ARX()
{
    //destrctor and make it aggregation(outside of that class, in mw)
    this->conf = new Config("C:\\!Maciej Kusnierz\\TA\\PSS_Proj\\PSS_Proj\\Config\\PSS_Config.xml");

    s_parA = conf->A;
    s_parB = conf->B;

    s_k = conf->delay;
    s_switchTime = conf->switchTime;
    s_switchTimePeriod = conf->switchTimePeriod;

    // stopnie wielomianów
    s_dA = s_parA.size();
    s_dB = s_parB.size()-1;

    // wstępne zerowanie wektorów
    for(int i=0; i < s_dA;i++)
    y.push_back(0);

    for(int i=0;i < s_dB+s_k+1 ;i++)
    u.push_back(0);

    //Licz zmiane
    CalculateParamChanges();

}

void ARX::CalculateParamChanges()
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
}

ARX::~ARX()
{

}


void ARX::UpdateParameters()
{
    for(int i=0; i<s_dA; i++)
    {
        s_parA.at(i) = s_parA.at(i) + s_changes_parA.at(i);
    }
    for(int i=0; i<=s_dB; i++)
    {
        s_parB.at(i) = s_parB.at(i) + s_changes_parB.at(i);
    }
    //s_parA = conf->A_N;
    //s_parB = conf->B_N;
}

void ARX::ResetParameters()
{
    s_parA = conf->A;
    s_parB = conf->B;
}

std::vector<double> ARX::GetA()
{
    return s_parA;
}

std::vector<double> ARX::GetB()
{
    return s_parB;
}

int ARX::GetAdegree()
{
    return s_dA;
}

int ARX::GetBdegree()
{
    return s_dB;
}

int ARX::Getk()
{
    return s_k;
}

int ARX::GetSwitchTime()
{
    return this->s_switchTime;
}

int ARX::GetSwitchPeriod()
{
    return this->s_switchTimePeriod;
}

double ARX::Simulate_step(double input)
{
    //make it static (optimal)
//    static std::deque<double> subU(s_k+s_dB);
    static std::deque<double> subY;

    static std::deque<double> subU;


    // generate random e value
    std::normal_distribution<double> distribution(0, s_var);
    double e = distribution(generator);

    // delete oldest value and push newest
    u.pop_back();
    u.push_front(input);

    // copy u vector with k offset
    auto it = u.begin();
    advance(it, this->s_k);
    std::copy(it, u.end(), std::front_inserter(subU));//std::back_inserter(subU));

    // copy y vector with dA offset
    it = y.begin();
    advance(it, this->s_dA);
    std::copy(y.begin(), it, std::front_inserter(subY));

    double output1, output2, dist;
    // generate new output
//    auto it_subU = subU.end();
//    advance(it_subU, -this->s_dB);
//    auto it_subY = subY.end();
//    advance(it_subY, -this->s_dA);
    output1 = inner_product(s_parB.begin(), s_parB.end(), subU.begin(), 0.0);
    output2 = - inner_product(s_parA.begin(), s_parA.end(), subY.begin(), 0.0);
    dist = 0 - e;

    this->y.pop_back();
    this->y.push_front(output1 + output2 + dist);
    double output = output1 + output2 + dist;

    //Powiadom wykres
//    Notify(input, output);

    //Powiadom regulator
    //Notify(output);

    this->yFromBeginning.push_back(output);
    return output;
}

std::deque<double> ARX::GetNewestY()
{
    return y;
}


std::deque<double> ARX::GetY()
{
    return yFromBeginning;
}


std::deque<double> ARX::GetU()
{
    return u;
}

void ARX::SetY(std::deque<double> yNew)
{
    this->y = yNew;
}


void ARX::SetU(std::deque<double> uNew)
{
    this->u = uNew;
}
