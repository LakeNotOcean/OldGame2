#include "creatures.hpp"
#include "../GameController/Print.hpp"


#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>

SpecificationsCreature::SpecificationsCreature(std::string name,ClassNames ClassName,
int hp,int armore,int initiative,coordinates c)
    : _armore(armore), _pos(c),_initiative(initiative),_ClassName(ClassName)
{
    _MaxHp=hp;
    _hp=hp;
    _defense=0;
    _name=name;

}

int SpecificationsCreature::GetHp() {
    return _hp;
}

int SpecificationsCreature::GetMaxHp(){
    return _MaxHp;
}
int SpecificationsCreature::GetArmore(){
    return _armore;
}
int SpecificationsCreature::GetInitiative(){
    return _initiative;
}
std::string SpecificationsCreature::GetName() {
    return _name;
} 
coordinates SpecificationsCreature::GetPos() {
    return _pos;
} 
bool SpecificationsCreature::isDefense() {
    return _defense;
}
bool SpecificationsCreature::isDead() {
    if (_hp<=0)
        return true;
    return false;
}
void SpecificationsCreature::ChangeMaxHp(int change){
    _MaxHp=change;
}

void SpecificationsCreature::AddHp(int add){
    _hp+=add;
}


ClassNames SpecificationsCreature::GetClassName() {
    return _ClassName;
}

void SpecificationsCreature::ChangeDefense(){
    _defense=(_defense==0)?1:0;
}




Creature::Creature(std::string name,ClassNames ClassName,
    int hp,int armore,int initiative,coordinates c)
        :SpecificationsCreature(name,ClassName,hp,armore,initiative,c){}


SwordsMan::SwordsMan(std::string name,coordinates c):Creature(name,ClassNames::SwordsMan,
    GetFromType::GetMaxHp(ClassNames::SwordsMan),30,10,c){
        AddAction(ActionsNames::melee,50);

}

Archer::Archer(std::string name,coordinates c):Creature(name,ClassNames::Archer,
    GetFromType::GetMaxHp(ClassNames::Archer),10,20,c){
        AddAction(ActionsNames::distant,30);

}

Priest::Priest(std::string name,coordinates c):Creature(name,ClassNames::Priest,
    GetFromType::GetMaxHp(ClassNames::Priest),0,15,c){
        AddAction(ActionsNames::heal,20);

}

HighPriest::HighPriest(std::string name,coordinates c):Creature(name,ClassNames::HighPriest,
    GetFromType::GetMaxHp(ClassNames::HighPriest),5,15,c){
        AddAction(ActionsNames::heal,20);
        AddAction(ActionsNames::distant,20);

}

Boomer::Boomer(std::string name,coordinates c):Creature(name,ClassNames::Boomer,
    GetFromType::GetMaxHp(ClassNames::Boomer),5,10,c){
        AddAction(ActionsNames::boom,15);
    }


using std::cout;
using std::cin;
using std::endl;

spp <ICreature> creature::MakeCreature(
    ClassNames ClassOf,std::string name,coordinates pos){
            spp<ICreature> c;
            switch(ClassOf) {
                case ClassNames::SwordsMan:
                    c=std::make_shared<SwordsMan>(name,pos);
                    break;
                case ClassNames::Archer:
                    c=std::make_shared<Archer>(name,pos);
                    break;
                case ClassNames::Priest:
                    c=std::make_shared<Priest>(name,pos);
                    break;
                case ClassNames::HighPriest:
                    c=std::make_shared<HighPriest>(name,pos);
                    break;
                case ClassNames::Boomer:
                    c=std::make_shared<Boomer>(name,pos);
                    break;
                default:
                    c=std::make_shared<SwordsMan>(name,pos);
                    break;
            }
    cout << "Герой создан " << GetFromType::GetClassName(ClassOf) << endl;
    return c;   
}

void Creature::GetDamage(int damage){
    cout << "Нанесено: " << damage <<' ' << "Урона" << endl;
    AddHp(-damage);
    if (isDead()) 
        cout << "Герой мертв" << endl;
}

int Creature::GetHeal(int hp){
    if (GetHp()+hp>GetMaxHp())
        hp-=GetHp()+hp-GetMaxHp();
    AddHp(hp);
    cout << "Востановленно: " << hp <<  endl;
    return hp;
}
void Creature::AddAction(ActionsNames name,int add){
    _acts[name]=action::MakeAct(name,add);
}

spp<IPlayer> Creature::GetMaster(){
    return _master.lock();
}

void Creature::GiveMaster(spp<IPlayer> master){
    _master=master;
}

bool Creature::isAction(ActionsNames name){
    if (_acts.find(name)!=_acts.end())
        return true;
    return false;
}


int Creature::DoAction(ActionsNames act,spp<ICrTargets> target){
    return _acts[act]->act(target);
}



