#include<ncurses.h>
#include<iostream>
#include<ctime>
#include "matrice.hpp"
#include<stdio.h>
#pragma once


using namespace std;




    GameMap::GameMap(){
        this->rows=0;
        this->cols=0;
    }
    GameMap::GameMap(int x, int y){
        init_pair(200, COLOR_BLACK, COLOR_BLUE);
        this->rows=y;
        this->cols=x;
        // Inizializza la matrice con le dimensioni specificate
        matrix = new int*[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
        }
        B = new chtype*[rows];
        for(int i = 0; i < rows; i++){
            B[i] = new chtype[cols];
        }
    }

    

    int GameMap::getx(){
        return cols;
    }

    int GameMap::gety(){
        return rows;
    }

    int** GameMap::createMap() {
        srand(time(0));
        
        bool controllo = false;
        while(controllo != true){
            int tmp=0;
        for(int i=3 ; i<rows-3; i++){
            for(int j=0 ; j<cols; j++ ){
                if(matrix[i][j]==1){
                    tmp++;
                }
            }
        }
        if(tmp >= (((cols*(rows-6))/2))){
            controllo = true;
        }else{
            for(int i=0; i<rows; i++){
                for(int j=0; j<cols; j++){
                    matrix[i][j]=rand()%2;
                }
            }
        }
        } 

        //modifiche basi;
        for(int i=0 ; i<rows; i++){
            for(int j=0; j<cols ; j++){
                if((i <=1 || i>= rows-3 ) && matrix[i][j] == 1 ){
                    matrix[i][j]=0;
                }
            }
        }

        for(int j=0; j<cols; j++){
            matrix[rows-1][j]=1;
        } 

        for(int j=cols-10; j<cols; j++){
            matrix[2][j]=1;
        }

        // sistemazione basi per l' asse delle ordinate

        for(int i=3; i<rows-3; i++){
            for(int j=0; j<cols; j++){
                if(matrix[i][j]==1){
                    if(matrix[i-1][j]== 1 || matrix[i-2][j]== 1){
                    matrix[i][j] = 0;
                    }
                }
            }
        }

     // sistemazione basi per l' asse delle ascisse

        for(int i=3; i<rows-3; i++){
        for(int j=0; j<cols; j++){
            if(matrix[i][j]==1){
                if((matrix[i-1][j-1]==1)&&(matrix[i-1][j+1]==1)){
                    matrix[i-1][j]=1;
                    matrix[i][j]=0;
                }
            }   
            }
        }

        for(int i=3; i<rows-3; i++){
        for(int j=0; j<cols; j++){
            if(matrix[i][j]==1){
                if((matrix[i+1][j-1]==1)&&(matrix[i+1][j+1]==1)){
                    matrix[i+1][j]=1;
                    matrix[i][j]=0;
                }
            }
            }
        }

        // aggiuta trappole 

        for(int i=0; i<rows-3; i++){
            for(int j=0; j<cols; j++){
                if(matrix[i][j]==1){
                    if((matrix[i][j-1]==1)&&(matrix[i][j+1]==1)&&(matrix[i+1][j]==0)){
                        int t;
                        t=rand()%2;
                        if(t==1){
                            matrix[i][j]=2;
                        }else{
                            matrix[i][j]=1;
                        }
                        
                    }
                }
            }
        }

        // riempimeto spazzi singoli 
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                if(matrix[i][j]==1 && matrix[i][j-1]==0 && matrix[i][j+1]==0 &&  (matrix[i][j-2]==1 || matrix[i][j+2]==1)){
                    if(matrix[i][j-2]==1 && matrix[i][j+2]==0){
                        matrix[i][j-1]=1;
                    }
                    if(matrix[i][j-2]==0 && matrix[i][j+2]==1){
                        matrix[i][j+1]=1;
                    }    
                    if(matrix[i][j-2]==1 && matrix[i][j+2]==1){
                        matrix[i][j+1]=1;
                        matrix[i][j-1]=1;
                    }                            
                }
            }
        }
        // correzzione singlarità 
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                if(matrix[i][j]==1 && matrix[i][j-1]==0 && matrix[i][j+1]==0 && matrix[i+1][j]==0 && matrix[i-1][j]==0){
                    if(matrix[i+1][j-1]==0 && matrix[i+1][j+1]==0 && matrix[i-1][j-1]==0 && matrix[i-1][j+1]==0) {
                        matrix[i][j]=0;
                    }
                    if(matrix[i+1][j-1]==0 && matrix[i+1][j+1]==0 && matrix[i-1][j-1]==1 && matrix[i-1][j+1]==0) {
                        matrix[i][j]=0;
                        matrix[i-1][j]=1;
                    } 
                    if(matrix[i+1][j-1]==0 && matrix[i+1][j+1]==1 && matrix[i-1][j-1]==0 && matrix[i-1][j+1]==1) {
                        matrix[i][j]=0;
                        matrix[i-1][j]=0;
                    }
                    if(matrix[i+1][j-1]==1 && matrix[i+1][j+1]==0 && matrix[i-1][j-1]==0 && matrix[i-1][j+1]==0) {
                        matrix[i][j]=0;
                        matrix[i+1][j]=1;
                    } 
                    if(matrix[i+1][j-1]==0 && matrix[i+1][j+1]==1 && matrix[i-1][j-1]==0 && matrix[i-1][j+1]==0) {
                        matrix[i][j]=0;
                        matrix[i+1][j]=1;
                    }                                 
                }
            }
        }

        //Snakesort 

        for(int i=rows-4; i>2; i=i-3){
            for(int j=0; j<cols; j++ ){
                if(matrix[i-1][j]==1 || matrix[i-2][j]==1){
                    matrix[i][j]=1;
                    matrix[i-1][j]=0;
                    matrix[i-2][j]=0;
                    //matrix[i-3][j]=0;
                }else if(matrix[i-1][j]==2 || matrix[i-2][j]==2 ){
                    matrix[i][j]=2;
                    matrix[i-1][j]=0;
                    matrix[i-2][j]=0;
                    //matrix[i-3][j]=0;
                }
            }
        }

        return matrix;


    }

    void GameMap::translateMap(chtype plat,int** matr) {

        init_pair(32, COLOR_BLACK, COLOR_RED);
        chtype t = ' ' | COLOR_PAIR(32);
        if(matr==0){
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                if (matrix[i][j] == 0) {
                    B[i][j] = ' ';
                } else if (matrix[i][j] == 1) {
                    B[i][j] = plat;
                } else if (matrix[i][j] == 2) {
                    B[i][j] = t;
                }
            }
        }  
        }else{
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                if (matr[i][j] == 0) {
                    B[i][j] = ' ';
                } else if (matr[i][j] == 1) {
                    B[i][j] = plat;
                } else if (matr[i][j] == 2) {
                    B[i][j] = t;
                }
            }
        }  
        }
        for(int j=0; j<12; j++){
            plat= ' '| COLOR_PAIR(200);            
            B[rows-1][j]=plat;
        }
        for(int j=cols-12; j<cols; j++){
            plat= ' '| COLOR_PAIR(200);
            B[4][j]=plat;
        }
    } 

    void GameMap::printMap(WINDOW* win) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            mvwaddch(win, i + 1, j + 1, B[i][j]);
        }
    }
        refresh();
        wrefresh(win);
    }





