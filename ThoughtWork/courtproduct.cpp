#include "courtproduct.h"

AbstractCourt::AbstractCourt(){
}

AbstractCourt::~AbstractCourt(){
}

void BadmintonCourt::show(){
    std::map<time_t,std::string>::iterator it = costlog.begin();
    std::cout<<"场地:"<<this->getName()<<std::endl;
    for(;it!=costlog.end();++it){
        std::cout<<(*it).second<<std::endl;
    }
    std::cout<<"小计: "<<this->cost->getSumcost()<<std::endl;
}
void BadmintonCourt::setName(std::string s){
    this->name = s;
}
void BadmintonCourt::setAddress(std::string s){
    this->address = s;
}
std::string BadmintonCourt::getName(){
    return this->name;
}

std::string BadmintonCourt::getAddress(){
    return this->address;
}

BadmintonCourt::~BadmintonCourt(){

}

BadmintonCourt::BadmintonCourt(){

}

void BadmintonCourt::setCost(Cost *cost){
    this->cost = cost;
}

void BadmintonCourt::setRecord(Record* record){
    this->record = record;
}
