#include <iostream>
#include <locale.h>
#include <ncurses.h>
#include "src/include/Board.cpp"
#include "src/include/Game.cpp"

#define BOARD_DIM 40
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5



using namespace std;



void print_animation(){
    
    int height, width;
    getmaxyx(stdscr, height, width);

    // Calcola la posizione iniziale a sinistra
    int x = (width - 51) / 2; // 51 è la lunghezza della tua stringa

    // Testo da stampare
    const char *text[] = {
        "     _  _____   _       _                      ",
        "    / \\|_   _|_| | ___ | |_    ___ _ __  _ __  ",
        "   / _ \\ | |/ _` |/ _ \\| __|  / __| '_ \\| '_ \\ ",
        "  / ___ \\| | (_| | (_) | |_  | (__| |_) | |_) |",
        " /_/   \\_\\_|\\__,_|\\___/ \\__|  \\___| .__/| .__/ ",
        "                                  |_|   |_|    "
    };

    // Stampa il testo da sinistra verso destra
    for (int i = 0; i < 48; ++i) {
        //clear();  // Pulisce la finestra ad ogni iterazione
        for (int j = 0; j < 6; ++j) {
            mvprintw(height / 3 + j, x + i, "%c", text[j][i]);
        }
        refresh();
        napms(60);  // Aggiungi un ritardo di 10 millisecondi tra le iterazioni
    }
    
    timeout(10);
    int ch;
    do {
        mvprintw(height / 2 + 3, (width - 37) / 2, "[Premere un tasto per continuare]");
        refresh();
        napms(500);  // Ritardo di 500 millisecondi durante il lampeggiamento
        mvprintw(height / 2 + 3, (width - 37) / 2, "                                 ");
        refresh();
        napms(500);
        ch = getch();
    }while (ch == ERR);
       
}

int main(int argc, char ** argv){

        initscr();
        start_color();
        init_pair(2, COLOR_WHITE, COLOR_BLACK);
        bkgdset(COLOR_PAIR(2));
        refresh();
        noecho();
        curs_set(0);

        print_animation();
        
        Game Atdot(BOARD_ROWS,BOARD_COLS);
        Atdot.scorri_livelli();




    return 0;
}
