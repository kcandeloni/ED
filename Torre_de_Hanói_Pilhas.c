#include <stdio.h>

struct lista {
    int tamDisco;
	struct lista *prox;
};

typedef struct lista Lista;

struct pilha {
    Lista *topo;
};

typedef struct pilha Pilha;

Pilha *pilhaA= NULL; /* Variaeis globais de cada torre*/
Pilha *pilhaB= NULL;
Pilha *pilhaC= NULL;

/* funcao para criar uma pilha */
Pilha *cria(void) {
    Pilha *novo = (Pilha*) malloc(sizeof(Pilha));
    novo -> topo = NULL;
    return novo;
}

/* funcao para inserir um elemento em uma pilha;
 insercao ocorre sempre no topo */
void push (Pilha *p, int i) {
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    novo -> tamDisco = i;
    novo -> prox = p -> topo;
    p -> topo = novo;
}

int pilha_vazia(Pilha *p) {
    if (p == NULL) return 1;
    else return 0;
}

/* funcao para remover um elemento em uma pilha;
 remocao ocorre sempre no topo */
int pop (Pilha *p) {
    int i;
    Lista *temp;
    if (pilha_vazia(p)) {
            printf("pilha vazia\n");
            exit(1);
    }
    if(!pilha_vazia(p->topo)){
		temp = p-> topo;
    	i = temp-> tamDisco;
    	p -> topo = temp-> prox;
    	free(temp);
    	return i; /* Retorna o valor do disco que esta sendo desalocado */
	}
	else return 0; /* retorna 0 caso a pilha esteja vazia */
}

/* Função recursiva que resolve a Torre de Hanoi, com o meor numero de
movimentos.
O numero de movimentos que seraão necessarios pode ser demonstrado pela formula: (2^nDiscos ) - 1 */
void moveDiscos(Pilha *torre1, Pilha *torre3, Pilha *torre2, int nDiscos){

	static int move=1;
	
	if(nDiscos > 0){
		
		moveDiscos(torre1, torre2, torre3, nDiscos-1);
		push(torre3, pop(torre1)); /* Realiza o movimento do disco */
		printf("\n\n\t------- Movimento %d -------", move++); /* imprime o numero do movimento */
		imprimePilha(); /* Imprime o estado atual das torres apos cada movimento realizado */
		moveDiscos(torre2, torre3, torre1, nDiscos-1);
		}		
}

/* Imprime a pilhas */
void imprimePilha(){
	
	Lista *percorre1;
	Lista *percorre2;
	Lista *percorre3;
	percorre1 = pilhaA->topo;
	percorre2 = pilhaB->topo;
	percorre3 = pilhaC->topo;
	
	printf("\n\n\tTorre A\tTorre B\tTorre C");
	/* Enquanto alguma das pilhas ainda nao chegou ao final, o laço continua sendo executado */
	while(percorre1 != NULL || percorre2 != NULL || percorre3 != NULL){
		printf("\n\t");
		if(percorre1!=NULL){ /* Se a torre 1 já chegou ao final, ela não sera mais impressa */
			printf("%d", percorre1->tamDisco); /* Imprime os discos presentes na torre 1 */
			percorre1 = percorre1->prox; /* O ponteiro da torre 1 recebe o valor do proximo 
			elemento da pilha */
		}	
		printf("\t");
		if(percorre2!=NULL){
			printf("%d", percorre2->tamDisco);
			percorre2 = percorre2->prox;
		}
		printf("\t");
		if(percorre3!=NULL){
			printf("%d", percorre3->tamDisco);
			percorre3 = percorre3->prox;
		}
	}
}

/* funcao principal */
int main(void) {
    
	pilhaA = cria();
    pilhaB = cria();
    pilhaC = cria();
    
    int nDiscos, i;
    
	printf("Numero de Discos: ");
	scanf("%d", &nDiscos); /* Define o numeo de discos */
	
	for(i=nDiscos; i>0; i--){
		printf("push %d\n", i);
    	push(pilhaA, i); /* Insere os discos na pilha */
    }
    
    printf("\n\n\t------ Estado Inicial ------");
    imprimePilha(); /* Imprime a torre de hanoi antes de começar a moimentar os discos */
	moveDiscos(pilhaA, pilhaC, pilhaB, nDiscos); /* Chama a função que realizara os movimentos dos discos */
    
    printf("\n\nFree\tTorre A\tTorre B\tTorre C");
    for(i=nDiscos; i>0; i--){
		printf("\n\tpop %d\tpop %d\tpop %d", pop(pilhaA), pop(pilhaB), pop(pilhaC)); /* Desaloca as pilhas */
    }
    
    // system("pause");
    return 0;
}

