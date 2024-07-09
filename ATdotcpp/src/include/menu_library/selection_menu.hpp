#pragma once
#include <ncurses.h>
#include <cstring>
#include "menu_creator.cpp"
#include "menu_creator_options.cpp"
#include "Market_menu.cpp"
 








 



class Menu_selector: public Options_menu{

    private:

    struct menu_start_pause{//menù di start e pausa
        char titolo[20];
        scelta varie[10];
        int len;
        
    };

    menu_start_pause start,pausa,newgame,shop;
    WINDOW*win;
    int monete;
    int prezzi_aggiornati[7]{0,200,150,500,100,300,3000},slot_upgrade[4];
    bool restored=false,double_j=false;

    struct menu_vari{//lista di menù
        menu_vari *next;
        menu_vari *prev;
        scelta selection;
    };

    typedef menu_vari *p_menu;
    
   
    public:



    Menu_selector(WINDOW *win);

    void inizializza_start();//inizializzo struct contenente menù di start

    void inizializza_shop();////inizializzo struct contenente menù shop

    void inizializza_pause();//inizializzo struct contenente menù di pausa

    void inizializza_newgame();//inizializzo struct contenente menù della NG

    void draw_box();//modifico box a secodna delle impostazioni

    void change_color();//cambio colore delle scritte  a seconda delle impostazioni




    scelta menu_selector(bool is_pause, bool newgameplus=false, bool is_market=false,int budget=0,bool dj=false,bool has_restored=false);//gestore di liste-menù, permette di muoversi fra un menù e l'altro

    void get_prezzi(int array_prz[]);

    void update_prz(int array_prz[]);

    int get_monete();

    void get_array_up(int arr[]);//get array upgrade

    bool get_restored_hp();

    bool get_doubleJ();


    

    
    


    

    


    





    

};
