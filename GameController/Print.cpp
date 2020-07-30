#include "Print.hpp"


#include <iostream>


using std::endl;
using std::cout;
using std::cin;

void print::PrintTargets(std::string &phrase,std::vector<spp<ICrTargets>> &targets){
    cout << endl << phrase << endl;
    for (int i=0; i<targets.size(); ++i) {
        cout << targets[i]->GetName() << '(' << i+1 << ')';
        cout << " hp:" << targets[i]->GetHp() <<  '(' << targets[i]->GetMaxHp() << ')';
        cout << " класс - " << GetFromType::GetClassName(targets[i]->GetClassName());
        PrintPos(targets[i]->GetPos());
        cout << endl;
    }
    cout << endl;
}

void print::PrintCreatures(std::vector<spp<ICreature>> &creatures){
    for (int i=0; i<creatures.size(); ++i){
        cout << '(' << i+1 << ')';
        PrintCrBriefly(creatures[i]);
    }
}



void print::PrintHelp(){
    cout << endl << "Возможные команды:" << endl;
    cout << "help, classes, enemy, friends, help, crinfo, acts" << endl;
    cout << "Выбор цели или действия осуществляется с помощью ввода соответствующего номера" << endl;
    cout << "0 - выход из режима выбора целей" << endl;
}

void print::PrintClasses(){
    cout << endl << "Список классов" << endl;
    cout << "SwordsMan(0)" << endl;
    cout << "Archer(1)" << endl;
    cout << "Priest(2)" << endl;
    cout << "Boomer(3)" << endl;
}

void print::PrintActs(spp<ICreature> creature){
    cout << GetFromType::GetActName(ActionsNames::defense)<< "(0) ";
    for (int i=1; i<static_cast<int>(MaxConst::ActMax); ++i)
        if (creature->isAction(static_cast<ActionsNames>(i)))
            cout << GetFromType::GetActName(static_cast<ActionsNames> (i)) <<'(' << i << ')'<< " ";
    cout << endl;
}

void print::PrintFriends(spp<IPlayer> player){
    cout << endl;
    for (int i=0; i<MaxConst::NumbOfCr; ++i){
        auto cr=player->GetCreature(i);
        if (!cr->isDead())
            PrintCrBriefly(cr);
    }
    cout << endl;
}

void print::PrintEnemy(spp<IPlayer> player){
    print::PrintFriends(player->GetEnemy());
}


void print::PrintPos(coordinates  pos){
    cout <<'(' << pos.GetX() << ',' << pos.GetY() << ')';
}




void print::PrintCrInfo(spp<ICreature> creature){
    cout << endl;
    cout << "Имя: " << creature->GetName() << endl;
    cout << "Класс: " << GetFromType::GetClassName(creature->GetClassName()) << endl;
    cout << "Здоровье: " << creature->GetHp() << endl;
    cout << "Броня: " << creature->GetArmore() << endl;
    cout << " Координаты: "; PrintPos(creature->GetPos()); cout << endl; 
    cout << "Имеет следующие скиллы: " << endl;
    PrintActs(creature);
}

void print::PrintCrBriefly(spp<ICreature> creature){
    cout << creature->GetName() << '(' << GetFromType::GetClassName(creature->GetClassName())
    << ')' << " игрока " <<creature->GetMaster()->GetName()
    << ' ' << "hp(" << creature->GetHp() << ") pos"; PrintPos(creature->GetPos()); 
    cout << endl;
}