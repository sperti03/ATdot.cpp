#pragma once 

#include <ncurses.h>
#include "Drawable.cpp"
#include "Board.cpp"
#include "Heal.hpp"


    Heal::Heal(int y, int x){
        init_pair(111,COLOR_CYAN, COLOR_BLACK);
        this->icon='^'| COLOR_PAIR(111);
        this->x=x;
        this->y=y;
    }
    
    Heal::Heal(){
        init_pair(111,COLOR_CYAN,COLOR_BLACK);
        this->icon='^'| COLOR_PAIR(111);
        this->x=0;
        this->y=0;
    }

