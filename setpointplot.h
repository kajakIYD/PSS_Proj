#ifndef SETPOINTPLOT_H
#define SETPOINTPLOT_H
#include "subject.h"
#include "regulationloop.h"

class SetPointPlot : public Subject
{
public:
    SetPointPlot();

private:
    std::deque<double> SP;

};

#endif // SETPOINTPLOT_H
