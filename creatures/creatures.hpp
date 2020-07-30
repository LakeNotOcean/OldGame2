#pragma once


#include <memory>
#include "ICreatures.hpp"
#include "../actions/IAction.hpp"
#include <string>
#include <unordered_map>

template <typename T>
using spp=std::shared_ptr<T>;
template <typename T>
using wpp=std::weak_ptr<T>;

using creature::ICreature;
using action::IAction;


class SpecificationsCreature:public ICreature{
    public:
        SpecificationsCreature(std::string name,ClassNames ClassName,int hp,int armore,int initiative,coordinates c);
        int GetHp() override;
        int GetMaxHp() override;
        int GetArmore() override;
        int GetInitiative() override;
        std::string GetName() override;
        coordinates GetPos() override;
        ClassNames GetClassName() override;
        bool isDefense() override;
        bool isDead() override;
        void ChangeDefense() override;
        void ChangeMaxHp(int change);
    protected:
        void AddHp(int add);
        virtual ~SpecificationsCreature(){}
    private:
        const ClassNames _ClassName;
        bool _defense;
        int _hp,_MaxHp;
        const int _armore,_initiative;
        coordinates _pos;
        std::string _name;
};


class Creature:public SpecificationsCreature, public std::enable_shared_from_this<Creature>{
    public:
        Creature(std::string name,ClassNames ClassName,
            int hp,int armore,int initiative,coordinates c);
        void GetDamage(int damage) override;
        int GetHeal(int hp) override;
        spp<IPlayer> GetMaster() override;
        bool isAction(ActionsNames name) override;
        int DoAction(ActionsNames act,spp<ICrTargets> target) override;
        void AddAction(ActionsNames name,int add);
        void GiveMaster(spp<IPlayer> master) override;
    protected:
        virtual ~Creature(){}
    private:
        wpp<IPlayer> _master;
        std::unordered_map<ActionsNames,spp<IAction>> _acts;
          
};

class SwordsMan: public Creature{
    public:
        SwordsMan(std::string name,coordinates c);
        virtual ~SwordsMan(){};
    
};

class Archer: public Creature{
    public:
        Archer(std::string name,coordinates c);
        virtual ~Archer(){};
};

class Priest:public Creature{
    public:
        Priest(std::string name,coordinates c);
        virtual ~Priest(){};
};

class  HighPriest:public Creature{
    public:
        HighPriest(std::string name,coordinates c);   
        virtual ~HighPriest(){};
};

class Boomer:public Creature{
    public:
        Boomer(std::string name,coordinates c);
        virtual ~Boomer(){};
};
