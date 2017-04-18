#include <stdio.h>
#include <stdlib.h>


struct lista {
    int tamDisco;
	struct lista *prox;
};

typedef struct lista Lista;

struct pilha {
    Lista *topo;
};

typedef struct pilha Pilha;

Pilha *pilhaA= NULL;
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
    	return i;
	}
	else return 0;
}

void moveDiscos(Pilha *torre1, Pilha *torre3, Pilha *torre2, int nDiscos){

	static int move=1;
	
	if(nDiscos > 0){
		
		moveDiscos(torre1, torre2, torre3, nDiscos-1);
		push(torre3, pop(torre1));
		printf("\n\n\t------- Movimento %d -------", move++);
		imprimePilha(torre1, torre2, torre3);
		moveDiscos(torre2, torre3, torre1, nDiscos-1);
		}		
}

void imprimePilha(){
	
	Lista *percorre1;
	Lista *percorre2;
	Lista *percorre3;
	percorre1 = pilhaA->topo;
	percorre2 = pilhaB->topo;
	percorre3 = pilhaC->topo;
	
	printf("\n\n\tTorre A\tTorre B\tTorre C");
	/*Enquanto alguma das pilhas ainda não chegou ao final*/
	while(percorre1 != NULL || percorre2 != NULL || percorre3 != NULL){
		printf("\n\t");
		if(percorre1!=NULL){
			printf("%d", percorre1->tamDisco);
			percorre1 = percorre1->prox;
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
	scanf("%d", &nDiscos);
	
	for(i=nDiscos; i>0; i--){
		printf("push %d\n", i);
    	push(pilhaA, i);
    }
    
    printf("\n\n\t------ Estado Inicial ------");
    imprimePilha();
	moveDiscos(pilhaA, pilhaC, pilhaB, nDiscos);
    
    printf("\n\nFree\tTorre A\tTorre B\tTorre C");
    for(i=nDiscos; i>0; i--){
		printf("\n\tpop %d\tpop %d\tpop %d", pop(pilhaA), pop(pilhaB), pop(pilhaC));
    }
    
    // system("pause");
    return 0;
}



