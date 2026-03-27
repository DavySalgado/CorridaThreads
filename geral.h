#ifndef GERAL_H

//Ate 10 threads nomeadas de forma personalizada, o resto das Threads sao nomeadas com apenas "Thread [numero identificador]"
char** gerarArrayNomesThreads(int quantidadeThreads);

void desalocaNome(char** nomesThreads, int quantidadeThreads);

#endif