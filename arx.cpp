#include "arx.h"

ARX::ARX()
{
    //destrctor and make it aggregation(outside of that class, in mw)
    this->conf = new Config("E:\\Qt\\Projects\\PSS_New\\PSS\\Config\\PSS_Config.xml");

    parA = conf->A;
    parB = conf->B;

    s_k = conf->delay;
    s_switchTime = conf->switchTime;

    // stopnie wielomianów
    s_dA = parA.size();
    s_dB = parB.size()-1;

    // wstępne zerowanie wektorów
    for(int i=0; i < s_dA;i++)
    y.push_back(0);

    for(int i=0;i < s_dB+s_k+1 ;i++)
    u.push_back(0);

}


ARX::~ARX()
{

}


void ARX::UpdateParameters()
{
    parA = conf->A_N;
    parB = conf->B_N;
}

void ARX::ResetParameters()
{
    parA = conf->A;
    parB = conf->B;
}


int ARX::GetSwitchTime()
{
    return this->s_switchTime;
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
    output1 = inner_product(parB.begin(), parB.end(), subU.begin(), 0.0);
    output2 = - inner_product(parA.begin(), parA.end(), subY.begin(), 0.0);
    dist = 0 - e;

    this->y.pop_back();
    this->y.push_front(output1 + output2 + dist);
    double output = output1 + output2 + dist;

    //Powiadom wykres
//    Notify(input, output);

    //Powiadom regulator
    //Notify(output);

    return output;
}
