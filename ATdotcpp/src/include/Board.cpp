#pragma once
#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include "Drawable.cpp"
#include "matrice.cpp"
#include "shop.cpp"
#include "Board.hpp"
using namespace std;


    //costruttore di default
    Board::Board(){
        construct(0,0,300);
    }
    
    //costruttore con parametri
    Board::Board(int height, int width,int speed){
        construct(height,width,speed);
    }

    //inizializza la finestra
    void Board::initialize(int lat,int orz,GameMap a,SHOP s,int** matr,bool market){
        clear(lat,orz,a,matr,s,market);
        refresh();
    }   
    
    //stampa la mappa e il negozio sulla board
    void Board::addBorder(GameMap A,SHOP S,int** matr,int lat, int orz,bool pause, bool is_market){
        if((lat==(int)'N') && (orz==(int)'N')){//questa serie di if-else serve a impostare correttamente i bordi se modificati dalle impostazioni
            box(board_win,0,0);
        }else if(lat==(int)'N'){
            box(board_win,0,orz);
        }else if(orz==(int)'N'){
            box(board_win,lat,0);
        }else{
            box(board_win,lat,orz);
        }

    if(pause==false){
    if(is_market==false){
    A.translateMap(getplat(),matr);
    A.printMap(board_win);
    }else{
    S.costruct_shop();
    S.translate_shop(piattaforma);
    S.print_shop(board_win);
    }
    } else {
    if(is_market==false){
    A.translateMap(getplat(),matr);
    A.printMap(board_win);
    }else{
    S.costruct_shop();
    S.translate_shop(piattaforma);
    S.print_shop(board_win);
    }}

        
    }
    
    //funzioni di get sulla Board
    //prende l'elemento della board a coordinate y,x
    chtype Board::getplat(){
        return piattaforma;
    }
    
    chtype Board::getexit(){
        return exit;
    }

    chtype Board::getCharAt(int y, int x){
        return mvwinch(board_win,y,x);
    }
    
    int Board::getheight(){
        return height;
    }
     
    chtype Board::getInput(){
        chtype input = wgetch(board_win);   
        return input;
    }

    void Board::getEmptyCoord(int& y,int& x){
        while(true){
            y=rand()%height;
            x=rand()%width;
            if(mvwinch(board_win, y, x) == ' ' && mvwinch(board_win, y+1, x) == getplat() && 
               mvwinch(board_win, y+1, x-1) == getplat() && mvwinch(board_win, y+1, x+1) == getplat() &&
               mvwinch(board_win, y, x-1) == ' ' && mvwinch(board_win, y, x+1) == ' ')
                break;
        }
    }

    int Board::getTimeout(){
        return timeout;
    }

    WINDOW* Board::getwin(){
        return board_win;
    }

    WINDOW* Board::getwin_menu(){
        int xm,ym;
        getmaxyx(stdscr,ym,xm);
        WINDOW* win=newwin(40,40*2.5,ym/2-20,xm/2-(40*2.5)/2);
        return win;
    }

    int Board::getyMax(){
        return height;
    }

    //funzioni base sulla board
    void Board::setTimeout(int speed){
        timeout=speed;
        wtimeout(board_win,speed);
    }

    void Board::clear(int lat,int orz, GameMap a,int** matr,SHOP s,bool market){
        //ripulisce tutto
        wclear(board_win);
        //riaggiunge la mappa
        addBorder(a,s,matr,lat,orz,false,market);
        refresh();
        
    }

    void Board::refresh(){
        wrefresh(board_win);
    }
   
    void Board::construct(int height, int width, int speed){
            int ym, xm;//serve ad impostare board_win
            getmaxyx(stdscr, ym, xm);//serve ad impostare board_win
            this->height =height;
            this->width= width;
            init_pair(55, COLOR_BLUE, COLOR_GREEN);
            init_pair(200,COLOR_BLACK, COLOR_BLUE);
            this->piattaforma=' '| COLOR_PAIR(55);
            this->exit=' '| COLOR_PAIR(200);
            board_win= newwin(40,40*2.5,ym/2-20,xm/2-(40*2.5)/2);
            setTimeout(speed);
            keypad(board_win, true);
        }