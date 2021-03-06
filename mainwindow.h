#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotdelegate.h"
#include "arx.h"
#include "armax.h"
#include "p.h"
#include "pid.h"
#include "config.h"
#include "regulationloop.h"
#include "identify.h"
#include "identifyarmax.h"
#include "identifyuber.h"
#include <string>
#include <sstream>
#include <deque>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(ARX *arx, PID *pid, Generator *generator, Config *conf, ARX *paralelArx, QWidget *parent=0);
    explicit MainWindow(ARMAX *armax, PID *pid, Generator *generator, Config *conf, ARMAX *paralelArmax, QWidget *parent=0);
    ~MainWindow();

private slots:
    void updateView();

    void on_startButton_clicked(bool checked);

    void on_stepButton_clicked(bool checked);

    void on_stopButton_clicked(bool checked);

    void on_restartButton_clicked(bool checked);
    void on_resetSetPoint_clicked(bool checked);

    void on_addStep_clicked();
    void on_addRectangle_clicked();
    void on_addSine_clicked();
    void on_addTriangle_clicked();
    void on_addNoise_clicked(bool checked);

    void on_horizontalSlider_valueChanged(int value);

    void on_changeRegulatorParametersButton_clicked(bool checked);

    void on_changeRegulatorButton_clicked(bool checked);

private:
    void PlotSP();
    void updateViewStep();
    void DisplayIdentParams();
    void DisplayRealParams();
    string doubleToString(double val);
    QString stringToQString(string str);

    Ui::MainWindow *ui;

    ARX *s_arx;
    ARX *s_paralelArx;
    ARMAX *s_armax;
    ARMAX *s_paralelArmax;
    Config *s_conf;
    Generator *s_generator;
    QTimer *timer;
    PID *s_pid;
    RegulationLoop *s_regLoop;
    IdentifyUber *s_id;

    PlotDelegate *s_plot1Delegate;
    PlotDelegate *s_plot2Delegate;
    PlotDelegate *s_plot3Delegate;


    QVector<double> s_SPVec = {};
    QVector<double> s_TimeVec = {};
    deque<double> theta;
    std::vector<double> A;
    std::vector<double> B;

    double currentOutput=0;
    int time=0;
    int  s_dA;
    int s_dB;
    int s_dC;
    bool start=false;
    bool step = false;
    bool restarted = false;
};

#endif // MAINWINDOW_H
