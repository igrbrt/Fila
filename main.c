/* 
 * File:   main.c
 * Author: igor
 *
 * Created on 10 de Novembro de 2010, 15:10
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */

typedef struct Pessoa{
    char nome[30];
    char endereco[50];
    char telefone[10];

}Pessoa;

typedef struct No{
    Pessoa *conteudo;
    struct No *prox;
}No;

typedef struct Fila{
     No *inicio;
     No *fim;
}Fila;

// prototipo das funcoes
void Enqueue(Fila**,Pessoa**);
Pessoa* Dequeue(Fila**);
void Print(Fila**);
int Check(Fila**);
void Fill(Pessoa**);


int main() {
    Fila *fila;
    fila = NULL;
    Pessoa *pessoa = NULL;
    int op;
    do{
        puts("\t\t == Fila ==\n\n");
        printf("(1) - Inserir\n(2) - Remover\n(3) - Imprimir\n(4) - Sair\n-->");
        scanf("%d",&op);
        __fpurge(stdin);
        switch(op){
            case 1:Fill(&pessoa);       //cadastra pessoa
                   Enqueue(&fila,&pessoa); //insere na fila
                   break;
            case 2:if(Check(&fila) == 0)  //verifica se a fila esta vazia
                        break;
                   pessoa = Dequeue(&fila);  // pessoa recebe elemento removido
                   printf("\nRemovido: %s \n",pessoa->nome);
                   break;
            case 3:if(Check(&fila) == 0)    //verifica se a fila esta vazia
                        break;
                   Print(&fila);printf("\n");  //imprime toda fila
                   break;
            case 4:puts("\nFechando...");
                   break;
            default:puts("\nCalma, Usuario amigo!");
        }
        getchar();getchar();
        system("clear");
    }while(op!=4);
    return (0);
}

void Enqueue(Fila **fila,Pessoa **pessoa){
    No* Novo;
    if(*fila == NULL){   // verifica se a fila tah vazia e aloca ela
        *fila = (Fila**)malloc(sizeof(Fila*));
        (*fila)->inicio = (*fila)->fim = NULL;
    }
    if( Novo = (No*)malloc(sizeof(No)) ){
        Novo->conteudo=(*pessoa);
        Novo->prox = NULL;
        if( (*fila)->inicio == NULL){ // insere na fila vazia
            (*fila)->inicio = (*fila)->fim = Novo;
            return;
        }
        ((*fila)->fim)->prox = Novo;  //insere do segundo elemento pra frente
        (*fila)->fim = Novo;
    }
    else
        puts("Erro ao alocar memoria");
}

Pessoa* Dequeue(Fila **fila){
    Pessoa *retorno;
    No* aux = (*fila)->inicio;
    retorno=aux->conteudo;
    (*fila)->inicio = aux->prox; // atualiza o inicio
    free(aux);      // libera memoria do primeiro elemento
    return retorno;
}

void Print(Fila **fila){    //imprime toda fila
    No* aux;
    aux = (*fila)->inicio;
    while(aux != NULL){
        printf("\n%s",aux->conteudo->nome);
        printf("%s",aux->conteudo->telefone);
        printf("%s",aux->conteudo->endereco);
        printf("---------------------------");
        aux = aux->prox;
    }
}

int Check(Fila **fila){  // verifica se a fila esta vazia
    if((*fila) == NULL || (*fila)->inicio == NULL ){
        puts("\nFila Vazia !");
        return 0;
    }
    return 1;
}

void Fill(Pessoa **Nova){ // cadastra nova pessoa
    if(*Nova == NULL)
        *Nova = (Pessoa*)malloc(sizeof(Pessoa));
    printf("\nNome: ");
    fgets((*Nova)->nome,30,stdin); __fpurge(stdin);
    printf("\nTelefone [ex: 6384515637]: ");
    fgets((*Nova)->telefone,10,stdin); __fpurge(stdin);
    printf("\nEndereco: ");
    fgets((*Nova)->endereco,50,stdin); __fpurge(stdin);
    puts("\nCadastrado!");
}