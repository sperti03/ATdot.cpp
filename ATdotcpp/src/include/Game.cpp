#pragma once
#include <ncurses.h>
#include <iostream>
#include "Platformgame.cpp"
#include "shop.cpp"
#include "Game.hpp"
#include "menu_library/selection_menu.cpp"
#include <fstream>




    Game::Game(int BOARD_ROWS,int BOARD_COLS){
        int xmax,ymax;
        exit=false;
        is_market=false;
        getmaxyx(stdscr,ymax,xmax);
        Board window;
        this->BOARD_COLS=BOARD_COLS;
        this->BOARD_ROWS=BOARD_ROWS;  
        win_menu=window.getwin_menu();
        SHOP B(38,98);
        riferimento=B.costruct_shop();
    }

    

    

    void Game::initialize_support_list(int x,int y,int** mat){
        support_head=new list2;
        support_head->next=NULL;
        support_head->x=x;
        support_head->y=y;
        support_head->lvl_c=1;
        support_head->mat=mat;
    }

    void Game::insert_in_support(support_list head,int** mat,int x, int y, int lvl){
        support_list tmp=head;
        while(tmp->next!=NULL){
            
            tmp=tmp->next;
        }

        tmp->next=new list2;
        tmp=tmp->next;

        tmp->x=x;
        tmp->y=y;
        tmp->lvl_c=lvl;
        tmp->mat=mat;
        tmp->next=NULL;
    }





//funzioni di pulizia e aggiutsamento dei salvataggi
    Game::support_list Game::elimina_0(support_list scorritore){
       if(scorritore==NULL) return NULL;
       else{
        if(scorritore->x==0){
            return elimina_0(scorritore->next);
        }else{
            scorritore->next=elimina_0(scorritore->next);
            return scorritore;
        }
       }
    }



  void Game::salvaLista(p_livello h, const char* nome_file) {
    std::remove(nome_file);
    std::ofstream file(nome_file);

    if (file.is_open()) {
        p_livello tmp = h;
        file << tmp->save_bullets << std::endl;
        file << tmp->save_monete << std::endl;
        file << tmp->save_vita << std::endl;
        file << tmp->save_atk_melee << std::endl;
        file << tmp->save_atk_b << std::endl;
        file << tmp->save_num_b << std::endl;
        file << tmp->save_max_vita << std::endl;
        file << tmp->in_NG_plus << std::endl;
        file << tmp->save_doublej << std::endl;
        file << tmp->true_lvl << std::endl;

        while (tmp != NULL) {
            file << tmp->level_counter << std::endl;
            tmp = tmp->next;
        }

        file.close();
    }
}

// Funzione per salvare i dati della matrice su un file di testo
void Game::salvamat(support_list h, const char* nome_file) {
    std::ofstream file(nome_file);

    if (file.is_open()) {
        support_list tmp = h;

        while (tmp != NULL) {
            file << tmp->x << std::endl;
            file << tmp->y << std::endl;

            for (int i = 0; i < tmp->x; i++) {
                for (int j = 0; j < tmp->y; j++) {
                    file << tmp->mat[i][j] << " ";
                }
                file << std::endl;
            }

            tmp = tmp->next;
        }

        file.close();
    }
}

// Funzione per caricare i dati di livello da un file di testo
Game::p_livello Game::caricaLista(const char* nome_file) {
    p_livello h = NULL, list = NULL;
    std::ifstream file(nome_file);
    int n_lvl, n_monete, n_bullets, n_vita, n_atk_melee, n_atk_b, n_b, n_max_vita;
    int n_true_lvl;
    bool NG, DJ;

    if (file.is_open()) {
        h = new single_level;
        file >> n_bullets >> n_monete >> n_vita >> n_atk_melee >> n_atk_b >> n_b >> n_max_vita >> NG >> DJ >> n_lvl >> n_true_lvl;
        tmp_bullets=n_bullets;
        tmp_monete=n_monete;
        tmp_vita=n_vita;
        h->save_atk_melee=n_atk_melee;
        h->save_atk_b=n_atk_b;
        h->save_num_b=n_b;
        h->save_max_vita=n_max_vita;
        h->level_counter=n_lvl;
        true_lvl=n_true_lvl;
        double_j=DJ;
        enact_new_game_plus=NG;
        assign_upgrade(h);
        h->prev=NULL;
        list=h;



        while (!file.eof()) {
            list->next = new single_level;
            file >> n_lvl;

            if (!file.eof()) {
                list->next->prev = list;
                list = list->next;
                list->level_counter = n_lvl;
                list->next = NULL;
            } else {
                list->next = NULL;
                break;
            }
        }

        file.close();
    }

    return h;
}

// Funzione per caricare i dati della matrice da un file di testo
Game::support_list Game::loadmat(const char* nome_file) {
    support_list h = NULL, list = NULL;
    std::ifstream file(nome_file);

    if (file.is_open()) {
        h = new list2;
        file >> h->x >> h->y;
        h->next = NULL;
        list = h;
        list->mat = new int*[list->x];
                for (int i = 0; i < list->x; ++i) {
                    list->mat[i] = new int[list->y];
                    for (int j = 0; j < list->y; j++) {
                        file >> list->mat[i][j];
                    }
                }

        while (!file.eof()) {
            list->next = new list2;

            if (!file.eof()) {
                list = list->next;
                file >> list->x >> list->y;

                list->mat = new int*[list->x];
                for (int i = 0; i < list->x; ++i) {
                    list->mat[i] = new int[list->y];
                    for (int j = 0; j < list->y; j++) {
                        file >> list->mat[i][j];
                    }
                }

                list->next = NULL;
            } else {
                list->next = NULL;
                break;
            }
        }

        file.close();
    }

    return h;
}
  //fine save*/

  void Game::assign_values(p_livello head){ //serve per salvare le stats del player nella testa
    head->save_bullets=tmp_bullets;
    head->save_monete=tmp_monete;
    head->save_vita=tmp_vita;
    head->save_atk_b=upgrade_totali[2];
    head->save_atk_melee=upgrade_totali[0];
    head->save_num_b=upgrade_totali[3];
    head->save_max_vita=upgrade_totali[1];
    head->in_NG_plus=enact_new_game_plus;
    head->true_lvl=true_lvl;
    head->save_doublej=double_j;
  }

  void Game::assign_upgrade(p_livello head){
    upgrade_totali[0]=head->save_atk_melee;
    upgrade_totali[1]=head->save_max_vita;
    upgrade_totali[2]=head->save_atk_b;
    upgrade_totali[3]=head->save_num_b;
  }
    


    bool Game::levels(Menu_selector menu_start, bool next_level, bool is_back,int lvl,bool prev_lvl, int** mappa_lvl){
        go_back=false;
        restored=false;
        has_saved=false;
        int** matrix;
        chtype check_input;
        scelta resume;
        Board game_win;
        int old_timeout=game_win.getTimeout();
        int x,y;
        getmaxyx(game_win.getwin(), y, x); 
        GameMap A(x-2, y-2);
        SHOP S(x-2,y-2);
        shop_matrix=S.costruct_shop();

        if(lvl%5!=0) is_market=false;
        else is_market=true;


        if(is_back==false){//se si avanza di lvl si crea una nuova mappa, altrimenti si usa quella del lvl attuale
        if(lvl%5!=0){//ogni 5 lvl compare lo shop
        tmp_matrix=A.createMap();//unica funzione di sta variabile è passare la matrice alla struct
        }else{
        tmp_matrix=shop_matrix;
        }
        matrix=tmp_matrix;
        } else{
        tmp_matrix=matrix=mappa_lvl;
        }
        if(is_back==false && lvl==1) initialize_support_list(A.gety(),A.getx(),tmp_matrix);
        else if(go_back==false) insert_in_support(support_head,tmp_matrix,A.gety(),A.getx(),lvl);


        Platformgame game(BOARD_ROWS,BOARD_COLS,menu_start.get_bd_lat(),menu_start.get_bd_orz(),A,S,matrix,tmp_monete,tmp_vita,tmp_bullets,lvl,diff,next_level,prev_lvl,is_market,enact_new_game_plus,true_lvl);
        game.upgrade_protg(upgrade_totali,restored,double_j);//deve essere chiamato 1 volta ogni lvl altrimenti gli upgrade non vengono contati
        
    
    


        while(game.LevelisOver()!=true){
            check_input=game.ProcessInput();

            if(is_market==true && check_input == 'm'){
            game_win.setTimeout(-1);
            menu_start.update_prz(new_prezzi);
            resume=menu_start.menu_selector(false,false,true,tmp_monete,double_j,restored);
            menu_start.get_prezzi(new_prezzi);
            menu_start.get_array_up(upgrade_totali);
            max_vita+=upgrade_totali[1];
            restored=menu_start.get_restored_hp();
            tmp_monete=menu_start.get_monete();
            double_j=menu_start.get_doubleJ();
            game.changeBG(tmp_monete);
            
            
            if(strcmp(resume.varie,"CONTINUA")==0){
            game_win.setTimeout(old_timeout);
            game.upgrade_protg(upgrade_totali,restored,double_j);
            game_win.addBorder(A,S,0,menu_start.get_bd_lat(),menu_start.get_bd_orz(),false,true);
            game_win.refresh();
            }
            }

            if(check_input=='p'){//inizio implementazione pause
            game_win.setTimeout(-1);
            resume=menu_start.menu_selector(true,false,false,0,double_j,restored);
            diff=menu_start.get_diff();//setta la difficoltà in caso di modifiche
            
            
            if(strcmp(resume.varie,"ESCI")==0){
                exit=true;
                tmp_monete=game.getMonete();
                tmp_vita=game.getVita();
                tmp_bullets=game.getBullets();
                return true;
            }
            

            else{
            if(strcmp(resume.varie,"SALVA")==0) has_saved=true;
            game_win.setTimeout(old_timeout);
            if(is_market==false)game_win.addBorder(A,S,matrix,menu_start.get_bd_lat(),menu_start.get_bd_orz(),true);//se si è nel market stampa mappa market, altrimenti no
            else  game_win.addBorder(A,S,0,menu_start.get_bd_lat(),menu_start.get_bd_orz(),false,true);
            game_win.refresh();
            }
            }//fine implementazione pausa
            game.UpdateState();
            game.stampaprotg();
            game.redraw();
        }
        wclear(game_win.getwin());
        if(lvl!=1) go_back=game.Go_Back();//serve per scorrimento all'indietro
        if(lvl%5!=0)tmp_monete=game.getMonete();
        if(is_market==false)tmp_vita=game.getVita();//se NON si è nel market stats aggiornata normalmente, altrimenti guardo quanti upgrade hp + sono stati presi
        else{
            if(game.getVita()+upgrade_totali[1]<max_vita) tmp_vita=game.getVita()+upgrade_totali[1];
            else tmp_vita=max_vita;
            if(restored==true)tmp_vita=max_vita;
        }
        tmp_bullets=game.getBullets();
        return game.isOver();  
    }

    

    void Game::scorri_livelli(){
        p_livello head,list;
        bool over=false,next_level;
        Menu_selector menu(win_menu);
        scelta has_continued;
        head=new single_level;

        head->prev=NULL;
        head->level_counter=0;
        has_continued=head->menu=menu.menu_selector(false,false,false,0,double_j);//inizio gioco: stampa menu start
        diff=menu.get_diff();

        if(strcmp(head->menu.varie,"START")==0 || strcmp(has_continued.varie,"CONTINUA")==0){

            if(strcmp(head->menu.varie,"START")==0){
            head->level=false;
            go_back=false;
            list=head;
            }else{

            head=caricaLista("save_lvl");
            support_head=loadmat("save_mappa");
            saved_game_head=support_head;
            saved_game_head=elimina_0(saved_game_head);
            list=head;
            int i=0;

            while(list->next!=NULL){
                if(i!=0 && saved_game_head!=NULL)list->matrix=saved_game_head->mat;
                list=list->next;
                if(i!=0 && saved_game_head!=NULL)saved_game_head=saved_game_head->next;
                i++;
            }
            

            list->matrix=saved_game_head->mat;
            list->level=levels(menu,true,true,list->level_counter,false,list->matrix);
            assign_values(head);
    

            }

            while(over==false){
               while(go_back==true){
                if(go_back==true && list->prev->level_counter!=0 && list->prev!=NULL){//if per tornare indietro fra livelli
                not_curr_lvl=true;//bool per vedere se sono ritornato al lvl corrente
                while(not_curr_lvl && exit==false){
                    if(go_back==false && list->next!=NULL){
                        list=list->next;
                        list->level=levels(menu,true,true,list->level_counter,true,list->matrix);//scorrro in avanti
                        assign_values(head);
                    }else if(go_back==true && list->prev->level_counter!=0){
                    list=list->prev;
                    list->level=levels(menu,true,true,list->level_counter,true,list->matrix);//scorro all'inietro
                    assign_values(head);
                }
                if(list->next==NULL) not_curr_lvl=false;
            }
            }}


            if(list->level==false && exit==false){
                list->next=new single_level;
                list->next->prev=list;
                list=list->next;
                list->level_counter=list->prev->level_counter+1;
                if(list->prev->level_counter==0) next_level=false;//per updatare la vita,monete ecc... del protagonista, se è falso non si fa update
                else next_level=true;
                list->level=levels(menu,next_level,false,list->level_counter,false);//evoco la funzione per giocare al livello
                assign_values(head);
                list->matrix=tmp_matrix;//salvo la mappa di gioco nel nodo
                list->next=NULL;

               
            }else if(exit==true && list->level==true){//controllo per usicta dal gioco
             if(has_saved==true){ 
                salvaLista(head,"save_lvl");//salvo la lista
                salvamat(support_head,"save_mappa");//salvo la mappa
                }

                over=true;

            }else if(exit!=true && list->level==true){//controllo per la new game plus
            
                list->menu=menu.menu_selector(true,true,false,0,double_j);
                if(strcmp(list->menu.varie,"new")==0){
                true_lvl=list->level_counter;
                enact_new_game_plus=true;
                p_livello tmp_head,garbage;
                support_list garbage2;
                garbage=list->prev;
                tmp_head=list;//creo una nuova testa per non perdere la lista
                delete garbage;//cancello livelli precedenti
                head=tmp_head;
                list=head;
                head->prev=NULL;
                head->next=new single_level;
                head->next->prev=head;
                list=list->next;
                list->next=NULL;
                garbage2=support_head->next;
                delete garbage2;
                //initialize_support_list();

                list->level=levels(menu,false,false,1,false);//re-inizio dal livello 1
                assign_values(head);
                list->level_counter=1;
                } else{
                    over=true;
                }
            }

             

           
            }

        }
    }

