#include "mainwindow.h"
#include <QApplication>
#include <QXmlStreamReader>
#include "p.h"
#include "pid.h"
#include "config.h"
#include "Xgenerator.h"
#include "arx.h"
#include <string>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ARX *arx = new ARX;
    ARX *paralelArx = new ARX;
    Config *conf = new Config(PUT_YOUR_PATH_HERE);
    Generator *generator = new Generator(PUT_YOUR_PATH_HERE);
    PID *pid = new PID(conf->kr, conf->Ti, conf->Td, conf->N, conf->b, conf->max_u, conf->min_u, generator);

    //MainWindow w;
    MainWindow w(arx, pid, generator, conf, paralelArx);

    w.show();

    return a.exec();
}
