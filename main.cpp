#include <iostream>
#include "lib/logwriter.h"

int main()
{
    Logwriter logwrite("testing");
    logwrite.writeLog("debug", "just testing");
    return 0;
}