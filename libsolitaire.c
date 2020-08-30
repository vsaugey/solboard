// SPDX-License-Identifier: GPL-3.0-only
/* Copyright 2020 Vincent Saugey <solboard@saugey.fr> */

/*
  This librairy define basic funtion of solitaire board game.

  initab : initialize the tab structure representing possible move in the board

  Rotation functions permit to calculate a rotation left or right of the pawn on board

  sym permit to calculate symetry

  rmax will calcuate a unique board index representing until 8 differents position by rotation and symetry

*/


#include <stdio.h>
#include "libsolitaire.h"

void inittab(void) {

    rmil[0]=1;rmil[1]=0;rmil[2]=0;rmil[3]=0;rmil[4]=0;rmil[5]=1;rmil[6]=1;rmil[7]=0;rmil[8]=0;rmil[9]=0;rmil[10]=0;rmil[11]=1;
    cmil[0]=0;cmil[1]=1;cmil[2]=1;cmil[3]=1;cmil[4]=1;cmil[5]=0;cmil[6]=0;cmil[7]=1;cmil[8]=1;cmil[9]=1;cmil[10]=1;cmil[11]=0;

    cache[0]=puis2(3)+puis2(4);   result[0]=0;           pawn[0]=puis2(3); 
    cache[1]=puis2(3)+puis2(4);   result[1]=puis2(3);    pawn[1]=0;
    cache[2]=puis2(4)+puis2(20);  result[2]=puis2(20);   pawn[2]=puis2(4);
    cache[3]=puis2(4)+puis2(20);  result[3]=puis2(4);    pawn[3]=puis2(20);
    cache[4]=puis2(19)+puis2(20); result[4]=puis2(19);   pawn[4]=0;
    cache[5]=puis2(19)+puis2(20); result[5]=0;           pawn[5]=puis2(19);
    
    for (int i=0;i<6;i++) {
        cache[i+6]=rotg(cache[i]);
        result[i+6]=rotg(result[i]);
        pawn[i+6]=rotg(pawn[i]);        
    }

    cache[12]=puis2(1)+puis2(2)+puis2(7);    result[12]=puis2(1);   pawn[12]=puis2(7); 
    cache[13]=puis2(1)+puis2(2)+puis2(7);    result[13]=puis2(7);   pawn[13]=puis2(1); 
    cache[14]=puis2(0)+puis2(3)+puis2(6);    result[14]=puis2(0);   pawn[14]=puis2(6);
    cache[15]=puis2(0)+puis2(3)+puis2(6);    result[15]=puis2(6);   pawn[15]=puis2(0);
    cache[16]=puis2(15)+puis2(14)+puis2(13); result[16]=puis2(15);  pawn[16]=puis2(13);
    cache[17]=puis2(15)+puis2(14)+puis2(13); result[17]=puis2(13);  pawn[17]=puis2(15);
    cache[18]=puis2(14)+puis2(13)+puis2(4);  result[18]=puis2(14);  pawn[18]=puis2(4);
    cache[19]=puis2(14)+puis2(13)+puis2(4);  result[19]=puis2(4);   pawn[19]=puis2(14); 
    cache[20]=puis2(13)+puis2(4)+puis2(5);   result[20]=puis2(13);  pawn[20]=puis2(5);
    cache[21]=puis2(13)+puis2(4)+puis2(5);   result[21]=puis2(5);   pawn[21]=puis2(13);
    cache[22]=puis2(4)+puis2(5)+puis2(24);   result[22]=puis2(4);   pawn[22]=puis2(24);
    cache[23]=puis2(4)+puis2(5)+puis2(24);   result[23]=puis2(24);  pawn[23]=puis2(4); 
    cache[24]=puis2(5)+puis2(24)+puis2(25);  result[24]=puis2(5);   pawn[24]=puis2(25);
    cache[25]=puis2(5)+puis2(24)+puis2(25);  result[25]=puis2(25);  pawn[25]=puis2(5);
    

    cache[26]=puis2(10)+puis2(11)+puis2(12); result[26]=puis2(10);  pawn[26]=puis2(12);
    cache[27]=puis2(10)+puis2(11)+puis2(12); result[27]=puis2(12);  pawn[27]=puis2(10);
    cache[28]=puis2(28)+puis2(27)+puis2(26); result[28]=puis2(28);  pawn[28]=puis2(26);
    cache[29]=puis2(28)+puis2(27)+puis2(26); result[29]=puis2(26);  pawn[29]=puis2(28);
    cache[30]=puis2(9)+puis2(8)+puis2(21);   result[30]=puis2(9);   pawn[30]=puis2(21);
    cache[31]=puis2(9)+puis2(8)+puis2(21);   result[31]=puis2(21);  pawn[31]=puis2(9);
    cache[32]=puis2(8)+puis2(21)+puis2(20);  result[32]=puis2(8);   pawn[32]=puis2(20);
    cache[33]=puis2(8)+puis2(21)+puis2(20);  result[33]=puis2(20);  pawn[33]=puis2(8);
    cache[34]=puis2(21)+puis2(20)+puis2(29); result[34]=puis2(21);  pawn[34]=puis2(29);
    cache[35]=puis2(21)+puis2(20)+puis2(29); result[35]=puis2(29);  pawn[35]=puis2(21);
    cache[36]=puis2(20)+puis2(29)+puis2(30); result[36]=puis2(20);  pawn[36]=puis2(30);
    cache[37]=puis2(20)+puis2(29)+puis2(30); result[37]=puis2(30);  pawn[37]=puis2(20);
    cache[38]=puis2(29)+puis2(30)+puis2(31); result[38]=puis2(29);  pawn[38]=puis2(31);
    cache[39]=puis2(29)+puis2(30)+puis2(31); result[39]=puis2(31);  pawn[39]=puis2(29);
    
    
    cache[40]=puis2(22)+puis2(19)+puis2(16); result[40]=puis2(22);  pawn[40]=puis2(16); 
    cache[41]=puis2(22)+puis2(19)+puis2(16); result[41]=puis2(16);  pawn[41]=puis2(22);
    cache[42]=puis2(23)+puis2(18)+puis2(17); result[42]=puis2(23);  pawn[42]=puis2(17);
    cache[43]=puis2(23)+puis2(18)+puis2(17); result[43]=puis2(17);  pawn[43]=puis2(23);
    
    
    for (int i=12;i<44;i++) {
        cache[i+32]=rotg(cache[i]);
        result[i+32]=rotg(result[i]);
        pawn[i+32]=rotg(pawn[i]);
    }

    for (int i=0;i<76;i++) coup[i]=cache[i]-result[i];
}


unsigned long rotd(unsigned long l) {
    plateau p;
    p.l = l;
    char s;
    s=p.c[0];
    p.l=(p.l>>8) & 0xFFFFFFFF;
    p.c[3]=s;
    return p.l;
}

unsigned long rotg(unsigned long l) {
    plateau p;
    p.l = l;
    char s;
    s=p.c[3];
    p.l=(p.l<<8) & 0xFFFFFFFF;
    p.c[0]=s;
    return p.l;
}

char transp(char c) {
    char buf=0;
    buf=(c&(128+64))>>6;
    buf|=(c&3)<<6;
    buf|=(c&(4+8+16));
    return buf;
}

unsigned long symp(unsigned long l) {
    plateau buf, cache, p;
    p.l = l;
    char s;
    cache.l=p.l&538976288L;
    buf.c[0]=transp(p.c[0]);
    buf.c[2]=transp(p.c[2]);
    buf.c[1]=transp(p.c[3]);
    buf.c[3]=transp(p.c[1]);
    buf.l&=3755991007L;
    s=cache.c[3];
    cache.l=(cache.l<<8) & 0xFFFFFFFF;
    cache.c[0]=cache.c[2];
    cache.c[2]=s;
    buf.l|=cache.l;
    return buf.l;
}


unsigned long rmax(unsigned long l) {
    unsigned long max;
    max=l;
    //unsigned long init=l;
    l=rotd(l);
    if (l>max) max=l;
    l=rotd(l);
    if (l>max) max=l;
    l=rotd(l);
    if (l>max) max=l;
    //l=rotd(l);
    //if (l != init) { printf ("Error in rotation droit"); } // max.l=p.l;

    l=symp(l);
    //init=l;
    if (l>max) max=l;
    l=rotd(l);
    if (l>max) max=l;
    l=rotd(l);
    if (l>max) max=l;
    l=rotd(l);
    if (l>max) max=l;
    //l=rotd(l);
    //if (l != init) { printf ("Error in rotation gauche"); } //max.l=p.l;

    return max;
}


unsigned long puis2(int p) {
    return 1L<<p;
}


/* affiche le plateau du solitaire
*/
void affiche(unsigned long p, int mil) {
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



void longPrint (unsigned long k) {
    int i = 0;
    do {
        i++;
        printf("%lu",k & 1L);        
    } while ((k=k>>1)!=0);
    printf(" with %i bits\n", i);
}

