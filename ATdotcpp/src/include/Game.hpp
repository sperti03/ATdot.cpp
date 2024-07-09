#pragma once
#include <ncurses.h>
#include <iostream>
#include "Platformgame.cpp"
#include "shop.cpp"
#include "menu_library/selection_menu.cpp"
#include <fstream>

class Game{
    private:

    


    WINDOW* win_menu;
    int BOARD_ROWS;
    int BOARD_COLS;
    bool go_back,not_curr_lvl,exit,has_saved,is_market;
    int** tmp_matrix;
    int** shop_matrix;
    int tmp_monete,tmp_vita,tmp_bullets=0;
    int diff=1;
    int true_lvl;
    bool enact_new_game_plus=false;
    int new_prezzi[7]{0,200,150,400,100,300,3000},upgrade_totali[4]{0,0,0,0};
    int max_vita=100;
    bool restored=false,double_j=false;
    int** riferimento;

    public:
    struct list2{//lista di supporto
    int x;
    int y;
    int**mat;
    list2 *next;
    int lvl_c;
};

typedef list2* support_list;

struct single_level{//lista di livello
        scelta menu;
        bool level;
        int level_counter;
        int** matrix;
        int save_monete,save_vita,save_bullets;
        int save_atk_melee,save_atk_b,save_num_b,save_max_vita;
        bool in_NG_plus,save_doublej;
        int true_lvl;
        single_level *next;
        single_level *prev;
    };

    typedef single_level *p_livello;

    support_list support_head,saved_game_head;



Game(int BOARD_ROWS,int BOARD_COLS);
    
void initialize_support_list(int x,int y,int** mat);

void insert_in_support(support_list head,int** mat,int x, int y, int lvl);//inserisce una mappa nella lista di supporto

support_list elimina_0(support_list scorritore);//elimina matrici indesiderate

void salvaLista(p_livello h, const char* nome_file);//salva variabili di gioco nella lista di livello

void salvamat(support_list h, const char* nome_file);//salva mappa nella lista di supporto

p_livello caricaLista(const char* nome_file);//carica dati dalla lista di lvl salvata

support_list loadmat(const char* nome_file);//carica dati dalla lista di supporto salvata
  
void assign_values(p_livello head); //assegna i valori della statistiche del player alla testa della lista di lvl (lo fa solo alla testa perchè era inutile ripetere il processo per ogni elemento della lista)

void assign_upgrade(p_livello head);//assegan upgrade comprati dal player alla testa della lista di lvl (lo fa solo alla testa perchè era inutile ripetere il processo per ogni elemento della lista)
    
bool levels(Menu_selector menu_start, bool next_level, bool is_back,int lvl,bool prev_lvl, int** mappa_lvl=0);// singolo livello giocabile

void scorri_livelli();//gestore di liste di livello che permette di andare avanti ed indietro fra livelli

};