#include <iostream>
#include <logwriter.h>
// #include "funclib/logwriter.h"
// #include "funclib/initParser.h"
// #include "funclib/dataQueue.h"
// #include "src/server.h"
// #include "src/client.h"


int main()
{
    Logwriter *logwriter = new Logwriter("FD", "/doc/log/");
    logwriter->write("Error", "testing");
    // Server *sr = new Server;
    // Client *cl = new Client("socket");
    return 0;
}