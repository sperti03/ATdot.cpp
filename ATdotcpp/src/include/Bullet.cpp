#pragma once 

#include <ncurses.h>
#include "Drawable.cpp"
#include "Board.cpp"
#include "Protagonist.cpp"
#include "Bullet.hpp"



    Bullet::Bullet(int yb, int xb, Direction dir,int t){
        this->d=dir;
        init_pair(11,COLOR_BLUE, COLOR_BLACK);
        this->icon='+'| COLOR_PAIR(11);
        this->y=yb;
        this->x=xb;
        this->type=t;
        this->currange=0;
    }

    Direction Bullet::getdirection(){
        return d;
    }
    int Bullet::gettype(){
        return type;
    }

    int Bullet::getcurrrange(){
        return currange;
    }
    
    void Bullet::incrrange(){
        currange+=1;
    }

    chtype Bullet::getnext(Board board){
        switch (d)
        {
        case destra:
            return board.getCharAt(y,x+1);
            break;
        case sinistra:
            return board.getCharAt(y,x-1);
            break;
        case sopra:
            return board.getCharAt(y-1,x);
            break;
        default:
            break;
        }
    }

    Bullet::Bullet(){
        this->d=destra;
        init_pair(11,COLOR_BLUE, COLOR_BLACK);
        this->icon='+'| COLOR_PAIR(11);
        this->x=0;
        this->y=0;
        this->type=0;
    }





