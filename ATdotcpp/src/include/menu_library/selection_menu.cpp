#pragma once
#include <ncurses.h>
#include <cstring>
#include "selection_menu.hpp"
#include "menu_creator.cpp"
#include "menu_creator_options.cpp"
#include "Market_menu.cpp"
#include "../Platformgame.cpp"








 







    Menu_selector::Menu_selector(WINDOW *win):Options_menu(win){
        inizializza_start();
        inizializza_pause();
        inizializza_newgame();
        inizializza_shop();
        this->win=win;
        init_pair(11,2,0);
    }



    void Menu_selector::inizializza_start(){
        strcpy(start.titolo,"ATdot cpp"); 

        int i=0,len=4;
        start.len=len;

        scelta tmp[4]{"START","CONTINUA","IMPOSTAZIONI","ESCI"};


        for(;i<len;i++){
            strcpy(start.varie[i].varie,tmp[i].varie);
        }
    }

    void Menu_selector::inizializza_shop(){
        strcpy(shop.titolo,"MARKET");

        int i=0,len=2;
        shop.len=len;

        scelta tmp[2]{"MARKET","CONTINUA"};//aggiunta opzione market per il testing, da rimuovere


        for(;i<len;i++){
            strcpy(shop.varie[i].varie,tmp[i].varie);
        }
    }

    void Menu_selector::inizializza_pause(){
        strcpy(pausa.titolo,"PAUSA");
        
        int i=0,len=4;
        pausa.len=len;

        scelta tmp[4]{"CONTINUA","SALVA","IMPOSTAZIONI","ESCI"};

        for(;i<len;i++){
            strcpy(pausa.varie[i].varie,tmp[i].varie);
        }

    }

    void Menu_selector::inizializza_newgame(){
        strcpy(newgame.titolo,"GAME OVER");

        int i=0,len=2;
        newgame.len=len;

        scelta tmp[2]{"NEW GAME +","ESCI"};

        for(;i<len;i++){
            strcpy(newgame.varie[i].varie,tmp[i].varie);
        };
    }

    void Menu_selector::draw_box(){
        if(get_modifiche()==false || (get_bd_lat()==(int)'N' && get_bd_orz()==(int)'N')){

            box(win,0,0);

        }else if(get_bd_lat()==(int)'N'){

            box(win,0,get_bd_orz());

        }else if(get_bd_orz()==(int)'N'){

            box(win,get_bd_lat(),0);

        }else{
        
            box(win,get_bd_lat(),get_bd_orz());
        }
    }

    void Menu_selector::change_color(){
        init_pair(12,get_color_string(),0);
    }




    scelta Menu_selector::menu_selector(bool is_pause, bool newgameplus, bool is_market,int budget,bool dj,bool has_restored){
        p_menu head, list,garbage;
        Market_menu market(win,budget,dj,has_restored);
        bool has_saved=false;
        draw_box();
        change_color();
        head=new menu_vari;
        head->prev=NULL;
        box(win,0,0);
        if(is_pause==false && is_market==false){
        head->selection=naviga_menu(start.varie,start.len,start.titolo);
        }else if(newgameplus==true && is_market==false){
        head->selection=naviga_menu(newgame.varie,newgame.len,newgame.titolo);
        }else if(is_market==true){
        head->selection=naviga_menu(shop.varie,shop.len,shop.titolo);
        }else{
        draw_box();
        change_color();
        head->selection=naviga_menu(pausa.varie,pausa.len,pausa.titolo);
        }
        list=head;

        

        while((strcmp(list->selection.varie,"ESCI")!=0) && strcmp(list->selection.varie,"START")!=0 && strcmp(list->selection.varie,"CONTINUA")!=0){

            if(strcmp(list->selection.varie,"MARKET")==0){
                draw_box();
                change_color();
                list->next=new menu_vari;
                list->next->prev=list;
                list=list->next;
                market.new_prices(prezzi_aggiornati,7);
                list->selection=market.naviga_menu_market();
                market.get_prezzi(prezzi_aggiornati,7);
                market.get_upgrade(slot_upgrade,4);
                double_j=market.get_double_j();
                restored=market.get_restored();
                monete=market.get_budget();
            }

            if(strcmp(list->selection.varie,"IMPOSTAZIONI")==0){
                draw_box();
                change_color();
                list->next=new menu_vari;
                list->next->prev=list;
                list=list->next;
                list->selection=naviga_menu_opzioni();
            }

            if(strcmp(list->selection.varie,"INDIETRO")==0){
                draw_box();
                change_color();
                list=list->prev;

                garbage=list->next;
                delete garbage;
                list->next=NULL;

                if(is_pause==false && is_market==false){
                    list->selection=naviga_menu(start.varie,start.len,start.titolo);
                } else if(is_pause==true && is_market==false){
                    list->selection=naviga_menu(pausa.varie,pausa.len,pausa.titolo);
                } else{
                    list->selection=naviga_menu(shop.varie,shop.len,shop.titolo);
                }
            }

            if(strcmp(list->selection.varie,"NEW GAME +")==0){
                scelta tmp;
                strcpy(tmp.varie,"new");
                return tmp;
            }

            if(strcmp(list->selection.varie,"SALVA")==0){
                return list->selection;
            }
        }
        if(strcmp(list->selection.varie,"START")==0 || strcmp(list->selection.varie,"CONTINUA")==0 || strcmp(list->selection.varie,"ESCI")==0){
        wclear(win);
        wrefresh(win);
        return list->selection;
        }
            


        

    }

    void Menu_selector::get_prezzi(int array_prz[]){
        for(int i=0;i<7;i++){
            array_prz[i]=prezzi_aggiornati[i];
        }
    }

    void Menu_selector::update_prz(int array_prz[]){
        for(int i=0;i<7;i++){
            prezzi_aggiornati[i]=array_prz[i];
        }
    }

    int Menu_selector::get_monete(){
        return monete;
    }

    void Menu_selector::get_array_up(int arr[]){
        for(int i=0;i<4;i++){
            arr[i]+=slot_upgrade[i];
        }
    }

    bool Menu_selector::get_restored_hp(){
        return restored;
    }

    bool Menu_selector::get_doubleJ(){
        return double_j;
    }


    

    

