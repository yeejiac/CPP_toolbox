#include "initParser.h"

InitParser::InitParser(std::string path, std::string target):target_(target), path_(path){}

void InitParser::readLine()
{
    std::ifstream myfile;
    myfile.open(path_);
    std::string line;
    if (myfile.is_open())
    {
        while (std::getline(myfile,line))
        {
            std::cout << line <<std::endl;
        }
        myfile.close();
    }
}

int main()
{
    InitParser *ip = new InitParser("../doc/settings.ini", "Socket");
    ip->readLine();
    return 0;
}

// g++ -std=c++11 -Wall initParser.cpp -o test.out