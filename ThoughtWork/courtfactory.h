#ifndef COURTFACTORY_H
#define COURTFACTORY_H

#include "courtproduct.h"

//工厂方法模式
class AbstractFactory{
public:
    virtual ~AbstractFactory()=0;
    virtual AbstractCourt* CreateCourt()=0;
protected:
    AbstractFactory();
};


//羽毛球场地工厂
class BadmintonCourtFactory:public AbstractFactory{
public:
    BadmintonCourtFactory();
    ~BadmintonCourtFactory();
    AbstractCourt* CreateCourt();
};
#endif // COURTFACTORY_H
