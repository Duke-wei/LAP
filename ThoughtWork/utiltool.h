#ifndef UTILTOOL_H
#define UTILTOOL_H
#include<vector>
#include<string>
#include<iostream>
#include<ctime>
#include<stdio.h>
namespace utiltool {
    static const std::string STATE_ERROR = "Error: the booking is invalid!";
    static const std::string STATE_BSUC = "Success: the booking is accept!";
    static const std::string STATE_BFAI = "Error: the booking conflicts with existing bookings!";
    static const std::string STATE_CSUC = "Success: the booking is accept!";
    static const std::string STATE_CFAI = "Error: the booking being cancelled does not exist!";
    class StringTool{
    public:
        static std::vector<std::string> splitstring(const std::string& str,const char delimiter);
    };
    //http://www.cnblogs.com/highway-9/p/5757113.html
    class DateTool{
    public:
        static std::string currentTime();

        static std::string time2string(time_t t);

        static std::string time2dhmstring(time_t t);

        static time_t string2time(const std::string& timeStr);

        static void string2tm(const std::string& timeStr,struct tm& stTm);
    };
}
#endif // UTILTOOL_H
