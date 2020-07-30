#include "Player.hpp"
#include "../GameController/Print.hpp"

#include <memory>
#include <string>
#include <array>
#include <vector>
#include <random>
#include <queue>
#include <iostream>


using std::cin;
using std::cout;
using std::endl;



Player::Player(std::string name){
    _name=name;
    _CountNames=0;
}


std::string Player::GetName() {
    return _name;
}

spp<IPlayer> Player::GetEnemy() {
    return _enemy.lock();
}

spp <ICreature> Player::GetCreature(int numb){
   return _creatures[numb]; 
}

void Player::SetEnemy(spp<IPlayer> p){
     _enemy=p;
}


 void Player::AddCreatures(CheckIn &check,TargetManager &map,bool isA){
    cout << endl << "Игрок " << GetName() << " создает существ" << endl;
    std::string phrase="Добавить существ автоматически?";
    std::string name=check.NoWrongAnswer(phrase);
    if (name=="Y")
        return AutoAdd(check,map,isA);
    for (int i=0; i<MaxConst::NumbOfCr; ++i) 
        if (_creatures[i]==nullptr || _creatures[i]->isDead()){
            ClassNames ClassOf;
            coordinates pos;
            if (_creatures[i]!=nullptr){
                check.EraseName(_creatures[i]->GetName());
                pos=_creatures[i]->GetPos();
            }
            else 
                pos=(isA)?(DefaultPos::GetDefPosA[i]):(DefaultPos::GetDefPosB[i]);
            if (pos.GetY()==Msize::Aforward || pos.GetY()==Msize::Bforward)
                phrase="Введите имя героя 1го ряда:";
            else phrase="Введите имя героя 2го ряда:";
            name=check.NoWrongName(phrase);
            phrase="Введите номер класса";
            ClassOf=check.NoWrongClass(phrase);
            _creatures[i]=creature::MakeCreature(ClassOf,name,pos);
            _creatures[i]->GiveMaster(shared_from_this());
            map.PushCr(_creatures[i]);
        }
        else _creatures[i]->GetHeal(_creatures[i]->GetMaxHp());
 }

 void Player::AutoAdd(CheckIn &check,TargetManager &map,bool isA){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distr(0,3);
    coordinates pos;
    for (int i=0; i<MaxConst::NumbOfCr; ++i) 
        if (_creatures[i]==nullptr || _creatures[i]->isDead()){
            if (_creatures[i]==nullptr){
                std::string name;
                do {
                    name=GetName()+std::to_string(_CountNames++);
                }while(check.isUsedName(name));
                pos=(isA)?(DefaultPos::GetDefPosA[i]):(DefaultPos::GetDefPosB[i]);
                _creatures[i]=creature::MakeCreature(static_cast<ClassNames>(distr(generator)),name,pos);
            }
            else if (_creatures[i]->isDead()){
                check.EraseName(_creatures[i]->GetName());
                std::string name=GetName()+std::to_string(_CountNames++);
                _creatures[i]=creature::MakeCreature(static_cast<ClassNames>(distr(generator)),name,
                _creatures[i]->GetPos());
            }
            _creatures[i]->GiveMaster(shared_from_this());
            map.PushCr(_creatures[i]);
        }
        else _creatures[i]->GetHeal(_creatures[i]->GetMaxHp());
 }

void Player::MakeQueue(){
    ClearQueue();
    std::priority_queue <ICreature,std::vector <spp<ICreature>>,CompareInit > priority;
    for (int i=0; i<MaxConst::NumbOfCr; ++i)
        priority.push(_creatures[i]);
    while (!priority.empty()){
        _que.push(priority.top());
        priority.pop();
    }
}

void Player::ClearQueue(){
     while (!_que.empty())
        _que.pop();
}

int Player::GetTopInitiative(){
    if (_que.empty())
        return -1;
    while (!_que.empty()){
        auto top=_que.front();
        if (!top->isDead())
            return top->GetInitiative();
        _que.pop();
    }
    return -1;
}

int Player::TopCreatureAct(CheckIn &check,TargetManager &map){
    auto creature=_que.front();
    _que.pop();
    cout << endl <<"Ходит: "; print::PrintCrBriefly(creature);
    if (creature->isDefense())
        creature->ChangeDefense();
    int exp=0;
    while (1){
        std::string phrase="Выберите действие: ";
        ActionsNames act=check.NoWrongAct(phrase,creature);
        if (act==ActionsNames::defense) {
            cout << "Выбрана защита" << endl;
            creature->ChangeDefense();
            _que.push(creature);
            return exp;
        }
        auto targets=map.MakeTargets(creature->GetPos(),act,shared_from_this());
        phrase="Возможные цели";
        print::PrintTargets(phrase,targets);
        phrase="Выберите цели";
        std::vector<spp<ICrTargets>> SelectedTargets;
        int MaxActs=GetFromType::NumbOfActs(creature->GetClassName(),act);
        for (int i=0; i<MaxActs; ++i){
            int choice=check.NoWrongInt(phrase,targets.size(),creature);
            if (choice==0)
                break;
            SelectedTargets.push_back(targets[choice-1]);
        }
        phrase="Выбранные цели";
        print::PrintTargets(phrase,SelectedTargets);
        phrase="Сделать ход?";
        std::string ans=check.NoWrongAnswer(phrase);
        if (ans=="Y"){
            for (int i=0; i<SelectedTargets.size(); ++i) 
                exp+=creature->DoAction(act,SelectedTargets[i]); 
            break;
            }
        }
    if (!creature->isDead())
        _que.push(creature);
    return exp;
}


void Player::NextLevel(CheckIn &check,TargetManager &map,int exp){
    cout << endl << "Игрок " << GetName() << " улучшает существ" << endl;
    while (1){
            auto candidates=MayBeNextLevel(exp);
            if (candidates.empty()){
            cout << endl << "Нет подходящих существ" << endl;
            return;
        }
        cout << endl << "Количество опыта: " << exp <<  endl;
        cout << endl << "Улучшение доступно для следующий существ:" << endl;
        print::PrintCreatures(candidates);
        std::string phrase="Выберите существо";
        int choice=check.NoWrongInt(phrase,candidates.size());
        if (choice==0)
            return;
        --choice;
        exp-=GetFromType::CostOfClasses.at(
            GetFromType::GetNextLevel(candidates[choice]->GetClassName()));
        replaceCr(creature::MakeCreature(
            GetFromType::GetNextLevel(candidates[choice]->GetClassName()),
            candidates[choice]->GetName(),
            candidates[choice]->GetPos()),map);
    }      
}

std::vector <spp<ICreature>> Player::MayBeNextLevel(int exp){
    std::vector <spp<ICreature>> ans;
    for (int i=0; i<MaxConst::NumbOfCr; ++i)
        if (!_creatures[i]->isDead() && 
        GetFromType::isNextLevel(_creatures[i]->GetClassName(),exp))
            ans.push_back(_creatures[i]);
    return ans;
}



spp<IPlayer> IPlayer::MakePlayer(std::string name){
    return  std::make_shared<Player>(name);
}

void Player::replaceCr(spp<ICreature> cr,TargetManager &map){
    for (int i=0; i<MaxConst::NumbOfCr; ++i)
        if (_creatures[i]->GetName()==cr->GetName()){
            map.PushCr(cr);
            _creatures[i]=cr;
            cr->GiveMaster(shared_from_this());
        }
}