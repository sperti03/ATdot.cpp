#include "Drawable.cpp"
#include "Board.cpp"
#include <ncurses.h>
#include "Enemy.hpp"
#pragma once





    Enemy::Enemy(){
        init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
        this->y= this->x=0;
        this->icon ='w'| COLOR_PAIR(5);
        turn=false;
        shooter=false;
        timer=0;
        int speed;
        }
    
    Enemy::Enemy(int y, int x, WINDOW* board, bool type,int lvl,int diff_lvl){
        init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
        init_pair(7,COLOR_BLUE,COLOR_BLACK);
        this->y=y;
        this->x=x;
        int speed=0;
        if(type==false)
            this->icon ='w'| COLOR_PAIR(5);
        else
            this->icon='w'| COLOR_PAIR(7);
        turn=false;
        lvl_scaling(lvl,diff_lvl);
        if(type){
            shooter=true;
            timer=5;}
        else{
            shooter=false;
            timer=0;}
        }
        
    void Enemy::switchturn(){
        turn=!turn;
    }

    //aumenta difficoltà di lvl in lvl
    void Enemy::lvl_scaling(int lvl,int diff_lvl){
     int original_hp=100;
     int damage_bullets=30,damage_melee=10;
     lvl--;
     if(diff_lvl>1){
        original_hp=original_hp + (original_hp/10)*diff_lvl;//il modificatore diff delle impopstazioni aumenta del 10% le stats nemiche 
        damage_bullets=damage_bullets + (damage_bullets/10)*diff_lvl;
        damage_melee=damage_melee + (damage_melee/10)*diff_lvl;
        }
     if(lvl==0){
        vita=original_hp;
        danno_b=damage_bullets;
        danno_m=damage_melee;
     }else{
        vita=original_hp+(original_hp/10)*lvl;//ogni lvl la vita aumenta del 10%
        danno_b=damage_bullets + (damage_bullets/10)*lvl;//ogni lvl i danni aumentano del 10%
        danno_m=damage_melee + (damage_melee/10)*lvl;
     }   
    }
    


    void Enemy::get_damaged(int d){
        this->vita=this->vita-d;
    }

    int Enemy::get_damage_bullets(){
        return -danno_b;
    }

    int Enemy:: get_damage_melee(){
        return -danno_m;
    }
 


