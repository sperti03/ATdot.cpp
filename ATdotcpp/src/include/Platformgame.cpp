#pragma once 
#pragma comment(lib, "winmm.lib")

#include <ncurses.h>
#include "Coin.cpp"
#include "Board.cpp"
#include "Drawable.cpp"
#include "Protagonist.cpp"
#include "Enemy.cpp"
#include "Bullet.cpp"
#include "HUD.cpp"
#include "Heal.cpp"
#include "Platformgame.hpp"
#include <time.h>
#include <cstdlib>


    Platformgame::Platformgame(int BOARD_ROWS, int  BOARD_COLS, int lat,int orz, GameMap a,SHOP s,int** matr,int monete,int vita, int bullets,int lvl,int diff_lvl, bool next_level,bool prev_lvl,bool is_market,bool new_game_plus,int true_lvl){
        end_level=false;
        this->lvl=lvl;
        this->new_game_plus=new_game_plus;
        this->true_lvl=true_lvl;
        this->is_market=is_market;
        this->diff_lvl=diff_lvl;
        this->lat=lat,
        this->orz=orz;
        this->rows=BOARD_ROWS-3;
        this->cols=BOARD_COLS-2;
        redrawstd();
        init_pair(2,COLOR_RED, COLOR_BLACK);
        redrawstd();
        game_win= Board(BOARD_ROWS,BOARD_COLS,100);
        initialize(this->lat,this->orz,a,s,matr,monete,vita,bullets,next_level,prev_lvl);
        go_back=false;
    }

    void Platformgame::initialize(int lat,int orz, GameMap a,SHOP s,int** matr,int monete,int vita, int bullets,bool next_level, bool prev_lvl){
        srand(time(NULL));
        list_enemy=NULL;
        list_coin=NULL;
        list_bullet=NULL;
        list_heal=NULL;
        srand(time(NULL));
        game_over=false;
        enemies_speed=3;
        protg=Protagonist(36,3,game_win.getwin());
        if(next_level==true){
            protg.Update_protg(monete,vita,bullets);
        }
        hud_menu=HUD();
        hud_menu.initialize();
        game_win.initialize(lat,orz,a,s,matr,is_market);
        
        hud_menu.print_controls();

        if(prev_lvl==false && is_market==false){
        initialize_enemy_coins(lvl);
        //push nemici brawlers
        for(int i=0;i<num_brawler;i++)
            list_enemy=enemyPush(list_enemy,0,lvl);
        //push nemici shooters
        for(int i=0;i<num_shooter;i++)
            list_enemy=enemyPush(list_enemy,1,lvl);
        //push monete
        for(int i=0;i<num_coins;i++)
            list_coin=coinPush(list_coin);
        }
        //push heal
        if(!is_market)
        for(int i=0;i<3;i++){
            list_heal=healPush(list_heal);
        }
        //riduci di 1 la velocità dei nemici ogi 5 lvl, al massimo lascia a 1
        if(lvl%5==0 && enemies_speed>1)
            enemies_speed=enemies_speed-1;
        move=enemies_speed;
        stampa_objects();    
    }

    //numero di nemici/monete deciso da lvl corrente
    void Platformgame::initialize_enemy_coins(int lvl){
        int max_enemy,min_enemy;
        if(new_game_plus==true)lvl=true_lvl;

        num_coins=rand()%5 +1;//max 5 coins a partita, min 1 coin
        if(lvl<5){
            num_brawler=rand()%3+1;
            num_shooter=rand()%2;
        } else{
            max_enemy=lvl/5;//ogni 5 lvl aumento di 1 il num max di nemici
            min_enemy=lvl/10;//ogni 10 lvl aumento di 1 il num min di nemici
            num_brawler=rand()%(3+max_enemy) + min_enemy;
            num_shooter=rand()%(3+max_enemy) + min_enemy;
        }



    }
    
    //push di oggetti nelle liste
    Platformgame::enemy_l Platformgame::enemyPush(enemy_l list_enemy,bool type,int lvl){
        int y,x;
        if(new_game_plus==true)lvl=true_lvl;
        enemy_l tmp= new enemylist;
        game_win.getEmptyCoord(y,x);
        tmp->e=Enemy(y,x,game_win.getwin(),type,lvl,diff_lvl);
        damage_b=tmp->e.get_damage_bullets();
        damage_m=tmp->e.get_damage_melee();
        tmp->next=list_enemy;
        return tmp;
    }
    Platformgame::coin_l Platformgame::coinPush(coin_l list_coin){
        int y,x;
        coin_l tmp= new coinlist;
        game_win.getEmptyCoord(y,x);
        tmp->c=Coin(y,x);
        tmp->next=list_coin;
        return tmp;
    }
    Platformgame::heal_l Platformgame::healPush(heal_l list_heal){
        int y,x;
        heal_l tmp= new heallist;
        game_win.getEmptyCoord(y,x);
        tmp->h=Heal(y,x);
        tmp->next=list_heal;
        return tmp;
    }
    Platformgame::bullet_l Platformgame::bulletPush(bullet_l l,int y, int x,Direction d,int t){
        bullet_l tmp=new bulletlist;
        tmp->b=Bullet(y,x,d,t);
        tmp->next=l;
        return tmp;
    }
    
    //pop di oggetti dalle liste
    Platformgame::coin_l Platformgame::coin_pop(coin_l list, int y, int x){
        if(list==NULL)
            return NULL;
        //elemento in testa
        if(list->c.getx()==x && list->c.gety()==y){
                mvwaddch(game_win.getwin(), y, x, ' ');
                protg.updatescore(10);
                coin_l tmp=list;
                list=list->next;
                delete tmp;
                return list;}

        //elemento in mezzo
        coin_l head=list;
        coin_l before=list;
        list=list->next;

        while(list!=NULL){
            if(list->c.getx()==x && list->c.gety()==y){
                mvwaddch(game_win.getwin(), list->c.gety(), list->c.getx(), ' ');
                protg.updatescore(10);
                coin_l tmp=list;
                before->next=list->next;
                delete tmp;}
            else
                before=list;

            list=list->next;}
        return head;
    }
    Platformgame::heal_l Platformgame::heal_pop(heal_l list, int y, int x){
        if(list==NULL)
            return NULL;
        //elemento in testa
        if(list->h.getx()==x && list->h.gety()==y){
                mvwaddch(game_win.getwin(), y, x, ' ');
                if(protg.getvita()+10 <= protg.get_max_vita())protg.updatevita(10);
                heal_l tmp=list;
                list=list->next;
                delete tmp;
                return list;}

        //elemento in mezzo
        heal_l head=list;
        heal_l before=list;
        list=list->next;

        while(list!=NULL){
            if(list->h.getx()==x && list->h.gety()==y){
                mvwaddch(game_win.getwin(), list->h.gety(), list->h.getx(), ' ');
                if(protg.getvita()+10 <= protg.get_max_vita())protg.updatevita(10);
                heal_l tmp=list;
                before->next=list->next;
                delete tmp;}
            else
                before=list;

            list=list->next;}
        return head;
    }
    Platformgame::enemy_l Platformgame::enemy_pop(enemy_l list, int y, int x, char type){
        if(list==NULL)
            return NULL;   
        //elemento in testa
        if(list->e.getx()==x && list->e.gety()==y){
                if(type=='c')
                    list->e.vita=list->e.vita - protg.get_meleedamage();
                else if(type=='b')
                    list->e.vita=list->e.vita - protg.get_bulletdamage();
                
                if(list->e.vita<=0 || type==' '){
                    mvwaddch(game_win.getwin(), list->e.gety(), list->e.getx(), ' ');
                    protg.updatescore(100);
                    enemy_l tmp=list;
                    list=list->next;
                    delete tmp;
                    return list;}
            }
        //elemento in mezzo
        enemy_l head=list;
        enemy_l before=list;
        list=list->next;

        while(list!=NULL){
            if(list->e.getx()==x && list->e.gety()==y){
                if(type=='c')
                    list->e.vita=list->e.vita - protg.get_meleedamage();
                else if(type=='b')
                    list->e.vita=list->e.vita - protg.get_bulletdamage();
                
                if(list->e.vita<=0 || type==' '){
                mvwaddch(game_win.getwin(), list->e.gety(), list->e.getx(), ' ');
                protg.updatescore(100);
                enemy_l tmp=list;
                before->next=list->next;
                delete tmp;
                return head;}
            }
            else{
                before=list;
            }
            list=list->next;
        }
        return head;
    }

    //funzione di movimento degli oggetti
    void Platformgame::movebullet(Board board, bullet_l& list) {
    bullet_l before = nullptr;
    bullet_l current = list;
    bullet_l tmp = nullptr;

    while (current != nullptr) {
        if (current->b.getnext(board) != ' ' || (current->b.getcurrrange()==protg.getweaponrange() && current->b.gettype()==0)){
            chtype nextto=current->b.getnext(board) & A_CHARTEXT;
            //se il carattere successivo al proiettile (non nemico !=1) è un nemico
            if (nextto == 'w' && list->b.gettype()==0) {
                switch (current->b.getdirection()) {
                    case destra:
                        list_enemy = enemy_pop(list_enemy, current->b.y, current->b.x + 1, 'b');
                        break;
                    case sinistra:
                        list_enemy = enemy_pop(list_enemy, current->b.y, current->b.x - 1, 'b');
                        break;
                    case sopra:
                        list_enemy = enemy_pop(list_enemy, current->b.y - 1, current->b.x, 'b');
                        break;
                }
            }
            //se colpisce protagonista fai danno
            if (current->b.getnext(board) ==protg.geticon())
                protg.updatevita(damage_b); 
            // Rimozione dell'elemento
            mvwaddch(game_win.getwin(), current->b.y, current->b.x, ' ');

            if (before != nullptr) {
                before->next = current->next;
            } else {
                list = current->next;
            }

            tmp = current;
            current = current->next;
            delete tmp; // Dealloca la memoria dell'oggetto proiettile eliminato
        } 
        else//muovi proiettile 
        {
            mvwaddch(board.getwin(), current->b.y, current->b.x, ' ');
            current->b.incrrange();
            if (current->b.getdirection() == destra) {
                current->b.x = current->b.x + 1;
            } else if (current->b.getdirection() == sinistra) {
                current->b.x = current->b.x - 1;
            } else if (current->b.getdirection() == sopra) {
                current->b.y = current->b.y - 1;
            }
            mvwaddch(board.getwin(), current->b.y, current->b.x, current->b.geticon());
            before = current;
            current = current->next;
        }
    }
}
    void Platformgame:: move_enemy(Board board, enemy_l list){
        //se turn è true si muove verso destra, se falso verso sinistra
        //uso la int move per farlo muovere ogni tot tic, sennò sarebbe troppo veloce :(
        if(move==enemies_speed){
        while(list!=NULL){
            
            //movimento
            chtype nexttol= board.getCharAt(list->e.gety(), list->e.getx()-2) & A_CHARTEXT;
            chtype nexttor= board.getCharAt(list->e.gety(), list->e.getx()+2) & A_CHARTEXT;
            if(board.getCharAt(list->e.gety()+1, list->e.getx()+1) == ' ' || board.getCharAt(list->e.gety()+1, list->e.getx()-1)==' '|| 
               board.getCharAt(list->e.gety(), list->e.getx()+1)!= ' '|| board.getCharAt(list->e.gety(),list->e.getx()-1)!=' ' || 
               nexttol== 'w'|| nexttor=='w')
                    list->e.switchturn();
            
            if(board.getCharAt(list->e.gety(), list->e.getx()+1) ==protg.geticon() || board.getCharAt(list->e.gety(), list->e.getx()-1)==protg.geticon())
                protg.updatevita(damage_m);
            
            if(list->e.turn){
                if(board.getCharAt(list->e.gety(),list->e.getx()+1) == ' '){
                    mvwaddch(board.getwin(), list->e.gety(), list->e.getx(),' ');
                    list->e.x=list->e.x+1;
                    mvwaddch(board.getwin(), list->e.gety(), list->e.getx(),list->e.geticon());
                    }
            }
            else{
                if(board.getCharAt(list->e.gety(),list->e.getx()-1) == ' '){
                    mvwaddch(board.getwin(), list->e.gety(), list->e.getx(),' ');
                    list->e.x=list->e.x-1;
                    mvwaddch(board.getwin(), list->e.gety(), list->e.getx(),list->e.geticon());
                    }
            }
            //sparo    
            if(list->e.shooter){
                if(list->e.timer==0){
                    Direction s=find_prot(board,list->e.y, list->e.x);
                    if(s!=nessuna){
                        if(s==sopra)
                            list_bullet=bulletPush(list_bullet,list->e.y-1, list->e.x,s,1);
                        else if(s==destra)
                            list_bullet=bulletPush(list_bullet,list->e.y, list->e.x+1,s,1);
                        else
                            list_bullet=bulletPush(list_bullet,list->e.y, list->e.x-1,s,1);
                        list->e.timer=5;    
                    }
                }
                else if(list->e.timer<=5)
                    list->e.timer=list->e.timer-1;
                 
            }
            list=list->next;
        }
            move=0;
        }
        else{
            move=move+1;
        }
    }

    //funzioni di stampa
    void Platformgame::stampa_coins(coin_l list_coin){
        while(list_coin!=NULL){
            mvwaddch(game_win.getwin(), list_coin->c.gety(), list_coin->c.getx(), list_coin->c.geticon());
            list_coin=list_coin->next;
        }
    }
    void Platformgame::stampa_heal(heal_l list_heal){
        while(list_heal!=NULL){
            mvwaddch(game_win.getwin(), list_heal->h.gety(), list_heal->h.getx(), list_heal->h.geticon());
            list_heal=list_heal->next;
        }
    }
    void Platformgame::printhud(Protagonist prossimo,int lvl){
            hud_menu.printmenu(protg.getscore(),protg.getvita(),protg.getnumbullet(),lvl);    
    }
    void Platformgame::stampa_objects(){
        stampa_coins(list_coin);
        stampa_heal(list_heal);
    }

    //funzioni protagonista
    //si occupa di gestire la caduta del protagonista
    void Platformgame::Falling(){
         //se mentre cade incontra nemico lo uccide (o se per qualche strano motivo, si ritrovino nello stesso posto)
        if(list_enemy!=NULL){
            chtype nextto=game_win.getCharAt(protg.gety()+1,protg.getx()) & A_CHARTEXT;
            chtype intto=game_win.getCharAt(protg.gety(),protg.getx()) & A_CHARTEXT;
            if(nextto =='w')
                list_enemy=enemy_pop(list_enemy,protg.gety()+1,protg.getx(),' ');
            if(intto =='w')
                list_enemy=enemy_pop(list_enemy,protg.gety(),protg.getx(),' ');
        }
        //se mentre cade incontra moneta la prende
        if(list_coin!=NULL)
            if(game_win.getCharAt(protg.gety(),protg.getx())==list_coin->c.geticon()){
                list_coin=coin_pop(list_coin,protg.gety(),protg.getx());
        }

        //se mentre cade incontra la cura la prende
        if(list_heal!=NULL)
            if(game_win.getCharAt(protg.gety(),protg.getx())==list_heal->h.geticon()){
                list_heal=heal_pop(list_heal,protg.gety(),protg.getx());
        }
    }
    void Platformgame::upgrade_protg(int arry_up[],bool restored,bool double_j){
        protg.upgrade_melee_dmg(arry_up[0]);
        protg.upgrade_bull_dmg(arry_up[2]);
        protg.upgrade_bullets(arry_up[3]);
        protg.restored_hp(restored);
        protg.have_doublej(double_j);
    }
    void Platformgame::stampaprotg(){
        mvwaddch(game_win.getwin(),protg.gety(),protg.getx(), protg.geticon());
    }
    int Platformgame::getMonete(){
        return protg.getscore();
    }
    int Platformgame::getVita(){
        return protg.getvita();
    }
    int Platformgame::getBullets(){
        return protg.getnumbullet();
    }
    Direction Platformgame::find_prot(Board board, int y, int x) {
        int range = 20;

        if (y == protg.y) {
            int d = x - protg.x;
            if (d < 0 && d > -range)
                return destra;
            if (d > 0 && d < range)
                return sinistra;
        } else if (x == protg.x) {
            int d = y - protg.y;
            if (d > 0 && d < range)
                return sopra;
        }

    return nessuna;
}

void Platformgame::changeBG(int bg){
    protg.change_budget(bg);
}
    
    
    //funzioni di livello
    bool Platformgame::LevelisOver(){
        return end_level;
    }
    bool Platformgame::isOver(){
        return game_over;
    }
    bool Platformgame:: Go_Back(){
        return go_back;
    }
    void Platformgame::redraw(){
        game_win.refresh();
    }

    //aggiorna gli stati di gioco
    void Platformgame::UpdateState(){
        //ristampa oggetti in caso di cambio impostazioni
        stampa_objects();

        //torna indietro fra i livelli
        if(list_coin==NULL && list_enemy==NULL && mvwinch(game_win.getwin(),rows,1)=='@' && lvl!=1){
            game_over=false;
            end_level=true;
            go_back=true;
        }
        //va avanti fra i livelli, controlla che tutti i nemici morti, mnete prese e che il prot sia nella posizione giusta
        if(list_coin==NULL && list_enemy==NULL && ((is_market==false && mvwinch(game_win.getwin(),4,cols)=='@') || (is_market==true && mvwinch(game_win.getwin(),rows,cols)=='@'))){
            game_over=false;
            end_level=true;
        }
        //se vita finita --> game over
        if(protg.getvita()<0){
            game_over=true;
            end_level=true;
        }

        //verifia se protagonista è in jump
        protg.jump(game_win);
        //riporta il protagonista a terra
        protg.gravity(game_win);
        //se il timer è diverso da 0 lo decrementa
        protg.shootingtimer();
        //update hud
        printhud(protg,lvl);
        //muove gli oggetti
        movebullet(game_win,list_bullet);
        move_enemy(game_win,list_enemy);
        //se in caduta,controlla se incontra qualcosa
        Falling();
        } 
    void Platformgame::redrawstd(){
        wclear(stdscr);
        wrefresh(stdscr);
    }
    chtype Platformgame::ProcessInput(){
        chtype input= game_win.getInput();

        switch(input){

           case KEY_RIGHT:
           protg.SetDirection(destra);
           break;
            case 'd':
            //muovi destra
                protg.SetDirection(destra);
                //se moneta mangia
                if(list_coin!=NULL)
                if(game_win.getCharAt(protg.gety(),protg.getx()+1)==list_coin->c.geticon()){
                    list_coin=coin_pop(list_coin,protg.gety(), protg.getx()+1);
                }
                //se cura mangia
                if(list_heal!=NULL)
                if(game_win.getCharAt(protg.gety(),protg.getx()+1)==list_heal->h.geticon()){
                   list_heal=heal_pop(list_heal,protg.gety(), protg.getx()+1);
                }
                protg.moveprot(game_win);
                break;

           case KEY_LEFT:
           protg.SetDirection(sinistra);
            break;
            case 'a':
            //muovi a sinistra
                protg.SetDirection(sinistra);
                //se moneta mangia
                if(list_coin!=NULL)
                if(game_win.getCharAt(protg.gety(),protg.getx()-1)==list_coin->c.geticon()){
                   list_coin=coin_pop(list_coin,protg.gety(), protg.getx()-1);
                }
                //se cura mangia
                if(list_heal!=NULL)
                if(game_win.getCharAt(protg.gety(),protg.getx()-1)==list_heal->h.geticon()){
                   list_heal=heal_pop(list_heal,protg.gety(), protg.getx()-1);
                }
                protg.moveprot(game_win);
                break;
            case KEY_UP:
            protg.SetDirection(sopra);
            break;
            case 'w':
            //guarda sopra/salta
                 protg.SetDirection(sopra);
                if(protg.getcurjump() < protg.getmaxjump()){
                    protg.setcurjump(protg.getcurjump()+1);
                    protg.setJump(true);
                }
                break;
            
            case 'p': //mette in pausa
            return 'p';

            case 'm':
            return 'm';//apre il market, nel lvl market
            
            case 'r'://ricarica
                if(protg.getnumbullet()==0){
                    int tmp=protg.get_max_bullets();
                    protg.setbullet(tmp);
                }
                break;
            //colpo melee con range 2
            case 'c':
            if(list_enemy!=NULL){ 
                chtype nexxto= game_win.getCharAt(protg.gety(),protg.getx()+protg.getDirection()) & A_CHARTEXT;   
                chtype nexxtoto= game_win.getCharAt(protg.gety(),protg.getx()+2*protg.getDirection()) & A_CHARTEXT;       
                if(nexxto == 'w' || nexxtoto == 'w'){
                    list_enemy=enemy_pop(list_enemy, protg.gety(), protg.getx()+protg.getDirection(),'c');
                    list_enemy=enemy_pop(list_enemy, protg.gety(), protg.getx()+2*protg.getDirection(),'c');
                }
            }
            break;
            //spara se timer == 0 
            case 32:
                if(protg.get_timer()==0){
                    if(protg.getnumbullet()>0){
                        //spara se ha il protagonista ha spazio libero davanti a se
                        if(game_win.getCharAt(protg.gety(),protg.getx()+protg.getDirection())==' '){
                            list_bullet=bulletPush(list_bullet,protg.gety(),protg.getx()+protg.getDirection(),protg.getDirection(),0);
                            protg.set_timer(5);
                        }
                    protg.setbullet(-1);
                    }       
                }
                
           default:
            break;
            }
        }
    

    
