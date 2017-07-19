
#include "queue.h"

/*	front -> ... -> final -> NULL 	*/

Queue *newQueue() {
	Queue *queue = (Queue *) calloc (sizeof (Queue), 1);
	queue->back = NULL;
	queue->front = NULL;
	queue->size = 0;
	return queue;
}

void 
enqueue (Queue *c, element e) {
	node *newNode = (node *) malloc (sizeof (node));
	newNode->e = e;
	newNode->next = NULL;
	if (!c->front)
		c->front = c->back = newNode;
	else {
		c->back->next = newNode;
		c->back = newNode;
	}
	c->size++;
}

/*	Si la queue esta vacia, se retorna basura.	*/
element
dequeue (Queue *c) {
	element e;
	if (c->front){
		e = c->front->e;
		node *del = c->front;
		c->front = c->front->next;
		free (del);
		if (c->front == NULL)
			c->back = NULL;
		c->size--;
	} else
		puts ("WARNING: Empty element returned because you've ordered to dequeue an empty queue..."); 
	return e;
}

void
clear (Queue *c) {
	element e;
	while (c->front)
		e = dequeue (c);
}

bool queueEmpty(Queue *c){ return c->size == 0; }

element front (Queue *c){ return c->front->e; }

element back (Queue *c){ return c->back->e; }

static int queueSize(Queue *c){ return c->size; }

element Element(Queue *c, int n) {
	int pos = 1;
	node * aux = c->front;
	element e;
	if (n <= queueSize(c)) {
		while (pos < n) {
			aux = aux->next;
			pos++;
		}
		e = aux->e;
	}
	return e;
}

