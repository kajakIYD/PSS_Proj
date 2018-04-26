#include "mainwindow.h"
#include <QApplication>
#include <QXmlStreamReader>
#include "p.h"
#include "pid.h"
#include "config.h"
#include "generator.h"
#include "arx.h"
#include <string>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ARX *arx = new ARX;
    Config *conf = new Config("E:\\Qt\\Projects\\PSS_New\\PSS\\Config\\PSS_Config.xml");
    Generator *generator = new Generator("E:\\Qt\\Projects\\PSS_New\\PSS\\Config\\PSS2_Config.xml");
    PID *pid = new PID(conf->kr, conf->Ti, conf->Td, conf->N, conf->b, conf->max_u, conf->min_u, generator);

    //MainWindow w;
    MainWindow w(arx, pid, generator, conf);

    w.show();

    return a.exec();
}
