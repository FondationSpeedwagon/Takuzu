#ifndef H_STRUCTS
#define H_STRUCTS

typedef struct{
    int x;
    int y;
    int sol;
    int nbr;
} t_indice;

typedef struct {
    SDL_Surface *screen, *z, *u, *batton, *menu;
    SDL_Surface ***grid;
    SDL_Rect **rect_grid;
    SDL_Rect rect_menu, rect_batton;

} t_interface;

typedef struct {
    int **solve;
    int **mask;
    int **display;
    int size;
    t_indice *indice;
} t_grid;


#endif





