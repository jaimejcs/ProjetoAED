#include <stdio.h>
#include <stdlib.h>
//define o tamanho dos vetores 
#define tam 500
//define o tamanho das strings
#define lenstr 50


//Estrutura que representa o cadastro de um paciente
typedef struct paciente{
    float peso;
    //A variável processo refere-se ao código do tipo de procedimento a ser realizado pelo paciente
    int idade, processo;
    char nome[lenstr];
}Paciente;

//Estrutura de nós para a fila encadeada
typedef struct no{
    //Struct paciente em cada nó representa uma posição na fila
    struct paciente cliente;
    //Ponteiro nó apontando para o próximo na fila
    struct no *prox;
}No;


//Estrutura que representa os produtos médicos no deposito
typedef struct deposito{
    //vetor com a quantidade de produtos 
    int qtd[tam];
    //cada posição do vetor de produto possui a sua quantificação no vetor qtd na mesma posição de vetor
    char produto[tam][lenstr];
}Deposito;


typedef struct hospital{
    //Representa o deposito do hospital
    struct deposito estoque;
    //Ponteiro nó para a fila de pacientes
    struct no* fila;
}Hospital;

//Leitura dos dados de cadastro
void lerCadastro(No **cadastro){
    //Nome do paciente
    printf("Digite o nome: ");
    scanf("%[^\n]", (*cadastro)->cliente.nome);
    //Peso do paciente
    printf("Digite o peso: ");
    scanf("%f%*c", &(*cadastro)->cliente.peso);
    //Idade do paciente
    printf("Digite a idade: ");
    scanf("%d%*c", &(*cadastro)->cliente.idade);
    //Código do procedimento a ser realizado pelo paciente
    printf("Digite o processo: ");
    scanf("%d%*c", &(*cadastro)->cliente.processo);
}

//Função de enfilerar
void insert(No** fila){
    No *novo = malloc(sizeof(No)), *aux;

    if(novo){   //Verifica se a alocação funcionou
        
        //Entrada dos dados do paciente
        lerCadastro(&novo);
        //Ponteiro nulo da última posição da fila
        novo->prox = NULL;
        
        if(*fila == NULL){
            *fila = novo;    
        }else{
            aux = *fila;
            while(aux->prox){
                aux = aux->prox;
            }
            aux->prox = novo;
        }
    }else{
        printf("\n---Erro ao alocar memoria---\n");
    }
}

//Função de desenfilerar
No* delete(No **fila){
    No* aux = NULL;

    if(*fila){
        aux = *fila;
        *fila = aux->prox;
    }else{
        printf("\n---Fila vazia---\n");
    }

    return aux;
}

//Inicializa a fila
void iniciaFila(No** fila){
    *fila = NULL;
}

void iniciaDeposito(Hospital** depo){
    int i;
    //Percorre o vetor qtd, inicializando-o
    for(i = 0; i < tam; i++){(*depo)->estoque.qtd[i] = 0;}
}

void iniciaHospital(Hospital* hosp){
    //Inicia o ponteiro nó da fila do hospital
    hosp->fila = NULL;
    //Inicia o depósito do hospital
    iniciaDeposito(&hosp);
}

void printaCadastro(No* cadastro){
    printf("Nome: %s\n", cadastro->cliente.nome);
    printf("Peso: %.2f\n", cadastro->cliente.peso);
    printf("Idade: %d\n", cadastro->cliente.idade);
    printf("Processo: %d\n", cadastro->cliente.processo);
}

void imprimeFila(No *cadastro){
    No* aux = cadastro; //Variável auxiliar para percorrer a fila

    //Percorre a fila printando todos os cadastros
    if(aux){
        do{
            printaCadastro(aux);
            aux = aux->prox;
        }while(aux);
    }else{
        printf("\n---Fila vazia---\n");
    }
}

void painel(){
    printf("\n\n      Sistema gestor 1.0\n");
    printf("-----------------------------\n");
    printf("1- Adicionar paciente a fila\n");
    printf("2- Retirar da fila\n");
    printf("3- Ver a fila\n");
    printf("4- Sair do sistema\n");
}

int main(){
    No *fila, *r;   //fila é o ponteiro de nó que aponta para o topo da fila
    Hospital hosp;  //estrutura que define a abstração do hospital
    int cmd;    //r é o ponteiro de nó usada apenas para mostrar o item da fila retirado e liberar memória

    iniciaFila(&fila);
    iniciaHospital(&hosp);

    do{
        painel();
        printf("Opcao: ");
        scanf("%d", &cmd);
        getchar(); //Consumir caractere de quebra de linha;

        switch(cmd){
            case 1:
                printf("Adicionando a fila...\n");
                insert(&fila);
                break;

            case 2:
                r = delete(&fila);
                
                if(r){
                    printf("Cadastro removido:\n");
                    printaCadastro(r);

                    //Libera memória alocada
                    free(r);
                }
                break;
            case 3:
                printf("Imprimindo fila...\n");
                imprimeFila(fila);
                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
            printf("Opcao invalida\n");
                break;
        }
    }while(cmd != 4);

    return 0;
}