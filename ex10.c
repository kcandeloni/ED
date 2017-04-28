#include <stdio.h>
#include <stdlib.h>


struct lista {
    char c;
    struct lista *prox;
    struct lista *ant;
};

typedef struct lista Lista;



/* funcao para criar uma lista */
Lista *lst_cria(void) {
    return NULL;
}

Lista *converte(Lista *l, char s[1]) {
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    Lista *p;
    
    novo->c = s;
    
    novo -> prox = NULL;
    if (l==NULL) {
           novo -> ant = NULL;
           l = novo;
    } else {
           for (p = l; p->prox != NULL; p=p->prox);
           p -> prox = novo;
           novo-> ant = p;
    }
    
    return l;
}


/* funcao para imprimir elementos de uma lista */
void lst_imprime (Lista *l) {
    Lista *p;
    for (p = l; p != NULL; p = p-> prox)
        printf("info = %c\n", p->c);
    
}

/* funcao principal */
int main(void) {

    Lista *c;
    c = lst_cria();
    
    int i;
	char palavra[20];
	
	printf("\n\n10) Insira a string: ");
    scanf("%s", &palavra);
	//printf("\n%s", palavra);
	
	for(i=0; i<strlen(palavra); i++)
    	c = converte(c, palavra[i]);
	lst_imprime(c);
	// system("pause");
    return 0;
}



