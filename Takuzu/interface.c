#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "const.h"
#include "structs.h"

t_interface init_interface(int tailleGrille, t_grid grid) {
    t_interface *interface = malloc(sizeof(t_interface));
    SDL_Init(SDL_INIT_VIDEO);
    interface->screen = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE);
SDL_WM_SetCaption("Takuzu", NULL);
    interface->grid = malloc(tailleGrille * sizeof(SDL_Surface * *));
    interface->rect_grid = malloc(tailleGrille * sizeof(SDL_Rect * ));
    interface->menu = IMG_Load("img/menu.png");
    interface->rect_menu.x = 700;
    interface->rect_menu.y = 0;
    interface->batton = IMG_Load("img/batton.png");
    interface->rect_batton.y = 290;
    SDL_BlitSurface(interface->menu, NULL, interface->screen, &interface->rect_menu);
    if (grid.size == 4) {
        interface->z = IMG_Load("img/0_4x4.png");
        interface->u = IMG_Load("img/1_4x4.png");
    } else {
        interface->z = IMG_Load("img/0_8x8.png");
        interface->u = IMG_Load("img/1_8x8.png");
    }
    for (int i = 0; i < tailleGrille; i++) {
        interface->grid[i] = malloc(tailleGrille * sizeof(SDL_Surface * ));
        interface->rect_grid[i] = malloc(tailleGrille * sizeof(SDL_Rect));
        for (int j = 0; j < tailleGrille; j++) {
            interface->grid[i][j] = SDL_CreateRGBSurface(0, 700 / tailleGrille - 5, 700 / tailleGrille - 5, 32,
                                                         0, 0, 0, 0);
            if (grid.mask[i][j] == 1) {
                SDL_FillRect(interface->grid[i][j], NULL, SDL_MapRGB(interface->screen->format, 200, 200, 200));
            } else {
                SDL_FillRect(interface->grid[i][j], NULL, SDL_MapRGB(interface->screen->format, 255, 255, 255));
            }
            interface->rect_grid[i][j].x = j * (700 / tailleGrille);
            interface->rect_grid[i][j].y = i * (700 / tailleGrille);
            SDL_BlitSurface(interface->grid[i][j], NULL, interface->screen, &interface->rect_grid[i][j]);
        }
    }
    return *interface;
}

void printScreen(int **grille, t_grid grid, t_interface *interface) {
    for (int i = 0; i < grid.size; i++) {
        for (int j = 0; j < grid.size; j++) {
            SDL_BlitSurface(interface->grid[i][j], NULL, interface->screen, &interface->rect_grid[i][j]);

            switch (grille[i][j]) {
                case 0:
                    SDL_BlitSurface(interface->z, NULL, interface->screen, &interface->rect_grid[i][j]);
                    break;
                case 1:
                    SDL_BlitSurface(interface->u, NULL, interface->screen, &interface->rect_grid[i][j]);
                    break;
            }
        }
    }
    SDL_BlitSurface(interface->menu, NULL, interface->screen, &interface->rect_menu);
    for(int i = 0; i<grid.indice->nbr;i++){
      interface->rect_batton.x = 920+i*20;
      SDL_BlitSurface(interface->batton, NULL, interface->screen, &interface-> rect_batton);
    }


}


void close_interface(t_interface *interface, int tailleGrille) {
    for (int i = 0; i < tailleGrille; i++) {
        for (int j = 0; j < tailleGrille; j++) {
            free(interface->grid[i][j]);
        }
        free(interface->grid[i]);
        free(interface->rect_grid[i]);
    }
    free(interface->grid);
    free(interface->rect_grid);
    free(interface->screen);
    free(interface->z);
    free(interface->u);
    free(interface->menu);
    free(interface->batton);
}
