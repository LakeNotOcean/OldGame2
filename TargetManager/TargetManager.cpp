#include "TargetManager.hpp"


#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

template <typename T>
using spp=std::shared_ptr<T>;
template <typename T>
using wpp=std::weak_ptr<T>;

using namespace Msize;




std::string SingleTar::GetName(){
    if (_creature.use_count()==0)
        return "#";
    return _creature.lock()->GetName();
}

ClassNames SingleTar::GetClassName(){
    if (_creature.use_count()==0)
        return ClassNames::Nothing;
    return _creature.lock()->GetClassName();
}


int SingleTar::GetHp(){
    if (_creature.use_count()==0)
        return -1;
    return _creature.lock()->GetHp();
}


int SingleTar::GetMaxHp(){
    if (_creature.use_count()==0)
        return -1;
    return _creature.lock()->GetMaxHp();
}


std::pair<spp<ICreature>,double> SingleTar::GetCr(){
    auto cr=_creature.lock();
    _creature=wpp<ICreature>();
    return std::make_pair(cr,1.0);
}

void SingleTar::PushCr(wpp<ICreature> creature,double quotient){
    _creature=creature;
}
        
        
bool SingleTar::isEmpty(){
    if (_creature.use_count()==0)
        return true;
    return false;
}

coordinates SingleTar::GetPos(){
    if (_creature.use_count()==0)
        return coordinates();
    return _creature.lock()->GetPos();
}

std::string MultiTar::GetName(){
    if (_creatures.empty())
        return "#";
    auto cr=_creatures.front();
    return cr.first.lock()->GetName();
}

ClassNames MultiTar::GetClassName(){
    if (_creatures.empty())
        return ClassNames::Nothing;
    auto cr=_creatures.front();
    return cr.first.lock()->GetClassName();
}


int MultiTar::GetHp(){
    if (_creatures.empty())
        return -1;
    auto cr=_creatures.front();
    return cr.first.lock()->GetHp();
}


int MultiTar::GetMaxHp(){
    if (_creatures.empty())
        return -1;
    auto cr=_creatures.front();
    return cr.first.lock()->GetMaxHp();
}

coordinates MultiTar::GetPos(){
    if (_creatures.empty())
        return coordinates();
    auto cr=_creatures.front();
    return cr.first.lock()->GetPos();
;    
}

std::pair<spp<ICreature>,double> MultiTar::GetCr(){
    auto cr=_creatures.front();
    _creatures.pop();
    return std::make_pair(cr.first.lock(),cr.second);
}

void MultiTar::PushCr(wpp<ICreature> creature,double quotient){
    _creatures.push(std::make_pair(creature,quotient));
}

bool MultiTar::isEmpty(){
    return _creatures.empty();
}

void TargetManager::PushCr(spp<ICreature> cr){
    _map[cr->GetPos()]=cr;
}

void TargetManager::RemoveDead(){
    std::vector<coordinates> selected;
    for (auto &el:_map)
        if (el.second.lock()->isDead())
            selected.push_back(el.first);
    for (int i=0; i<selected.size(); ++i)
        _map.erase(selected[i]);
}

void TargetManager::EraseAll(){
    _map.clear();
}


std::vector<spp<ICrTargets>> TargetManager::MakeTargets(coordinates pos,ActionsNames act,spp<IPlayer> p){
    switch (act) {
    case ActionsNames::melee:
        return MakeMelee(pos,p);
        break;
    case ActionsNames::distant:
        return MakeDistant(pos,p);
        break;
    case ActionsNames::heal:
        return MakeHeal(pos,p);
        break;
    case::ActionsNames::boom:
        return MakeBoom(pos,p);
    default:
        return MakeMelee(pos,p);
        break;
    }
}

std::vector<spp<ICrTargets>> TargetManager::MakeMelee(coordinates pos,spp<IPlayer> p){
    bool isBack=1;
    std::vector<spp<ICrTargets>> targets;
    for (int i=1; i<=MaxY; ++i){
        if (!isBack)
            break;
        for (int j=1; j<=MaxX; ++j) {
            coordinates curr(j,i);
            if (!_map[curr].lock()->isDead() 
            && _map[curr].lock()->GetMaster()!=p){
                spp<ICrTargets> target=std::make_shared<SingleTar>();
                target->PushCr(_map[curr],1.0);
                targets.push_back(target);
                isBack=0;
            }      
        }
    }
    return targets;
}

std::vector<spp<ICrTargets>> TargetManager::MakeHeal(coordinates pos,spp<IPlayer> p){
    std::vector<spp<ICrTargets>> targets;
    for (int i=1; i<=MaxY; ++i)
        for (int j=1; j<=MaxX; ++j){
            coordinates curr(j,i);
            if (!_map[curr].lock()->isDead()
            && _map[curr].lock()->GetMaster()==p) {
                spp<ICrTargets> target=std::make_shared<SingleTar>();
                target->PushCr(_map[curr],1.0);
                targets.push_back(target);
            }
        }
    return targets;
}

std::vector<spp<ICrTargets>> TargetManager::MakeDistant(coordinates pos,spp<IPlayer> p){
    std::vector<spp<ICrTargets>> targets;
    for (int i=1; i<=MaxY; ++i)
        for (int j=1; j<=MaxX; ++j){
            coordinates curr(j,i);
            if (!_map[curr].lock()->isDead()
            && _map[curr].lock()->GetMaster()!=p) {
                spp<ICrTargets> target=std::make_shared<SingleTar>();
                target->PushCr(_map[curr],1.0);
                targets.push_back(target);
            }
        }
    return targets;
}

std::vector<spp<ICrTargets>> TargetManager::MakeBoom(coordinates pos,spp<IPlayer> p){
    std::vector <spp<ICrTargets>> targets;
    for (int i=1; i<=MaxY; ++i)
        for (int j=1; j<=MaxX; ++j){
            coordinates curr(j,i);
            if (!_map[curr].lock()->isDead()
            && _map[curr].lock()->GetMaster()!=p){
                spp<ICrTargets> target=std::make_shared<MultiTar>();
                double qoutient=1.0;
                target->PushCr(_map[curr],qoutient);
                int d1[]={1,0,-1,0};
                int d2[]={0,1,0,-1};
                int i1,j1;
                for (int k=0; k<4; ++k){
                    i1=d1[k]+i; j1=d2[k]+j;
                    if (i1>1 && j1>1 && i1<=MaxY && j1<=MaxX){
                        coordinates pos(j1,i1);
                        if (!_map[pos].lock()->isDead())
                            target->PushCr(_map[pos],qoutient/2);
                    }
                }
                targets.push_back(target);
            }
        }
    return targets;
}