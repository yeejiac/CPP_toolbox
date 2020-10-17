#ifndef LOGWRITER_H_
#define LOGWRITER_H_
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip>

class Logwriter
{
public:
    Logwriter(std::string logType, std::string filePath);
    void write(std::string level, std::string documentation);
    std::string getTime();
    void fatallevel();
    void warnlevel();
    void errorlevel();
    void debuglevel();
    void tracelevel();
    void infolevel();
private:
    std::string logType_;
    std::string logcontent_;
    std::string documentation_;
    std::string filePath_;
};

#endif 