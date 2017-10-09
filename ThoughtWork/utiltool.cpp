#include "utiltool.h"

namespace utiltool{

std::vector<std::string> StringTool::splitstring(const std::string& str,const char delimiter=' '){
    std::vector<std::string> splited;
    std::string s(str);
    std::size_t pos;
    while((pos = s.find(delimiter)) != std::string::npos){
        std::string sec = s.substr(0,pos);
        if(!sec.empty()){
            splited.push_back(s.substr(0,pos));
        }
        s = s.substr(pos+1);
    }
    splited.push_back(s);
    return splited;
}

std::string DateTool::currentTime(){
    return time2string(time(nullptr));
}

std::string DateTool::time2string(time_t t){
    struct tm* tmNow = localtime(&t);
    char timeStr[sizeof("yyyy-mm-dd hh:mm:ss")]={'\0'};
    std::strftime(timeStr,sizeof(timeStr),"%Y-%m-%d %H:%M:%S",tmNow);
    return timeStr;
}

std::string DateTool::time2dhmstring(time_t t){
//    struct tm* tmNow = localtime(&t);
//    int year = tm.tm_year+1900;
//    int month = tm.tm_mon + 1;
//    int day = tm.tm_mday;
//    int hour = tm.tm_hour;
//    int min = tm.tm_min;
    return "";
}

void DateTool::string2tm(const std::string& timeStr,struct tm& stTm){
    time_t tt = string2time(timeStr);
    stTm = *(gmtime(&tt));
    //struct tm* t = gmtime(&tt);
    //memcpy(&stTm,t,sizeof(struct tm));
//    stTm.tm_hour = t->tm_hour;
//    stTm.tm_isdst = t->tm_isdst;
//    stTm.tm_mday = t->tm_mday;
//    stTm.tm_min = t->tm_min;
//    stTm.tm_mon = t->tm_mon;
//    stTm.tm_sec = t->tm_sec;
//    stTm.tm_wday = t->tm_wday;
//    stTm.tm_yday = t->tm_yday;
//    stTm.tm_yday = t->tm_yday;
}

time_t DateTool::string2time(const std::string& timeStr){
    struct tm stTm;
    sscanf(timeStr.c_str(),"%d-%d-%d %d:%d:%d",
           &(stTm.tm_year),
           &(stTm.tm_mon),
           &(stTm.tm_mday),
           &(stTm.tm_hour),
           &(stTm.tm_min),
           &(stTm.tm_sec));
    stTm.tm_year -= 1900;
    stTm.tm_mon--;
    stTm.tm_isdst = -1;
    return mktime(&stTm);
}

}
