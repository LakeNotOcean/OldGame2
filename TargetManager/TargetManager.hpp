#pragma once

#include "ITargetManager.hpp"

class SingleTar:public ICrTargets{
    public:
        std::string GetName() override;
        ClassNames GetClassName() override;
        int GetHp() override;
        int GetMaxHp() override;
        coordinates GetPos() override;
        std::pair<spp<ICreature>,double> GetCr() override;
        void PushCr(wpp<ICreature> creature,double quotient) override;
        bool isEmpty() override;
        virtual ~SingleTar(){};
    private:
        wpp<ICreature> _creature;
};

class MultiTar: public ICrTargets{
    public:
        std::string GetName() override;
        ClassNames GetClassName() override;
        int GetHp() override;
        int GetMaxHp() override;
        coordinates GetPos() override;
        std::pair<spp<ICreature>,double> GetCr() override;
        void PushCr(wpp<ICreature> creature,double quotient) override;
        bool isEmpty() override;
        virtual ~MultiTar(){};
    private:
        std::queue <std::pair<wpp<ICreature>,double>> _creatures;
};

