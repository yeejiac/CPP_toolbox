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