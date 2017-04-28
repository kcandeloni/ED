#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct lista {
    int info;
    char *chave;
	struct lista *prox;
};

typedef struct lista Lista;

/* funcao para criar uma lista */
Lista *lst_cria(void) {
    return NULL;
}

/* funcao para inserir um elemento em uma lista;
 insercao ocorre sempre na cabeca da lista */
Lista *lst_insere (Lista *l, int i, char *chave) {
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    novo -> info = i;
    novo->chave = (char*) malloc(strlen(chave)*sizeof(char));
    strcpy(novo->chave , chave);
    novo -> prox = l;
    return novo;
}

/* funcao para imprimir elementos de uma lista */
void lst_imprime (Lista *l) {
    Lista *p;
    for (p = l; p != NULL; p = p-> prox)
        printf("info = %d\n", p->info); 
}

/* funcao para remover um elemento de uma lista */
    Lista* lst_remove (Lista* l, int v)
    {
        Lista* ant = NULL; /* ponteiro para elemento anterior */
        Lista* p = l; /* ponteiro para percorrer a lista */
        /* procura elemento na lista, guardando anterior */

		while (p != NULL && p->info != v)
        { ant = p;
            p = p->prox; }
        /* verifica se achou elemento */
        if (p == NULL)
            return l; /* nÃ£o achou: retorna lista original */
        /* retira elemento */
        if (ant == NULL)
        { /* retira elemento do inicio */
            l = p->prox; }
        else { /* retira elemento do meio da lista */
            ant->prox = p->prox; }
        free(p);

        return l;
    }

/* Funcao que remove o (k-1)-esimo elemento da lista */
Lista* removeBefore(Lista *l, int chave){

    Lista* ant = NULL; /* ponteiro para elemento anterior */
    Lista* p = l; /* ponteiro para percorrer a lista */
    int i=0;
	/* procura elemento na lista, guardando anterior */
    while (p != NULL && p->info != chave){
		ant = p;
    	p = p->prox;
    	i++;
	}
	if(i>=1){
		ant = NULL;
		p = l;
		while(i>1){
			ant = p;
			p = p->prox;
			i--;
		}
	}
	else return l;
    /* verifica se achou elemento */
    if (p == NULL)
    	return l; /* nÃ£o achou: retorna lista original */
	/* retira elemento */
    
	if (ant == NULL){ 
	/* retira elemento do inicio */
		l = p->prox;
	}
	else { /* retira elemento do meio da lista */
		ant->prox = p->prox;
	}
	free(p->chave);
	free(p);
	return l;
}	

/* funcao para remover todos elementos com chave k elemento de uma lista */
Lista* removeChave(Lista* l, int v){

    Lista* ant = NULL; /* ponteiro para elemento anterior */
    Lista* p = l; /* ponteiro para percorrer a lista */
    /* procura elemento na lista, guardando anterior */
    while (p != NULL && p->info != v){
		ant = p;
    	p = p->prox;
	}
    /* verifica se achou elemento */
    if (p == NULL)
    	return l; /* nÃ£o achou: retorna lista original */
	/* retira elemento */
    if (ant == NULL){ 
	/* retira elemento do inicio */
		l = p->prox;
	}
	else { /* retira elemento do meio da lista */
		ant->prox = p->prox;
	}
	removeChave(p->prox, v); /* Chama a função que retira da 
	lista mandadno o prox elemento */
	free(p->chave);
	free(p);
	return l;
}

/* Funcao recursiva que retorna o maior elemnto de uma lista */
int maiorElemento(Lista* l, int mChave){
	
	if(l==NULL) return mChave; /* Retorna o maior elemento */
	if(mChave > l->info) maiorElemento(l->prox, mChave); /* Se o elemento 
	presente na lista é menor que o mChave(atual maior), chama a função 
	mandando mChave */
	else maiorElemento(l->prox, l->info); /* o elemento presente na lisa é
	maior que o atual maior, chama a função mandando o elemento da lista,
	tornando esse o atual maior */
}

Lista* inverteLista(Lista *l){
	
	Lista *raiz=NULL;
	Lista *aux;
	
	while(l!=NULL){
		aux=l->prox;
		l->prox=raiz;
		raiz=l;
		l=aux;
	}
	return raiz;
}

bool find(Lista *l, char *chave){

	Lista *percorre = l;
	
	while(percorre != NULL){
		if(strcmp(chave ,percorre->chave)==0)return true;
		percorre = percorre->prox;
	}
	return false;
}

void limpaMem(Lista *l){
	Lista *auxLista;
	while(l!=NULL){
		auxLista = l;
		l = l->prox;
		free(auxLista->chave);
		free(auxLista);
	}
}

/* funcao principal */
int main(void) {
    Lista *l;
    l = lst_cria();
    l = lst_insere(l, 31, "31");
    l = lst_insere(l, 29, "29");
	l = lst_insere(l, 23, "23");
    l = lst_insere(l, 25, "25");
    l = lst_insere(l, 28, "28");
    l = lst_insere(l, 25, "25");
    l = lst_insere(l, 30, "30");
    l = lst_insere(l, 24, "24");
    l = lst_insere(l, 26, "26");
    l = lst_insere(l, 25, "25");
    l = lst_insere(l, 27, "27");
	l = lst_insere(l, 25, "25");
	printf("\norigem lista\n");
	lst_imprime(l);
    
    l = removeBefore(l, 31);
	printf("\n2) nova lista - Chave = 31 / Remove (Chave-1)\n");
	lst_imprime(l);
	
	l = removeChave(l, 25);
    printf("\n3) nova lista - Chave = 25 / Remove todas as Chave\n");
	lst_imprime(l);
    
	printf("\n4) Maior Elemento da lista: %d\n", maiorElemento(l, l->info));
	
	l=inverteLista(l);
	printf("\n5) inverte lista\n");
    lst_imprime(l);
    
	if(find(l,"25"))printf("\n7) A chave '25' esta pesente na lista\n");
    else printf("\n7)A chave '25' nao esta presente na lista!\n");
    
	limpaMem(l);
    
	return 0;
}
