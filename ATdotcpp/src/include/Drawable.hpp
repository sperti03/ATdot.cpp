#pragma once
#include <ncurses.h>
#include <stdlib.h>

class Drawable{
    public:
    int y,x;
    chtype icon;
    
        Drawable();

        Drawable(int y, int x , chtype ch);

        int getx();

        int gety();

        chtype geticon();
  
    protected:
        
};