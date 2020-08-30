// SPDX-License-Identifier: GPL-3.0-only
/* Copyright 2020 Vincent Saugey <solboard@saugey.fr> */

/*
  This program implement a interface to the library to illustrate how computation of board are done.

*/

#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h> 
#include <ncurses.h>
#include "libsolitaire.h"
#include "list-opti.h"

#define SAUVES "Winning-Boards-Without-Middle"
#define SAUVEA "Winning-Boards-With-Middle"

#define ENTER 10
#define ESCAPE 27

unsigned int xy_toboard[8][8] = {{ 0, 0 , 0x2, 0x4 , 0x80, 0, 0},
                           { 0, 0 , 0x1, 0x8 , 0x40, 0, 0},
                           { 0x8000, 0x4000 , 0x2000, 0x10, 0x20 , 0x1000000, 0x2000000},
                           { 0x400, 0x800 , 0x1000, 0x0, 0x10000000, 0x8000000, 0x4000000},
                           { 0x200, 0x100 , 0x200000, 0x100000, 0x20000000, 0x40000000, 0x80000000},
                           { 0, 0 , 0x400000, 0x80000 , 0x10000, 0, 0},
                           { 0, 0 , 0x800000, 0x40000 , 0x20000, 0, 0}};


list W [2]; // list of winning board
int depth=0;
char plays[34];
int nb_game=0;


/* return the board value after the move move_number done  */
unsigned long move_board (unsigned long board, int move_number) {
  board&=~cache[move_number];
  board|=result[move_number];
  return board;
}

/* return a middle position value after the move move_number done  */
int move_middle_position (int middle_position, int move_number) {
  return move_number<12?middle_position=rmil[move_number]:middle_position;
}

/* return a board after the move move_number undone  */
unsigned long undo_move_board (unsigned long board, int move_number) {
  board&=~cache[move_number];
  board|=coup[move_number];
  return board;
}

/* return value of the middle position after the move move_number undone  */
int undo_move_middle_position (int middle_position, int move_number) {
  return move_number<12?middle_position=cmil[move_number]:middle_position;
}

int compt(unsigned long p, int middle) {
  lon k;
  k=p;
  int n=0;
  do
  if (k & 1L) n++;
  while ((k=k>>1)!=0);
  if (middle) n++;
  return n;
}

int move_test (unsigned long board, int middle_position, int i) {
  if ((board&cache[i])==coup[i]) {
    if (i>=12 || (middle_position==cmil[i])) {
      return true;
    }
  }
  return false;
}

void play_board (unsigned long board, int middle_position) {

  if (!list_exist(W[middle_position], rmax(board))) { return; }
  
  // For every possible unmove, find new boards.
  for (int i=0;i<76;i++) if (move_test(board, middle_position, i)) {
    plays[++depth] = i;
    play_board (move_board (board,i), move_middle_position(middle_position,i));
    depth--;
  } 

}

void readfile(list li, char * fileName) {
  unsigned int p=0;
  printf ("open file %s\n",fileName);

  FILE * f=fopen(fileName,"rb");

  if (f == NULL) { printf("%s not found, please run 'generate-boards-files' exec to generate winning board files"); exit (-1); }

  fread(&p,4,1,f);
  while (!feof(f)) { list_add(li,p); fread(&p,4,1,f); }
  printf ("close file %s\n",fileName);
  fclose(f);
}


void show_board(WINDOW * board, unsigned int p, int middle, char * grab_move, char x, char y) {

  wattroff(board, COLOR_PAIR(1));
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  if (!list_exist(W[middle], rmax(p)) && p != 0xFFFFFFFF) {    
    init_pair(1, COLOR_RED, COLOR_BLACK);
  }
  wattron(board, COLOR_PAIR(1));

  mvwprintw(board, 0, 0, "XX");

  if (p&puis2(1)) wprintw(board, "*"); else wprintw(board," ");
  if (p&puis2(2)) wprintw(board, "*"); else wprintw(board," ");
  if (p&puis2(7)) wprintw(board, "*"); else wprintw(board," ");

  wprintw(board, "XXX");
  mvwprintw(board, 1, 0, "XX");

  if (p&puis2(0)) wprintw(board, "*"); else wprintw(board," ");
  if (p&puis2(3)) wprintw(board, "*"); else wprintw(board," ");
  if (p&puis2(6)) wprintw(board, "*"); else wprintw(board," ");

  wprintw(board, "XXX");
  wmove(board, 2, 0);
  if (p&puis2(15)) wprintw(board,"*"); else wprintw(board, " ");
  if (p&puis2(14)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(13)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(4)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(5)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(24)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(25)) wprintw(board, "*"); else wprintw(board, " ");
  wmove(board, 3, 0);
  
  if (p&puis2(10)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(11)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(12)) wprintw(board, "*"); else wprintw(board, " ");
  if (middle) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(28)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(27)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(26)) wprintw(board, "*"); else wprintw(board, " ");

  if (p&puis2(9)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(8)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(21)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(20)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(29)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(30)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(31)) wprintw(board, "*"); else wprintw(board, " ");

  wprintw(board, "XX");
  if (p&puis2(22)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(19)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(16)) wprintw(board, "*"); else wprintw(board, " ");
  wprintw(board, "XX");

  wprintw(board, "XX");
  if (p&puis2(23)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(18)) wprintw(board, "*"); else wprintw(board, " ");
  if (p&puis2(17)) wprintw(board, "*"); else wprintw(board, " ");
  wprintw(board, "XX");

  wattron(board, A_REVERSE);
//    wattron(board, A_REVERSE);
  if (grab_move[0] != -1) {
    mvwaddch(board, y-1, x, 94 | A_REVERSE);   
  }
  if (grab_move[1] != -1) {
    mvwaddch(board, y+1, x, 118 | A_REVERSE);
  }
  if (grab_move[2] != -1) {
    mvwaddch(board, y, x-1, '<' | A_REVERSE);
  }
  if (grab_move[3] != -1) {
    mvwaddch(board, y, x+1, '>' | A_REVERSE);
  }
  
  wattroff(board, A_REVERSE);
}

int is_selectable (unsigned int p, int mil, char x, char y) {
  unsigned int z = xy_toboard[y][x];
  move(1,0);
  printw("                                    ");
  for (int i = 0 ; i < 76; i++) {
      if ((pawn[i] == z) && move_test(p, mil, i) ) {
        return 1;
      }
  }
  move(1,0);
  printw("PAWN NOT SELECTABLE                       ");
  return 0;
}

void clear_move (char * t) {
for (int i=0; i<4; i++) {
  t[i] = -1;
}
}


int main() {
WINDOW * board;
unsigned int b = 0xFFFFFFFF;
int middle=0;

inittab();

W[0]=list_init();
W[1]=list_init();
char game [33];
int depth=-1;

initscr();
keypad(stdscr, TRUE);
noecho();
cbreak();

char pawn_grab=0;
char pawn_grab_move[4];
int x=3,y=3;
int sel_x=-1,sel_y=-1;
board = subwin(stdscr, 7, 7, LINES / 2 - 4, COLS / 2 - 4);
show_board (board, b, middle, pawn_grab_move, sel_x, sel_y);

readfile (W[0], SAUVES);
readfile (W[1], SAUVEA);

clear_move(pawn_grab_move);
mvprintw(0,0,"Press 'q' to quit and 'u' to undo a move"); 

int key=0;
while (key != 'q') {
  wmove(board, y, x);
  refresh();
  wrefresh(board);
  key = getch();
 // if (depth == -1) mvprintw(0,0, "No last move");
 // else mvprintw (0,0,"last move %i, with depth : %i                 ", game[depth], depth);
  
  if (key == 'u') {
  //  mvprintw (0,0,"undo move %i, with depth : %i            ", game[depth], depth);
    if (depth != -1) {
      b = undo_move_board (b, game[depth]);
      middle = undo_move_middle_position (middle, game[depth]); 
      depth--;
      pawn_grab = 0;
      clear_move(pawn_grab_move);
      show_board (board, b, middle, pawn_grab_move, sel_x, sel_y);
      wrefresh(board);
     }
  }
  if (pawn_grab){ // is a pawn is in grabbed state
    int m = -1;
    switch (key) {
      case ENTER:
        pawn_grab = 0;
        clear_move(pawn_grab_move);
        show_board (board, b, middle, pawn_grab_move, sel_x, sel_y);
      break;
      case KEY_DOWN: m = pawn_grab_move[1]; break;
      case KEY_UP: m = pawn_grab_move[0]; break;
      case KEY_LEFT: m = pawn_grab_move[2]; break;
      case KEY_RIGHT: m = pawn_grab_move[3]; break;
    }
    if (m >= 0) { 
      pawn_grab = 0;
      clear_move(pawn_grab_move);
      b = move_board(b,m);
      middle = move_middle_position(middle, m);
      game[++depth]=m;
      show_board (board, b, middle, pawn_grab_move, sel_x, sel_y);
    } 
  }
  else { // if pawn is in selection state
    switch (key) {
      case 'u':break;
      case KEY_DOWN: y = (y<6) && ((y!=4) || ((x>1) && (x<5))) ? y+1 : y; break;
      case KEY_UP: y = (y>0) && ((y!=2) || ((x>1) && (x<5))) ? y-1 : y; break;
      case KEY_LEFT: x = (x>0) && ((x!=2) || ((y>1) && (y<5))) ? x-1 : x; break;
      case KEY_RIGHT: x = (x<6) && ((x!=4) || ((y>1) && (y<5))) ? x+1 : x; break;
      case KEY_ENTER: 
      case ENTER:
        if (is_selectable (b, middle, x, y)) {
          sel_x = x; sel_y = y;
          unsigned int z = xy_toboard[y][x];
          for(int i=0; i<76; i++) {
            if ((pawn[i] == z) && move_test(b, middle, i)) {
              if (i>43) { // Vertical move
                if (i%2) { pawn_grab_move [0] = i; }
                else { pawn_grab_move [1] = i; }
              }
              if (i<6) {
                if ((i+1)%2) { pawn_grab_move [1] = i; }
                else { pawn_grab_move [0] = i; }
              }

              if ((i>=6) && (i<12)) {
                if ((i+1)%2) {  pawn_grab_move [3] = i; }
                else {  pawn_grab_move [2] = i; }
              }
              if ((i>=12) && (i<=43)) { // Horizontal move
                if (i%2) {  pawn_grab_move [3] = i; }
                else {  pawn_grab_move [2] = i; }
              }

            } 
          }
          pawn_grab=1;
          show_board (board, b, middle, pawn_grab_move, sel_x, sel_y);
        }
        break;

      default:
        mvprintw (1,0,"Unknow character : %c with code : %i", key, key);
    }
//    mvprintw (0,0,"x = %i and y = %i | sel_x = %i and sel_y %i\n", x,y, sel_x, sel_y);
//    mvprintw (0,0,"Down : %i\nUp   : %i\nLeft : %i\nRight: %i\n", pawn_grab_move[0], pawn_grab_move[1], pawn_grab_move[2], pawn_grab_move[3]);
  }
  wrefresh(board);
  refresh();
}

endwin();
//free(board);    
return 0;


}
