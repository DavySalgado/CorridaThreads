#include "geral.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

//Ate 10 threads nomeadas de forma personalizada, o resto das Threads sao nomeadas com apenas "Thread [numero identificador]"
char** gerarArrayNomesThreads(int quantidadeThreads){
    char** nomes = malloc(quantidadeThreads * sizeof(char*));
    if (!nomes) return NULL;

    const char* nomesPersonalizados[10] = {
        "Davy Super Cavalo",
        "Flávio Dos Teclados",
        "Ayrton Senna",
        "Junior Pitomba",
        "Jacare Bangao",
        "Irani",
        "Eduardo Costa",
        "Erivelton",
        "Bumba meu boi",
        "Homem que cosme lasmina"
    };

    for(int i = 0; i < quantidadeThreads; i++){
        if(i < 10){
            nomes[i] = strdup(nomesPersonalizados[i]);
        }else{
            nomes[i] = malloc(32);
            snprintf(nomes[i], 32, "Thread %d", i);
        }
    }

    return nomes;
}

void desalocaNome(char** nomesThreads, int quantidadeThreads){
    for(int i = 0; i < quantidadeThreads; i++){
        free(nomesThreads[i]);
    }
    free(nomesThreads);
}
