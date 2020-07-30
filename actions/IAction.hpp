#pragma once

#include <memory>
#include "../TargetManager/ITargetManager.hpp"
#include "../GameController/GameConst.hpp"


template <typename T>
using spp=std::shared_ptr<T>;
template <typename T>
using wpp=std::weak_ptr<T>;

namespace action{

class IAction{
    public:
        virtual int act(spp<ICrTargets> target)=0;
    protected:
        virtual ~IAction(){};
};

    spp<IAction> MakeAct(ActionsNames name,int add);
}