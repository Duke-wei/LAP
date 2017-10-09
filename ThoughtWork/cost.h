#ifndef COST_H
#define COST_H
#include<ctime>
#include "message.h"
class Cost{
public:
    virtual ~Cost()=0;
    virtual int getCost(Message& m)=0;
    virtual int getSumcost()=0;
    virtual void addSumcost(int t)=0;
    int sumcost;
protected:
    Cost();
};
class DefaultCost:public Cost{
public:
    DefaultCost();
    ~DefaultCost();
    int getCost(Message& m);
    int getSumcost();
    void addSumcost(int t);
private:
    int CalcCost15(int t,int d);
    int CalcCost67(int t,int d);
};
#endif // COST_H
