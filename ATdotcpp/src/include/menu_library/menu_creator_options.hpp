#pragma once
#include "menu_creator.cpp"
#include <ncurses.h>
#include <cstring>
#include <iostream>








class Options_menu: public Menu_creator{

    private:
    char titolo[8]{"OPZIONI"};
    scelta indietro[1]{"INDIETRO"};
    scelta freccia_sx[4]{"<","<","<","<"},freccia_dx[4]{">",">",">",">"};
    scelta menu_opzioni[4]{"DIFFICOLTA'","BORDO LATERALE","BORDO ORIZZONTALE","COLORE TESTO"};
    int sx=(xM/2)+11,dx=(xM/2)+15,centre=(xM/2)+13;
    int opzioni_totali=4;
    
    struct modificatori{
        int opzione_corrente;
        int valore_corrente;//valore associato a posizione in array, quindi è utile anche dove non c'è un display del valore in se
        char brd_lat[10]{'N','*','!','.','|','$','^','I','X','#'};
        char brd_orz[10]{'N','*','_','.','-','$','^','O','X','#'}; 
    };

    modificatori array_mod[4];
    bool has_been_modified=false;

    


    public:

    Options_menu(WINDOW*win);

    
    void stampa_varie_menu_opzioni(scelta menu_opz[],int opz_tot,char nome[],bool cambia_ax,int new_ax=0);

    void inizializza_mod();//inizializzo array modificatori

    void stampa_mod();

    void stampa_freccine();

    void stampa_menu_opzioni();

    void move_right(scelta optz_sx[],scelta optz_dx[],int asse_y,int opzione_corrente);//metodo per muoversi nel menù opzioni

    void move_left(scelta optz_sx[],scelta optz_dx[],int asse_y,int opzione_corrente);//metodo per muoversi nel menù opzioni

    void clean(int asse_y);

    void change_value_sx(int asse_y_corrente);//cambia valore opzione corrente 

    void change_value_dx(int asse_y_corrente);//cambia valore opzione corrente 

    scelta naviga_menu_opzioni();

    int get_bd_lat();//get bordo laterale

    int get_bd_orz();//get bordo orizzontale

    bool get_modifiche();

    int get_diff();

    int get_color_string();



    

};