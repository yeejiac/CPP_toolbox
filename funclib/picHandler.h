#ifndef PICHANDLER_H_
#define PICHANDLER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

class PicHandler
{
public:
    PicHandler(std::string path);
    ~PicHandler();
    bool loadPic(std::string path);

private:
    std::string filePath_;
    std::vector<std::string> result_;

};

#endif