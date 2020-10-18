#include "mailSending.h"

MailSending::MailSending(std::string content):content_(content)
{
    // std::cout<<"Input password"<<std::endl;
    // std::cin>>password_;
}

void MailSending::sendmail()
{
    Client *cl = new Client("gmail_sending");
}

int main()
{
    MailSending *ml = new MailSending("testing");
    ml->sendmail();
}