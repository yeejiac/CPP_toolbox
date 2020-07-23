#include "logwriter.h"

std::string to_zero_lead(const int value, const unsigned precision)
{
     std::ostringstream oss;
     oss << std::setw(precision) << std::setfill('0') << value;
     return oss.str();
}

Logwriter::Logwriter(std::string logType):logType_(logType){}

std::string Logwriter::getTime()
{
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    std::string datetiming = std::to_string(now->tm_year + 1900) + "-" + to_zero_lead(now->tm_mon + 1, 2)+ "-" + to_zero_lead(now->tm_mday,2);
    std::string timing = to_zero_lead(now->tm_hour, 2) + ":" + to_zero_lead(now->tm_min, 2)+ ":" + to_zero_lead(now->tm_sec, 2);
    return datetiming + " " + timing;
}

void Logwriter::writeLog(std::string level, std::string documentation)
{
    documentation_ = documentation;
    if(level == "fatal")
    {
        fatallevel();
        
    }
    else if(level == "warn")
    {
        warnlevel();
        std::ofstream log_file(filePath_.c_str(), std::ios_base::out | std::ios_base::app );
        log_file << logcontent_ + " " + documentation << std::endl;
    }
    else if(level == "error")
    {
        errorlevel();
    }
    else if(level == "debug")
    {
        debuglevel();
    }
    else if(level == "trace")
    {
        tracelevel();
    }
    else if(level == "info")
    {
        infolevel();
    }
    std::cout<<logcontent_ + " " + documentation_<<std::endl;
}

void Logwriter::fatallevel()
{
    logcontent_ = getTime() + " fatal " + logType_;
    std::ofstream log_file(filePath_.c_str(), std::ios_base::out | std::ios_base::app );
    log_file << logcontent_ + " " + documentation_ << std::endl;
}

void Logwriter::warnlevel()
{
    logcontent_ = getTime() + " warn " + logType_;
    std::ofstream log_file(filePath_.c_str(), std::ios_base::out | std::ios_base::app );
    log_file << logcontent_ + " " + documentation_ << std::endl;
}

void Logwriter::errorlevel()
{
    logcontent_ = getTime() + " error " + logType_;
    std::ofstream log_file(filePath_.c_str(), std::ios_base::out | std::ios_base::app );
    log_file << logcontent_ + " " + documentation_ << std::endl;
}

void Logwriter::debuglevel()
{
    logcontent_ = getTime() + " debug " + logType_;
    std::ofstream log_file(filePath_.c_str(), std::ios_base::out | std::ios_base::app );
    log_file << logcontent_ + " " + documentation_ << std::endl;
}

void Logwriter::tracelevel()
{
    logcontent_ = getTime() + " trace " + logType_;
}

void Logwriter::infolevel()
{
    logcontent_ = getTime() + " info " + logType_;
}

