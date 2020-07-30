#include "Iposition.hpp"


coordinates::coordinates(int x,int y):_x(x),_y(y){}

coordinates::coordinates():_x(0),_y(0){}

int coordinates::GetX() const{
    return _x;
}

int coordinates::GetY() const{
    return _y;
}

bool coordinates::operator ==(const coordinates &c) const{
    return (_x==c.GetX() && _y==c.GetY());
}

size_t HashFunc::operator()(const coordinates &c) const{
    size_t h1 = std::hash<int>()(c.GetX());
    size_t h2 = std::hash<int>()(c.GetY());
    return (h1 ^ (h2 << 1));   
}


