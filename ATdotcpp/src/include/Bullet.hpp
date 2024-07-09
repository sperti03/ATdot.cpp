#pragma once 

#include <ncurses.h>
#include "Drawable.cpp"
#include "Board.cpp"
#include "Protagonist.hpp"


class Bullet: public Drawable{

    public:
    Bullet(int yb, int xb, Direction dir,int t);

    Direction getdirection();

    int gettype();

    int getcurrrange();
    
    void incrrange();

    chtype getnext(Board board);

    Bullet();








    protected:
        Direction d;
        int type; //se type == 0 allora il proiettile è del protagonista, sennò è dei nemici
        int currange=0;
} ;