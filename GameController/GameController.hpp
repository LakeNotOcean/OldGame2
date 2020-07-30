#pragma once

#include "../CheckIn/CheckIn.hpp"
#include "../player/IPlayer.hpp"
#include "../TargetManager/ITargetManager.hpp"

using checkin::CheckIn;

class GameController{
    public:
        GameController();
        void Round();
        ~GameController(){};
    private:
        CheckIn _check;
        TargetManager _map;
        spp<IPlayer> _A,_B;
        int _expA,_expB;
}; 