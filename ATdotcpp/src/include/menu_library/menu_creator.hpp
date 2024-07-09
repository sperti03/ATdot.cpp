#pragma once
#include <ncurses.h>
#include <cstring>


struct scelta{  
    char varie[25];
};

class Menu_creator{ 
   private: 
   
   public:
   WINDOW*win; 
   int xM,yM;


 
   




   
   Menu_creator(WINDOW *win);

    void stampa_titolo(char nome_gioco[]);
        
    int calcola_posizione_y(int len);//calcola la posizione verticale della scritta

    int calcola_posizione_x(char stringa[]);//calcola la posizione orizzonatle della scritta

    void colora_scritta_int(int asse_y,int asse_x,int stampa,bool is_blinking=false);

    void colora_scritta_ch(int asse_y,int asse_x,char stampa,bool is_blinking=false);

    void colora_scritta_string(int asse_y,int asse_x,char stampa[],bool is_blinking=false, bool is_mod=false);
   
    void stampa_varie_menu(scelta scelte[],int len, char titolo_menu_corrente[],bool cambia_asse_x=false,int asse_x2=0);
    
    chtype getInput();//prende input della tastier dell'utente
    
    void evidenzia_opzione(scelta lista_opzioni[],int asse_y,int opzione_evidenziata,bool cambia_asse_x=false,int asse_x2=0);
    
    void non_evidenziare_opzione(scelta lista_opzioni[],int asse_y,int opzione_evidenziata,bool cambia_asse_x=false,int asse_x2=0);
    
    void move_up(scelta lista_opzioni[],int &asse_y,int &opzione_corrente,int incr,bool cambia_asse=false,int asse_x_cambiata=0);//metodo per muoversi nel menù
   
    void move_down(scelta lista_opzioni[],int &asse_y,int &opzione_corrente,int incr,int len,bool cambia_asse=false,int asse_x_cambiata=0);//metodo per muoversi nel menù
    
    scelta naviga_menu(scelta lista_opzioni[],int len,char titolo_menu_corrente[]);
    };
    

