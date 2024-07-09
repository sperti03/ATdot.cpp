#pragma once 
#include "Protagonist.hpp"
#include <ncurses.h>
#include "Drawable.cpp"
#include "Coin.cpp"
#include "Board.cpp"







        Protagonist::Protagonist(){
            this->y= this->x=0;
            this->icon ='@';
            mvwaddch(stdscr,this->y,this->x, this->icon);
            init_pair(31,COLOR_CYAN,COLOR_GREEN);
            cur_direction=destra;
            jumping=false;
            melee_damage=50;
            bullet_damage=30;
        }

        Protagonist::Protagonist(int y, int x, WINDOW* board ){
            this->x=x;
            this->y=y;
            this->icon='@';
            mvwaddch(board,this->y,this->x, this->icon);
            cur_direction=destra;
            jumping=false;
            score=0;
            vita=100;
            max_vita=100;
            melee_damage=50;
            bullet_damage=30;
        }

        void Protagonist::upgrade_vita(int vita_aggiuntiva){
            this->max_vita+=vita_aggiuntiva;
            if(this->vita+=vita_aggiuntiva<=max_vita)this->vita+=vita_aggiuntiva;
            else this->vita=max_vita;
        }

        void Protagonist::upgrade_melee_dmg(int dmg_aggiuntivo){
            this->melee_damage+=dmg_aggiuntivo;
        }

        void Protagonist::upgrade_bull_dmg(int dmg_aggiuntivo){
            this->bullet_damage+=dmg_aggiuntivo;
        }
        
        void Protagonist::upgrade_bullets(int bullets_aggiuntive){
            this->max_bullet+=bullets_aggiuntive;
        }

        void Protagonist::restored_hp(bool has_restored){
            if(has_restored==true){
                vita=max_vita;
            }
        }

        //double jump da fare 
        int Protagonist::getmaxjump(){
            return maxjumps;
        }

        int Protagonist::getcurjump(){
            return curjump;
        }

        void Protagonist::setcurjump(int val){
            curjump=val;
        }

        void Protagonist::Update_protg(int monete, int vita, int bullets){//modifiche
            this->score=monete;
            this->vita=vita;
            this->num_bullet=bullets;
        }

        void Protagonist::SetDirection(Direction d){
            cur_direction=d;
        }

        Direction Protagonist::getDirection(){
            return cur_direction;
        }

        int Protagonist::getweaponrange(){
            return weaponrange;
        }

        int Protagonist::getscore(){
            return score;
        }

        int Protagonist::getvita(){
            return vita;
        }

        int Protagonist::get_max_vita(){
            return max_vita;
        }

        void Protagonist::updatevita(int v){
            vita=vita+v;
        }
        
        int Protagonist::getnumbullet(){
            return num_bullet;
        }

        int Protagonist::get_max_bullets(){
            return max_bullet;
        }
        
        void Protagonist::setbullet(int n){
            num_bullet=num_bullet+n;
        }
        
        void Protagonist::updatescore(int sc){
            score=score+sc;
        }

        void Protagonist::change_budget(int bg){
            score=bg;
        }

        int Protagonist::get_meleedamage(){
            return melee_damage;
        }

        int Protagonist::get_bulletdamage(){
            return bullet_damage;
        }
        int Protagonist::get_timer(){
            return timer;
        }
        void Protagonist::set_timer(int n){
            timer=n;
        }
        void Protagonist::shootingtimer(){
            if(timer<=5 && timer !=0)
            timer=timer-1;
        }
    
        void Protagonist::moveprot(Board board){
            int row=gety();
            int col=getx();
            if(cur_direction==destra){
                if(board.getCharAt(y,x+1) == ' '){
                this->x=this->x+1;
                mvwaddch(board.getwin(), row, col,' ');
                mvwaddch(board.getwin(), row, col+1,this->icon);
                }
            }
            else if(cur_direction==sinistra){
                if(board.getCharAt(y,x-1) ==' ' ){
                this->x=this->x-1;
                mvwaddch(board.getwin(), row, col,' ');
                mvwaddch(board.getwin(), row, col-1,this->icon);
            }
            }
        }
        

        void Protagonist::gravity(Board board){
            if(!jumping){
            //se sotto il protagonista c'è vuoto allora cade giù
                if(board.getCharAt(y+1,x) != board.getplat() && board.getCharAt(y+1,x) != board.getexit()){
                    mvwaddch(board.getwin(), y, x, ' ');
                    y=y+1;
                    mvwaddch(board.getwin(), y, x, this->icon);
                }
                if(board.getCharAt(y+1,x) == board.getplat() || board.getCharAt(y+1,x) == board.getexit()){
                    setcurjump(0);
                }
                
            }
        }

        void Protagonist::resetjump(){
            jumpHeight=0;
        }

        void Protagonist::setJump(bool val){
            jumping=val;
        }

        void Protagonist::have_doublej(bool doublej){
            this->double_j=doublej;
            if(double_j==true){
                maxjumps=2;
            }else{
                maxjumps=1;
            }
        }


        void Protagonist::jump(Board board){
                    if(jumping){
                        if(board.getCharAt(y-1,x) == ' '){
                                    mvwaddch(board.getwin(), y, x,' ');
                                    this->y=this->y-1;
                                    mvwaddch(board.getwin(), y, x,this->icon);
                                    wrefresh(board.getwin());
                                    }
                                    jumpHeight++;        
                            
                        if(jumpHeight==maxJumpHeight){
                            jumpHeight=0;
                            jumping=false;
                        }
                    }
        }
        
        



        