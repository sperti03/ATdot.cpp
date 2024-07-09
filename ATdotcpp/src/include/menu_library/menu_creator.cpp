#pragma once
#include <ncurses.h>
#include <cstring>
#include "menu_creator.hpp"



   Menu_creator::Menu_creator(WINDOW *win){
    this->win=win;
    keypad(win,true);
    getmaxyx(win,yM,xM);
   }








   
   void Menu_creator::stampa_titolo(char nome_gioco[]){             
    int tot_lettere=strlen(nome_gioco);               
    mvwprintw(win,0,(xM/2)-tot_lettere/2,nome_gioco);
    }           
    





    
    int Menu_creator::calcola_posizione_y(int len){
        int pos_y=yM/len;
        if(pos_y-1>2) return pos_y-3;
        else return pos_y;
    }









    int Menu_creator::calcola_posizione_x(char stringa[]){
        int tot_lettere=strlen(stringa);
        int pos_x=(xM/2)-tot_lettere/2;
        return pos_x;
    }

    



    void Menu_creator::colora_scritta_int(int asse_y,int asse_x,int stampa,bool is_blinking){

        if(is_blinking==false){
            wattron(win,COLOR_PAIR(11));
            mvwprintw(win,asse_y,asse_x,"%d",stampa);
            wattroff(win,COLOR_PAIR(11));
        } else{
            wattron(win,COLOR_PAIR(11));
            wattron(win,A_BLINK);
            mvwprintw(win,asse_y,asse_x,"%d",stampa);
            wattroff(win,A_BLINK);
            wattroff(win,COLOR_PAIR(11));
        }
        
    }

    void Menu_creator::colora_scritta_ch(int asse_y,int asse_x,char stampa,bool is_blinking){
        if(is_blinking==false){
            wattron(win,COLOR_PAIR(11));
            mvwaddch(win,asse_y,asse_x,stampa);
            wattroff(win,COLOR_PAIR(11));
        }else{
            wattron(win,COLOR_PAIR(11));
            wattron(win,A_BLINK);
            mvwaddch(win,asse_y,asse_x,stampa);
            wattroff(win,A_BLINK);
            wattroff(win,COLOR_PAIR(11));
        }
    }


    void Menu_creator::colora_scritta_string(int asse_y,int asse_x,char stampa[],bool is_blinking, bool is_mod){
        if(is_blinking==false && is_mod==false){
            wattron(win,COLOR_PAIR(12));
            mvwprintw(win,asse_y,asse_x,stampa);
            wattroff(win,COLOR_PAIR(12));
        }else if(is_blinking==true && is_mod==false){
            wattron(win,COLOR_PAIR(12));
            wattron(win,A_BLINK);
            mvwprintw(win,asse_y,asse_x,stampa);
            wattroff(win,A_BLINK);
            wattroff(win,COLOR_PAIR(12));
        } else if(is_mod==true){
            wattron(win,COLOR_PAIR(11));
            wattron(win,A_BLINK);
            mvwprintw(win,asse_y,asse_x,stampa);
            wattroff(win,A_BLINK);
            wattroff(win,COLOR_PAIR(11));
        }

    }








    void Menu_creator::stampa_varie_menu(scelta scelte[],int len, char titolo_menu_corrente[],bool cambia_asse_x,int asse_x2){ 
        stampa_titolo(titolo_menu_corrente);                                                                             
        int incr=calcola_posizione_y(len),asse_x,asse_y=incr;                                  
        for(int i=0;i<len;i++){

            if(cambia_asse_x==false){

            asse_x=calcola_posizione_x(scelte[i].varie);

            }else{

            asse_x=asse_x2;

            }

            colora_scritta_string(asse_y,asse_x,scelte[i].varie);
            asse_y+=incr;
        }
        
    }










    chtype Menu_creator::getInput(){             
        chtype input=wgetch(win);
        return input;
    }








    void Menu_creator::evidenzia_opzione(scelta lista_opzioni[],int asse_y,int opzione_evidenziata,bool cambia_asse_x,int asse_x2){
                                                                    
        if(cambia_asse_x==false){

        int asse_x=calcola_posizione_x(lista_opzioni[opzione_evidenziata].varie);
        wattron(win,A_STANDOUT);
        mvwprintw(win,asse_y,asse_x,lista_opzioni[opzione_evidenziata].varie);
        wattroff(win,A_STANDOUT);

        }else{

        wattron(win,A_STANDOUT);
        mvwprintw(win,asse_y,asse_x2,lista_opzioni[opzione_evidenziata].varie);
        wattroff(win,A_STANDOUT);

        }
        
    }









    
    void Menu_creator::non_evidenziare_opzione(scelta lista_opzioni[],int asse_y,int opzione_evidenziata,bool cambia_asse_x,int asse_x2){ 
        if(cambia_asse_x==false){
        int asse_x=calcola_posizione_x(lista_opzioni[opzione_evidenziata].varie);
        colora_scritta_string(asse_y,asse_x,lista_opzioni[opzione_evidenziata].varie);
        }else{
        colora_scritta_string(asse_y,asse_x2,lista_opzioni[opzione_evidenziata].varie);
        }
    }












    void Menu_creator::move_up(scelta lista_opzioni[],int &asse_y,int &opzione_corrente,int incr,bool cambia_asse,int asse_x_cambiata){
        non_evidenziare_opzione(lista_opzioni,asse_y,opzione_corrente,cambia_asse,asse_x_cambiata);                              
            if(asse_y-incr<incr) evidenzia_opzione(lista_opzioni,asse_y,opzione_corrente,cambia_asse,asse_x_cambiata);
            else{
                asse_y-=incr;
                opzione_corrente--;
                evidenzia_opzione(lista_opzioni,asse_y,opzione_corrente,cambia_asse,asse_x_cambiata);
            }

    }








    
    void Menu_creator::move_down(scelta lista_opzioni[],int &asse_y,int &opzione_corrente,int incr,int len,bool cambia_asse,int asse_x_cambiata){
        non_evidenziare_opzione(lista_opzioni,asse_y,opzione_corrente,cambia_asse,asse_x_cambiata);
            if(asse_y+incr>(len*incr)) evidenzia_opzione(lista_opzioni,asse_y,opzione_corrente,cambia_asse,asse_x_cambiata);
            else{
                asse_y+=incr;
                opzione_corrente++;
                evidenzia_opzione(lista_opzioni,asse_y,opzione_corrente,cambia_asse,asse_x_cambiata);
            }
    }










   
    scelta Menu_creator::naviga_menu(scelta lista_opzioni[],int len,char titolo_menu_corrente[]){
        

        int asse_y=calcola_posizione_y(len),incr=asse_y,opzione_corrente=0;
        chtype input;
        bool end=false;
        
        stampa_varie_menu(lista_opzioni,len,titolo_menu_corrente);

        while(end!=true){
        input=getInput();

        switch(input){

            case KEY_UP:
            move_up(lista_opzioni,asse_y,opzione_corrente,incr);
            break;

            case KEY_DOWN:
            move_down(lista_opzioni,asse_y,opzione_corrente,incr,len);
            break;

            case 10:
            wclear(win);
            end=true;
            break;

            default:
            break;


        }
       

    }
    return lista_opzioni[opzione_corrente];
    }

   

    

