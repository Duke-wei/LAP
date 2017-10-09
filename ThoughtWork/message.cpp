#include "message.h"
#include "utiltool.h"
using namespace utiltool;

Message::Message(){
    struct tm bt;
    DateTool::string2tm("1970-01-02 00:00:00",bt);
    this->setBtime(bt);
    this->setEtime(bt);
    this->setCancel("");
    this->setFlag(0);
    this->setUname("");
    this->setTimestring("");
}

Message::~Message(){

}

void Message::setBtime(struct tm t){
    this->btime = t;
}

void Message::setEtime(struct tm t){
    this->etime = t;
}

struct tm Message::getBTime(){
    return this->btime;
}

struct tm Message::getETime(){
    return this->etime;
}

void Message::setCourtname(string s){
    this->courtname = s;
}

string Message::getCourtname(){
    return this->courtname;
}

void Message::setTimestring(string s){
    this->timestring = s;
}

string Message::getTimestring(){
    return this->timestring;
}

void Message::Str2Message(const std::string& s,Message& m){
    vector<string> sv = StringTool::splitstring(s,' ');
    if((sv.size()==4)||(sv.size()==5)){
        m.setUname(sv[0]);
        m.setTimestring(sv[1]+" "+sv[2]);
        vector<string> hm = StringTool::splitstring(sv[2],'~');
        if(hm.size()==2){
            string btimes = sv[1]+" "+hm[0]+":00";
//            std::cout<<btimes<<std::endl;
            string etimes = sv[1]+" "+hm[1]+":00";
//           std::cout<<etimes<<std::endl;
            struct tm bt,et;
            DateTool::string2tm(btimes,bt);
            DateTool::string2tm(etimes,et);
            m.setBtime(bt);
            m.setEtime(et);
        }
        m.setCourtname(sv[3]);
        if(sv.size()==5) m.setCancel(sv[4]);
    }
}

std::string Message::Message2Str(Message& m){
    return "";
}

int Message::getFlag(){
    return this->flag;
}

void Message::setFlag(int t){
    this->flag = t;
}

void Message::setUname(string s){
    this->uname = s;
}

string Message::getUname(){
    return this->uname;
}

void Message::setCancel(string t){
    this->cancel = t;
}

string Message::getCancel(){
    return this->cancel;
}
