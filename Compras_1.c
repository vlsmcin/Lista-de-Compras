#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float preco;
    int quantidade,tam;
    char nome[100];
} produto;

produto* inserir (char *n,float x,int q,produto *lista,int *tam) {
    lista = (produto*) realloc (lista,((*tam)+1)* sizeof(produto));
    strcpy(lista[(*tam)].nome,n);
    lista[(*tam)].preco = x;
    lista[(*tam)].quantidade = q;
    (*tam)++;
    return lista;
}
void remover (char *n,int q,produto *lista,int *tam) {
    produto troca;
    for (int i=0;i<(*tam);i++){
        if (strcmp(lista[i].nome,n)==0)
            lista[i].quantidade = lista[i].quantidade - q;
            if (lista[i].quantidade <= 0){
                troca = lista[(*tam)-1];
                lista[(*tam)-1] = lista[i];
                lista[i] = troca;
                (*tam)--;
                i-=1;
            }
    }
}
void removergrupo (float valor,produto *lista, int *tam) {
    produto troca;
    for (int i=0;i<(*tam);i++){
        if (lista[i].preco > valor){
            troca = lista[(*tam)-1];
            lista[(*tam)-1] = lista[i];
            lista[i] = troca;
            (*tam)--;
            i -= 1;
        }
    }
}
void consultar (produto *lista,int tam) {
    float soma=0;
    for (int i=0;i<tam;i++){
        soma += lista[i].preco*lista[i].quantidade;
    }
    printf("\nAtualmente a lista esta em R$%.1f\n",soma);
}
void procurar (char *n,produto *lista,int tam) {
    int achou = 0;
    for (int i=0;i<tam;i++) {
        if (strcmp(n,lista[i].nome)==0){
            achou = 1;
            printf("%s\n",lista[i].nome);
            printf("- %.1f\n",lista[i].preco);
            printf("- %d\n",lista[i].quantidade);
        }
    }
    if (achou == 0)
        printf("\n%s nao foi encontrado.\n",n);
}

int main() {
    float preco;
    int tam = 0,i = 0,removido,quantidade;
    produto *produtos = NULL;
    char instrucao[20],nome[100];
    while (scanf(" %s",instrucao) != EOF){
        if (strcmp(instrucao,"INSERIR") == 0){
            scanf(" %s %f %d",nome,&preco,&quantidade);
            produtos = inserir(nome,preco,quantidade,produtos,&tam);
        }
        else if (strcmp(instrucao,"CONSULTAR")== 0){
            consultar(produtos,tam);
        }
        else if (strcmp(instrucao,"REMOVER")==0){
            scanf(" %s %d",nome,&quantidade);
            remover(nome,quantidade,produtos,&tam);
        }
        else if (strcmp(instrucao,"REMOVERGRUPO")==0){
            scanf("%d",&removido);
            removergrupo(removido,produtos,&tam);
        }
        else if (strcmp(instrucao,"PROCURAR")==0){
            scanf(" %s",nome);
            procurar(nome,produtos,tam);
        }
        i++;
    }
    /*printf("%d\n",tam);
    procurar("Salgadinho",produtos,tam);
    procurar("Guarana",produtos,tam);
    procurar("Sprite",produtos,tam);
    procurar("Vodka",produtos,tam);*/

    return 0;
}
