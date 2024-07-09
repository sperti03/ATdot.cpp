#pragma once

#include <ncurses.h>
#include <iostream>
#include "mercante.cpp"

using namespace std;

class SHOP {
private:
    int cols;
    int rows;
    int** matrix;
    chtype** B;

public:
    SHOP(int x, int y);

    int** costruct_shop();

    void translate_shop(chtype plat);

    void print_shop(WINDOW* win);



};
























