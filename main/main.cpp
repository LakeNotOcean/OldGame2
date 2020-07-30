#include "../GameController/GameController.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(){
    int r;
    GameController game;
    std::string phrase="Введите количество раундов";
    r=checkin::GetInteger(phrase);
    for (int i=0; i<r; ++i)
        game.Round();
    return 0;
}