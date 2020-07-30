#pragma once

#include "../creatures/ICreatures.hpp"
#include "../position/Iposition.hpp"

#include <queue>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


template <typename T>
using spp=std::shared_ptr<T>;
template <typename T>
using wpp=std::weak_ptr<T>;

using creature::ICreature;

class ICrTargets{
    public:
        virtual std::string GetName()=0;
        virtual ClassNames GetClassName()=0;
        virtual int GetHp()=0;
        virtual int GetMaxHp()=0;
        virtual coordinates GetPos()=0;
        virtual std::pair<spp<ICreature>,double> GetCr()=0;
        virtual void PushCr(wpp<ICreature> creature,double quotient)=0;
        virtual bool isEmpty()=0;
    protected:
        virtual ~ICrTargets(){};
    private:
};

class TargetManager{
    public:
        ~TargetManager(){};
        void PushCr(spp<ICreature> cr);
        void RemoveDead();
        void EraseAll();
        void printcoord();
        std::vector<spp<ICrTargets>> MakeTargets(coordinates pos,ActionsNames act,spp<IPlayer> p);
        std::vector<spp<ICrTargets>> MakeMelee(coordinates pos,spp<IPlayer> p);
        std::vector<spp<ICrTargets>> MakeHeal(coordinates pos,spp<IPlayer> p);
        std::vector<spp<ICrTargets>> MakeDistant(coordinates pos,spp<IPlayer> p);
        std::vector<spp<ICrTargets>> MakeBoom(coordinates pos,spp<IPlayer> p);
    private:
        std::unordered_map<coordinates,wpp<ICreature>,HashFunc> _map;    
};