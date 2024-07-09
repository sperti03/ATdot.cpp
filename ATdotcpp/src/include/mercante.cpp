
#pragma once
#include <ncurses.h>
#include "menu_library/menu_creator.cpp"
#include "mercante.hpp"


    Mercante::Mercante(WINDOW*win){
        this->win=win;
        init_pair(81,COLOR_RED,COLOR_BLACK);
        init_pair(82,COLOR_YELLOW,COLOR_BLACK);
        init_pair(83,COLOR_MAGENTA,COLOR_BLACK);
    }

    void Mercante::stampa_cappello(){
        Menu_creator colora(win);
        wattron(win,COLOR_PAIR(81));
        mvwprintw(win,19,48,"___");
        mvwprintw(win,20,45," _|_ _|_");//1 in per riga, 2 per colonna
        wattroff(win,COLOR_PAIR(81));
        colora.colora_scritta_ch(20,49,'$',true);
    }

    void Mercante::stampa_faccia(){
        wattron(win,COLOR_PAIR(82));
        mvwprintw(win,21,44," '(O 3 O)'");
        wattroff(win,COLOR_PAIR(82));
    }

    void Mercante::stampa_busto(){
        wattron(win,COLOR_PAIR(83));
        mvwprintw(win,22,44,"*==|-:-|==*");
        wattroff(win,COLOR_PAIR(83));

    }

    void Mercante::stampa_gambe(){
        wattron(win,COLOR_PAIR(83));
        mvwprintw(win,23,46," _| |_");
        wattroff(win,COLOR_PAIR(83));
    }

    void Mercante::stampa_mercante(){
        stampa_cappello();
        stampa_faccia();
        stampa_busto();
        stampa_gambe();
        finestra_dialogo();
    }

    void Mercante::finestra_dialogo(){
        mvwprintw(win,15,54," __________________");
        mvwprintw(win,16,54,"|     WELCOME!     |");
        mvwprintw(win,17,54,"|PRESS 'm' TO OPEN |");
        mvwprintw(win,18,54,"|    THE MARKET.   |");
        mvwprintw(win,19,54,"| _________________|");
        mvwprintw(win,20,54,"|/");
    }

    void Mercante::decorazioni_ax(){
        //1 ascia
        mvwprintw(win,20,7,"(>|-");
        mvwprintw(win,21,7,"  | ");
        mvwprintw(win,22,7,"  ! ");
        //2 ascia
        mvwprintw(win,20,13,"(>+<)");
        mvwprintw(win,21,13,"  |");
        mvwprintw(win,22,13,"  ! ");
        //3 ascia
        mvwprintw(win,20,19,"<|>  ");
        mvwprintw(win,21,19," | ");
        mvwprintw(win,22,19," ! ");


    }

    void Mercante::decorazioni_tnt(){
        mvwprintw(win,18,80,"  )  ");
        mvwprintw(win,19,80," ( ");
        mvwprintw(win,20,80,".-`-. ");
        mvwprintw(win,21,80,":TNT:  ");
        mvwprintw(win,22,80,":___:");
    }

    void Mercante::decorazini_spade(){
        mvwprintw(win,22,60," =={==========-  ");
    }

    void Mercante::decorazioni_ak47(){
        mvwprintw(win,21,26," ____q==y______,_");
        mvwprintw(win,22,23,"  /__.-^-|_|''`");

    }

    void Mercante::dec_shop(){
        decorazioni_ax();
        decorazioni_tnt();
        decorazini_spade();
        decorazioni_ak47();
    }

    void Mercante::stampa_shop(){
        stampa_mercante();
        dec_shop();
    }


