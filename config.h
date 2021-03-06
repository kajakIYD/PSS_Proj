#ifndef CONFIG_H
#define CONFIG_H
#include <QVector>
#include <QFile>
#include <QXmlStreamReader>

class Config
{
    //Komentarze!
public:
    Config(const char* filePath);
    Config();
    int delay;
    int switchTime;
    int switchTimePeriod;
    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C;
    std::vector<double> A_N;
    std::vector<double> B_N;
    std::vector<double> C_N;
    double kr;
    double Ti;
    double Td;
    double N;
    double b;
    double max_u;
    double min_u;
    double H;
    double L;
    double alpha;
    double ro;
private:
    bool LoadValues(const char* filePath);
    int ExtractTime(std::string str);
    std::vector<double> ExtractParams(std::vector<std::string> str);
};

#endif // CONFIG_H
