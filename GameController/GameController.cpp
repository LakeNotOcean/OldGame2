#include "GameController.hpp"

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

GameController::GameController(){
    std::string phrase="Введите имя первого игрока",name;
    name=_check.NoWrongName(phrase);
    _A=IPlayer::MakePlayer(name);
    phrase="Введите имя второго игрока";
    name=_check.NoWrongName(phrase);
    _B=IPlayer::MakePlayer(name);
    _A->SetEnemy(_B); _B->SetEnemy(_A);
    _expA=0; _expB=0;
}

void GameController::Round(){
    _map.RemoveDead();
    _A->AddCreatures(_check,_map,true);
    _B->AddCreatures(_check,_map,false);
    _A->MakeQueue(); _B->MakeQueue();
    cout <<endl << "###НАЧАЛО РАУНДА###" << endl;
    int expA=0,expB=0;
    while (_A->GetTopInitiative()>0 && _B->GetTopInitiative()>0){
        if (_A->GetTopInitiative()>_B->GetTopInitiative()){
            expA=_A->TopCreatureAct(_check,_map);
            if (_B->GetTopInitiative()>0)
                expB=_B->TopCreatureAct(_check,_map);
        }
        else {
            expB=_B->TopCreatureAct(_check,_map);
            if (_A->GetTopInitiative()>0)
                expA=_A->TopCreatureAct(_check,_map);
        }
        _expA+=expA;
        _expB+=expB; 
    }
    
    if (_A->GetTopInitiative()>0) {
        cout << endl << "Победил игрок " << _A->GetName() << endl;
        _A->NextLevel(_check,_map,_expA);
    }
    if (_B->GetTopInitiative()>0) {
        cout << endl << "Победил игрок " << _B->GetName() << endl;
        _B->NextLevel(_check,_map,_expB);
    }    
    cout << endl << "###КОНЕЦ РАУНДА###" << endl;

}