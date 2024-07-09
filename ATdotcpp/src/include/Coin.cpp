#pragma once 

#include <ncurses.h>
#include "Drawable.cpp"
#include "Board.cpp"
#include "Coin.hpp"


    Coin::Coin(int y, int x){
        init_pair(4,COLOR_YELLOW, COLOR_BLACK);
        this->icon='o'| COLOR_PAIR(4);
        this->x=x;
        this->y=y;
    }

    Coin::Coin(){
        init_pair(4,COLOR_YELLOW, COLOR_BLACK);
        this->icon='o'| COLOR_PAIR(4);
        this->x=0;
        this->y=0;
    }





 