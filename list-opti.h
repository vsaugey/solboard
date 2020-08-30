// SPDX-License-Identifier: GPL-3.0-only
/* Copyright 2020 Vincent Saugey <solboard@saugey.fr> */

/* 
  This library implement a simple and fast storage of list of 32 bits solitaire boards 
  A memory area contening the a bit flag for all possible position is reserved
  flag are tested by list_exist and activate by list_add
  A small counter keep the number of elements added
*/ 




typedef struct L {
        unsigned char * l;
        unsigned long nb;
} * list;


list list_init();
int list_exist(list l, unsigned long x);
int list_add(list l, unsigned long x);




