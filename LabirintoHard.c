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
    //labirinto
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
        "E           *"
    };



    //parede = 0, caminho livre(inexplorado) = 1, entrada = -1, saida = 2
    int **caminhoBinario = allocM(12, 12);
    transformLabInBy(labirinto, caminhoBinario, 12,12);
    int **vector2d = allocM(1000, 2);// eu nao sei quantos passos eu precisaria
    int **caminhante = allocM(1, 2);

    int index = 1;//vai incrementar e adicionar uma nova coord



    //demarcar a entrada 
    for(int i =0; i < 12; i++){
        for(int j=0; j < 12; j++){
            if(caminhoBinario[i][j] == -1){
                vector2d[0][0] = i;
                vector2d[0][1] = j;

            }
        }
    }
    //eu vou considerar que eu sei onde tá a saida;-;
    printf("entrada está em: (%d, %d)\n", vector2d[0][0], vector2d[0][1]);
    //coordenada linha do caminhante
    caminhante[0][0] = vector2d[0][0];
    //coordenada coluna do caminhante
    caminhante[0][1] = vector2d[0][1];

    //walk(caminhante, caminhoBinario, vector2d, &index, 12, 12);
    recursiveImplement(caminhante, caminhoBinario, vector2d, 12, 12, &index);
    //printf("%d is caminhavel\n", isCaminhavel(caminhoBinario, 11, 0));
    printf("a saida está em (%d, %d)\n", vector2d[index - 1][0], vector2d[index - 1][1]);

    for(int i = 0; i < 12; i++){
        for(int j =0; j<12; j++){
            if(caminhoBinario[i][j] == 3) printf("[#]");
            else if(caminhoBinario[i][j] == 1) printf("[1]");
            else printf("[0]");
        }
        printf("\n");
    }
    //print tracejado
    char tracePath[12][12];
    //encher de espaço
    for(int i=0; i< 12; i++){
        for(int j =0; j < 12; j++){
            tracePath[i][j] = '1';
        }
    }
    //marcar o tracejado;-;
    for(int k =0; k<index; k++){
        int line = vector2d[k][0];
        int col  = vector2d[k][1];

        tracePath[line][col] = '#';
    }

    //printar
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
    
    //up
    if (linePos - 1 >= 0 && isCaminhavel(mapa, linePos - 1, colPos)){
        linePos -= 1;
    }
    //diagonal 1 quadrante(cartesiano)
    else if(linePos - 1 >= 0 && colPos + 1 < lenCol && isCaminhavel(mapa, linePos - 1, colPos + 1)){
        linePos -= 1;
        colPos += 1;
    }
    //direita
    else if(colPos + 1 < lenCol && isCaminhavel(mapa, linePos, colPos + 1)){
        colPos += 1;
    }
    //diagonal 4 quadrante (carteasiano)
    else if(linePos + 1 < lenLine && colPos + 1 < lenCol && isCaminhavel(mapa, linePos + 1, colPos + 1)){
        linePos += 1;
        colPos += 1;
    }
    //down
    else if (linePos + 1 < lenLine && isCaminhavel(mapa, linePos + 1, colPos)){
        linePos += 1;
    }
    //diagonal 3 quadratnte (cartesiano)
    else if(linePos + 1 < lenLine && colPos - 1 >= 0 && isCaminhavel(mapa, linePos + 1, colPos - 1)){
        linePos += 1;
        colPos -= 1;
    }
    //esquerda
    else if(colPos - 1 >= 0  && isCaminhavel(mapa, linePos, colPos - 1)){
        colPos -= 1;
    }
    //diagonal 4 quadrante (cartesiano)
    else if(linePos - 1 >= 0 && colPos - 1 >= 0 && isCaminhavel(mapa, linePos - 1, colPos - 1)){
        linePos -= 1;
        colPos -= 1;
    } else {
        //se nao achar caminho em uma das 8 direcoes, volta caminho
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
//verifica se o caminho é caminhavel...
int isCaminhavel(int **mapa, int line, int col){
    //printf("%d, %d\n", line, col);
    if(mapa[line][col] == 1 || mapa[line][col] == 2) return 1;
    return 0; 

}
//se o caminhante avançar, entao o caminho adiociona uma coordenada, no entanto
//se retornar, ele zera uma coordenada pra ser reescrita!
//resumo: verifica se as 8 direcoes sao caminho livres(1)
//se nao, verifica se nas 8 direcoes há uma saida
//se nao(KKKKKKK) retorna o caminho até achar um caminho livre ou saida KKKKKK
void walk(int **caminhante, int **mapa, int **caminho, int *indiceCaminho,
int linha, int coluna){
//caminho livre(explorado) = 3
    //essa porra de coordenada é (y,x)
    int line = caminhante[0][0];
    int col =  caminhante[0][1];
    //enquanto nao achar a saida ou voltar para a entrada
    do {
        //deslocamento
        line = caminhante[0][0];
        col = caminhante[0][1];
        //verificar se a posição é uma entrada
        if(mapa[line][col] != -1) mapa[line][col] = 3;



        //up
        if(line - 1 >= 0 && mapa[line - 1][col] == 1 ) {
            caminhante[0][0] = line - 1;
            caminhante[0][1] = col;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;
            //mapa[line - 1][col] = 3;
            continue;
        }
        //diagonal 1 quadrante (cartesiana)
        else if(line - 1 >= 0 && col + 1 < coluna && mapa[line -1][col+1] == 1)  {
            caminhante[0][0] = line - 1;
            caminhante[0][1] = col + 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;
            //mapa[line - 1][col + 1] = 3;
            continue;
        }
        //direita
        else if(col + 1 < coluna && mapa[line][col + 1] == 1 ){
            caminhante[0][0] = line;
            caminhante[0][1] = col + 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;
            //mapa[line][col + 1] = 3;
            continue;

        }
        //diagonal 4 quadrante (cartesiana)
        else if(line + 1 < linha && col + 1 < coluna && mapa[line + 1][col+ 1] == 1 ){
            caminhante[0][0] = line + 1;
            caminhante[0][1] = col + 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;
            //mapa[line + 1][col + 1] = 3;
            continue;

        }
        //down
        else if(line + 1 < linha && mapa[line + 1][col] == 1) {
            caminhante[0][0] = line + 1;
            caminhante[0][1] = col;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;
            //mapa[line + 1][col] = 3;
            continue;
        }
        //diagonal 3 quadrante (cartesiano)
        else if(line + 1 < linha && col - 1 >= 0 && mapa[line + 1][col - 1] == 1){
            caminhante[0][0] = line + 1;
            caminhante[0][1] = col - 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;
            //mapa[line + 1][col - 1] = 3;
            continue;
        }
        //esquerda
        else if(col - 1 >= 0 && mapa[line][col - 1] == 1 || mapa[line][col - 1] == 1) {
            caminhante[0][0] = line;
            caminhante[0][1] = col - 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;
            //mapa[line][col - 1] = 3;
            continue;

        }
        //diagonal 1 quadrante(cartesiano)
        else if(line - 1 >= 0 && col - 1>= 0 &&  mapa[line - 1][col - 1] == 1){
            caminhante[0][0] = line - 1;
            caminhante[0][1] = col - 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;
            //mapa[line - 1][col - 1] = 3;
            continue;

        } else {
            //procurar saida
              if(line - 1 >= 0 && mapa[line - 1][col] == 2 ) {
            caminhante[0][0] = line - 1;
            caminhante[0][1] = col;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;

            break;
        }
        //diagonal 1 quadrante (cartesiana)
        else if(line - 1 >= 0 && col + 1 < coluna && mapa[line -1][col+1] == 2)  {
            caminhante[0][0] = line - 1;
            caminhante[0][1] = col + 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;

            break;
        }
        //direita
        else if(col + 1 < coluna && mapa[line][col + 1] == 2 ){
            caminhante[0][0] = line;
            caminhante[0][1] = col + 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;

            break;

        }
        //diagonal 4 quadrante (cartesiana)
        else if(line + 1 < linha && col + 1 < coluna && mapa[line + 1][col+ 1] == 2 ){
            caminhante[0][0] = line + 1;
            caminhante[0][1] = col + 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;

            break;

        }
        //down
        else if(line + 1 < linha && mapa[line + 1][col] == 2) {
            caminhante[0][0] = line + 1;
            caminhante[0][1] = col;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;

            break;
        }
        //diagonal 3 quadrante (cartesiano)
        else if(line + 1 < linha && col - 1 >= 0 && mapa[line + 1][col - 1] == 2){
            caminhante[0][0] = line + 1;
            caminhante[0][1] = col - 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;

            break;
        }
        //esquerda
        else if(col - 1 >= 0 && mapa[line][col - 1] == 1 || mapa[line][col - 1] == 2) {
            caminhante[0][0] = line;
            caminhante[0][1] = col - 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;
            //mapa[line][col - 1] = 3;
            break;

        }
        //diagonal 1 quadrante(cartesiano)
        else if(line - 1 >= 0 && col - 1>= 0 &&  mapa[line - 1][col - 1] == 2){
            caminhante[0][0] = line - 1;
            caminhante[0][1] = col - 1;
            caminho[*indiceCaminho][0] = caminhante[0][0];
            caminho[*indiceCaminho][1] = caminhante[0][1];
            *indiceCaminho += 1;

            break;
        }
            //agora que a brincadeira começa ahahahahahah
            //o indice ta a frente da posicao do caminhante, -2 tu tem
            //a posicao anterior
            if(mapa[line][col] == -1) break;
            *indiceCaminho -= 1;
            caminhante[0][0] = caminho[*indiceCaminho][0];
            caminhante[0][1] = caminho[*indiceCaminho][1];
            continue;
        }

        //zona morta


    }
    // até o caminhante estar na saida ou entrada
    while(1);
    //*indiceCaminho -= 1;
    //printf("(%d, %d) == (%d, %d)\n", line, col, caminho[*indiceCaminho][0], caminho[*indiceCaminho][1] );
    //printf("(%d, %d)\n", line, col);

    /*for(int i =0; i < *indiceCaminho; i++){
        printf("(%d, %d), ", caminho[i][1], caminho[i][0] );
    }
    printf("\n"); */
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
