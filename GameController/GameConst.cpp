#include "GameConst.hpp"

using namespace MaxConst;

const array<array<int,static_cast<int>(ActMax)>,
        static_cast<int>(ClassMax)> GetFromType::TNumbOFActs{
                //defense melee distant heal boom
    /*SwordsMan*/ {{1,1,0,0,0},
    /*Archer*/     {1,0,1,0,0},
    /*Priest*/      {1,0,0,2,0},
    /*Boomer*/      {1,0,0,0,1},
    /*HighPriest*/  {1,0,2,2,0}}
    };
const std::unordered_map<ClassNames,ClassNames> GetFromType::NextLevel{
        {ClassNames::Priest,ClassNames::HighPriest}
    };

const array<coordinates,NumbOfCr> DefaultPos::GetDefPosA{
    coordinates(1,1),coordinates(2,1),
    coordinates(1,2),coordinates(2,2)
};


const array<coordinates,NumbOfCr> DefaultPos::GetDefPosB{
    coordinates(1,3),coordinates(2,3),
    coordinates(1,4),coordinates(2,4)
};

const std::unordered_map<ClassNames,int> GetFromType::CostOfClasses{
    {ClassNames::HighPriest,50}
};

int GetFromType::GetMaxHp(ClassNames name){
    switch(name){
        case ClassNames::SwordsMan:
            return 50; 
        case ClassNames::Archer:
            return 30;
        case ClassNames::Priest:
            return 30;
        case ClassNames::HighPriest:
            return 35;
        case ClassNames::Boomer:
            return 20;
        default:
            return 10;
    }
}

std::string GetFromType::GetActName(ActionsNames act){
    switch(act){
        case ActionsNames::defense:
            return "defense";
        case ActionsNames::melee:
            return "melee";
        case ActionsNames::heal:
            return "heal";
        case ActionsNames::distant:
            return "distant";
        case ActionsNames::boom:
            return "boom";
        default:
            return "nothing";
    }
}

std::string GetFromType::GetClassName(ClassNames name){
    switch(name){
        case ClassNames::Archer:
            return "Archer";
        case ClassNames::SwordsMan:
            return "SwordsMan";
        case ClassNames::Priest:
            return "Priest";
        case ClassNames::HighPriest:
            return "HighPriest";
        case ClassNames::Boomer:
            return "Boomer";
        default:
            return "#";
    }
}


int GetFromType::NumbOfActs(ClassNames name,ActionsNames act){
    return TNumbOFActs[static_cast<int>(name)][static_cast<int>(act)];
}

bool GetFromType::isNextLevel(ClassNames name,int exp){
    if (GetNextLevel(name)!=ClassNames::Nothing && 
        CostOfClasses.at(GetNextLevel(name))<=exp)
        return true;
    return false;
}

ClassNames GetFromType::GetNextLevel(ClassNames name){
    if (NextLevel.find(name)!=NextLevel.end())
        return NextLevel.at(name);
    return ClassNames::Nothing;
}