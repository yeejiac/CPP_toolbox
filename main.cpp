#include <iostream>
#include "lib/logwriter.h"
#include "lib/initParser.h"
#include "src/server.h"


int main()
{
    // Logwriter logwrite("testing");
    // logwrite.writeLog("debug", "just testing");
    Server *sr = new Server;
    sr->recv_conn();
    int a;
    std::cin>>a;
    return 0;
}