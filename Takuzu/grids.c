#include <stdio.h>
#include <stdlib.h>

t_grid grid4() {
    t_grid *grid4x4 = malloc(sizeof(t_grid));
    grid4x4->solve = malloc(4 * sizeof(int *));
    grid4x4->mask = malloc(4 * sizeof(int *));
    grid4x4->indice = malloc(sizeof(t_indice));


    for (int i = 0; i < 4; i++) {
        grid4x4->solve[i] = calloc(4, sizeof(int));
        grid4x4->mask[i] = calloc(4, sizeof(int));
    }
    grid4x4->solve[0][0] = 1;
    grid4x4->solve[0][3] = 1;
    grid4x4->solve[1][0] = 1;
    grid4x4->solve[1][2] = 1;
    grid4x4->solve[2][1] = 1;
    grid4x4->solve[2][2] = 1;
    grid4x4->solve[3][1] = 1;
    grid4x4->solve[3][3] = 1;
    grid4x4->mask[0][0] = 1;
    grid4x4->mask[1][2] = 1;
    grid4x4->mask[2][1] = 1;
    grid4x4->mask[3][1] = 1;
    grid4x4->size = 4;
    return *grid4x4;
}

t_grid grid8(){
    t_grid *grid8x8 = malloc(sizeof(t_grid));
    grid8x8->solve = malloc(8 * sizeof(int *));
    grid8x8->mask = malloc(8 * sizeof(int *));
    grid8x8->size = 8;
    grid8x8->indice = malloc(sizeof(t_indice));

    for (int i = 0; i < 8; i++) {
        grid8x8->solve[i] = calloc(8, sizeof(int));
        grid8x8->mask[i] = calloc(8, sizeof(int));
    }
    char sol[] = "1011010010101001010110100101011010100101010010110011011011001001";
    for(int i = 0; i< 8; i++){
        for(int j = 0; j<8; j++){
        grid8x8->solve[i][j] = (int)(sol[(8*i)+j]-'0');
        }
    }
    char mask[] = "1011010100100000100000011010011010001001000010000111110001010010";
    for(int i = 0; i< 8; i++){
        for(int j = 0; j<8; j++){
        grid8x8->mask[i][j] = mask[(8*i)+j]-'0';
        }
    }
    return *grid8x8;
}
t_grid grid8_2(){
    t_grid *grid8x8 = malloc(sizeof(t_grid));
    grid8x8->solve = malloc(8 * sizeof(int *));
    grid8x8->mask = malloc(8 * sizeof(int *));
    grid8x8->size = 8;
    grid8x8->indice = malloc(sizeof(t_indice));

    for (int i = 0; i < 8; i++) {
        grid8x8->solve[i] = calloc(8, sizeof(int));
        grid8x8->mask[i] = calloc(8, sizeof(int));
    }
    char sol[] = "0010101110010101010110100110011010100101100110010110101011010100";
    for(int i = 0; i< 8; i++){
        for(int j = 0; j<8; j++){
        grid8x8->solve[i][j] = (int)(sol[(8*i)+j]-'0');
        }
    }
    char mask[] = "1111110010101000111000101000101010000100011111100000000100100011";
    for(int i = 0; i< 8; i++){
        for(int j = 0; j<8; j++){
        grid8x8->mask[i][j] = mask[(8*i)+j]-'0';
        }
    }
    return *grid8x8;
}
t_grid grid8_3(){
    t_grid *grid8x8 = malloc(sizeof(t_grid));
    grid8x8->solve = malloc(8 * sizeof(int *));
    grid8x8->mask = malloc(8 * sizeof(int *));
    grid8x8->size = 8;
    grid8x8->indice = malloc(sizeof(t_indice));

    for (int i = 0; i < 8; i++) {
        grid8x8->solve[i] = calloc(8, sizeof(int));
        grid8x8->mask[i] = calloc(8, sizeof(int));
    }
    char sol[] = "1001010100110011110011001101010000101011001101011100101001101010";
    for(int i = 0; i< 8; i++){
        for(int j = 0; j<8; j++){
        grid8x8->solve[i][j] = (int)(sol[(8*i)+j]-'0');
        }
    }
    char mask[] = "0110100100001101001000000000000011001100000000111011001001100100";
    for(int i = 0; i< 8; i++){
        for(int j = 0; j<8; j++){
        grid8x8->mask[i][j] = mask[(8*i)+j]-'0';
        }
    }
    return *grid8x8;
}
t_grid grid8_4(){
    t_grid *grid8x8 = malloc(sizeof(t_grid));
    grid8x8->solve = malloc(8 * sizeof(int *));
    grid8x8->mask = malloc(8 * sizeof(int *));
    grid8x8->size = 8;
    grid8x8->indice = malloc(sizeof(t_indice));

    for (int i = 0; i < 8; i++) {
        grid8x8->solve[i] = calloc(8, sizeof(int));
        grid8x8->mask[i] = calloc(8, sizeof(int));
    }
    char sol[] = "1101010010101001010100110110011010101100100110010101011000101011";
    for(int i = 0; i< 8; i++){
        for(int j = 0; j<8; j++){
        grid8x8->solve[i][j] = (int)(sol[(8*i)+j]-'0');
        }
    }
    char mask[] = "0111101001000011110001001001110011001011011000100000000000001000";
    for(int i = 0; i< 8; i++){
        for(int j = 0; j<8; j++){
        grid8x8->mask[i][j] = mask[(8*i)+j]-'0';
        }
    }
    return *grid8x8;
}
