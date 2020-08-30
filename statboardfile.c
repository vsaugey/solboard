// SPDX-License-Identifier: GPL-3.0-only
/* Copyright 2020 Vincent Saugey <solboard@saugey.fr> */

/*
  Small utility to verify number of winning board generated files
*/


#include <stdio.h>
#include <stdlib.h>

unsigned long puis2(int p) {
    return 1L<<p;
}

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
printf( "0x%08.8X", p);

getchar();
}

int compt(unsigned int k, int mil) {
  int n=0;
  do
    if (k & 1L) n++;
  while ((k=(k>>1))!=0);
  if (mil) n++;
  return n;
}


void main(int argc, char *argv[]) {
    unsigned int p;
    int mil=1;
    unsigned long stat[34];
    for (int i=0; i<34; i++) {
        stat[i]=0;
    }
 //   
    printf ("open file %s\n",argv[1]);

 if (argc == 0) { printf ("Usage %s filenamewith filenamewithout", argv[0]); exit(0);} 

for (int i = 1 ; i < argc; i++) {

    FILE * f=fopen(argv[i],"rb");
    fread(&p,4,1,f);
    while (!feof(f)) {
//       if (compt(p,1)<=5) {print_board (p, 1);}
//        print_board (p, mil);
//       printf ("%i\n", compt(p,1));
        stat[compt(p,i%2)]++;
        fread(&p,4,1,f);
    }
    printf ("close file %s\n",argv[i]);

    fclose(f);
}

    for (int i=0; i<33; i++) {
        printf ("%i:%lu\n", i, stat[i]);
    }


}