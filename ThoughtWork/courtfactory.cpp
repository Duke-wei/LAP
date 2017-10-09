#include "courtfactory.h"

AbstractFactory::AbstractFactory(){
}

AbstractFactory::~AbstractFactory(){
}

//羽毛球场地工厂
BadmintonCourtFactory::BadmintonCourtFactory(){
}

BadmintonCourtFactory::~BadmintonCourtFactory(){
}

AbstractCourt* BadmintonCourtFactory::CreateCourt(){
    AbstractCourt* court = new BadmintonCourt();
    Cost* cost = new DefaultCost();
    Record* record = new DefaultRecord();
    court->setCost(cost);
    court->setRecord(record);
    return court;
}
