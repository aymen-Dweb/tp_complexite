#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BTree.c"

// QST 1---
//----recursive
int rec_equalBTrees(BTree bt1, BTree bt2){ 
	if(isEmptyBTree(bt1))
     {
          return (isEmptyBTree(bt2));
     }
	else
     {
          if(isEmptyBTree(bt2)){
               return 0;
          }
          else{
               return root(bt1)==root(bt2) && rec_equalBTrees(leftChild(bt1),leftChild(bt2)) && rec_equalBTrees(rightChild(bt1),rightChild(bt2));
          }
     }			
}
//--------iterative
int ite_equalBTrees(Node* x, Node* y)
{
     //si les deux arbres sont vides = TRUE
	if (x == NULL && y == NULL) {return 1;}
     //si la 1er arbre est vide (et la deuxieme n'est pas vide) = FALSE
	if (x == NULL) {return 0;}
     //si la 2eme arbre est vide (et la premiere n'est pas vide) = FALSE
	if (y == NULL) {return 0;}

     //creation d'une pile(15) pour stocker Node*
	struct stack *st = newStack(15);
     push(st, x);
     push(st, y);

	//on boucle jusqua que la pile soit vide
	while (!isEmpty(st))
	{
		// depiler the top element dans la pile
		Node* x = pop(st);
		Node* y = pop(st);
          //if les racines des 2 arbres sont pas egaux = FALSE
		if (x->elem != y->elem) {return 0;}


          //si la sous arbre gauche de x et y existe, on doit pusher leurs @adr dans la pile
          //sinon si le fils gauche existe d'un seul coté = FALSE
		if (x->left && y->left) {
               push(st, x->left);   push(st, y->left);
		}
		else if (x->left || y->left) {return 0;}
          //si la sous arbre droite de x et y existe, on doit pusher leurs @adr dans la pile
          //sinon si le fils droit existe d'un seul coté = FALSE
		if (x->right && y->right) {
			push(st, x->right);   push(st, x->right);
		}
		else if (x->right || y->right) {return 0;}
	}
	//TRUE
	return 1;
}


// QST 2---------------
//-----------recursive
int rec_isSubBTree(BTree sbt, BTree bt){ 
	if(isEmptyBTree(bt)){
          return isEmptyBTree(sbt);
     }	
	else{
          if(rec_equalBTrees(sbt,bt)){
               return 1;
          }
          else return rec_isSubBTree(sbt,leftChild(bt)) || rec_isSubBTree(sbt,rightChild(bt));
     }
}
//----------------iterative
/*int sub(Node *n1, Node *n2)
{
    Node *stack1[100], *stack2[100];
    int stack_size1 = 0, stack_size2 = 0;
    Node *p1, *p2;
    
    //remplir les deux pile avec les noeud gauche des deux arbre
    for (p1 = n1; p1 != NULL; p1 = p1->left) {
        stack1[stack_size1++] = p1;
    }
    for (p2 = n2; p2 != NULL; p2 = p2->left) {
        stack2[stack_size2++] = p2;
    }
    
    //tq la pile est rempis depiler et comparer
    while (stack_size1 > 0) {
        Node *n1 = stack1[--stack_size1]; // depiler - pop
        Node *n2 = stack2[--stack_size2]; // depiler - pop
        
        //comparaison
        if(n1->elem != n2->elem){
        	printf("----> Arbre1 n'est pas un sous arbre de Arbre2.\n \n");
        	return 0;
        }
         
        //remplir les deux pile avec les noeud droit des deux arbre 
        for (p1 = n1->right; p1 != NULL; p1 = p1->left) {
            stack1[stack_size1++] = p1;
        }
        for (p2 = n2->right; p2 != NULL; p2 = p2->left) {
            stack2[stack_size2++] = p2;
        }
    }
    printf("----> Arbre1 est un sous arbre de Arbre2.\n \n");
    return 1;
}

void subBTreesIter(Node *t1, Node *t2)
{
    sub(t1, t2);
}*/
int ite_isSubBTree(Node *n1, Node *n2)
{
     //printf("aaaaaaaaaaaaaaaaaaa");
    Node *stack1[100];
    int stack_size = 0;
    Node *p ;
    stack1[stack_size++] = n2;
    //printf("%d",stack_size);
    while (stack_size > 0)
    {
     //printf("%d",stack_size);
     p=stack1[stack_size];
     //printf("%d",p->elem);
     //printf("%d",n2->elem);
     stack1[--stack_size];
     //printf("%d",stack_size);
     if (p->elem == n1->elem)
     {
          if(ite_equalBTrees(n1,p)) {return 1;}
     }
     if (p->right)
     {
          stack1[stack_size++] = p->right;
     }
     if (p->left)
     {
          stack1[stack_size++] = p->left;
     }   
     //printf("%d",stack_size);
    }
    return 0;
}


/////////////////////// Q3 ----------- Q4 ------------ Q5 ////////////////////////

// QST 3---------------
//-----------recursive
int rec_findElem(BTree bt,Element e){
	if(isEmptyBTree(bt))
		return 0;
	else {
		if(root(bt)==e)
			return 1;
		else
			return rec_findElem(leftChild(bt),e) ||  rec_findElem(rightChild(bt),e);
	}
}
//-----------iterative
int ite_findElem(Node*x , Element e)
{
     if (x== NULL) {return 0;}
	struct stack *pt = newStack(15);
     push(pt, x);
     
	while (!isEmpty(pt)) 
	{
		// depiler le top --pop
		Node* x = pop(pt);
          // test
		if (x->elem == e) {return 1;}
          //empiler les element gauche 
		if (x->left) {push(pt, x->left);}
          //empiler les element droit 
		if (x->right) {push(pt, x->right);}	
	}
	return 0;
}

// QST 4---------------
//------------recursive
Element rec_findMin(BTree bt){
	if(isEmptyBTree(bt))     {printf("FIND : Empty Tree!!! ");}
	if(isLeaf(bt))           {return root(bt);}
	else {
		Element m=root(bt);
		if(!isEmptyBTree(leftChild(bt)))
			m=min(m,rec_findMin(leftChild(bt)));
		if(!isEmptyBTree(rightChild(bt)))
			m=min(m,rec_findMin(rightChild(bt)));

		return m;
	}
}

//------------iterative
int ite_findMin(Node*x)
{
     int min;
     if (x== NULL) {return 0;} 
     else {min = root(x);}

	struct stack *pt = newStack(3);
     push(pt, x);

	while (!isEmpty(pt))
	{
		// depiler le sommet
		Node* x = pop(pt);
          // test (elem poper) < min
		if (x->elem < min) {min = x->elem;}
          //empiler les element gauche
		if (x->left) {push(pt, x->left);}
          //empiler les element droit
		if (x->right) {push(pt, x->right);}
	}
	return min;
}





// QST 5---------------
//------------recursive

//prototype-
void printCurrentLevel(Node* root, int level);
int height(Node* node);
//----------
struct node* newNode(int data);


// Function to print arbre dans l’ordre d’un parcours en largeur
void rec_printWidthOrder(Node* root)
{
	int h = height(root);
	int i;
     //pour chaque niveau je fait appel recursive --complexite O(n*n)
	for (i = 1; i <= h; i++)
		printCurrentLevel(root, i);
}
//print le niveau actuel
void printCurrentLevel(Node* root, int level)
{
	if (root == NULL)   return;
	if (level == 1)     {printf("%d ", root->elem);}//print elt
	else if (level > 1) {//for exmpl level=2 donc pour afficher le niveau 2 il faut afficher les fils G et D de niveau 1
		printCurrentLevel(root->left, level - 1);
		printCurrentLevel(root->right, level - 1);
	}
}

//the hight of a tree 
int height(Node* node)
{
	if (node == NULL)
		return 0;
	else {
		//appel rec to height() pour calculer la longueur de SA-G et SA-D 
		int lheight = height(node->left);
		int rheight = height(node->right);

		//pour retourner la valeur de la plus grande longueur entre SA-G et SA-D = la langueur de larbre
		if (lheight > rheight)
			return (lheight + 1);
		else
			return (rheight + 1);
	}
}

//------------iterative
void ite_printWidthOrder(Node*x)
{
     if (x == NULL) {printf("PRINT : Empty Tree!!! ");}
     else{
          // create a file
          queue *q;
          q = queue_new();
          queue_send(q, x);
          // JUSQUA la file sera vide
          while (q != NULL)
          {
               // defiler
               Node* n = queue_receive(q);
               printf("%d ", root(n));		
               //enfiler gauche
               if (n->left) {
                    queue_send(q, n->left);
               }
               //enfiler droit
               if (n->right) {
                    queue_send(q, n->right);
               }  
          }
     }
}



int main(){
     // la declaration de deux arbres
     BTree A1=NULL, A2=NULL;

     //time 
     clock_t t1, t2;
     double delta;

     //la creation de la premiere arbre
     addNode(&A1, 30);
     addNode(&A1, 20);
     addNode(&A1, 50);
     addNode(&A1, 45);
     addNode(&A1, 25);
     addNode(&A1, 80);
     addNode(&A1, 40);
     addNode(&A1, 70);
     addNode(&A1, 25);
     addNode(&A1, 9);
     addNode(&A1, 60);


     //la creation de la 2eme arbre
     addNode(&A2, 30);
     addNode(&A2, 20);
     addNode(&A2, 50);
     addNode(&A2, 45);
     addNode(&A2, 25);
     addNode(&A2, 80);
     addNode(&A2, 40);
     addNode(&A2, 70);
     addNode(&A2, 25);
     addNode(&A2, 10);
     addNode(&A2, 60);

     

     
     puts("-------------------------------");
     printf("Arbre A1 ----->\n");
     //printTree(A1);
     puts("-------------------------------");
     printf("Arbre A2 ----->\n");
     //printTree(A2);
     puts("-------------------------------\n\n\n");

/*
     // le test de la qst 1
     printf("-------------------------QST 1 RECURSIVE\n");
     int result11 = rec_equalBTrees(A1, A2);
     if(result11>0){
          printf("----> Les deux arbres sont ------ EGAUX------.\n \n");
     }else{
          printf("----> Les deux arbres sont ------ PAS EGAUX ------!\n \n");
     }
     printf("-------------------------QST 1 ITERATIVE\n");
     int result12 = ite_equalBTrees(A1, A2);
     if(result12>0){
          printf("----> Les deux arbres sont ------ EGAUX------.\n \n");
     }else{
          printf("----> Les deux arbres sont ------ PAS EGAUX ------!\n \n");
     }

     // le test de la qst 2
     printf("-------------------------QST 2 RECURSIVE\n");
     int result2 = rec_isSubBTree(A1, A2);
     if(result2>0){
          printf("----> Aebre1 est un sous-arbre de Arbre2.\n \n");
     }else{
          printf("----> Arbre1 n\'est pas un sous-arbre de Arbre2!\n \n");
     }
     printf("-------------------------QST 2 ITERATIVE\n");
     int result22 = ite_isSubBTree(A1, A2);
     if(result22>0){
          printf("----> Aebre1 est un sous-arbre de Arbre2.\n \n");
     }else{
          printf("----> Arbre1 n\'est pas un sous-arbre de Arbre2!\n \n");
     }
*/



// le test de la qst 3

t1 = clock();

     printf("-------------------------QST 3 RECURSIVE");
     int recfind1 = rec_findElem(A1, 300);
     if(recfind1>0){
          printf("\n ----> element exists in the tree \n");
     }else{
          printf("\n ----> element does not exist in the tree \n");
     }
t2 = clock();
delta = (float)(t2 - t1) / CLOCKS_PER_SEC;
printf("TIME > le temps dexecution 'rec_findElem' ===  %f milliseconde \n", delta*1000);

     int recfind2 = rec_findElem(A1, 30);
     if(recfind2>0){
          printf("\n ----> element exists in the tree \n\n");
     }else{
          printf("\n ----> element does not exist in the tree \n\n");
     }


t1 = clock();

     printf("-------------------------QST 3 ITERATIVE");
     int recfind3 = ite_findElem(A1, 300);
     if(recfind3>0){
          printf("\n ----> element exists in the tree \n");
     }else{
          printf("\n ----> element does not exist in the tree \n");
     }
t2 = clock();
delta = (float)(t2 - t1) / CLOCKS_PER_SEC;
printf("TIME > le temps dexecution 'ite_findElem' ===  %f milliseconde \n", delta*1000);

     int recfind4 = ite_findElem(A1, 30);
     if(recfind4>0){
          printf("\n ----> element exists in the tree \n\n");
     }else{
          printf("\n ----> element does not exist in the tree \n\n");
     }





















// le test de la qst 4
t1 = clock();
     
     printf("\n\n-------------------------QST 4 RECURSIVE");
     Element min1 = rec_findMin(A1);
     printf("\n ----> Le min de Arbre1 est: %d",min1);
t2 = clock();
delta = (float)(t2 - t1) / CLOCKS_PER_SEC;
printf("\nTIME > le temps dexecution 'rec_findMin' ===  %f milliseconde \n", delta*1000);
     Element min2 = rec_findMin(A2);
     printf("\n ----> Le min de Arbre2 est: %d\n \n",min2);



t1 = clock();

     printf("-------------------------QST 4 ITERATIVE");
     Element min3 = ite_findMin(A1);
     printf("\n ----> Le min de Arbre1 est: %d\n",min3);
t2 = clock();
delta = (float)(t2 - t1) / CLOCKS_PER_SEC;
printf("TIME > le temps dexecution 'ite_findMin' ===  %f milliseconde \n", delta*1000);
     Element min4 = ite_findMin(A2);
     printf("\n ----> Le min de Arbre2 est: %d\n\n",min4);























// le test de la qst 5
t1 = clock();
     
     printf("\n\n-------------------------QST 5 RECURSIVE\n");
     rec_printWidthOrder(A1);     

t2 = clock();
delta = (float)(t2 - t1) / CLOCKS_PER_SEC;
printf("\nTIME > le temps dexecution 'rec_printWidthOrder' ===  %f milliseconde \n", delta*1000);



t1 = clock();
     printf("\n-------------------------QST 5 ITERATIVE\n");
     ite_printWidthOrder(A1);

t2 = clock();
delta = (float)(t2 - t1) / CLOCKS_PER_SEC;
printf("TIME > le temps dexecution 'ite_printWidthOrder' ===  %f milliseconde \n", delta*1000);












     // vider l espace memoire occupe pour les 2 arbres
     clearTree(&A1);
     clearTree(&A2);


     

    
	return 0;
}