#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"
#include "queue.h"


void errorB(char *s){
	fprintf(stderr, "%s", s);
	exit(EXIT_FAILURE);
}

/*****************************************************************************/
/**************************** fonctions de base ******************************/
/*****************************************************************************/

BTree makeEmptyBTree(void){
	return (BTree)NULL;
}

BTree makeNode(Element e, BTree l,  BTree r){
	BTree new;
	if ((new=(BTree)malloc(sizeof(Node)))==NULL) errorB("Allocation rat�e!");
	new->elem=e;
	new->left=l;
	new->right=r;
	return new;
}

BTree makeLeaf(Element e){
	return makeNode(e,makeEmptyBTree(),makeEmptyBTree());
}


int isEmptyBTree(BTree bt){
	return (bt==NULL);
}

Element root(BTree bt){
	if(isEmptyBTree(bt)) errorB("\n\nPas de noeud � la racine d'un arbre vide!!!");
	return bt->elem;
}


BTree leftChild(BTree bt){
	if(isEmptyBTree(bt)) errorB("Pas de fils gauche dans un arbre vide!!!");
	return bt->left;
}

BTree rightChild(BTree bt){
	if(isEmptyBTree(bt)) errorB("Pas de fils droit dans un arbre vide!!!");
	return bt->right;
}

int isLeaf(BTree bt){
	return !isEmptyBTree(bt) && isEmptyBTree(leftChild(bt)) && isEmptyBTree(rightChild(bt));
}

void freeNode(Node *c){
	free(c);
}

/*****************************************************************************/
/*************************** fonctions bas niveau ****************************/
/*****************************************************************************/

void insertRight(Node *n, Element e){
	if(!isEmptyBTree(n) && isEmptyBTree(rightChild(n)))
		n->right=makeLeaf(e);
	else errorB("insertRight impossible!");
}

void insertLeft(Node *n, Element e){
	if(!isEmptyBTree(n) && isEmptyBTree(leftChild(n)))
		n->left=makeLeaf(e);
	else errorB("insertLeft impossible!");
}

Element deleteRight(Node *n){
	if(isEmptyBTree(n) || !isLeaf(rightChild(n)))
		errorB("deleteRight imossible!");

	Element res=root(n->right);
	n->right=makeEmptyBTree();
	return res;
}

Element deleteLeft(Node *n){
	if(isEmptyBTree(n)  || !isLeaf(leftChild(n)))
		errorB("deleteLeft imossible!");

	Element res=root(n->left);
	n->left=makeEmptyBTree();
	return res;
}

void insertRightmostNode(BTree *bt, Element e){
	if(isEmptyBTree(*bt))
		*bt=makeLeaf(e);
	else{
		BTree tmp=*bt;
		while(!isEmptyBTree(rightChild(tmp)))
			tmp=rightChild(tmp);
		insertRight(tmp,e);
	}
}

Element deleteLeftmostNode(BTree *bt){
	Element res;
	if(isEmptyBTree(*bt))
		errorB("deleteLeftmostNode imossible!");
	if(isEmptyBTree(leftChild(*bt))){
		res=root(*bt);
		*bt=rightChild(*bt);
	}
	else{
		BTree tmp=*bt;
		while(!isEmptyBTree(leftChild(leftChild(tmp))))
			tmp=leftChild(tmp);
		res=root(leftChild(tmp));
		tmp->left=(tmp->left)->right;
	}
	return res;
}

//__________________________________________________________________________

// renvoie le min
int min(int a, int b){
	return (a > b)? b : a;
}


// la creation d un arbre
void addNode(Node **tree, unsigned int key)
{
    Node *tmpNode;
    Node *tmpTree = *tree;

    //la creation de l element a ajouter
    Node *elem = malloc(sizeof(Node));
    elem->elem = key;
    elem->left = NULL;
    elem->right = NULL;

    if(tmpTree)  //TQ l arbre n est pas vide
    do
    {
        tmpNode = tmpTree;
        if(key > tmpTree->elem )
        {
            tmpTree = tmpTree->right;
            if(!tmpTree) tmpNode->right = elem;
        }
        else
        {
            tmpTree = tmpTree->left;
            if(!tmpTree) tmpNode->left = elem;
        }
    }
    while(tmpTree);
    else  *tree = elem;
}


//l affichage d un arbre parcour infexe
void printTree(Node *tree)
{
    if(!tree) return;

    if(tree->left)  printTree(tree->left);

    printf("Cle => %d\n", tree->elem); 

    if(tree->right) printTree(tree->right);
	
}


//le nettoyage de l arbre
void clearTree(Node **tree)
{
    Node *tmpTree = *tree;

    if(!tree) return;

    if(tmpTree->left)  clearTree(&tmpTree->left);

    if(tmpTree->right) clearTree(&tmpTree->right);

    free(tmpTree);      

    *tree = NULL;
}







/*****************************************************************************/
/*************************** stack (pile) ****************************/
/*****************************************************************************/
// Data structure to represent a stack
struct stack
{
	int maxsize;	// define max capacity of the stack
	int top; //sommet
	Node* *items; 
};

// Utility function to initialize the stack
struct stack* newStack(int capacity)
{
	struct stack *pt = (struct stack*)malloc(sizeof(struct stack));  //allocation dynamique

	pt->maxsize = capacity;
	pt->top = -1;
	pt->items = (Node**)malloc(sizeof(int) * capacity);

	return pt;
}

// Utility function to return the size of the stack
int size(struct stack *pt) {
	return pt->top + 1;
}

// Utility function to check if the stack is empty or not
int isEmpty(struct stack *pt) {
	return pt->top == -1;   				// or return size(pt) == 0;
}

// Utility function to check if the stack is full or not
int isFull(struct stack *pt) {
	return pt->top == pt->maxsize - 1;  	// or return size(pt) == pt->maxsize;
}

// Utility function to add an element `x` to the stack
void push(struct stack *pt, Node* x)
{
	// check if the stack is already full. Then inserting an element would
	// lead to stack overflow
	if (isFull(pt))
	{
		printf("Overflow\nProgram Terminated\n");
		exit(EXIT_FAILURE);
	}

	//printf("Inserting %d\n", x->elem);

	// add an element and increment the top's index
	pt->items[++pt->top] = x;
}

// Utility function to return the top element of the stack
Node* peek(struct stack *pt)
{
	// check for an empty stack
	if (!isEmpty(pt)) {
		return pt->items[pt->top];
	}
	else {
		exit(EXIT_FAILURE);
	}
}

// Utility function to pop a top element from the stack
Node* pop(struct stack *pt)
{
	// check for stack underflow
	if (isEmpty(pt))
	{
		printf("Underflow\nProgram Terminated\n");
		exit(EXIT_FAILURE);
	}

	//printf("Removing %d\n", peek(pt));

	// decrement stack size by 1 and (optionally) return the popped element
	return pt->items[pt->top--];
}





/*****************************************************************************/
/*************************** file ****************************/
/*****************************************************************************/

/* Retourne une nouvelle file vide, ou NULL en cas d’erreur. */
queue *queue_new()
{
	queue *q;
	q = malloc(sizeof(queue));
	if (!q)
	return NULL;
	q -> head = NULL;
	q -> tail = NULL;
	q -> nb_values = 0;
	return q;
	}
	/* Libère la file <q>. */
	void queue_free(queue *q)
	{
	queue_element *e, *e_next;
	for (e = q -> head; e; e = e_next)
	{
	e_next = e -> next;
	free(e);
	}
	free(q);
}


/* Ajoute le pointeur <p> à la file <q>. Retourne 0 en cas de succès,
ou -1 en cas d’insuffisance mémoire. */
void queue_send(queue *q, Node* p)
{
	queue_element *e;
	e = malloc(sizeof(queue_element));
	// if (!e)
	// return -1;
	e -> content = p;
	e -> next = NULL;
	if (q -> tail)
	q -> tail -> next = e;
	else
	q -> head = e;
	q -> tail = e;
	q -> nb_values++;
	// return 0;
}

/* Extrait un pointeur de la file <q> et retourne ce pointeur,
ou NULL si la file est vide. */
Node* queue_receive(queue *q)
{
	queue_element *e;
	Node* p;
	if (!(q -> head))
	return NULL;
	e = q -> head;
	p = e -> content;
	q -> head = e -> next;
	if (!--(q -> nb_values))
	q -> tail = NULL;
	free(e);
	return p;
}

/* Retourne le pointeur en tête de la file <q>, sans le retirer,
ou NULL si la file est vide. */
void *queue_front(queue *q)
{
	if (!(q -> head))
	return NULL;
	return q -> head -> content;
}

/* Retourne le nombre d’éléments présents dans la file <q>. */
unsigned queue_size(queue *q)
{
	return q -> nb_values;
	}
	/* Détermine si la file <q> est vide. */
	int queue_is_empty(queue *q)
	{
	return q -> nb_values == 0;
}














