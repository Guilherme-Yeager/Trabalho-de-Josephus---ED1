#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct no{
    char nome[30];
    struct no *proxNo;
}tipoNo;

typedef struct listaGerenciada{
    tipoNo *fim;
    int quant;
}tipoLista;

void inicializaLista(tipoLista *listaEnc){
    listaEnc->fim = NULL;
    listaEnc->quant = 0;
}

int quantClientes(tipoLista *listaEnc){
    int quantCli = listaEnc->quant;
    return quantCli;
}
int insereListaVazia(tipoLista *listaEnc, char name[]){
    tipoNo *novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    if(!novoNo){
        setlocale(LC_ALL, "Portuguese");
        printf("\nErro ao alocar memória.\n");
        return 0;
    }
    strcpy(novoNo->nome, name);
    novoNo->proxNo = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant++;
    return 1;
}

int insereNoFim(tipoLista *listaEnc, char name[]){
    if(listaEnc->quant == 0){
        insereListaVazia(listaEnc, name);
        return 1;
    }
    tipoNo *novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    if(!novoNo){
        setlocale(LC_ALL, "Portuguese");
        printf("\nErro ao alocar memória.\n");
        return 0;
    }
    strcpy(novoNo->nome, name);
    novoNo->proxNo = listaEnc->fim->proxNo;
    listaEnc->fim->proxNo = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant++;
    return 1;
}

void exibirLista(tipoLista *listaEnc){
    if(listaEnc->quant == 0){
        printf("\nLista de clientes vazia.\n");
        return;
    }
    int posCont = 0;
    tipoNo *atual = listaEnc->fim->proxNo;
    printf("\nLista de clientes:\n");
    setlocale(LC_ALL, "C");
    printf("\n%d - %-20s", ++posCont, atual->nome);
    while(atual != listaEnc->fim){
        atual = atual->proxNo;
        printf("\n%d - %-20s", ++posCont, atual->nome);
    }
    printf("\n");
    return;
}

int sortear(tipoLista *listaEnc){
    int random;
    srand(time(NULL));
    random = (rand() % listaEnc->quant) + 1;
    return random;
}

tipoNo* acharPosicao(tipoLista *listaEnc, int aleatorio){
    tipoNo *novoNo = listaEnc->fim->proxNo;
    while(aleatorio != 0){
        novoNo = novoNo->proxNo;
        aleatorio--;
    }
    return novoNo;
}

void removerNoDaFrente(tipoLista *listaEnc){
    if(listaEnc->quant == 0){
        printf("\nLista de clientes vazia.\n");
        return;
    }
    if(listaEnc->quant == 1){
        free(listaEnc->fim);
        listaEnc->fim = NULL;
        listaEnc->quant--;
        return;
    }
    tipoNo *aux;
    aux = listaEnc->fim->proxNo;
    listaEnc->fim->proxNo = aux->proxNo;
    free(aux);
    listaEnc->quant--;
    return;
}

void removerNoDoFim(tipoLista *listaEnc){
    if(listaEnc->quant == 0){
        printf("\nLista de clientes vazia.\n");
        return;
    }
    tipoNo *penu, *ult = listaEnc->fim;
    penu = listaEnc->fim->proxNo;
    while(penu != listaEnc->fim){
        if(penu->proxNo == listaEnc->fim){
            break;
        }
        penu = penu->proxNo;
    }
    penu->proxNo = listaEnc->fim->proxNo;
    listaEnc->fim = penu;
    free(ult);
    listaEnc->quant--;
}

void removerTodosNos(tipoLista *listaEnc){
    while(listaEnc->fim != NULL){
        removerNoDaFrente(listaEnc);
    }
}

void removerCliente(tipoLista *listaEnc, tipoNo *noRemovido){
    if(noRemovido == listaEnc->fim->proxNo){
        removerNoDaFrente(listaEnc);
        return;
    }
    if(noRemovido == listaEnc->fim){
        removerNoDoFim(listaEnc);
        return;
    }
    tipoNo *anterior, *sucessor;
    anterior = listaEnc->fim->proxNo;
    while(anterior != noRemovido){
        if(anterior->proxNo == noRemovido){
            sucessor = anterior->proxNo;
            break;
        }
        anterior = anterior->proxNo;
    }
    anterior->proxNo = sucessor->proxNo;
    free(sucessor);
    listaEnc->quant--;
    return;
}

void verificaGanhador(tipoLista *listaEnc){
    if(listaEnc->quant == 1){
        setlocale(LC_ALL, "C");
        printf("\nO ganhador do sorteio foi: %s\n", listaEnc->fim->nome);
        return;
    }else{
        printf("\nContinuam no sorteio:\n");
        exibirLista(listaEnc);
    }
    return;
}

int exibirSorteado(tipoLista *listaEnc, tipoNo *eliminado){
    if(listaEnc->quant == 1){
        verificaGanhador(listaEnc);
        return 0;
    }
    setlocale(LC_ALL, "C");
    printf("\nO sorteado para ser o eliminado do sorteio foi: %s\n", eliminado->nome);
    return 1;
}

int vericarSorteio(tipoLista *listaEnc){
    if(listaEnc->quant == 0){
        return 0;
    }else
        return 1;
}

int main()
{
    tipoLista lista;
    inicializaLista(&lista);
    int op, aux, aux2;
    char nom[30];
    do{
        aux2 = 1;
        setlocale(LC_ALL, "Portuguese");
        printf("\n\tMenu\n");
        printf("\n1 - Cadastrar clientes");
        printf("\n2 - Exibir clientes cadastrados");
        printf("\n3 - Realizar sorteio");
        printf("\n4 - Sair do programa\n");
        printf("\nDigite uma opção: ");
        setlocale(LC_ALL, "C");
        scanf("%d", &op);
        switch(op){
            case 1:
                setlocale(LC_ALL, "Portuguese");
                printf("\n\tCadastro de clientes:\n");
                printf("\nDigite o nome do %dº cliente: ", quantClientes(&lista) + 1);
                getchar();
                fgets(nom, 30, stdin);
                nom[strcspn(nom, "\n")] = '\0';
                setlocale(LC_ALL, "C");
                if(insereNoFim(&lista, nom)){
                    setlocale(LC_ALL, "Portuguese");
                    printf("\nCliente cadastrado.\n");
                }else{
                    setlocale(LC_ALL, "Portuguese");
                    printf("\nCliente não cadastrado.\n");
                }
                break;
            case 2:
                exibirLista(&lista);
                break;
            case 3:
                if(!vericarSorteio(&lista)){
                    setlocale(LC_ALL, "Portuguese");
                    printf("\nLista de clientes vazia. Não há possibilidade de sorteio.\n");
                    break;
                }
                system("cls");
                do{
                    setlocale(LC_ALL, "Portuguese");
                    printf("\n\tMenu\n");
                    printf("\n1 - Sortear");
                    printf("\n2 - Exibir clientes que continuam no sorteio");
                    printf("\n3 - Realizar novo sorteio (Volta ao menu principal para cadastrar novos clientes)");
                    printf("\n4 - Sair do programa\n");
                    printf("\nDigite uma opção: ");
                    setlocale(LC_ALL, "C");
                    scanf("%d", &op);
                    switch(op){
                        case 1:
                            aux = sortear(&lista);
                            exibirLista(&lista);
                            if(!exibirSorteado(&lista, acharPosicao(&lista, aux))){
                                break;
                            }
                            removerCliente(&lista, acharPosicao(&lista, aux));
                            verificaGanhador(&lista);
                            break;
                        case 2:
                            exibirLista(&lista);
                            break;
                        case 3:
                            printf("\nLista de clientes atual limpa.\n");
                            removerTodosNos(&lista);
                            aux2 = 0;
                            break;
                        case 4:
                            printf("\nPrograma encerrado.\n");
                            exit(0);
                            break;
                            default:
                                setlocale(LC_ALL, "Portuguese");
                                printf("\nOpção inválida. Escolha outra opção.\n");
                        }
                        printf("\n\n\n");
                        system("pause");
                        system("cls");
                }while(op != 4 && op  != 3);
                break;
            case 4:
                setlocale(LC_ALL, "Portuguese");
                printf("\nPrograma encerrado.\n");
                exit(0);
                break;
                default:
                    setlocale(LC_ALL, "Portuguese");
                    printf("\nOpção inválida. Escolha outra opção.\n");
                    setlocale(LC_ALL, "C");
        }
        if(aux2){
            printf("\n\n\n");
            system("pause");
            system("cls");
        }
    }while(op != 4);
    return 0;
}
