#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void transformLabInBy(char lab[12][12], int **pathBy, int l, int c);
int **allocM(int l, int c);
void desalloc(int **mat, int len);
void countSteps(int **path, int l, int c, int *steps);
void searchPath(int **path, int **coords, int l, int c);
int main(){
    char labirinto[12][12] = {
        "************",
        "*     *    *",
        "* *** * ** *",
        "* *     *  *",
        "* * *** ** *",
        "*   *      *",
        "*** * **** *",
        "*   *    * *",
        "* *** ** * *",
        "*   *  *   *",
        "* *** **** S",
        "E          *"
    };
    //sera passos dado por vectors2d
    int steps =0;


    //parede = 0, caminho livre = 1, entrada = -1, saida = 2
    int **caminhoBinario = allocM(12, 12);
    transformLabInBy(labirinto, caminhoBinario, 12,12);
    countSteps(caminhoBinario, 12,12, &steps);
    int **vector2d = allocM(steps, 2);

    //demarcar a entrada
    for(int i =0; i < 12; i++){
        for(int j=0; j < 12; j++){
            if(caminhoBinario[i][j] == -1){
                vector2d[0][0] = i;
                vector2d[0][1] = j;

            }
        }
    }
    printf("entrada está em: (%d, %d)\n", vector2d[0][0], vector2d[0][1]);

    searchPath(caminhoBinario, vector2d, 12,12);
    for(int i=0; i < 12; i++){
        for(int j=0; j < 12; j++){
            printf("[%d]", caminhoBinario[i][j]);
        }
        printf("\n");
    }
}
void searchPath(int **path, int **coords, int l, int c){
    int x =0, y = 0, step = 0;
    //origem
    x = coords[0][0];
    y = coords[0][1];
    do {
        //verificar 8 direçoes
        //verificar direita
        if(x + 1 < 12 && path[x + 1][y] == 1){
            x++;
            step++;
            coords[step][0] = x;
            coords[step][1] = y;
        //verificar diagonal direita
        } else if(x + 1 < 12 && y + 1 < 12 && path[x + 1][ y+1] == 1){
            x++;
            y++;
            step++;
            coords[step][0] = x;
            coords[step][1] = y;
        //verificar baixo(baixo é incrementando
        } else if(y + 1 < 12 && path[x][y + 1] == 1){

        }


    } while(path[x][y] != 2);
}
void backOne(int **path, int **coords, int *x, int *y){

}
void countSteps(int **path, int l, int c, int *steps){
    for(int i =0; i < l; i++){
        for(int j = 0; j< c; j++){
            if(path[i][j] == 1){
                *steps += 1;
            }
        }
    }

}
void transformLabInBy(char lab[12][12], int **pathBy, int l, int c){
    if (pathBy != NULL){
        for(int i =0; i < l; i++){
            for(int j = 0; j< c; j++){
                switch(lab[i][j]){
                    case '*':
                        pathBy[i][j] = 0;
                    break;
                    case ' ':
                        pathBy[i][j] = 1;
                    break;
                    case 'E':
                        pathBy[i][j] = -1;
                    break;
                    case 'S':
                        pathBy[i][j] = 2;
                    break;
                    default:
                    //considere que já foi visto
                        pathBy[i][j] = 404;

                }
            }
        }
    }

}

int **allocM(int line, int col){
    int **mat;
    mat = (int **) malloc(line * sizeof(int*));

    if (mat == NULL) return NULL;

    for (int i = 0; i < line; i++){
        mat[i] = (int *) malloc(col * sizeof(int));
        if (mat[i] == NULL) {
            desalloc(mat, i);
            return NULL;
        }
    }
    return mat;
}
void desalloc(int **mat, int len){
    for(int i=0; i <= len; i++){
        free(mat[i]);
    }
    free(mat);

}
