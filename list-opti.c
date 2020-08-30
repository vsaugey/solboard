// SPDX-License-Identifier: GPL-3.0-only
/* Copyright 2020 Vincent Saugey <solboard@saugey.fr> */

/* 
  This library implement a simple and fast storage of list of 32 bits solitaire boards 
  A memory area contening the a bit flag for all possible position is reserved
  flag are tested by list_exist and activate by list_add
  A small counter keep the number of elements added
*/ 

#include <malloc.h>
#include <stdio.h>
#include "list-opti.h"


list list_init() {
    list l;
    l=(list)malloc(sizeof(struct L));
    l->l=(unsigned char *)malloc(sizeof(char) * 0x1FFFFFFF);
    //printf ("last index = %lu\n\n", 0x1FFFFFFF - 1);
    l->nb = 0;
    return l;
}

/*void longPrint2 (unsigned long k) {
int i = 0;
do {
 i++;
 printf("%lu",k & 1L);
    
} while ((k=k>>1)!=0);
 printf(" with %i bits\n", i);
}*/


int list_exist(list l,unsigned long x) {
	char bit = x & 0x00000007;
	return l->l[x >> 3] & (1 << bit);
}


int list_add (list l,unsigned long x) {
	char bit = (x & 0x00000007);  
    unsigned long index = x >> 3;
    if (!list_exist(l, x)) {
       l->nb++;
	   l->l[index] |= (1 << bit);
       return 1;
    }
    return 0;
}
