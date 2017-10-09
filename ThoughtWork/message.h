#ifndef MESSAGE_H
#define MESSAGE_H
#include<ctime>
#include<string>
#include<vector>
using namespace std;
class Message{
public:
    Message();
    ~Message();
    static void Str2Message(const std::string& s,Message& m);
    static std::string Message2Str(Message& m);
    void setBtime(struct tm t);
    void setEtime(struct tm t);
    void setFlag(int t);
    void setUname(std::string s);
    void setCancel(std::string t);
    void setCourtname(std::string s);
    void setTimestring(std::string s);
    std::string getUname();
    struct tm getBTime();
    struct tm getETime();
    int getFlag();
    std::string getCancel();
    std::string getCourtname();
    std::string getTimestring();
private:
    struct tm btime; //begin time
    struct tm etime;
    int flag; //flag 0:error 100:can book 200:can cancel
    std::string timestring;
    std::string uname;
    std::string courtname;
    std::string cancel;
};

#endif // MESSAGE_H
