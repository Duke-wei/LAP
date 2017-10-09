#include "record.h"

Record::Record(){
}

Record::~Record(){
}

//默认记录
DefaultRecord::DefaultRecord(){
    //cout<<"DefaultRecord"<<endl;
}

DefaultRecord::~DefaultRecord(){

}

int DefaultRecord::checkRecordE(time_t bt,time_t et){
    for(int i=0;i<brecord.size();++i){
        time_t bibt = brecord[i].first;
        time_t biet = brecord[i].second;
        if(bt==bibt&&bt==biet){
            return i;
        }
    }
    return -1;
}

bool DefaultRecord::checkRecordI(time_t bt,time_t et){
    for(int i=0;i<brecord.size();++i){
        time_t rbt = brecord[i].first;
        time_t ret = brecord[i].second;
        if(bt==rbt&&et==ret) return false;
        if(bt<rbt&&et>rbt) return false;
        if(bt>rbt&&bt<ret) return false;
    }
    return true;
}

bool DefaultRecord::addRecord(Message& m){
    struct tm tt = m.getBTime();
    time_t bt = mktime(&tt);
    tt = m.getETime();
    time_t et = mktime(&tt);
    if(checkRecordI(bt,et)){
        brecord.push_back(tat(bt,et));
        sort(brecord.begin(),brecord.end());
        return true;
    }else{
        m.setFlag(101);
        return false;
    }
}

bool DefaultRecord::delRecord(Message& m){
    struct tm tt = m.getBTime();
    time_t bt = mktime(&tt);
    tt = m.getETime();
    time_t et = mktime(&tt);
    int ret = checkRecordE(bt,et);
    if(ret != -1){
        brecord.erase(brecord.begin()+ret);
        crecord.push_back(tat(bt,et));
        sort(crecord.begin(),crecord.end());
        return true;
    }else{
        m.setFlag(201);
        return false;
    }
}

void DefaultRecord::showRecord(){

}
