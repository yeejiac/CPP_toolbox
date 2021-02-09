#include "main.h"

int main()
{
    //Server *sr = new Server("./doc/settings.ini", "socket", "./doc/log/");
    Client *cl = new Client("./doc/settings.ini", "socket", "./doc/log/");
    return 0;
}