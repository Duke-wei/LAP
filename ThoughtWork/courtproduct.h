#ifndef COURTPRODUCT_H
#define COURTPRODUCT_H

#include "cost.h"
#include "record.h"
#include <string>
#include <map>

class AbstractCourt{
public:
    //策略模式加载cost 和 record 模块
    AbstractCourt();
    virtual ~AbstractCourt()=0;
    virtual void setCost(Cost* cost) = 0;
    virtual void setRecord(Record* record)=0;
    virtual void show()=0;
    virtual std::string getName()=0;
    virtual std::string getAddress()=0;
    virtual void setName(std::string s)=0;
    virtual void setAddress(std::string s)=0;
    Cost* cost;
    Record* record;
    std::string name;
    std::string address;
    std::map<time_t,std::string> costlog;
};

class BadmintonCourt:public AbstractCourt{
public:
    ~BadmintonCourt();
    BadmintonCourt();
    void setCost(Cost* cost);
    void setRecord(Record* record);
    void show();
    std::string getName();
    std::string getAddress();
    void setName(std::string s);
    void setAddress(std::string s);
};

#endif // COURTPRODUCT_H
