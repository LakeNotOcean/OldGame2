#pragma once

#include <memory>
#include "IAction.hpp"

template <typename T>
using spp=std::shared_ptr<T>;
template <typename T>
using wpp=std::weak_ptr<T>;


using action::IAction;

class SpecAction:public IAction{
    public:
        SpecAction(int add);
    protected:
        int GetAdd() const;
        virtual ~SpecAction(){};
    private:
        int _add;
        
};


class DamageAction:public SpecAction{
    public:
        DamageAction(int add);
        int act(spp<ICrTargets> target) override;
        virtual ~DamageAction(){};
};


class HealAction:public SpecAction{
    public:
        HealAction(int add);
        int act(spp<ICrTargets> target) override;
        virtual ~HealAction(){};
};


