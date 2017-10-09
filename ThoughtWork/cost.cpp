#include "cost.h"

Cost::Cost(){
}

Cost::~Cost(){
}
//默认消费模型
DefaultCost::DefaultCost(){
    //cout<<"DefaultCost"<<endl;
}

DefaultCost::~DefaultCost(){
    this->sumcost = 0;
}

int DefaultCost::CalcCost15(int bt,int et){
    if(bt<9||et>22) return 0;
    int costArray[24]={0,0,0,0,0,0,0,0,0,30,60,90,140,190,240,290,340,390,440,490,550,610,610};
    return costArray[et]-costArray[bt];
}
int DefaultCost::CalcCost67(int bt,int et){
    if(bt<9||et>22) return 0;
    int costArray[24]={0,0,0,0,0,0,0,0,0,40,80,120,170,220,270,320,370,420,480,540,600,660,660};
    return costArray[et]-costArray[bt];
}

int DefaultCost::getCost(Message& m){
    struct tm bt = m.getBTime();
    struct tm et = m.getETime();
    if((bt.tm_year!=et.tm_year)&&(bt.tm_mon!=et.tm_mon)&&(bt.tm_mday!=et.tm_mday)){
        //return 1 ,book or cancel time error
        m.setFlag(0);
        return 0;
    }
    int ret = 0;
    int weeknum = bt.tm_wday;
    int bth = bt.tm_hour;
    int eth = et.tm_hour;
    switch (weeknum) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        ret = CalcCost15(bth,eth);
        if(m.getFlag()==200) ret=ret/2;
        if(ret=0){
            if(m.getFlag()==200) m.setFlag(201);
            else m.setFlag(101);
        }
        break;
    case 0:
    case 6:
        ret = CalcCost67(bth,eth);
        if(m.getFlag()==200) ret = ret/4;
        if(ret=0){
            if(m.getFlag()==200) m.setFlag(201);
            else m.setFlag(101);
        }
    }
    return ret;
}

int DefaultCost::getSumcost(){
    return this->sumcost;
}

void DefaultCost::addSumcost(int s){
    this->sumcost = getSumcost()+s;
}
