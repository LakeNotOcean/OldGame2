#include "CheckIn.hpp"
#include "../GameController/Print.hpp"

#include <memory>
#include <string>
#include <set>
#include <iostream>




template <typename T>
using spp=std::shared_ptr<T>;
template <typename T>
using wpp=std::weak_ptr<T>;


using std::cout;
using std::cin;
using std::endl;

using Special::SpecialWords;
using checkin::CheckIn;
using checkin::isInteger;


const std::set<std::string> Special::SpecialWords{
    "classes","enemy","friends","help","crinfo","acts",
};

CheckIn::CheckIn(){
    cout << endl << "Для просмотра возможных команд введите help" << endl;
}

std::string CheckIn::isHelp(std::string &phrase,spp<ICreature> creature){
    std::string in;
    while (1){
        cout << endl << phrase << endl;
        cin >> in;
        if (SpecialWords.find(in)!=SpecialWords.end())
            Help(*SpecialWords.find(in),creature);
        else return in;
    }
}

bool CheckIn::isUsedName(std::string &name){
    if (NamesOfObj.find(name)!=NamesOfObj.end())
        return true;
    return false;
}

void CheckIn::Help(std::string word,spp<ICreature> creature){
    if (word=="help")
        return print::PrintHelp();
    if (word=="classes")
        return print::PrintClasses();
    if (creature!=nullptr){
        if (word=="friends")
            return print::PrintFriends(creature->GetMaster());
        if (word=="enemy")
            return print::PrintEnemy(creature->GetMaster());
        if (word=="crinfo")
            return print::PrintCrInfo(creature);   
        if (word=="acts")   
            return print::PrintActs(creature);   
    }
    cout << endl << "В данный момент невозможно" << endl;
}


std::string CheckIn::NoWrongAnswer(std::string &phrase){
    std::string in;
    phrase+="(Y/N)";
    while (1){
        in=isHelp(phrase);
        if (in=="Y" || in=="N")
            return in;
        }
}

std::string CheckIn::NoWrongName(std::string &phrase){
    std::string in;
    while (1){
        in=isHelp(phrase);
        if (isUsedName(in))
            cout << "Такое имя уже есть" << endl;
        else {
            NamesOfObj.insert(in);
            return in;
        }
    }
}

ClassNames CheckIn::NoWrongClass(std::string &phrase){
    std::string in;
    while (1){
        in=isHelp(phrase);
        if (isInteger(in)) {
            int CrClass=stoi(in);
            if (CrClass>=0 && CrClass<MaxConst::CreateMax)
                return static_cast<ClassNames> (CrClass);
        }
        cout << "Такого класса нет" << endl;
    }
}

ActionsNames CheckIn::NoWrongAct(std::string &phrase,spp<ICreature> creature){
    std::string in;
    while (1){
        in=isHelp(phrase,creature);
        if (isInteger(in)){
            int ActClass=stoi(in);
            if (ActClass==0)
                return static_cast<ActionsNames> (ActClass);
            if (ActClass>0 && ActClass<MaxConst::ActMax
            && creature->isAction(static_cast<ActionsNames>(ActClass)))
                return static_cast<ActionsNames> (ActClass);  
            cout << endl << "Такого действия нет" << endl;  
        }
    }
}

int CheckIn::NoWrongInt(std::string &phrase,int max,spp<ICreature> c){
    std::string in;
    while (1){
        in=isHelp(phrase,c);
        if (isInteger(in)){
            int choice=stoi(in);
            if (choice==0)
                return choice;
            if (choice<=max)
                return choice;
        }
    }
}

void CheckIn::EraseName(std::string name){
    if (NamesOfObj.find(name)!=NamesOfObj.end())
        NamesOfObj.erase(name);
}

int checkin::GetInteger(std::string &phrase){
    std::string in;
    while (1){
        cout << endl << phrase << endl;
        cin >> in;
        if  (isInteger(in))
            return std::stoi(in);
    }
}

bool checkin::isInteger(std::string &s){
    for (int i=0; i<s.size(); ++i)
        if (s[i]<'0' || s[i]>'9')
            return false;
    return true;
}
