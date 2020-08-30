// SPDX-License-Identifier: GPL-3.0-only
/* Copyright 2020 Vincent Saugey <solboard@saugey.fr> */

/*
  This librairy define basic funtion of solitaire board game.

  initab : initialize the tab structure representing possible move in the board

  Rotation functions permit to calculate a rotation left or right of the pawn on board

  sym permit to calculate symetry

  rmax will calcuate a unique board index representing until 8 differents position by rotation and symetry


*/

typedef unsigned long lon;

typedef union bo
                {
                 unsigned long l;
                 unsigned int i[2];
                 unsigned char c[4];
                }
                plateau;



void aff_bin(unsigned long i);

unsigned long rotd(unsigned long l);
unsigned long rotg(unsigned long l);

char transp(char c);
unsigned long symp(unsigned long l);
unsigned long rmax(unsigned long l);
void aff_bin(unsigned long i);

void affiche(unsigned long p, int mil);

unsigned long puis2(int p);

void longPrint (unsigned long k);

// Tabs representing the different moves
lon cache[76];
lon coup[76];
lon result[76];
lon pawn[76];
char cmil[12];
char rmil[12];


/* init the table of possible move on the board 
*/
void inittab(void);
