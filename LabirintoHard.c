#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void transformLabInBy(char lab[12][12], int **pathBy, int l, int c);
int verifyDirection(int **path, int *coords, int lenLine, int lenCol);
void walk(int **caminhante, int **mapa, int **caminho, int *indiceCaminho,int linha, int coluna);
int recursiveImplement(int **caminhante, int **mapa, int **caminho, int lenLine, int lenCol, int *index);
int isCaminhavel(int **mapa, int l, int c);

int **allocM(int l, int c);
void desalloc(int **mat, int len);

int main(){
    char labirinto[12][12] = {
        "************",
        "* S   *    *",
        "* **** **  *",
        "* *     *  *",
        "* ***** ** *",
        "*   *      *",
        "*** * **** *",
        "*   *    * *",
        "* *** ** * *",
        "*   *  *   *",
        "***** ****  ",
        "E          *"
    };

    int **caminhoBinario = allocM(12, 12);
    transformLabInBy(labirinto, caminhoBinario, 12,12);
    int **vector2d = allocM(1000, 2);
    int **caminhante = allocM(1, 2);

    int index = 1;

    for(int i =0; i < 12; i++){
        for(int j=0; j < 12; j++){
            if(caminhoBinario[i][j] == -1){
                vector2d[0][0] = i;
                vector2d[0][1] = j;
            }
        }
    }

    printf("entrada está em: (%d, %d)\n", vector2d[0][0], vector2d[0][1]);

    caminhante[0][0] = vector2d[0][0];
    caminhante[0][1] = vector2d[0][1];

    recursiveImplement(caminhante, caminhoBinario, vector2d, 12, 12, &index);

    printf("a saida está em (%d, %d)\n", vector2d[index - 1][0], vector2d[index - 1][1]);

    for(int i = 0; i < 12; i++){
        for(int j =0; j<12; j++){
            if(caminhoBinario[i][j] == 3) printf("[#]");
            else if(caminhoBinario[i][j] == 1) printf("[1]");
            else printf("[0]");
        }
        printf("\n");
    }

    char tracePath[12][12];

    for(int i=0; i< 12; i++){
        for(int j =0; j < 12; j++){
            tracePath[i][j] = '1';
        }
    }

    for(int k =0; k<index; k++){
        int line = vector2d[k][0];
        int col  = vector2d[k][1];
        tracePath[line][col] = '#';
    }

    for(int i=0; i< 12; i++){
        for(int j =0; j < 12; j++){
            printf("%c", tracePath[i][j]);
        }
        printf("\n");
    }
}

int recursiveImplement(int **caminhante, int **mapa, int **caminho, int lenLine, int lenCol, int *index)
{   
    static int step = 1;
    int linePos = caminhante[0][0], colPos = caminhante[0][1];
    
    if (linePos - 1 >= 0 && isCaminhavel(mapa, linePos - 1, colPos)){
        linePos -= 1;
    }
    else if(linePos - 1 >= 0 && colPos + 1 < lenCol && isCaminhavel(mapa, linePos - 1, colPos + 1)){
        linePos -= 1;
        colPos += 1;
    }
    else if(colPos + 1 < lenCol && isCaminhavel(mapa, linePos, colPos + 1)){
        colPos += 1;
    }
    else if(linePos + 1 < lenLine && colPos + 1 < lenCol && isCaminhavel(mapa, linePos + 1, colPos + 1)){
        linePos += 1;
        colPos += 1;
    }
    else if (linePos + 1 < lenLine && isCaminhavel(mapa, linePos + 1, colPos)){
        linePos += 1;
    }
    else if(linePos + 1 < lenLine && colPos - 1 >= 0 && isCaminhavel(mapa, linePos + 1, colPos - 1)){
        linePos += 1;
        colPos -= 1;
    }
    else if(colPos - 1 >= 0  && isCaminhavel(mapa, linePos, colPos - 1)){
        colPos -= 1;
    }
    else if(linePos - 1 >= 0 && colPos - 1 >= 0 && isCaminhavel(mapa, linePos - 1, colPos - 1)){
        linePos -= 1;
        colPos -= 1;
    } else {
        if(step <= 1) return 0;
        step--;
        linePos = caminho[step][0];
        colPos = caminho[step][1];
    }
    
    caminhante[0][0] = linePos;
    caminhante[0][1] = colPos; 
    if (mapa[linePos][colPos] == 1) {
        mapa[linePos][colPos] = 3;
        caminho[step][0] = linePos;
        caminho[step][1] = colPos;
        step++;
    }
    *index = step;
    
    if (mapa[linePos][colPos] == 2) return 1;
    return recursiveImplement(caminhante, mapa, caminho, lenLine, lenCol, index);
}

int isCaminhavel(int **mapa, int line, int col){
    if(mapa[line][col] == 1 || mapa[line][col] == 2) return 1;
    return 0; 
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
