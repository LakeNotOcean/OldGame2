#include "action.hpp"


#include <memory>

template <typename T>
using spp=std::shared_ptr<T>;
template <typename T>
using wpp=std::weak_ptr<T>;

SpecAction::SpecAction(int add):_add(add){}


DamageAction::DamageAction(int add)
    :SpecAction(add){}

HealAction::HealAction(int add)
    :SpecAction(add){}




int SpecAction::GetAdd() const {
    return _add;
}


int DamageAction::act(spp<ICrTargets> target){
    int KillCount=0;
    while (!target->isEmpty()) {
        auto cr=target->GetCr();
        if (!cr.first->isDead()) {
            int damage=GetAdd()*cr.second;
            if (cr.first->isDefense()) damage/=2;
            damage-=damage*cr.first->GetArmore()/100;
                cr.first->GetDamage(damage); 
            if (cr.first->isDead())
                ++KillCount;
        }
    }
    return experience::ExpForKill*KillCount;
}

int HealAction::act(spp<ICrTargets> target){
    int ans=0;
    while (!target->isEmpty()){
        auto cr=target->GetCr();
        int heal=GetAdd()*cr.second;
        ans+=cr.first->GetHeal(heal)*experience::expForHeal;
    }
    return ans;
}

spp<IAction> action::MakeAct(ActionsNames name, int add){
    spp <IAction> act;
        switch(name){
            case ActionsNames::melee:
            case ActionsNames::distant:
            case ActionsNames::boom:
                act=std::make_shared<DamageAction>(add);
                break;
            case ActionsNames::heal:
                act=std::make_shared<HealAction> (add);
                break;
        }
    return act;
}

