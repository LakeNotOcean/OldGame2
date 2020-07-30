#pragma once

#include <string>
#include <array>
#include <unordered_map>
#include "../position/Iposition.hpp"


enum class ActionsNames{
    defense,melee,distant,heal,boom
};
enum class ClassNames{
    SwordsMan,Archer,Priest,Boomer,HighPriest,Nothing
};


using std::array;

namespace MaxConst{
    const int CreateMax=4;
    const int ClassMax=5;
    const int ActMax=5;
    const int NumbOfCr=4;
}

namespace experience{
    const int ExpForKill=50;
    const int expForHeal=1;
}


namespace Msize{
    const int MaxX=2;
    const int MaxY=4;
    const int MinX=1;
    const int MinY=1;
    const int Aforward=2;
    const int Bforward=3;
}


namespace GetFromType{
    int GetMaxHp(ClassNames name);
    std::string GetActName(ActionsNames act);
    std::string GetClassName(ClassNames name);
    int NumbOfActs(ClassNames name,ActionsNames act);
    bool isNextLevel(ClassNames name,int exp);
    ClassNames GetNextLevel(ClassNames name);

    extern const array<array<int,static_cast<int>(MaxConst::ClassMax)>,
        static_cast<int>(MaxConst::ActMax)> TNumbOFActs;
    extern const std::unordered_map<ClassNames,ClassNames> NextLevel;
    extern const std::unordered_map<ClassNames,int> CostOfClasses;
}
   

namespace DefaultPos{
    extern const array<coordinates,MaxConst::NumbOfCr> GetDefPosA;
    extern const array<coordinates,MaxConst::NumbOfCr> GetDefPosB;
}
