#include "config.h"
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <sstream>


double string_to_double( const std::string& s )
 {
   std::istringstream i(s);
   double x;
   if (!(i >> x))
     return 0;
   return x;
 }


template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

int Config::ExtractTime(std::string str)
{
    int res = std::stoi(str);
    return res;
}

std::vector<double> Config::ExtractParams(std::vector<std::string> str)
{
    std::vector<double> tempVec={};
    for(auto const& value: str) {
        tempVec.push_back(string_to_double(value));
    }
    return tempVec;
}


bool Config::LoadValues(const char* filePath)
{
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        //qDebug() << "Cannot read file" << file.errorString();
        return false;
    }

    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        if (reader.name() == "PSS_Config"){
            while(reader.readNextStartElement()){
                if(reader.name() == "delay"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            delay = ExtractTime(str);
                            //qDebug(qPrintable(s));
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "kr"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->kr = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "Ti"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->Ti = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "Td"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->Td = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "N"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->N = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "b"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->b = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "max_u"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->max_u = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "min_u"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->min_u = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "H"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->H = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "L"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->L = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "ro"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->ro = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "alpha"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->alpha = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "c_Parameters"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            std::vector<std::string> x = split(str, ',');
                            C = ExtractParams(x);
                        }
                        else if(reader.name() == "valueN"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            std::vector<std::string> x = split(str, ',');
                            C_N = ExtractParams(x);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "b_Parameters"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            std::vector<std::string> x = split(str, ',');
                            B = ExtractParams(x);
                        }
                        else if(reader.name() == "valueN"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            std::vector<std::string> x = split(str, ',');
                            B_N = ExtractParams(x);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "a_Parameters"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            std::vector<std::string> x = split(str, ',');
                            A = ExtractParams(x);
                            //qDebug(qPrintable(s));
                        }
                        else if(reader.name() == "valueN"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            std::vector<std::string> x = split(str, ',');
                            A_N = ExtractParams(x);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "switch_time_period"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            this->switchTimePeriod = string_to_double(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else if(reader.name() == "switch_time"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "value"){
                            QString s = reader.readElementText();
                            std::string str = s.toUtf8().constData();
                            switchTime = ExtractTime(str);
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else
                    reader.skipCurrentElement();
            }
        }
        else
        {
            reader.raiseError(QObject::tr("Incorrect file"));
            return false;
        }
    }
    file.close();
    return true;
}


Config::Config(const char* filePath)
{
    LoadValues(filePath);
}

Config::Config()
{
}
