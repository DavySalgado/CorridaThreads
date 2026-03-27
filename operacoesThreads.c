#include "operacoesThreads.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

pthread_barrier_t barreira_inicio;
pthread_mutex_t mutex_ganhador;
int ganhador = 0;
int contador = 0;


void* corridaPadraoMutexVerificacaoGanhador(void* arg) {
    char* nomeThread = (char*)arg;

    ganhador = 0;
    pthread_barrier_wait(&barreira_inicio);

    for (int i = 1; i <= 100; i++) {
        pthread_mutex_lock(&mutex_ganhador);

        if (ganhador) {
            pthread_mutex_unlock(&mutex_ganhador);
            break;
        }
        
        printf("Thread %s: %d\n", nomeThread, i);

        if (i == 100) {
            ganhador = 1;
            printf("\nThread %s venceu!\n", nomeThread);
            pthread_mutex_unlock(&mutex_ganhador);
            break;
        }

        pthread_mutex_unlock(&mutex_ganhador);
    }

    return NULL;
}

void* corridaPadrao(void* arg) {
    char* nomeThread = (char*)arg;

    ganhador = 0;
    pthread_barrier_wait(&barreira_inicio);

    for (int i = 1; i <= 100; i++) {
        if (ganhador) {
            break;
        }
        
        printf("Thread %s: %d\n", nomeThread, i);

        if (i == 100) {
            ganhador = 1;
            printf("\nThread %s venceu!\n", nomeThread);
            break;
        }

    }

    return NULL;
}

//várzea pura
void* corridaComContadorCompartilhadoSemMutex(void* arg){
    char* nomeThread = (char*)arg;
    
    ganhador = 0;
    contador = 0;
    pthread_barrier_wait(&barreira_inicio);

    while(!ganhador){
        contador++;
        printf("Thread %s: %d\n", nomeThread, contador);

        if(contador == 100){
            ganhador = 1;
            printf("\nThread %s venceu!\n", nomeThread);
            break;
        }

        if(contador > 200 && !ganhador){
            printf("\nNão houve ganhador");
            break;
        }
    }

    return NULL;
}

void* corridaComContadorCompartilhadoComMutexGanhador(void* arg){
    char* nomeThread = (char*)arg;
    
    ganhador = 0;
    contador = 0;
    pthread_barrier_wait(&barreira_inicio);

    while (1) {
        contador++;

        pthread_mutex_lock(&mutex_ganhador);

        if (ganhador) {
            pthread_mutex_unlock(&mutex_ganhador);
            break;
        }

        printf("Thread %s: %d\n", nomeThread, contador);

        if (contador >= 100) {
            ganhador = 1;
            printf("\nThread %s venceu!\n", nomeThread);
            pthread_mutex_unlock(&mutex_ganhador);
            break;
        }

        pthread_mutex_unlock(&mutex_ganhador);
    }

    return NULL;
}

void* corridaComContadorCompartilhadoComMutexTotal(void* arg){
    char* nomeThread = (char*)arg;
    
    ganhador = 0;
    contador = 0;
    pthread_barrier_wait(&barreira_inicio);

    while (1) {
        pthread_mutex_lock(&mutex_ganhador);
        contador++; 

        if (ganhador) {
            pthread_mutex_unlock(&mutex_ganhador);
            break;
        }

        printf("Thread %s: %d\n", nomeThread, contador);

        if (contador >= 100) {
            ganhador = 1;
            printf("\nThread %s venceu!\n", nomeThread);
            pthread_mutex_unlock(&mutex_ganhador);
            break;
        }

        pthread_mutex_unlock(&mutex_ganhador);
    }

    return NULL;
}

void chamadaCorridaPadrao(int quantidadeThreads, char** nomesThreads, int funcao) {
    pthread_t threads[quantidadeThreads];
    pthread_barrier_init(&barreira_inicio, NULL, quantidadeThreads + 1);

    void* (*funcaoEscolhida)(void*) = NULL;

    switch (funcao) {
        case 1:
            funcaoEscolhida = corridaPadrao;
            break;
        case 2:
            funcaoEscolhida = corridaPadraoMutexVerificacaoGanhador;
            break;
        case 3:
            funcaoEscolhida = corridaComContadorCompartilhadoSemMutex;
            break;
        case 4:
            funcaoEscolhida = corridaComContadorCompartilhadoComMutexGanhador;
            break;
        case 5:
            funcaoEscolhida = corridaComContadorCompartilhadoComMutexTotal;
            break;
        default:
            printf("Função inválida!\n");
            pthread_barrier_destroy(&barreira_inicio);
            return;
    }

    for (int i = 0; i < quantidadeThreads; i++) {
        pthread_create(&threads[i], NULL, funcaoEscolhida, nomesThreads[i]);
    }

    pthread_barrier_wait(&barreira_inicio);

    for (int i = 0; i < quantidadeThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barreira_inicio);
}

void caca(){

}