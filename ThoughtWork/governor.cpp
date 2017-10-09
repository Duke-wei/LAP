#include "governor.h"

using namespace std;
using namespace utiltool;
Governor::Governor(){

}

Governor::~Governor(){
    map<string,AbstractCourt*>::iterator it = msc.begin();
    for(;it!=msc.end();++it){
        delete (*it).second;
    }
}

void Governor::AddMember(AbstractCourt* s){
    msc[s->name] = s;
}

bool Governor::DelMember(const std::string& s){
    if(msc.count(s)>0){
        msc.erase(s);
        return true;
    }else
        return false;
}

void Governor::StateInput(const std::string& s){
    Message m;
    Message::Str2Message(s,m);
    StateCheck(m);
    if(m.getFlag()==100){
        StateBook(m);
    }else if(m.getFlag()==200){
        StateCancel(m);
    }
    StateOutput(m);
}

void Governor::StateOutput(Message& m){
    //0  input error
    //100 book sucess
    //101 book fail
    //200 cancel sucess
    //201 cancel fail
    if(m.getFlag()==0){
        std::cout<<utiltool::STATE_ERROR<<endl;
    }else if(m.getFlag()==100){
        std::cout<<utiltool::STATE_BSUC<<endl;
    }else if(m.getFlag()==101){
        std::cout<<utiltool::STATE_BFAI<<endl;
    }else if(m.getFlag()==200){
        std::cout<<utiltool::STATE_CSUC<<endl;
    }else if(m.getFlag()==201){
        std::cout<<utiltool::STATE_CFAI<<endl;
    }
}

void Governor::StateCheck(Message& m){
    if(m.getUname()==""){
        //input error
        m.setFlag(0);
    }else if(msc.count(m.getUname())>0){
        if(m.getCancel()=="c"){
            m.setFlag(200);
        }else if(m.getCancel()==""){
            //book check ok
                m.setFlag(100);
        }else{
            //cancel fail , error cancel input
            m.setFlag(201);
        }
    }else{
        //book fail,no court
        m.setFlag(101);
    }
}

void Governor::StateBook(Message& m){
    AbstractCourt* court = msc[m.getCourtname()];
    int costfee = court->cost->getCost(m);
    if(m.getFlag()==100){
        bool bookflag = court->record->addRecord(m);
        if(bookflag){
            court->cost->addSumcost(costfee);
            struct tm bt= m.getBTime();
            time_t t = mktime(&bt);
            string log = m.getTimestring()+" "+to_string(costfee)+"元";
            court->costlog[t] = log;
        }
    }
}

void Governor::StateCancel(Message& m){
    AbstractCourt* court = msc[m.getCourtname()];
    int costfee = court->cost->getCost(m);
    if(m.getFlag()==200){
        bool bookflag = court->record->delRecord(m);
        if(bookflag) {
            struct tm bt = m.getBTime();
            time_t t = mktime(&bt);
            string log = m.getTimestring()+" 违约金 "+to_string(costfee)+"元";
            court->costlog[t] = log;
            court->cost->addSumcost(costfee);
        }
    }
}

void Governor::StateShow(){
    std::cout<<"收入汇总"<<endl;
    std::cout<<"---"<<endl;
    map<string,AbstractCourt*>::iterator it = msc.begin();
    for(;it!=msc.end();++it){
        AbstractCourt* court = (*it).second;
        court->show();
    }
}
