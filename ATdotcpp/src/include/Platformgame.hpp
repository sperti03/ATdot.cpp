#pragma once 
#pragma comment(lib, "winmm.lib")

#include <ncurses.h>
#include "Coin.cpp"
#include "Board.cpp"
#include "Drawable.cpp"
#include "Protagonist.cpp"
#include "Enemy.cpp"
#include "Bullet.cpp"
#include "HUD.cpp"
#include <time.h>
#include <cstdlib>




class Platformgame{
    
    protected:

    Board game_win;
    Protagonist protg;
    bool game_over,go_back;
    string mode;
    HUD hud_menu;
    int move;
    int lat,orz;
    bool end_level,is_market;
    int rows,cols;
    int lvl,diff_lvl;
    int num_brawler,num_shooter,num_coins;
    int damage_b,damage_m;
    int true_lvl;
    int enemies_speed;
    bool new_game_plus=false;

    public:
    //strutture dati per le liste di oggetti
    struct enemylist{
        Enemy e;
        enemylist* next;
    };
    typedef enemylist* enemy_l;
    enemy_l list_enemy=NULL;

    struct coinlist{
        Coin c;
        coinlist* next;
    };
    typedef coinlist* coin_l;
    coin_l list_coin=NULL;

    struct bulletlist{
        Bullet b;
        bulletlist* next;
    };
    typedef bulletlist* bullet_l;
    bullet_l list_bullet=NULL;

    struct heallist{
        Heal h;
        heallist* next;
    };
    typedef heallist* heal_l;
    heal_l list_heal=NULL;

    //costruttore
    Platformgame(int BOARD_ROWS, int  BOARD_COLS, int lat,int orz, GameMap a,SHOP s,int** matr,int monete,int vita, int bullets,int lvl,int diff_lvl, bool next_level=false,bool prev_lvl=false,bool is_market=false,bool new_game_plus=false,int true_lvl=0);

    void initialize(int lat,int orz, GameMap a,SHOP s,int** matr,int monete,int vita, int bullets,bool next_level=false, bool prev_lvl=false);


    //numero di nemici deciso da lvl corrente
    void initialize_enemy_coins(int lvl);

    //push di oggetti nelle liste
    enemy_l enemyPush(enemy_l list_enemy,bool type,int lvl);
    coin_l coinPush(coin_l list_coin);
    heal_l healPush(heal_l list_heal);
    bullet_l bulletPush(bullet_l l,int y, int x,Direction d,int t);

    //pop di oggetti dalle liste
    coin_l coin_pop(coin_l list, int y, int x);
    enemy_l enemy_pop(enemy_l list, int y, int x, char type);
    heal_l heal_pop(heal_l list, int y, int x);



    ///funzioni di movimento degli oggetti
    void movebullet(Board board, bullet_l& list);
    void move_enemy(Board board, enemy_l list);


    //funzioni di stampa
    void stampa_coins(coin_l list_coin);
    void stampa_heal(heal_l list_heal);
    void stampa_objects();

    //funzioni protagonista
    void printhud(Protagonist prossimo,int lvl);
    void changeBG(int bg);
    Direction find_prot(Board board, int y, int x);
    void stampaprotg();
    void Falling();
    void upgrade_protg(int arry_up[],bool restored=false,bool double_j=false);

    //funzioni di gioco
    int getMonete();
    int getVita();
    int getBullets();
    bool LevelisOver();
    bool isOver();
    bool Go_Back();
    void redraw();
    void UpdateState();
    chtype ProcessInput();
    void redrawstd();






    
};