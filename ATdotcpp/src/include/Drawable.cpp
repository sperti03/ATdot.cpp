#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include "Drawable.hpp"


    
        Drawable::Drawable(){
            y=x=0;
            icon=' ';
        }

        Drawable::Drawable(int y, int x , chtype ch){
            this->y=y;
            this->x=x;
            this->icon=icon;
        }

        int Drawable::getx(){
            return x;
        }

        int Drawable::gety(){
            return y;
        }

        chtype Drawable::geticon(){
            return icon;
        }
  
  
        
