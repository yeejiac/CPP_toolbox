#include "mailSending.h"

MailSending::MailSending(std::string content):content_(content)
{
    std::cout<<"Input password"<<std::endl;
    std::cin>>password_;
}