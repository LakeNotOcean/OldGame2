#pragma once

#include <memory>
#include <string>

#include "../position/Iposition.hpp"
#include "../GameController/GameConst.hpp"

template <typename T>
using spp=std::shared_ptr<T>;
template <typename T>
using wpp=std::weak_ptr<T>;

class ICrTargets;
class IPlayer;


namespace creature{

    class ICreature{
        public:
            virtual std::string GetName()=0;
            virtual int GetHp()=0;
            virtual int GetArmore()=0;
            virtual void GetDamage(int damage)=0;
            virtual int GetHeal(int hp)=0;
            virtual int GetInitiative()=0;
            virtual spp<IPlayer> GetMaster()=0;
            virtual coordinates GetPos()=0;
            virtual int GetMaxHp()=0;
            virtual ClassNames GetClassName()=0;
            virtual bool isDefense()=0;
            virtual bool isDead()=0;
            virtual bool isAction(ActionsNames name)=0;
            virtual void GiveMaster(spp<IPlayer> master)=0;
            virtual void ChangeDefense()=0;
            virtual int DoAction(ActionsNames act,spp<ICrTargets> target)=0;
        protected:
            virtual ~ICreature(){}
    };

    spp <ICreature> MakeCreature(
                ClassNames ClassOf,std::string name, coordinates coord);

}