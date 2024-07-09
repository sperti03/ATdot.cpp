#pragma once
#include "menu_creator_options.cpp"
#include <ncurses.h>
#include <cstring>
#include <iostream>

class Market_menu: public Options_menu{
private:
WINDOW * win;
scelta shop_item[7]{"BUDGET","MELEE ATK +","HP +","BULLETS ATK +","MORE BULLETS","RESTORE HP","DOUBLE JUMP"};
scelta titolo[1]{"MARKET"};
scelta indietro[1]{"INDIETRO"};
int budget;
int prezzi[7];
int upgrade[4]{0,0,0,0};
bool restored_hp=false,double_j=false;
int opzioni_totali=7;


public:
    Market_menu(WINDOW* win,int budget,bool dj,bool has_restored);


    void stampa_item();

    void stampa_prezzi();

    void clear_prices(int asse_y);//rimuove dalla finestra prezzi precedenti

    void esaurito(int asse_y);//stampa esaurito 

    void stampa_market();

    void inizilizza_up();//inizializza array upgrade

    void update_prices(int opzione_corrente,int asse_y);//aggiorna i prezzi dopo compera

    scelta naviga_menu_market();

    

    void update_upgrade(int opzione_corrente);//aggiorna array degli upgrade a seconda di ciò che si è comprato

    void new_prices(int prezzi_aggiornati[],int len);//prendo in input array con prezzi aggiornati e lo uso per dettare i prezzi dello shop

    void get_upgrade(int up_array[],int len);

    void get_prezzi(int array_prezzi[],int len);

    int get_budget();

    bool get_double_j();

    bool get_restored();



};