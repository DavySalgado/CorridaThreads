#include <pthread.h>
#include <stdio.h>
#include "geral.h"
#include "operacoesThreads.h"

int main() {
    int quantidadeThreads;
    int funcao;

    printf("Digite a quantidade de threads: ");
    scanf("%d", &quantidadeThreads);

    printf("Escolha a função para as threads:\n");
    printf("1 - corridaPadrao\n");
    printf("2 - corridaPadraoMutexVerificacaoGanhador\n");
    printf("3 - corridaComContadorCompartilhadoSemMutex\n");
    printf("4 - corridaComContadorCompartilhadoComMutexGanhador\n");
    printf("5 - corridaComContadorCompartilhadoComMutexTotal\n");
    printf("Digite o número da função: ");
    scanf("%d", &funcao);

    printf("\nVocê escolheu a função %d para todas as threads.\n\n", funcao);
    char** nomesThreads = gerarArrayNomesThreads(quantidadeThreads);
    chamadaCorridaPadrao(quantidadeThreads, nomesThreads, funcao);

    desalocaNome(nomesThreads, quantidadeThreads);
    return 0;
}