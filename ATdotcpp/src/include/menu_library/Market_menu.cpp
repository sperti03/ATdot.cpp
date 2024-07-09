#pragma once
#include "menu_creator_options.cpp"
#include "Market_menu.hpp"
#include <ncurses.h>
#include <cstring>
#include <iostream>


    Market_menu::Market_menu(WINDOW* win,int budget,bool dj,bool has_restored):Options_menu(win){
        this->win=win;
        double_j=dj;
        restored_hp=has_restored;
        this->budget=budget;
        prezzi[0]=this->budget;
    }


    void Market_menu::stampa_item(){
        stampa_varie_menu_opzioni(shop_item,7,"MARKET",true,(xM/2)-20);
    }

    void Market_menu::stampa_prezzi(){
        int asse_y=calcola_posizione_y(opzioni_totali),incr=calcola_posizione_y(opzioni_totali);
        for(int i=0;i<opzioni_totali-1;i++){
            clear_prices(asse_y);
            if(i==0) mvwprintw(win,asse_y,(xM/2)+20,"%i",prezzi[i]);
            else colora_scritta_int(asse_y,(xM/2)+20,prezzi[i],true);
            asse_y+=incr;
        }
        if(double_j==false)colora_scritta_int(asse_y,(xM/2)+20,3000,true);
        else{
            esaurito(asse_y);
        }
    }

    void Market_menu::clear_prices(int asse_y){
        mvwprintw(win,asse_y,(xM/2)+20,"     ");
    }

    void Market_menu::esaurito(int asse_y){
       mvwprintw(win,asse_y,(xM/2)+20,"ESAURITO");
    }

    void Market_menu::stampa_market(){
        stampa_item();
        stampa_prezzi();
    }

    void Market_menu::inizilizza_up(){
        for(int i=0;i<4;i++){
            upgrade[i]=0;
        }
    }

    void Market_menu::update_prices(int opzione_corrente,int asse_y){
        if(opzione_corrente<5){//le opz di aquisto < 5 hanno compere infinite, il resto sono singole
        if(prezzi[0]-prezzi[opzione_corrente]>=0){//verifico di avere abbstanza soldi per comprare
        prezzi[0]=prezzi[0]-prezzi[opzione_corrente];
        prezzi[opzione_corrente]=(prezzi[opzione_corrente]) + (prezzi[opzione_corrente]/10);//prezzi aumentano del 10% a compera
        update_upgrade(opzione_corrente);
        stampa_prezzi();//aggiorno prezzi
        }
        }else{
            if(prezzi[0]-prezzi[opzione_corrente]>=0){// cura tutta la vita, 1 compera a market
                if(opzione_corrente==5 && restored_hp==false){
                    prezzi[0]=prezzi[0]-prezzi[opzione_corrente];
                    prezzi[opzione_corrente]=(prezzi[opzione_corrente]) + (prezzi[opzione_corrente]/10);
                    update_upgrade(opzione_corrente);
                    stampa_prezzi();
                }
                if(opzione_corrente==6 && double_j==false){//item unica
                    prezzi[0]=prezzi[0]-prezzi[opzione_corrente];
                    prezzi[opzione_corrente]=(prezzi[opzione_corrente]) + (prezzi[opzione_corrente]/10);
                    update_upgrade(opzione_corrente);
                    stampa_prezzi();
                    esaurito(asse_y);
                }
            }
        }
    }

    scelta Market_menu::naviga_menu_market(){
        

        int asse_y=calcola_posizione_y(opzioni_totali),incr=asse_y,opzione_corrente=0,asse_x=(xM/2)-20,check;
        chtype input;
        int controllo;
        bool end=false,back=false;
        //restored_hp=false;
        inizilizza_up();
        
        stampa_market();

        while(end!=true){
        input=getInput();

        switch(input){

            case KEY_UP:
            if(back==true){
                    non_evidenziare_opzione(indietro,calcola_posizione_y(opzioni_totali)*(opzioni_totali+1),0);
                    move_up(shop_item,asse_y,opzione_corrente,incr,true,asse_x);
                    back=false;
            } else if(opzione_corrente-1>0) move_up(shop_item,asse_y,opzione_corrente,incr,true,asse_x);
            break;

            case KEY_DOWN:
            controllo=asse_y+1;
                if(controllo>incr*opzioni_totali){
                    non_evidenziare_opzione(shop_item,calcola_posizione_y(opzioni_totali)*opzioni_totali,opzione_corrente,true,asse_x);
                    evidenzia_opzione(indietro,calcola_posizione_y(opzioni_totali)*(opzioni_totali+1),0);
                    back=true;
                }else{
                    move_down(shop_item,asse_y,opzione_corrente,incr,opzioni_totali ,true,asse_x);
                }
            break;

            case 10:
            if(back!=true){
                update_prices(opzione_corrente,asse_y);
            }else{
            wclear(win);
            end=true;
            budget=prezzi[0];
            }
            break;

            default:
            break;


        }
       

    }
    return indietro[0];
    }

    

    void Market_menu::update_upgrade(int opzione_corrente){
        int melee_up=10,hp_up=10,dmg_b_up=5,more_b=1;

        switch (opzione_corrente)
        {
        case 1:
            upgrade[0]+=melee_up;
            break;
        
        case 2:
            upgrade[1]+=hp_up;
            break;

        case 3:
            upgrade[2]+=dmg_b_up;
            break;

        case 4:
            upgrade[3]+=more_b;
            break;
        
        case 5:
            restored_hp=true;
            break;

        case 6:
            double_j=true;
            break;
        
        default:
            break;
        }
    }

    void Market_menu::new_prices(int prezzi_aggiornati[],int len){//fa update dei prezzi
        for(int i=1;i<len;i++){
            prezzi[i]=prezzi_aggiornati[i];//budget non deve essere aggoirnato, parto quindi da cella 1
        }
    }

    void Market_menu::get_upgrade(int up_array[],int len){
        for(int i=0; i<len; i++){
            up_array[i]=upgrade[i];
        }
    }

    void Market_menu::get_prezzi(int array_prezzi[],int len){//ritorna i prezzi dopo averli modificati
        for(int i=0;i<len;i++){
            array_prezzi[i]=prezzi[i];
        }
    }

    int Market_menu::get_budget(){
        return budget;
    }

    bool Market_menu::get_double_j(){
        return double_j;
    }

    bool Market_menu::get_restored(){
        return restored_hp;
    }



