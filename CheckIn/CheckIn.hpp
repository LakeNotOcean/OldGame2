#pragma once

#include <memory>
#include <string>
#include <set>
#include <queue>
#include "../creatures/ICreatures.hpp"
#include "../GameController/GameConst.hpp"


template <typename T>
using spp=std::shared_ptr<T>;
template <typename T>
using wpp=std::weak_ptr<T>;


using creature::ICreature;


namespace checkin{

    class CheckIn{
        public:
            CheckIn();
            bool isUsedName(std::string &name);
            std::string NoWrongAnswer(std::string &phrase);
            std::string NoWrongName(std::string &phrase);
            ClassNames NoWrongClass(std::string &phrase);
            ActionsNames NoWrongAct(std::string &phrase,spp<ICreature> creature);
            int NoWrongInt(std::string &phrase,int max,spp<ICreature> c=nullptr);
            void EraseName(std::string name);
        private:
             std::string isHelp(std::string &phrase,spp<ICreature> creatur=nullptr);
            void Help(std::string word,spp<ICreature> c);
            std::set<std::string> NamesOfObj;
        
    };

    int GetInteger(std::string &phrase);
    bool isInteger(std::string &s);
}


namespace Special{
    extern const std::set<std::string> SpecialWords;
}
