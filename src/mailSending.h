#ifndef MAILSENDING_H_
#define MAILSENDING_H_

#include <iostream>

#include "../src/client.h"

class MailSending
{
public:
    MailSending(std::string content);
    void sendmail();
    Logwriter logwrite = Logwriter("testing");
    InitParser *ip = new InitParser("D:\\program_file\\CPP_toolbox\\doc\\settings.ini", "gmail_sending");
private:
    std::string senderName_ = "default@gmail.com";
    std::string subject_ = "testing"; 
    std::string password_;
    std::string content_;

};

#endif