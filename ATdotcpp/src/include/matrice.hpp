#include<ncurses.h>
#include<iostream>
#include<ctime>
#include<stdio.h>
#pragma once


using namespace std;



class GameMap {
    private:
    int rows;
    int cols;
    int**matrix;
    chtype** B;
    
public: 
    GameMap();

    GameMap(int x, int y);

    

    int getx();

    int gety();

    int** createMap() ;


bool giocabile() ;


    void translateMap(chtype plat,int** matr) ;

    void printMap(WINDOW* win);




};