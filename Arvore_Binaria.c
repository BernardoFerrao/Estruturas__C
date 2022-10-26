#include <stdio.h>
#include <stdlib.h>

struct pessoa
{
    char letra;
    float cpf;
};
typedef struct pessoa Pessoa;

struct no
{
    struct no *esquerda;
    struct no *direita;
    Pessoa pessoa;
};
typedef struct no No;

No *inicializar()
{
    return NULL;
}

Pessoa CriarPessoa(float cpf, char letra)
{
    Pessoa pessoa;
    pessoa.cpf = cpf;
    pessoa.letra = letra;
    return pessoa;
}

No *inserir(No *raiz, Pessoa p)
{
    No *no = (No *)malloc(sizeof(No));
    no->pessoa = p;
    if (raiz == NULL)
    {
        raiz = no;
        no->direita = NULL;
        no->esquerda = NULL;
        return no;
    }
    else
    {
        if (p.cpf > raiz->pessoa.cpf)
        {
            raiz->direita = inserir(raiz->direita, p);
        }

        if (p.cpf < raiz->pessoa.cpf)
        {
            raiz->esquerda = inserir(raiz->esquerda, p);
        }
    }
    return raiz;
}

void imprimir(No *raiz)
{
    if (raiz != NULL)
    {
        printf("%f %c", raiz->pessoa.cpf, raiz->pessoa.letra);
        printf("\n");
        imprimir(raiz->direita);
        imprimir(raiz->esquerda);
    }
}

void liberar(No *raiz)
{
    if (raiz != NULL)
    {
        liberar(raiz->direita);
        liberar(raiz->esquerda);
        free(raiz);
    }
}

No *pesquisar(No *raiz, float cpf)
{
    if (raiz != NULL)
    {
        if (raiz->pessoa.cpf = cpf)
        {
            return raiz;
        }
        else
        {
            if (cpf > raiz->pessoa.cpf)
            {
                return pesquisar(raiz->direita, cpf);
            }
            else if (cpf < raiz->pessoa.cpf)
            {
                return pesquisar(raiz->esquerda, cpf);
            }
        }
    }
    return NULL;
}

No *arvoremenor(No *raiz)
{
    if (raiz != NULL)
    {
        No *aux = raiz;
        while (aux->esquerda != NULL)
        {
            aux = raiz->esquerda;
        }
        return aux;
    }
    return NULL;
}

No *remover(No *raiz, float cpf)
{
    if (raiz != NULL)
    {
        if (cpf > raiz->pessoa.cpf)
        {
            raiz->direita = remover(raiz->direita, cpf);
        }
        else if (cpf < raiz->pessoa.cpf)
        {
            raiz->esquerda = remover(raiz->esquerda, cpf);
        }
        else
        { // encontrou
            if (raiz->direita == NULL && raiz->esquerda == NULL)
            { // Nó não tem filhos
                free(raiz);
                return NULL;
            }
            else if (raiz->esquerda == NULL && raiz->direita != NULL)
            { // Um filho direita
                No *aux = raiz->direita;
                free(raiz);
                return aux;
            }
            else if (raiz->direita == NULL && raiz->esquerda != NULL)
            { // Um filho esquerda
                No *aux = raiz->esquerda;
                free(raiz);
                return aux;
            }
            else
            {
                No *aux = arvoremenor(raiz->direita); // encontrei o menor número da maior subarvore
                Pessoa pessoaaux = aux->pessoa;
                raiz = remover(raiz, pessoaaux.cpf);
                raiz->pessoa = pessoaaux;
            }
        }
        return raiz;
    }
    else return NULL;
}

int main()
{
    No *raiz = inicializar();
    raiz = inserir(raiz, CriarPessoa(10, 'r'));
    raiz = inserir(raiz, CriarPessoa(15, 'd'));
    raiz = inserir(raiz, CriarPessoa(20, 'd'));
    raiz = inserir(raiz, CriarPessoa(12, 'e'));
    raiz = inserir(raiz, CriarPessoa(5, 'e'));
    /*No *temp = pesquisar(raiz, 10);
    if (temp == NULL)
        printf("Nao encontrou");
    else
        printf("Encontrou %i\n", *temp);
    */
    imprimir(raiz);
    raiz = remover(raiz,10);
    imprimir(raiz);
    liberar(raiz);
    return 0;
}