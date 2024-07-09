#pragma once
#include <ncurses.h>
#include "menu_library/menu_creator.cpp"

class Mercante{
private:
WINDOW* win,win_shop;

public:
    Mercante(WINDOW*win);

    //tutte fuznioni di stampa e decorazioni estetiche

    void stampa_cappello();

    void stampa_faccia();

    void stampa_busto();

    void stampa_gambe();

    void stampa_mercante();

    void finestra_dialogo();

    void decorazioni_ax();

    void decorazioni_tnt();

    void decorazini_spade();

    void decorazioni_ak47();

    void dec_shop();

    void stampa_shop();


};