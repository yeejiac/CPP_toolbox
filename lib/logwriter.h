#ifndef LOGWRITER_H_
#define LOGWRITER_H_
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

class Logwriter
{
public:
    Logwriter(std::string logType);
    std::string getTime();
private:
    std::string logType_;
};

#endif 