#include "Drawable.cpp"
#include "Board.cpp"
#include <ncurses.h>
#pragma once



class Enemy: public Drawable{
protected:

//due tipi di nemici, uno normale e uno shooter
public:
bool turn;
int vita;
int danno_b,danno_m;
bool shooter;
int timer;
int speed;

    Enemy();
    
    Enemy(int y, int x, WINDOW* board, bool type,int lvl,int diff_lvl);
        
    void switchturn();

    //aumenta difficoltà di lvl in lvl
    void lvl_scaling(int lvl,int diff_lvl);

    void get_damaged(int d);

    int get_damage_bullets();

    int get_damage_melee();
 



};