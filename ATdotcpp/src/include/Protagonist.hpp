#pragma once 
#include <ncurses.h>
#include "Drawable.hpp"
#include "Coin.cpp"
#include "Board.cpp"





enum Direction{
    sinistra=-1,
    destra=1,
    sopra=2,
    nessuna=0
};


class Protagonist: public Drawable{
    Direction cur_direction;
    bool jumping,double_j;
    int maxJumpHeight=5;
    int jumpHeight=0;
    int score;
    int vita,max_vita;
    int melee_damage;
    int num_bullet=10,max_bullet=10;
    int bullet_damage;
    int timer=5;
    int maxjumps=1;
    int curjump=0;
    int weaponrange=30;

    public:
        //costruttore di default
        Protagonist();
        
        //costruttore con parametri
        Protagonist(int y, int x, WINDOW* board );

        //upgrade delle statistiche del protagonista
        void upgrade_vita(int vita_aggiuntiva);
        
        void upgrade_melee_dmg(int dmg_aggiuntivo);
        
        void upgrade_bull_dmg(int dmg_aggiuntivo);
        
        void upgrade_bullets(int bullets_aggiuntive);
        
        void restored_hp(bool has_restored);

        //funzioni di get
        
        int getscore();

        int getvita();

        int getmaxjump();

        int getcurjump();
        
        int getweaponrange();
               
        int getnumbullet();

        int get_max_bullets();
        
        int get_meleedamage();

        int get_bulletdamage();

        int get_timer();

        int get_max_vita();
        
        Direction getDirection();
        
        void have_doublej(bool doublej);

        
        //funzioni di set
        void setcurjump(int val);

        void Update_protg(int monete, int vita, int bullets);

        void SetDirection(Direction d);

        void updatevita(int v);

        void change_budget(int bg);
 
        void setbullet(int n);
        
        void updatescore(int sc);
        
        void set_timer(int n);

        void shootingtimer();
        
        void resetjump();

        void setJump(bool val);

        //funzioni di check e movimento
        Drawable next_place(Board board);

        void moveprot(Board board);
        
        void gravity(Board board);

        void jump(Board board);
        
        



        };