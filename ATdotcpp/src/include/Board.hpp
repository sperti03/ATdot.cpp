#pragma once
#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include "Drawable.cpp"
#include "matrice.cpp"
#include "shop.cpp"
using namespace std;


class Board{

    public: 
    Board();

    Board(int height, int width,int speed);

    void initialize(int lat,int orz,GameMap a,SHOP s,int** matr,bool market);

    void addBorder(GameMap A,SHOP S,int** matr,int lat=0, int orz=0,bool pause=false, bool is_market=false);
    
    chtype getCharAt(int y, int x);

    chtype getplat();

    chtype getexit();
    
    int getheight();

    void clear(int lat,int orz, GameMap a,int** matr,SHOP s,bool market);

    void refresh();
    
    chtype getInput();

    void getEmptyCoord(int& y,int& x);

    int getTimeout();

    void setTimeout(int speed);

    WINDOW* getwin();

    WINDOW* getwin_menu();

    int getyMax();

    void construct(int height, int width, int speed);

    private:
    WINDOW* board_win;
    int height, width;
    int timeout;
    int x,y;
    chtype piattaforma;
    chtype exit;
    chtype trap;


};