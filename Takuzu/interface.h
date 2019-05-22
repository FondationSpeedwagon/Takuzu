#ifndef H_INTERFACE
#define H_INTERFACE

#include "interface.c"

t_interface init_interface(int, t_grid);

void printScreen(int **, t_grid, t_interface *);

void close_interface(t_interface *, int);

#endif
