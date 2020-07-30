#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <array>
#include <queue>

#include "IPlayer.hpp"
#include "../GameController/GameConst.hpp"



class Player:public IPlayer{
    public:
        Player(std::string name);
        int GetTopInitiative() override;
        std::string GetName() override;
        spp <ICreature> GetCreature(int numb) override;
        spp<IPlayer> GetEnemy() override;
        void AddCreatures(CheckIn &check,TargetManager &map,bool isA) override;
        void AutoAdd(CheckIn &check,TargetManager &map,bool isA);
        void SetEnemy(spp<IPlayer> p) override;
        void MakeQueue() override;
        void ClearQueue() override;
        int TopCreatureAct(CheckIn &check,TargetManager &map) override;
        void NextLevel(CheckIn &check,TargetManager &map,int exp) override;
        virtual ~Player(){};
    private:
        std::vector <spp<ICreature>> MayBeNextLevel(int exp);
        void replaceCr(spp<ICreature> cr,TargetManager &map);
        std::string _name;   
        wpp <IPlayer> _enemy;
        int _CountNames;
        std::array<spp<ICreature>,MaxConst::NumbOfCr> _creatures;
        std::queue<spp<ICreature>> _que;
};

struct CompareInit{
    bool operator()(const spp <ICreature>& c1,const spp <ICreature>& c2) const{
        return c1->GetInitiative()<c2->GetInitiative();
    }
};


