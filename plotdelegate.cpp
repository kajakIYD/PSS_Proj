#include "plotdelegate.h"

PlotDelegate::PlotDelegate(Ui::MainWindow* ui, QMainWindow* mw)
{
    this->ui = ui;
    this->ui->setupUi(mw);
    this->ui->Plot1->addGraph();
    this->ui->Plot1->addGraph();
    this->ui->Plot1->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    this->ui->Plot1->yAxis->scaleRange(0,10);
    this->ui->Plot2->addGraph();
    this->ui->Plot2->graph(0)->setPen(QPen(Qt::green));
    this->ui->Plot1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
//    Test Data
//    QVector<double> t={1,2,3};
//    QVector<double> y={3,4,10};
//    QVector<double> u={2,3,11};
    this->ui->Plot1->graph(0)->setData(t,y);
    this->ui->Plot2->graph(0)->setData(t,u);
    this->ui->Plot1->xAxis->setLabel("t");
    this->ui->Plot1->yAxis->setLabel("y");
    this->ui->Plot2->xAxis->setLabel("t");
    this->ui->Plot2->yAxis->setLabel("u");
    this->ui->Plot1->yAxis->rescale();
    this->ui->Plot1->xAxis->setRange(0, 50);
    this->ui->Plot1->replot();
    this->ui->Plot2->yAxis->rescale();
    this->ui->Plot2->xAxis->setRange(0, 50);
    this->ui->Plot2->replot();
    //connect(ui->addStep, SIGNAL(clicked()), this, SLOT(on_addStep_clicked(bool)));
}


void PlotDelegate::Update(double u, double y)
{
    time++;
    t.push_back(time);
    this->u.push_back(u);
    this->y.push_back(y);
    this->ui->Plot1->graph(0)->setData(this->t,this->y);
    this->ui->Plot2->graph(0)->setData(this->t,this->u);
    this->ui->Plot1->yAxis->rescale();

    if (t.size()>50)
    {
        this->ui->Plot1->xAxis->setRange(t.size()-50, t.size());
        this->ui->Plot2->xAxis->setRange(t.size()-50, t.size());
    }

    this->ui->Plot1->replot();
    this->ui->Plot2->yAxis->rescale();

    this->ui->Plot2->replot();
    return;
}

void PlotDelegate::Update(double u)
{
    return;
}

