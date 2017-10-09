#ifndef GOVERNOR_H
#define GOVERNOR_H

#include<vector>
#include<ctime>
#include<string>
#include "message.h"
#include "courtproduct.h"
#include "utiltool.h"

class Governor{
public:
    Governor();
    ~Governor();
    void AddMember(AbstractCourt* c);
    bool DelMember(const std::string& s);
    void StateInput(const std::string& s);
    void StateCheck(Message& m);
    void StateBook(Message& m);
    void StateCancel(Message& m);
    void StateOutput(Message& m);
    void StateShow();
    std::map<std::string,AbstractCourt*> msc;
//    Message m;
};

#endif // GOVERNOR_H
