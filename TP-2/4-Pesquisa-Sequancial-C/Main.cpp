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
void imprimir(int i);
void ler(char line[], char *infos[], int i);
Jogador clonar(int i);
int PesquisaBinaria(char *pesquisa, int tam);

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

//função q ira ordenar o vetor por ordem alfabetica, usando inserção
void OrdenarVetorPorNome(int tam){
    for(int i = 1; i < tam; i++){
        char tmp[100];
        strcpy(tmp, jogadores2[i].nome);
        int j = i-1;
        while((j >= 0) && strcmp(jogadores2[j].nome, tmp) > 0){
            comparacoes++;
            strcpy(jogadores2[j+1].nome, jogadores2[j].nome);
            j--;
        }
        strcpy(jogadores2[j+1].nome, tmp);
    }
}

//funçao para fazer uma pesquisa binaria dentro do algoritmo
int PesquisaBinaria(char *pesquisa, int tam){
    int inf = 0;
    int sup = tam-1;
    int meio;
    while(inf <= sup){
        comparacoes++;
        meio = (inf + sup)/2;
        if (strcmp(jogadores2[meio].nome, pesquisa) == 0){
            comparacoes++;
            return 1;
        }
        if (strcmp(jogadores2[meio].nome, pesquisa) > 0){
            comparacoes++;
            sup = meio-1;
        }
        else
            inf = meio+1;
    }
    return 0;
}

int main(){
    clock_t t;
    t = clock();
    lerArquivo();
    int cont = 0;
    char pesquisa[MAX];
    scanf(" %[^\n]", pesquisa);
    do{
        jogadores2[cont] = clonar(atoi(pesquisa));
        scanf(" %[^\n]", pesquisa);
        cont++;
    }while(strcmp(pesquisa, "FIM") != 0);

    OrdenarVetorPorNome(cont);

    scanf(" %[^\n]", pesquisa);
    do{
        printf("%s\n",(PesquisaBinaria(pesquisa, cont) == 1) ? "SIM" : "NAO");
        scanf(" %[^\n]", pesquisa);
        cont++;
    }while(strcmp(pesquisa, "FIM") != 0);
    t = clock() - t;
    FILE *arq = fopen("matricula_sequencial.txt", "w");
    fprintf(arq, "%s", "561170\t");
    fprintf(arq, "%.8lf", ((double)t)/((CLOCKS_PER_SEC)));
    fprintf(arq, "%s", "\t");
    fprintf(arq, "%d", comparacoes);
    fclose(arq);
    return 0;
}

//"Metodos get and set, clonar, imprimir e ler"
void imprimir(int i){
    printf("[%d ## %s ## %d ## %d ## %d ## %s ## %s ## %s]\n", jogadores[i].id, jogadores[i].nome,
    jogadores[i].alt, jogadores[i].peso, 
    jogadores[i].ano, jogadores[i].universidade, jogadores[i].cidade, jogadores[i].estado); 
}

Jogador clonar(int i){
    Jogador j;
    j.id = jogadores[i].id;
    j.alt = jogadores[i].alt;
    j.peso = jogadores[i].peso;
    j.ano = jogadores[i].ano;
    strcpy(j.nome, jogadores[i].nome);
    strcpy(j.universidade, jogadores[i].universidade);
    strcpy(j.cidade, jogadores[i].cidade);
    strcpy(j.estado, jogadores[i].estado);
    return j;
}

void ler(char line[], char *infos[], int i){
    removerQuebra(line);
    separarNoVetor(line, infos, ",", 8);
    preecherInfos(infos, i);
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
