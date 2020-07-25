#ifndef INIPARSER_H_
#define INIPARSER_H_

#include <iostream>
#include <fstream>
#include <string>

class InitParser
{
public:
    InitParser(std::string path, std::string target);
    void findLine();
    void readLine();

private:
    std::string target_;
    std::string path_;
};




#endif