#pragma once

#include <cstddef>
#include <functional>

struct coordinates{
    public:
        coordinates(int x,int y);
        coordinates();
        int GetX() const;
        int GetY() const;
        ~coordinates(){};
        bool operator ==(const coordinates &c) const;
    private:
        int _x,_y;
};

//for unodered_map, key-coordinates
struct HashFunc{
    size_t operator()(const coordinates &c) const;
};