#include <ncurses.h>
#include "Drawable.cpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include "HUD.hpp"
#pragma once
using namespace std;


    
    HUD::HUD(){
        construct(0,0);
    }

    void HUD::printmenu(int punti,int vita,int bullets,int lvl){
        int start_vita=7;
        int start_bullets=9;
        chtype cuore=' '| COLOR_PAIR(3);
        chtype bullet=' '| COLOR_PAIR(8);
        werase(hud_menu);
        box(hud_menu,0,0);
        //mvwaddch(hud_menu,1,1,c);
        mvwprintw(hud_menu,2,2,"Coins:");
        mvwprintw(hud_menu,2,8,"%i",punti);
        mvwprintw(hud_menu,4,2,"vita:");
        for(int i=0;i<vita/10;i++){
            mvwaddch(hud_menu,4,start_vita,cuore);
            start_vita++;
        }
        mvwprintw(hud_menu,6,2,"bullet:");
        for(int i=0;i<bullets;i++){
            mvwaddch(hud_menu,6,start_bullets,bullet);
            start_bullets++;
        }
        mvwprintw(hud_menu,8,2,"level:");
        mvwprintw(hud_menu,8,8,"%i",lvl);
        refresh();
    }

    void HUD:: print_controls(){
        werase(controls_menu);
        box(controls_menu,0,0);
        mvwprintw(controls_menu,1,20,"CONTROLS");
        mvwprintw(controls_menu,3,2,"W: jump");
        mvwprintw(controls_menu,5,2,"A: move left");
        mvwprintw(controls_menu,7,2,"D: move right");
        mvwprintw(controls_menu,9,2,"SPACE: shoot");
        mvwprintw(controls_menu,11,2,"C: melee attack");
        mvwprintw(controls_menu,13,2,"R: reload");
        mvwprintw(controls_menu,15,2,"^: look up");
        mvwprintw(controls_menu,17,2,"<: look left");
        mvwprintw(controls_menu,19,2,">: look right");
        mvwprintw(controls_menu,21,2,"P: pause");
        mvwprintw(controls_menu,23,2,"M: market");
        refresh();
    }

    void HUD::clear(){
        //ripulisce tutto
        wclear(hud_menu);
        //riaggiunge la mappa
        printmenu(0,100,10,0);
        print_controls();
    }

    void HUD::refresh(){
        wrefresh(hud_menu);
        wrefresh(controls_menu);
    }
    
    void HUD::initialize(){
        clear();
        refresh();
    }   

    

void HUD::construct(int height, int width){
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(8, COLOR_WHITE, COLOR_BLUE);
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    this->height = height;
    this->width = width;
    init_pair(21, COLOR_WHITE, COLOR_GREEN);
    hud_menu = newwin(10, 50, yMax/2-20, 1);
    controls_menu = newwin(28, 50, yMax/2-8, 1);  // Modifica delle dimensioni e della posizione
}

