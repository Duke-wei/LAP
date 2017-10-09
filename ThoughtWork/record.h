#ifndef RECORD_H
#define RECORD_H
#include<ctime>
#include<vector>
#include<iostream>
#include<algorithm>
#include "cost.h"
#include "message.h"
using namespace std;
//抽象产品元素类——记录
struct tat{
    tat(time_t a,time_t b):first(a),second(b){}
    time_t first;
    time_t second;
    bool operator<(const tat b){
        return this->first<b.first;
    }
};

class Record{
public:
    virtual ~Record()=0;
    virtual bool checkRecordI(time_t bt,time_t et)=0;
    virtual int checkRecordE(time_t bt,time_t et)=0;
    virtual bool addRecord(Message& m)=0;
    virtual bool delRecord(Message& m)=0;
    virtual void showRecord()=0;
protected:
    Record();
};
//默认记录
class DefaultRecord:public Record{
public:
    DefaultRecord();
    ~DefaultRecord();
    bool checkRecordI(time_t bt,time_t et);
    int checkRecordE(time_t bt,time_t et);
    bool addRecord(Message& m);
    bool delRecord(Message& m);
    //总收益
    void showRecord();
    std::vector<tat> brecord;
    std::vector<tat> crecord;
};
#endif
