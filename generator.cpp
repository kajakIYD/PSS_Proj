#include "generator.h"

Generator::Generator(string filePath)
{
    this->crp = new configRegulatorParameters(filePath);
}

Generator::Generator()
{

}


bool Generator::RegisterSignal(Signal * signal) {
    if (std::find(s_Signals.begin(), s_Signals.end(), signal) == s_Signals.end()) {
        s_Signals.push_back(signal);
        return true;
    } else
        return false;
}

bool Generator::UnregisterSignals() {
    try
    {
        s_Signals.clear();  //No-throw guarantee: this member function never throws exceptions.
        return true;
    }
    catch(...)
    {
        return false;
    }
}

double Generator::CalculateSignal(int t) const {
    double u = 0;
    std::list<Signal *>::const_iterator it = s_Signals.begin();
    for (; it != s_Signals.end(); ++it) {
            u+=(*it)->simulate(t);
    }
    return u;
}



RectWave::RectWave(double amp, int interval, double fill) :
    s_amp(amp), s_interval(interval), s_fill(fill)
{

}

double RectWave::simulate(int t)
{
    try
    {
        if (s_interval <= 0)
        {
            string ex = "Interval of a wave cannot be zero or negative!";
            throw ex;
        }
    }
    catch (string ex)
    {
        return 0;
    }
    return ((t % s_interval) < (s_fill/100 * s_interval)) ? s_amp : 0;

}

TriaWave::TriaWave(double amp, int interval) :
    s_amp(amp), s_interval(interval)
{

}

double TriaWave::simulate(int t)
{
   try
   {
       if (s_interval <= 0)
       {
           string ex = "Interval of a wave cannot be zero or negative!";
           throw ex;
       }
   }
   catch (string ex)
   {
       return 0;
   }
    unsigned int restOfInterval = t % s_interval;
    double delta = (restOfInterval) ? (s_amp / (s_interval / 2.0)) : 0;
   return ((restOfInterval >= (s_interval / 2.0))) ?
       2*s_amp - (delta * restOfInterval) : delta * restOfInterval;

}

SineWave::SineWave(double amp, int interval) :
    s_amp(amp), s_interval(interval)
{

}

double SineWave::simulate(int t)
{
    try
    {
        if (s_interval <= 0)
        {
            string ex = "Interval of a wave cannot be zero or negative!";
            throw ex;
        }
    }
    catch (string ex)
    {
        return 0;
    }
    return s_amp*std::sin((static_cast<double>(t % s_interval) / s_interval) * 6.28);
}

Step::Step(double amp) :
    s_amp(amp)
{

}

double Step::simulate(int t)
{
    return s_amp;
}

NoiseWave::NoiseWave(double var) :
    s_var(var)
{

}

double NoiseWave::simulate(int t)
{
    try
    {
        if (s_var <= 0)
        {
            string ex = "Variance of a wave cannot be zero or negative!";
            throw ex;
        }
    }
    catch (string ex)
    {
        return 0;
    }
    // generate random e value
    std::normal_distribution<double> distribution(0, s_var);
    return distribution(generator);
}
