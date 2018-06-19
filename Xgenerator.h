#ifndef GENERATOR_H
#define GENERATOR_H
#include "Xsignal.h"
#include "configregulatorparameters.h"
#include <string>
#include <random>

//class configRegulatorParameters;
class Signal;

class Generator
{
public:
    Generator(string filePath);
    configRegulatorParameters *crp;
    bool RegisterSignal (Signal * signal);
    bool UnregisterSignals();
    double CalculateSignal(int t) const;
private:
    std::list<Signal * > s_Signals;

};


class RectWave :public Signal  //: public Decorator//
{
public:
    RectWave(double amp, int interval, double fill);
    virtual double simulate(int t);
private:
    double s_amp;
    int s_interval;
    double s_fill;

};

class TriaWave:public Signal //: public Decorator //
{
public:
    TriaWave(double amp, int interval);
    virtual double simulate(int t);
private:
    double s_amp;
    int s_interval;

};


class SineWave :public Signal //: public Decorator//
{
public:
    SineWave(double amp, int interval);
    virtual double simulate(int t);
private:
    double s_amp;
    int s_interval;

};


class Step :public Signal//: public Decorator//
{
public:
    Step(double amp);
    virtual double simulate(int t);
private:
    double s_amp;


};


class NoiseWave : public Signal
{
public:
    NoiseWave(double var);
    virtual double simulate(int t);
private:
    double s_var;
    std::default_random_engine generator;
};


#endif // GENERATOR_H
