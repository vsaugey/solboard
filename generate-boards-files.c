// SPDX-License-Identifier: GPL-3.0-only
/* Copyright 2020 Vincent Saugey <solboard@saugey.fr> */

/*
  This executable generate winning board file that is needed by solboard.
*/

#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h> 
#include "libsolitaire.h"
#include "list-opti.h"


list L [2]; // Store list of possible winning boards starting from final pawn positions
list W [2]; // Store list of winning boards reduced to accessible from initial pawn positions 


/* print board */
void print_board(unsigned long p, int mil)
{
int i;
printf("\n");
for (i=0;i<9;i++) printf("x");
printf("\nxxx");
if (p&puis2(1)) printf("*"); else printf(" ");
if (p&puis2(2)) printf("*"); else printf(" ");
if (p&puis2(7)) printf("*"); else printf(" ");
printf("xxx\nxxx");
if (p&puis2(0)) printf("*"); else printf(" ");
if (p&puis2(3)) printf("*"); else printf(" ");
if (p&puis2(6)) printf("*"); else printf(" ");
printf("xxx\nx");
if (p&puis2(15)) printf("*"); else printf(" ");
if (p&puis2(14)) printf("*"); else printf(" ");
if (p&puis2(13)) printf("*"); else printf(" ");
if (p&puis2(4)) printf("*"); else printf(" ");
if (p&puis2(5)) printf("*"); else printf(" ");
if (p&puis2(24)) printf("*"); else printf(" ");
if (p&puis2(25)) printf("*"); else printf(" ");
printf("x\nx");
if (p&puis2(10)) printf("*"); else printf(" ");
if (p&puis2(11)) printf("*"); else printf(" ");
if (p&puis2(12)) printf("*"); else printf(" ");
if (mil) printf("*"); else printf(" ");
if (p&puis2(28)) printf("*"); else printf(" ");
if (p&puis2(27)) printf("*"); else printf(" ");
if (p&puis2(26)) printf("*"); else printf(" ");
printf("x\nx");
if (p&puis2(9)) printf("*"); else printf(" ");
if (p&puis2(8)) printf("*"); else printf(" ");
if (p&puis2(21)) printf("*"); else printf(" ");
if (p&puis2(20)) printf("*"); else printf(" ");
if (p&puis2(29)) printf("*"); else printf(" ");
if (p&puis2(30)) printf("*"); else printf(" ");
if (p&puis2(31)) printf("*"); else printf(" ");
printf("x\nxxx");
if (p&puis2(22)) printf("*"); else printf(" ");
if (p&puis2(19)) printf("*"); else printf(" ");
if (p&puis2(16)) printf("*"); else printf(" ");
printf("xxx\nxxx");
if (p&puis2(23)) printf("*"); else printf(" ");
if (p&puis2(18)) printf("*"); else printf(" ");
if (p&puis2(17)) printf("*"); else printf(" ");
printf("xxx\n");
for (i=0;i<9;i++) printf("x");
printf("\n");
getchar();
}


/* return the board value after the move move_number done  */
unsigned long move_board (unsigned long board, int move_number) {
  board&=~cache[move_number];
  board|=result[move_number];
  return board;
}

/* return a board after the move move_number done  */
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

int compt(unsigned long p, int mil) {
  lon k;
  k=p;
  int n=0;
  do
  if (k & 1L) n++;
  while ((k=k>>1)!=0);
  if (mil) n++;
  return n;
}

void find_board (unsigned long board, int middle_position) {
  if (!list_add(L[middle_position], rmax(board))) { return; }

  // For every possible unmove, find new boards.
  for (int i=0;i<12;i++) if (((board&cache[i])==result[i]) && (middle_position==rmil[i])) {
          find_board (undo_move_board (board,i), undo_move_middle_position(middle_position,i));
  } 
  for (int i=12;i<76;i++) if ((board&cache[i])==result[i]) {
          find_board (undo_move_board (board,i), middle_position);
  }
}

void play_board (unsigned long board, int middle_position) {
  if (!list_exist(L[middle_position], rmax(board))) { return; }
  if (!list_add(W[middle_position], rmax(board))) { return; }

//  print_board(board,middle_position);

  // For every possible unmove, find new boards.
  for (int i=0;i<12;i++) if (((board&cache[i])==coup[i]) && (middle_position==cmil[i])) {
          play_board (move_board (board,i), move_middle_position(middle_position,i));
  } 
  for (int i=12;i<76;i++) if ((board&cache[i])==coup[i]) {
          play_board (move_board (board,i), middle_position);
  }
}



/* backup list in the target file */
void saveliste(list li,char * fileName) {
  FILE * f;
  f=fopen(fileName,"wb+");
  for (unsigned long l=0;l<=0xFFFFFFFF;l++) {
      if (list_exist(li, l)) { fwrite(&l,4,1,f); }
  }   
  fclose(f);
}

int main() {

clock_t begin = clock();    
    
inittab();
L[0]=list_init();
L[1]=list_init();
print_board(0x0, 1);
printf("Start computation of possible boards, please wait computation could take few minutes\n");
//find_board (0L, 1); // find all winning boards that finish on the possition on the middle of the board. 
find_board (0x0, 1); // You could add other final position. 
unsigned long k=1L;
/* do {
  printf("\n\nnb of possible board : %llu\n", L[1]->nb + L[0]->nb);
  find_board (k, 0);
}while ((k=k<<1)!=0);
*/
printf("\n\nnb of possible boards : %llu\n", L[1]->nb + L[0]->nb);
printf( "Possible boards computed in %ld secondes\n", (clock() -  begin) / CLOCKS_PER_SEC );

W[0]=list_init();
W[1]=list_init();

printf("Reducing to winnig boards from starting position\n");
play_board (0xFFFFFFFF, 0); // Extract to list of boards that are possible to reach beginning at middle position
printf("\n\nnb of winning boards : %llu\n", W[1]->nb + W[0]->nb);
printf( "Winning boards computed in %ld secondes\n", (clock() -  begin) / CLOCKS_PER_SEC );

#define SAUVES "Winning-Boards-Without-Middle"
#define SAUVEA "Winning-Boards-With-Middle"

printf ("Creating %s\n", SAUVES); 
saveliste(W[0],SAUVES);
printf ("Creating %s\n", SAUVEA); 
saveliste(W[1],SAUVEA);

printf("\n\nnb of winning board find : with %llu  without :%llu\n", W[1]->nb,W[0]->nb);
clock_t end = clock();
unsigned long millis = (end -  begin) / CLOCKS_PER_SEC;
printf( "Compouted finished in %ld secondes\n", millis );  
    
}
