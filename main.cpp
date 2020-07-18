#include <iostream>
#include "lib/logwriter.h"

int main()
{
    Logwriter logwrite("testing");
    std::cout<<logwrite.getTime()<<std::endl;
    return 0;
}