#include "Lista.h"

void Initialize(lista *l){
	l->frente = NULL;
	l->final = NULL;
	l->tamano = 0;
	return;
}

void Destroy(lista *l){
	posicion tmp;
	while(l->frente != NULL){
		tmp = l->frente->siguiente;
		free(l->frente);
		l->frente = tmp;
	}
	l->final = NULL;
	l->tamano = 0;
	return;
}

posicion First(lista *l){
	return l->frente;
}

posicion Final(lista *l){
	return l->final;
}

boolean ValidatePosition(lista *l, posicion p){
	posicion pos = l->frente;
	while(pos != NULL && pos != p)
		pos = pos->siguiente;
	return pos == p;
}

posicion Previous(lista *l, posicion p){
	if(ValidatePosition(l, p)) return p->anterior;
	return NULL;
}

posicion Following(lista *l, posicion p){
	if(ValidatePosition(l, p)) return p->siguiente;
	return NULL;
}

posicion Search(lista *l, elemento e){
	posicion pos = l->frente;
	while(pos != NULL && memcmp(&pos->e, &e, sizeof(elemento)) != 0)
		pos = pos->siguiente;
	return pos;
}

int Size(lista *l){
	return l->tamano;
}

boolean IsEmpty(lista *l){
	return Size(l) == 0;
}

elemento Position(lista *l, posicion p){
	elemento e;
	if(ValidatePosition(l, p)) e = p->e;
	return e;
}

posicion ElementPosition(lista *l, int n){
	posicion pos = NULL;
	int c = 1;
	if(n <= l->tamano){
		pos = l->frente;
		while(c < n){
			pos = pos->siguiente;
			c++;
		}
	}
	return pos;
}

elemento Element(lista *l, int n){
	elemento e;
	posicion pos = ElementPosition(l, n);
	if(pos != NULL) e = pos->e;
	return e;
}

boolean InsertBefore(lista *l, elemento e, posicion p){
	boolean r = FALSE;
	posicion nuevo = (posicion)malloc(sizeof(nodo));
	if(nuevo != NULL){
		nuevo->e = e;
		nuevo->siguiente = p;
		if(p->anterior == NULL){
			nuevo->anterior = NULL;
			l->frente = nuevo;
		}else{
			nuevo->anterior = p->anterior;
			p->anterior->siguiente = nuevo;
		}
		p->anterior = nuevo;
		l->tamano++;
		r = TRUE;
	}
	return r;
}

boolean InsertAfter(lista *l, elemento e, posicion p){
	boolean r = FALSE;
	posicion nuevo = (posicion)malloc(sizeof(nodo));
	if(nuevo != NULL){
		nuevo->e = e;
		nuevo->anterior = p;
		if(p->siguiente == NULL){
			nuevo->siguiente = NULL;
			l->final = nuevo;
		}else{
			nuevo->siguiente = p->siguiente;
			p->siguiente->anterior = nuevo;
		}
		p->siguiente = nuevo;
		l->tamano++;
		r = TRUE;
	}
	return r;
}

boolean AddBeginning(lista *l, elemento e){
	boolean r = FALSE;
	posicion nuevo;
	if(l->frente == NULL){
		nuevo = (posicion)malloc(sizeof(nodo));
		if(nuevo != NULL){
			nuevo->e = e;
			l->frente = nuevo;
			l->final = nuevo;
			nuevo->anterior = NULL;
			nuevo->siguiente = NULL;
			l->tamano++;
			r = TRUE;
		}
		return r;
	}else{
		return InsertBefore(l, e, l->frente);
	}
}

boolean AddEnd(lista *l, elemento e){
	if(l->final == NULL){
		return AddBeginning(l, e);
	}else{
		return InsertAfter(l, e, l->final);
	}
}

boolean Remove(lista *l, posicion p){
	boolean r = FALSE;
	if(ValidatePosition(l, p)){
		if(p->anterior == NULL){
			l->frente = p->siguiente;
		}else{
			p->anterior->siguiente = p->siguiente;
		}
		if(p->siguiente == NULL){
			l->final = p->anterior;
		}else{
			p->siguiente->anterior = p->anterior;
		}
		free(p);
		l->tamano--;
		r = TRUE;
	}
	return r;
}

boolean Replace(lista *l, posicion p, elemento e){
	boolean r = FALSE;
	if(ValidatePosition(l, p)){
		p->e = e;
		r = TRUE;
	}
	return r;
}