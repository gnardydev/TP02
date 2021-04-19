#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAX 10000


typedef struct jogador
{
    int id;
    int alt;
    int peso;

    char nome[MAX];
    char universidade[MAX];
    int ano;
    char cidade[MAX];
    char estado[MAX];
}Jogador;

Jogador jogadores[5000];
Jogador jogadores2[5000];
int numJogadores = 0;
int comparacoes = 0;
int movimentacoes = 0;

int getId(int i);
int getAltura(int i);
int getPeso(int i);
int getAno(int i);
char* getNome(int i);
char* getUniversidade(int i);
char* getCidade(int i);
char* getEstado(int i);
void ler(char line[], char *infos[], int i);
Jogador clonar(int i, Jogador vet[]);
int PesquisaBinaria(char *pesquisa, int tam);
void swap(int i, int min);
void imprimir(int i, Jogador vet[]);
void OrdenarVetorShellSortPeso(int tam);
void insercaoPorCor(int cor, int h, int tam);

//funcao q separa cada informao da linha em uma parte do vetor infos
void separarNoVetor(char *str, char *infos[], char *separador, int tam){
    char *prt;
    prt = strsep(&str, separador);
    for(int i = 0; i < tam; i++){
        infos[i] = prt;
        prt = strsep(&str, separador);
    }
}

//Funcao para retirar a quebra de linha
void removerQuebra(char line[]){
    int tamanho = strlen(line);
    if(line[tamanho-2] == '\r' && line[tamanho-1] == '\n'){
        line[tamanho-2] = '\0';
    }else if (line[tamanho-1] == '\r' || line[tamanho-1] == '\n'){
        line[tamanho-1] = '\0';
    }
}

//pegas as informacoes colocadas e preencher cada jogador
void preecherInfos(char *infos[], int i){
    jogadores[i].id = atoi(infos[0]);
    strcpy(jogadores[i].nome, (const char*)(infos[1]));
    jogadores[i].alt = atoi(infos[2]);
    jogadores[i].peso = atoi(infos[3]);

    if(*infos[4]=='\0'){
        infos[4]="nao informado";
    }
    
    jogadores[i].ano = atoi(infos[5]);

    if(*infos[6]=='\0'){
        infos[6]="nao informado";
    }
    if(*infos[7]=='\0'){
        infos[7]="nao informado";
    }

    strcpy(jogadores[i].universidade, (const char*)(infos[4]));
    strcpy(jogadores[i].cidade, (const char*)(infos[6]));
    strcpy(jogadores[i].estado, (const char*)(infos[7]));
}

//le o arquivo onde o fgets pega cada linha do arquivo
void lerArquivo(){
    FILE *csv = fopen("/tmp/players.csv", "r");
   
    char * infos_receb[8];
    char line[MAX];
    int i = 0;
    fgets(line, 1024, csv);
    fgets(line, 1024, csv);

    while(!feof(csv)){
        ler(line, infos_receb, i);
        i++;
        fgets(line, 1024, csv);
    }
    fclose(csv);
}

int main(){
    clock_t t;
    t = clock();
    lerArquivo();
    int cont = 0;
    char pesquisa[MAX];
    scanf(" %[^\n]", pesquisa);
    do{
        jogadores2[cont] = clonar(atoi(pesquisa), jogadores);
        scanf(" %[^\n]", pesquisa);
        cont++;
    }while(strcmp(pesquisa, "FIM") != 0);

    OrdenarVetorShellSortPeso(cont);

    for(int i = 0; i < cont; i++){
        imprimir(i, jogadores2);
    }

    t = clock() - t;
    FILE *arq = fopen("matricula_shellsort.txt", "w");
    fprintf(arq, "%s", "561170\t");
    fprintf(arq, "%d", comparacoes);
    fprintf(arq, "%s", "\t");
    fprintf(arq, "%d", movimentacoes);
    fprintf(arq, "%s", "\t");
    fprintf(arq, "%.8lf", ((double)t)/((CLOCKS_PER_SEC)));
    
    fclose(arq);
    return 0;
}

//"Metodos get and set, clonar, imprimir e ler"
void ler(char line[], char *infos[], int i){
    removerQuebra(line);
    separarNoVetor(line, infos, ",", 8);
    preecherInfos(infos, i);
}

void imprimir(int i, Jogador vet[]){
    printf("[%d ## %s ## %d ## %d ## %d ## %s ## %s ## %s]\n", vet[i].id, vet[i].nome,
    vet[i].alt, vet[i].peso, 
    vet[i].ano, vet[i].universidade, vet[i].cidade, vet[i].estado); 
}

Jogador clonar(int i, Jogador vet[]){
    Jogador j;
    j.id = vet[i].id;
    j.alt = vet[i].alt;
    j.peso = vet[i].peso;
    j.ano = vet[i].ano;
    strcpy(j.nome, vet[i].nome);
    strcpy(j.universidade, vet[i].universidade);
    strcpy(j.cidade, vet[i].cidade);
    strcpy(j.estado, vet[i].estado);
    return j;
}

//chamada do shell sort
void OrdenarVetorShellSortPeso(int tam){
    int h = 1;
    do{h=(h*3)+1; comparacoes++;}while(h < tam);
    do{
        h /=3;
        for(int cor = 0; cor < h; cor++){
            insercaoPorCor(cor, h, tam);
        }
        comparacoes++;
    }while(h != 1);
}
//insercao chamada pela divisao das cores
void insercaoPorCor(int cor, int h, int tam){
    for (int i = (h + cor); i < tam; i+=h) {
        Jogador tmp = jogadores2[i];
        int j = i - h;
        while ((j >= 0) && (jogadores2[j].peso > tmp.peso)) {
            comparacoes +=2;
            movimentacoes++;
            jogadores2[j + h] = jogadores2[j];
            j -= h;
        }
        while ((j >= 0) && ((jogadores2[j].peso == tmp.peso) && (strcmp(jogadores2[j].nome, tmp.nome) > 0))) {
            comparacoes +=2;
            movimentacoes++;
            jogadores2[j + h] = jogadores2[j];
            j -= h;
        }
        jogadores2[j + h] = tmp;
        movimentacoes++;
    }
}

//função q ira ordenar o vetor por ordem alfabetica, usando inserção
void OrdenarVetorSelecaoRecursivo(int i, int tam){
    if(i == tam)
        return;
    int min = i;
    for(int j = (i+1); j < tam; j++){
        if(strcmp(jogadores2[j].nome, jogadores2[min].nome) < 0){
            min = j;
            comparacoes++;
        }
    }
    swap(i, min);
    OrdenarVetorSelecaoRecursivo(i+1, tam);
}

void swap(int i, int min){
    Jogador aux = clonar(i, jogadores2);
    jogadores2[i] = jogadores2[min];
    jogadores2[min] = aux;
    movimentacoes += 3;
}

void setId(int i, int newId){
    jogadores[i].id = newId;
}

void setAlt(int i, int newAlt){
    jogadores[i].alt = newAlt;
}

void setPeso(int i, int newPeso){
    jogadores[i].peso = newPeso;
}

void setNome(int i, char newNome[]){
    strcpy(jogadores[i].nome, newNome);
}

void setAno(int i, int newAno){
    jogadores[i].ano = newAno;
}

void setUniversidade(int i, char newNome[]){
    strcpy(jogadores[i].universidade, newNome);
}

void setCidade(int i, char newNome[]){
    strcpy(jogadores[i].cidade, newNome);
}

void setEstado(int i, char newNome[]){
    strcpy(jogadores[i].estado, newNome);
}

int getId(int i){
    return jogadores[i].id;
}

int getAltura(int i){
    return jogadores[i].alt;
}

int getPeso(int i){
    return jogadores[i].peso;
}

int getAno(int i){
    return jogadores[i].ano;
}

char* getNome(int i){
    return jogadores[i].nome;
}

char* getUniversidade(int i){
    return jogadores[i].universidade;
}

char* getCidade(int i){
    return jogadores[i].cidade;
}

char* getEstado(int i){
    return jogadores[i].estado;
}

//fim dos metodos
