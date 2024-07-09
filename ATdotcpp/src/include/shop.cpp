#pragma once

#include <ncurses.h>
#include <iostream>
#include "mercante.cpp"
#include "shop.hpp"


    SHOP::SHOP(int x, int y) {
        this->cols = x;
        this->rows = y;

        // Inizializzazione della matrice con le dimensioni specificate
        matrix = new int*[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
        }

        B = new chtype*[rows];
        for (int i = 0; i < rows; i++) {
            B[i] = new chtype[cols];
        }
    }

    int** SHOP::costruct_shop() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = 0;
            }
        }

        /* Crea la base */
        for (int i = 0; i < cols; i++) {
            matrix[rows - 1][i] = 1;
        }

        /* Crea 5 piattaforme, ognuna delle quali costituisce uno shop per i potenziamenti */
        for (int i = 0; i < cols; i++) {
            if ((i > 5 && i < 21) || (i > 23 && i < 42) || (i > 43 && i < 53) || (i > 54 && i < 76) || (i > 78 && i < 84)) {
                matrix[rows - 15][i] = 1;
            }
        }
        return matrix;
    }

    void SHOP::translate_shop(chtype plat) {
        start_color();
        init_pair(32, COLOR_BLACK, COLOR_GREEN);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == 0) {
                    B[i][j] = ' ';
                } else if (matrix[i][j] == 1) {
                    B[i][j] = plat;
                }
            }
        }
    }

    void SHOP::print_shop(WINDOW* win) {
        Mercante merc(win);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mvwaddch(win, i + 1, j + 1, B[i][j]);
            }
        }
        merc.stampa_shop();
        wrefresh(win);
    }



























