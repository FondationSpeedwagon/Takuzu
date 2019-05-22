#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>

#include "const.h"
#include "structs.h"
#include "grids.h"
#include "interface.h"

// declaration des fonctions
t_grid generation(int);

t_grid generation_test(int);

void completion(t_grid*);

int verif_total(t_grid);

int verif_cons(int **, int, int);

int verif_coup(int **, int, const int *);

void destroy(int **, int);

int **hide(t_grid);

int *convertbin(int);

int indice(t_grid*);


// fonction principale 
int main(int argc, char *argv[]) {
  // iniatialisation de la SDL et du random
  SDL_Event event;
  srand((unsigned int) time(0));
  // inialisation de la grille joué
  t_grid grid = grid8_4();
  int continuer = 1, tailleGrille = 8, tmp, pos[2], complet= 0, test = 0;
  grid.display = hide(grid);
  t_interface interface = init_interface(tailleGrille, grid);
  grid.indice->nbr = 3;
  //completion(&grid);
  printScreen(grid.display, grid, &interface);
  while (continuer) {
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          continuer = 0;
          break;
        case SDL_MOUSEBUTTONUP: // action de la souris dans la SDL
          if (event.button.button == 1 && complet == 0 && event.button.x < 700) {
            pos[0] = event.button.y / (700 / tailleGrille);
            pos[1] = event.button.x / (700 / tailleGrille);
            if (grid.mask[pos[0]][pos[1]] == 0) {
              if (grid.display[pos[0]][pos[1]] == 2)
                grid.display[pos[0]][pos[1]] = 0;
              else
                grid.display[pos[0]][pos[1]]++;
              tmp = verif_coup(grid.display, tailleGrille, pos);
              if (tmp != 1)
                SDL_FillRect(interface.grid[pos[0]][pos[1]], NULL,
                    SDL_MapRGB(interface.screen->format, 200, 50, 50));
              else
                SDL_FillRect(interface.grid[pos[0]][pos[1]], NULL,
                    SDL_MapRGB(interface.screen->format, 255, 255, 255));


            }
          }// action du clic gauche 
          else if(event.button.button == 1 && complet == 0 && event.button.x > 700){
            if(event.button.x > 800 && event.button.x < 900 && event.button.y >200 && event.button.y <300){
              if (indice(&grid) != 0 && grid.indice->nbr>0){
                SDL_FillRect(interface.grid[grid.indice->x][grid.indice->y], NULL, SDL_MapRGB(interface.screen->format, 0, 255, 0));
                grid.indice->nbr--; 
                printScreen(grid.display, grid, &interface);
                SDL_Flip(interface.screen);
              }

            }

          }
          printScreen(grid.display, grid, &interface);
          break;
        case SDL_KEYUP: 
          if(event.key.keysym.sym == SDLK_RETURN){ // on complete une case a chaque apuie d'entrée
            completion(&grid);
            SDL_FillRect(interface.grid[grid.indice->x][grid.indice->y], NULL, SDL_MapRGB(interface.screen->format, 0, 255, 0));
            printScreen(grid.display, grid, &interface);
          }


      }

    }
    test = verif_total(grid);// on met la grille en ert quand elle est complété 
    if(test){
      for(int i = 0; i< grid.size; i++){
        for(int j = 0; j<grid.size; j++){
          SDL_FillRect(interface.grid[i][j], NULL,
              SDL_MapRGB(interface.screen->format, 50,200,50));

        }
      }
    }
    SDL_Flip(interface.screen);

  }

  close_interface(&interface, tailleGrille);
  SDL_Quit();
  destroy(grid.display, tailleGrille);
  return EXIT_SUCCESS;

}

// generation d'une grille aleatoire

t_grid generation_test(int tailleGrille) {
  t_grid *grid = malloc(sizeof(t_grid));
  grid->solve = malloc(tailleGrille * sizeof(int *));
  grid->mask = malloc(tailleGrille * sizeof(int *));
  grid->size = tailleGrille;
  grid->indice = malloc(sizeof(t_indice));
  int combinaison[] = {3, 5, 6, 9, 10, 12};
  int combinaison8[] = {1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13};
  int *played = calloc((size_t) 6, sizeof(int));
  int *played_1 = calloc((size_t) 12, sizeof(int));
  int *played_2 = calloc((size_t) 12, sizeof(int));

  for (int i = 0; i < tailleGrille; i++) {
    grid->mask[i] = calloc((size_t) tailleGrille, sizeof(int));
  }
  int tmp_1 = 0, tmp_2 = 0;
  int k = 0;
  int stack;
  while (k < tailleGrille) {
    do {
      if (tailleGrille == 4) {
        tmp_1 = rand() % 6;
        while (played[tmp_1] != 0) {
          tmp_1 = rand() % 6;
        }
        grid->solve[k] = convertbin(combinaison[tmp_1]);


      } else if (tailleGrille == 8) {
        tmp_1 = rand() % 12;
        tmp_2 = rand() % 12;

        while (played_1[tmp_1] == 1 && played_2[tmp_2] == 1) {
          tmp_1 = rand() % 12;
          tmp_2 = rand() % 12;
        }
        grid->solve[k] = convertbin((combinaison8[tmp_1] << 4) + combinaison8[tmp_2]);


      }
      stack++;
      if (stack > 12 * 12) {
        k = 0;
        stack = 0;
        played_1 = calloc(14, sizeof(int));
        played_2 = calloc(14, sizeof(int));
      }

    } while (verif_cons(grid->solve, k, tailleGrille) != 1);
    stack = 0;
    played[tmp_1] = 1;
    played_1[tmp_2] = 1;
    k++;
  }
  for (int i = 0; i < (tailleGrille * tailleGrille) / 2; i++) {
    tmp_1 = rand() % tailleGrille;
    tmp_2 = rand() % tailleGrille;
    while (grid->mask[tmp_1][tmp_2]) {
      tmp_1 = rand() % tailleGrille;
      tmp_2 = rand() % tailleGrille;
    }
    grid->mask[tmp_1][tmp_2] = 1;
  }
  return *grid;
}

// verification des grilles genere 
int verif_cons(int **grille, int indice, int tailleGrille) {
  int n = 0, tmp_1 = 0, tmp_0 = 0, nb_1 = 0;
  int act = grille[indice][0];
  for (int j = 0; j < tailleGrille; j++) {
    if (act == grille[indice][j])
      n++;
    else
      n = 1;
    if (n > 2) {
      free(grille[indice]);
      grille[indice] = calloc((size_t) tailleGrille, sizeof(int));
      return 0;
    }
    if (grille[indice][j] == 1)
      nb_1++;

    act = grille[indice][j];
  }
  if (nb_1 != tailleGrille / 2) {
    free(grille[indice]);
    return 0;
  }
  n = 0;
  act = grille[0][0];
  for (int i = 0; i < tailleGrille; i++) {
    for (int j = 0; j <= indice; j++) {
      if (grille[j][i] == 1)
        tmp_1++;
      else
        tmp_0++;
      if (act == grille[j][i])
        n++;
      else
        n = 1;
      if (n > 2) {
        free(grille[indice]);
        grille[indice] = calloc((size_t) tailleGrille, sizeof(int));
        return 0;
      }
      act = grille[j][i];

    }
    n = 0;
    if (tmp_0 > tailleGrille / 2 || tmp_1 > tailleGrille / 2) {
      free(grille[indice]);
      grille[indice] = calloc((size_t) tailleGrille, sizeof(int));
      return 0;
    }
    tmp_0 = 0;
    tmp_1 = 0;
  }
  return 1;
}

// fonction qui verifie si le coup est en accord avec les regles
int verif_coup(int **grille, int tailleGrille, const int *pos) {
  int actuel = grille[pos[0]][0], n = 0, tmp_0 = 0, tmp_1 = 0;
  if (grille[pos[0]][pos[1]] == 2)
    return 1;
  for (int j = 0; j < tailleGrille; j++) {
    if (actuel == grille[pos[0]][j] && grille[pos[0]][j] != 2)
      n++;
    else
      n = 1;
    if (n > 2)
      return 0;
    actuel = grille[pos[0]][j];
    if (grille[pos[0]][j] == 1)
      tmp_1++;

    else if (grille[pos[0]][j] == 0)
      tmp_0++;

  }
  if (tmp_0 > tailleGrille / 2 || tmp_1 > tailleGrille / 2) {
    return 0;
  }
  n = 0;
  tmp_1 = 0;
  tmp_0 = 0;
  actuel = grille[0][pos[1]];
  for (int j = 0; j < tailleGrille; j++) {
    if (actuel == grille[j][pos[1]] && grille[j][pos[1]] != 2)
      n++;
    else
      n = 1;
    if (n > 2)
      return 0;
    actuel = grille[j][pos[1]];

    if (grille[j][pos[1]] == 1)
      tmp_1++;

    else if (grille[j][pos[1]] == 0)
      tmp_0++;
  }
  if (tmp_0 > tailleGrille / 2 || tmp_1 > tailleGrille / 2)
    return 0;
  return 1;

}

// free les grilles
void destroy(int **grille, int tailleGrille) {
  for (int i = 0; i < tailleGrille; i++)
    free(grille[i]);
  free(grille);
}


int **hide(t_grid grille) {
  int **grid_hide = malloc(grille.size * sizeof(int *));
  for (int i = 0; i < grille.size; i++) {
    grid_hide[i] = calloc((size_t) grille.size, sizeof(int));
    for (int j = 0; j < grille.size; j++) {
      if (grille.mask[i][j] == 1)
        grid_hide[i][j] = grille.solve[i][j];
      else
        grid_hide[i][j] = 2;
    }
  }
  return grid_hide;

}

int verif_total(t_grid grid) {
  int somme = 0;
  for (int i = 0; i < grid.size; i++) {
    for (int j = 0; j < grid.size; j++) {
      if (grid.display[i][j])
        somme++;
    }
  }
  if (somme == (grid.size * grid.size) / 2)
    return 1;
  else
    return 0; 
}

void completion(t_grid* grid) {
  if (indice(grid))
    grid->display[grid->indice->x][grid->indice->y]=grid->indice->sol;
}

// convertie en binaire un nombre
int *convertbin(int nbr) {
  int *bin = NULL;
  if (nbr < 16) {
    bin = calloc(4, sizeof(int));
    for (int i = 0; i < 4; i++) {
      bin[3 - i] = nbr % 2;
      nbr /= 2;
    }
  } else {
    bin = calloc(8, sizeof(int));
    for (int i = 0; i < 8; i++) {
      bin[7 - i] = nbr % 2;
      nbr /= 2;
    }
  }
  return bin;
}

// genere les indices en fonction des coupevidents
int indice(t_grid *grid) {
  char actuel = grid->display[0][0];
  int n = 0, tmp_0 = 0, tmp_1 = 0;
  for (int i = 0; i < grid->size; i++) {
    for (int j = 0; j < grid->size; j++) {
      if (actuel == grid->display[i][j] && grid->display[i][j] != 2)
        n++;
      else
        n = 1;
      if (n == 2 && j > 1 && grid->display[i][j - 2] == 2) {
        grid->indice->x  = i;
        grid->indice->y  = j-2;
        grid->indice->sol = (grid->display[i][j]-1)*(grid->display[i][j]-1);
        return 1;
      }
      if (n == 2 && j < grid->size - 1 && grid->display[i][j + 1] == 2) {
        grid->indice->x  = i;
        grid->indice->y  = j+1;
        grid->indice->sol = (grid->display[i][j]-1)*(grid->display[i][j]-1);
        return 1;
      }
      actuel = grid->display[i][j];
      if (grid->display[i][j] == 1)
        tmp_1++;

      else if (grid->display[i][j] == 0)
        tmp_0++;

      if (j > 0 && j < grid->size - 1 && grid->display[i][j - 1] == grid->display[i][j + 1] &&  grid->display[i][j] == 2 && grid->display[i][j-1] != 2){
        grid->indice->x  = i;
        grid->indice->y  = j;
        grid->indice->sol = (grid->display[i][j-1]-1)*(grid->display[i][j-1]-1);
        return 1;
      }

    }
    if(tmp_0 == grid->size/2 && tmp_1<grid->size/2){
      for(int k = 0; k< grid->size; k++){
        if (grid->display[i][k] == 2){
          grid->indice->x  = i;
          grid->indice->y  = k;
          grid->indice->sol = 1;
          return 1;
        }
      }
    }
    if(tmp_1 == grid->size/2 && tmp_0<grid->size/2){
      for(int k = 0; k< grid->size; k++){
        if (grid->display[i][k] == 2){
          grid->indice->x  = i;
          grid->indice->y  = k;
          grid->indice->sol = 0;
          return 1;
        }
      }
    }
    tmp_0 = 0;
    tmp_1 = 0;
    n = 0;
  }
  n = 0;
  tmp_1 = 0;
  tmp_0 = 0;
  actuel = grid->display[0][0];
  for (int i = 0; i < grid->size; i++) {
    for (int j = 0; j < grid->size; j++) {
      if (actuel == grid->display[j][i] && grid->display[j][i] != 2) {
        n++;
      } else
        n = 1;
      if (n == 2 && j > 1 && grid->display[j-2][i] == 2) {
        grid->indice->x  = j-2;
        grid->indice->y  = i;
        grid->indice->sol = (grid->display[j][i]-1)*(grid->display[j][i]-1);
        return 1;
      }
      if (n == 2 && j < grid->size - 1 && grid->display[j+1][i] == 2) {
        grid->indice->x  = j+1;
        grid->indice->y  = i;
        grid->indice->sol = (grid->display[j][i]-1)*(grid->display[j][i]-1);
        return 1;
      }
      actuel = grid->display[j][i];
      if (grid->display[j][i] == 1)
        tmp_1++;

      else if (grid->display[j][i] == 0)
        tmp_0++;
      if (j > 0 && j < grid->size - 1 && grid->display[j-1][i] == grid->display[j+1][i] &&  grid->display[j][i] == 2 && grid->display[j-1][i] != 2){
        grid->indice->x  = j;
        grid->indice->y  = i;
        grid->indice->sol = (grid->display[j-1][i]-1)*(grid->display[j-1][i]-1);
        return 1;
      }

    }
    if(tmp_0 == grid->size/2 && tmp_1<grid->size/2){
      for(int k = 0; k< grid->size; k++){
        if (grid->display[k][i] == 2){
          grid->indice->x  = k;
          grid->indice->y  = i;
          grid->indice->sol = 1;
          return 1;
        }
      }
    }
    if(tmp_1 == grid->size/2 && tmp_0<grid->size/2){
      for(int k = 0; k< grid->size; k++){
        if (grid->display[k][i] == 2){
          grid->indice->x  = k;
          grid->indice->y  = i;
          grid->indice->sol = 0;
          return 1;
        }
      }
    }
    tmp_0 = 0;
    tmp_1 = 0;
    n=0;
  }
  return 0;
}
