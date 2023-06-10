#include <stdio.h>
#include <stdlib.h>

typedef struct no No;

struct no{
    int valor;
    int pos;
    struct no *proximo;
    struct no *anterior;
};

typedef struct lista Lista;

struct lista{
    struct no *ini;
    struct no *fim;
    int tam;
};

void criar_lista(Lista *lista);

void inserir_no_inicio(Lista *lista, int num);

void inserir_no_fim(Lista *lista, int num);

void inserir_no_meio(Lista *lista, int num, int loc);

No* remover_no_inicio(Lista *lista);

No* remover_no_fim(Lista *lista);

No* remover_no_meio(Lista *lista, int loc);

void imprimir_lista(Lista *lista);

void imprimir_lista_ao_contrario(Lista *lista);

void limpar_tela();

int main(){
    Lista *lista=(Lista*)malloc(sizeof(Lista));
    int n=0,valor=0,posicao=0;
    No *removido=NULL;
    criar_lista(lista);


    do{
        printf("\n\t\t        LISTA DUPLAMENTE ENCADEADA\n");
        printf("\t\t\t         Escolha uma opcao das seguintes:\n");
        printf("\t\t\t         0 - Fechar programa\n");
        printf("\t\t\t         1 - Inserir no Inicio\n");
        printf("\t\t\t         2 - Inserir no Fim\n");
        printf("\t\t\t         3 - Inserir em Posicao\n");
        printf("\t\t\t         4 - Remover no Inicio\n");
        printf("\t\t\t         5 - Remover no Fim\n");
        printf("\t\t\t         6 - Remover em Posicao\n");
        printf("\t\t\t         7 - Imprimir Lista\n");
        printf("\t\t\t         8 - Imprimir Lista ao Contrario\n");
        printf("\t\t\t         9 - Limpar Tela\n");
        scanf("%d",&n);

        switch(n){
            case 0:
                printf("Saida\n");
                break;
            case 1:
                printf("Digite um valor para Inserir no Inicio: \n");
                scanf("%d",&valor);
                inserir_no_inicio(lista,valor);
                break;
            case 2:
                printf("Digite um valor para a Insercao no Final: \n");
                scanf("%d",&valor);
                inserir_no_fim(lista,valor);
                break;
            case 3:
                printf("Digite em qual posicao a insercao sera realizada (obs: a primeira posicao e a posicao 0)\n");
                printf("Lista: \n");
                imprimir_lista(lista);
                scanf("%d",&posicao);
                printf("Digite um valor para a insercao na posicao escolhida\n");
                scanf("%d",&valor);
                inserir_no_meio(lista,valor,posicao);
                break;
            case 4:
                removido=remover_no_inicio(lista);
                if(removido != NULL){
                    printf("Elemento removido: %d \n",removido->valor);
                    free(removido);
                }
                break;
            case 5:
                removido=remover_no_fim(lista);
                if(removido != NULL){
                    printf("Elemento removido: %d \n",removido->valor);
                    free(removido);
                }
                break;
            case 6:
                printf("Digite em qual posicao a remocao sera realizada (obs: a primeira posicao e a posicao 0)\n");
                printf("Lista: \n");
                imprimir_lista(lista);
                scanf("%d",&posicao);
                removido=remover_no_meio(lista,posicao);
                if(removido != NULL){
                    printf("Elemento removido: %d \n",removido->valor);
                    free(removido);
                }
                break;
            case 7:
                imprimir_lista(lista);
                break;
            case 8:
                imprimir_lista_ao_contrario(lista);
                break;
            case 9:
                limpar_tela();
                break;
            default:
                printf("Esta opcao nao existe!! Escolha outra opcao\n");
        }
    }while(n != 0);
    return 0;
}

void criar_lista(Lista *lista){
    lista->ini=NULL;
    lista->fim=NULL;
    lista->tam=0;
}

void inserir_no_inicio(Lista *lista, int num){
    No *novo_no=(No*)malloc(sizeof(No));
    if(novo_no){
        novo_no->valor=num;
        novo_no->pos=0;

        novo_no->proximo=NULL;
        novo_no->anterior=NULL;
        if(lista->ini == NULL){
            lista->ini=novo_no;
            lista->fim=novo_no;
        }else{
            lista->ini->anterior=novo_no;
            novo_no->proximo=lista->ini;
            lista->ini=novo_no;
        }
        lista->tam++;
    }
}

void inserir_no_fim(Lista *lista, int num){
    No *novo_no=(No*)malloc(sizeof(No));
    if(novo_no){
        novo_no->valor=num;
        novo_no->pos=0;

        novo_no->proximo=NULL;
        novo_no->anterior=NULL;
        if(lista->ini == NULL){
            lista->ini=novo_no;
            lista->fim=novo_no;
            lista->fim->proximo=NULL;
        }
        else{
            lista->fim->proximo=novo_no;
            novo_no->anterior=lista->fim;
            lista->fim=novo_no;
            novo_no->proximo=NULL;
        }
        lista->tam++;
    }
}

void inserir_no_meio(Lista *lista, int num, int loc){
    No *novo_no=(No*)malloc(sizeof(No));
    No *aux;
    int cont=0,passou=0;
    aux=lista->ini;
    if(lista->ini){

        
        do{
            aux->pos=cont;
            cont++;
            aux=aux->proximo;
        }while(aux != NULL);
        aux=lista->ini;
        if(novo_no){
            novo_no->valor=num;
            if(loc == 0 && aux->pos == loc){
                novo_no->proximo=NULL;
                novo_no->anterior=NULL;
                if(lista->ini == NULL){
                    lista->ini=novo_no;
                    lista->fim=novo_no;
                }else{
                    lista->ini->anterior=novo_no;
                    novo_no->proximo=lista->ini;
                    lista->ini=novo_no;
                }
                lista->fim->proximo=NULL;
                lista->tam++;
            }
            else{
                aux=lista->ini;
                do{
                    if(aux->pos+1 == loc && aux->proximo == NULL){
                        novo_no->proximo=NULL;
                        novo_no->anterior=NULL;
                        lista->fim->proximo=novo_no;
                        novo_no->anterior=lista->fim;
                        lista->fim=novo_no;
                        novo_no->proximo=NULL;
                        passou=1;                   
                    }
                    else if(aux->proximo->pos == loc && aux->proximo != NULL){
                        novo_no->proximo=aux->proximo;
                        novo_no->anterior=aux;
                        aux->proximo->anterior=novo_no;
                        aux->proximo=novo_no;
                        passou=1;
                    }
                    aux=aux->proximo;
                }while(passou == 0);
                lista->tam++;
            }
        }
    }else{
        if(loc == 0){
            novo_no->valor=num;
            inserir_no_inicio(lista,novo_no->valor);
        }else{
            printf("opcao invalida\n");
        }
    }
}

No* remover_no_inicio(Lista *lista){
    No *aux, *remover=NULL;
    if(lista->ini){
        if(lista->ini == lista->fim){
            remover=lista->ini;
            lista->ini=NULL;
            lista->fim=NULL;
            lista->tam--;
        }
        else{
            remover=lista->ini;
            lista->ini=remover->proximo;
            lista->ini->anterior=NULL;
            lista->tam--;
        }
    }
    return remover;
}

No* remover_no_fim(Lista *lista){
    No *aux, *remover=NULL;
    if(lista->ini){
        if(lista->ini == lista->fim){
            remover=lista->ini;
            lista->ini=NULL;
            lista->fim=NULL;
        }
        else{
            aux=lista->ini;
            do{
                if(lista->fim == aux->proximo){
                    remover=aux->proximo;
                    aux->proximo=remover->proximo;
                    lista->fim=aux;
                }
                aux=aux->proximo;
            }while(aux != NULL);
        }
        lista->tam--;
    }
    return remover;
}

No* remover_no_meio(Lista *lista, int loc){
    No *aux, *remover=NULL;
    int cont=0;
    remover=NULL;
    aux=lista->ini;
    do{
        aux->pos=cont;
        cont++;
        aux=aux->proximo;
    }while(aux != NULL);
    aux=lista->ini;
    if(lista->ini){
        if(loc == 0 && aux->pos == loc){
            if(lista->ini == lista->fim){
                remover=lista->ini;
                lista->ini=NULL;
                lista->fim=NULL;
            }
            else{
                remover=lista->ini;
                lista->ini=remover->proximo;
                lista->ini->anterior=NULL;
            }
        }
        else{
            aux=lista->ini;
            do{
                if(aux->proximo->pos == loc){
                    if(lista->fim == aux->proximo){
                        remover=aux->proximo;
                        aux->proximo=remover->proximo;
                        lista->fim=aux;
                    }
                    else{
                        remover=aux->proximo;
                        aux->proximo=remover->proximo;
                        aux->proximo->anterior=aux;
                    }
                }
                aux=aux->proximo;
            }while(remover == NULL);
        }
        lista->tam--;
    }
    return remover;
}

void imprimir_lista(Lista *lista){
    No *no = lista->ini;
    printf("\n\tLista tam %d: ", lista->tam);
    if(no){
        do{
            printf("| %d | ",no->valor);
            no = no->proximo;
        }while(no != NULL);
        printf("\nInicio: %d\n", lista->ini->valor);
        printf("Fim: %d\n",lista->fim->valor);
    }
    printf("\n\n");
}

void imprimir_lista_ao_contrario(Lista *lista){
    No *no = lista->fim;
    printf("\n\tLista tam %d: ", lista->tam);
    if(no){
        do{
            printf("| %d | ",no->valor);
            no = no->anterior;
        }while(no != NULL);
        printf("\nInicio: %d\n", lista->ini->valor);
        printf("Fim: %d\n",lista->fim->valor);
    }
    printf("\n\n");
}

void limpar_tela(){
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#else
#endif
}