
#pragma once
#include "menu_creator.cpp"
#include "menu_creator_options.hpp"
#include <ncurses.h>
#include <cstring>
#include <iostream>










    Options_menu::Options_menu(WINDOW*win):Menu_creator(win){
        inizializza_mod();
    }


    
    void Options_menu::stampa_varie_menu_opzioni(scelta menu_opz[],int opz_tot,char nome[],bool cambia_ax,int new_ax){
        mvwprintw(win,calcola_posizione_y(opz_tot)*(opz_tot+1),calcola_posizione_x(indietro[0].varie),indietro[0].varie);
        stampa_varie_menu(menu_opz,opz_tot,nome,cambia_ax,new_ax);
    }


    void Options_menu::inizializza_mod(){
        int len=0;
        int opzione_corrente=calcola_posizione_y(opzioni_totali);
        int incr=calcola_posizione_y(opzioni_totali);
        for(;len<5;len++){
            if(len==1 || len==2){
            array_mod[len].valore_corrente=0;
            }else{
            array_mod[len].valore_corrente=1;
            }
            array_mod[len].opzione_corrente=opzione_corrente;
            opzione_corrente+=incr;
        }
    }



    void Options_menu::stampa_mod(){
        int asse_y=calcola_posizione_y(opzioni_totali),incr=calcola_posizione_y(opzioni_totali); 
        int supp,supp2;
        if(array_mod[1].valore_corrente-1>=0){ 
        supp=1;
        }else{ 
        supp=0;
        }

        if(array_mod[2].valore_corrente-1>=0){
         supp2=1;
        }else{
         supp2=0;
        }


        for(int i=0;i<opzioni_totali;i++){
            if(i==1){
                
                colora_scritta_ch(asse_y,centre,array_mod[1].brd_lat[array_mod[1].valore_corrente-supp],true);
                
            }else if(i==2){
                
                colora_scritta_ch(asse_y,centre,array_mod[2].brd_orz[array_mod[2].valore_corrente-supp2],true);
                
            }else{

               colora_scritta_int(asse_y,centre,array_mod[i].valore_corrente,true);
              
            }
            asse_y+=incr;
        }
        
    }


    void Options_menu::stampa_freccine(){
        stampa_varie_menu(freccia_dx,opzioni_totali,titolo,true,dx);
        stampa_varie_menu(freccia_sx,opzioni_totali,titolo,true,sx);
    }


    void Options_menu::stampa_menu_opzioni(){
        stampa_varie_menu_opzioni(menu_opzioni,opzioni_totali,titolo,true,(xM/2)-20);
        stampa_mod();
        stampa_freccine();
        colora_scritta_string(calcola_posizione_y(opzioni_totali)*(opzioni_totali+1),calcola_posizione_x(indietro[0].varie),indietro[0].varie);
    }


    void Options_menu::move_right(scelta optz_sx[],scelta optz_dx[],int asse_y,int opzione_corrente){
        non_evidenziare_opzione(optz_sx,asse_y,opzione_corrente,true,sx);
        evidenzia_opzione(optz_dx,asse_y,opzione_corrente,true,dx);
    }



    void Options_menu::move_left(scelta optz_sx[],scelta optz_dx[],int asse_y,int opzione_corrente){
        non_evidenziare_opzione(optz_dx,asse_y,opzione_corrente,true,dx);
        evidenzia_opzione(optz_sx,asse_y,opzione_corrente,true,sx);
    }



    void Options_menu::clean(int asse_y){
        mvwprintw(win,asse_y,centre+1," ");
    }



    void Options_menu::change_value_sx(int asse_y_corrente){

        int i=0,tmp;
        bool found=false;

        while(asse_y_corrente!=array_mod[i].opzione_corrente && i<opzioni_totali){
            i++;
        }
        if(asse_y_corrente==array_mod[i].opzione_corrente) found=true;

        if(found==true && (array_mod[i].valore_corrente-1>0) ){

            array_mod[i].valore_corrente--;
            tmp=array_mod[i].valore_corrente-1;

            if(asse_y_corrente>(calcola_posizione_y(opzioni_totali)*3) || asse_y_corrente<(calcola_posizione_y(opzioni_totali)*2)){

                colora_scritta_int(asse_y_corrente,centre,array_mod[i].valore_corrente,true);
                if(array_mod[i].valore_corrente+1==10) clean(asse_y_corrente);

            }else{

                if(asse_y_corrente==(calcola_posizione_y(opzioni_totali)*2)){

                    colora_scritta_ch(asse_y_corrente,centre,array_mod[i].brd_lat[tmp],true);
                  
                }
                else {
                    
                    colora_scritta_ch(asse_y_corrente,centre,array_mod[i].brd_orz[tmp],true);
                    
                }

            }
        }
       
    }



    void Options_menu::change_value_dx(int asse_y_corrente){

        int i=0,tmp;
        bool found=false;

        while(asse_y_corrente!=array_mod[i].opzione_corrente && i<opzioni_totali){
            i++;
        }
        if(asse_y_corrente==array_mod[i].opzione_corrente) found=true;

        if(found==true && (array_mod[i].valore_corrente+1<11) ){
            array_mod[i].valore_corrente++;
            tmp=array_mod[i].valore_corrente-1;

            if(asse_y_corrente>(calcola_posizione_y(opzioni_totali)*3) || asse_y_corrente<(calcola_posizione_y(opzioni_totali)*2)){

                colora_scritta_int(asse_y_corrente,centre,array_mod[i].valore_corrente,true);

            }else{

                if(asse_y_corrente==(calcola_posizione_y(opzioni_totali)*2)){

                    colora_scritta_ch(asse_y_corrente,centre,array_mod[i].brd_lat[tmp],true);

                }else{ 

                    colora_scritta_ch(asse_y_corrente,centre,array_mod[i].brd_orz[tmp],true);

                }

            }
        }

    }




     scelta Options_menu::naviga_menu_opzioni(){

        chtype input;
        int asse_y=calcola_posizione_y(opzioni_totali);
        int incr=asse_y;
        int opzione_corrente=0;
        bool is_dx=false,is_indietro=false;
        bool end=false;

        stampa_menu_opzioni();

        while(end!=true){
            int controllo;
            input=getInput();

            switch(input){


                case KEY_UP:
                if(is_dx==false){

                    if(is_indietro==true){
                    non_evidenziare_opzione(indietro,calcola_posizione_y(opzioni_totali)*(opzioni_totali+1),0);
                    evidenzia_opzione(freccia_sx,calcola_posizione_y(opzioni_totali)*(opzioni_totali),opzione_corrente,true,sx);
                    is_indietro=false;

                    }else{

                    move_up(freccia_sx,asse_y,opzione_corrente,incr,true,sx);

                    }

                } else{

                    if(is_indietro==true){ 
                    non_evidenziare_opzione(indietro,calcola_posizione_y(opzioni_totali)*(opzioni_totali+1),0);
                    evidenzia_opzione(freccia_dx,calcola_posizione_y(opzioni_totali)*opzioni_totali,opzione_corrente,true,dx);
                    is_indietro=false;

                    }else{

                    move_up(freccia_dx,asse_y,opzione_corrente,incr,true,dx);

                    }
                }
                break;


                case KEY_DOWN:
                controllo=asse_y+1;
                if(controllo>incr*opzioni_totali){

                    if(is_dx==false){

                        non_evidenziare_opzione(freccia_sx,calcola_posizione_y(opzioni_totali)*opzioni_totali,opzione_corrente,true,sx);

                    } else{

                        non_evidenziare_opzione(freccia_dx,calcola_posizione_y(opzioni_totali)*opzioni_totali,opzione_corrente,true,dx);

                    }

                    evidenzia_opzione(indietro,calcola_posizione_y(opzioni_totali)*(opzioni_totali+1),0);
                    is_indietro=true;

                }else{
                if(is_dx==false){

                    move_down(freccia_sx,asse_y,opzione_corrente,incr,opzioni_totali,true,sx);

                } else{

                    move_down(freccia_dx,asse_y,opzione_corrente,incr,opzioni_totali,true,dx);
    
                }
                }

                break;

                case KEY_RIGHT:
                is_dx=true;

                if(is_indietro==false){ 
                move_right(freccia_sx,freccia_dx,asse_y,opzione_corrente);
                change_value_dx(asse_y);
                if(array_mod[opzione_corrente].opzione_corrente==calcola_posizione_y(opzioni_totali)*2 || array_mod[opzione_corrente].opzione_corrente==calcola_posizione_y(opzioni_totali)*3) has_been_modified=true;
                }

                break;

                case KEY_LEFT:
                is_dx=false;
                if(is_indietro==false){ 
                move_left(freccia_sx,freccia_dx,asse_y,opzione_corrente);
                change_value_sx(asse_y);
                if((array_mod[opzione_corrente].opzione_corrente==calcola_posizione_y(opzioni_totali)*2 || array_mod[opzione_corrente].opzione_corrente==calcola_posizione_y(opzioni_totali)*3) && array_mod[opzione_corrente].valore_corrente>1) has_been_modified=true;
                }
                break;

                case 10:
                if(is_indietro==true){
                    wclear(win);
                    end=true;
                } 
                break;



            }
        }
        return indietro[0];

     }





    int Options_menu::get_bd_lat(){
        return (int)array_mod[1].brd_lat[array_mod[1].valore_corrente-1];
    }

    int Options_menu::get_bd_orz(){
        if(array_mod[2].valore_corrente-1<0) return (int)array_mod[2].brd_orz[array_mod[2].valore_corrente];
        else {
        return (int)array_mod[2].brd_orz[array_mod[2].valore_corrente-1];
        }
    }

    bool Options_menu::get_modifiche(){
        return has_been_modified;
    }

    int Options_menu::get_diff(){
        return array_mod[0].valore_corrente;
    }

    int Options_menu::get_color_string(){
        return array_mod[3].valore_corrente;
    }



    

