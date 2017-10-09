#include <iostream>
#include "utiltool.h"
#include "courtfactory.h"
#include "courtproduct.h"
#include "governor.h"
#include "message.h"

using namespace std;
using namespace utiltool;

int main()
{
    string s;
    Governor governor;
    AbstractFactory* bmtfactory = new BadmintonCourtFactory();
    string ns[4]={"A","B","C","D"};
    for(int i=0;i<4;++i){
        AbstractCourt* bmtcourt = bmtfactory->CreateCourt();
        bmtcourt->setName(ns[i]);
        governor.AddMember(bmtcourt);
    }
    while(getline(cin,s)){
      //  cout<<s<<endl;
        if(s==" "){
            governor.StateShow();
        }else{
        //cout<<s<<endl;
            governor.StateInput(s);
        }
    }

//    struct tm bt;
//    DateTool::string2tm("1970-01-02 00:00:00",bt);
//    cout<<bt.tm_year<<" "
//       <<bt.tm_mon<<" "
//       <<bt.tm_mday<<" "
//       <<bt.tm_hour<<" "
//       <<bt.tm_min<<" "
//       <<bt.tm_sec<<" "
//       <<bt.tm_wday<<" "
//       <<bt.tm_yday<<" "
//       <<endl;
    return 0;
}
