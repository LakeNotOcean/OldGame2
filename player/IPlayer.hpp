#pragma once


#include <string>
#include <vector>


#include "../CheckIn/CheckIn.hpp"
#include "../TargetManager/ITargetManager.hpp"

template <typename T>
using spp=std::shared_ptr<T>;
template <typename T>
using wpp=std::weak_ptr<T>;

using creature::ICreature;
using checkin::CheckIn;

class IPlayer:public std::enable_shared_from_this<IPlayer>{
    public:
        virtual std::string GetName()=0;
        virtual int GetTopInitiative()=0;
        virtual spp<IPlayer> GetEnemy()=0;
        virtual spp <ICreature> GetCreature(int numb)=0;
        virtual void SetEnemy(spp<IPlayer> p)=0;
        virtual void AddCreatures(CheckIn &check,TargetManager &map,bool isA)=0;
        virtual void MakeQueue()=0;
        virtual int TopCreatureAct(CheckIn &check,TargetManager &map)=0;
        virtual void NextLevel(CheckIn &check,TargetManager &map,int exp)=0;
        static spp<IPlayer> MakePlayer(std::string name);
    protected:
        virtual ~IPlayer(){} 
        virtual void ClearQueue()=0;   
};