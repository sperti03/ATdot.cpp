#include <ncurses.h>
#include "Drawable.cpp"
#include <stdio.h>
#include <iostream>
#include <string>
#pragma once
using namespace std;

class HUD{


public:
    
    HUD();

    void printmenu(int punti,int vita,int bullets,int lvl);

    void clear();

    void refresh();
    
    void initialize();

    void print_controls();
    
protected:
WINDOW* hud_menu;
WINDOW* controls_menu;
int height, width,start_row,start_col;
void construct(int height, int width);

};