#pragma once

#include "GameConst.hpp"
#include "../TargetManager/ITargetManager.hpp"
#include "../player/IPlayer.hpp"


namespace print{
    void PrintTargets(std::string &phrase,std::vector<spp<ICrTargets>> &targets);
    void PrintCreatures(std::vector<spp<ICreature>> &creatures);
    void PrintHelp();
    void PrintClasses();
    void PrintActs(spp<ICreature> creature);
    void PrintFriends(spp<IPlayer> player);
    void PrintEnemy(spp<IPlayer> player);
    void PrintCrInfo(spp<ICreature> creature);
    void PrintCrBriefly(spp<ICreature> creature);
    void PrintPos(coordinates  pos);
}