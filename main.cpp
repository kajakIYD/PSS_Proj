#include "mainwindow.h"
#include <QApplication>
#include <QXmlStreamReader>
#include "p.h"
#include "pid.h"
#include "config.h"
#include "Xgenerator.h"
#include "arx.h"
#include "armax.h"
#include <string>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ARX *arx = new ARX;
    ARX *paralelArx = new ARX;
    ARMAX *armax = new ARMAX;
    ARMAX *paralelArmax = new ARMAX;
    Config *conf = new Config("C:\\PSS\\PSS_Config.xml");
    Generator *generator = new Generator("C:\\PSS\\PSS_Config.xml");
    PID *pid = new PID(conf->kr, conf->Ti, conf->Td, conf->N, conf->b, conf->max_u, conf->min_u, generator);

    //MainWindow w;
    MainWindow w(arx, pid, generator, conf, paralelArx);
    //MainWindow w(armax, pid, generator, conf, paralelArmax);

    w.show();

    return a.exec();
}
