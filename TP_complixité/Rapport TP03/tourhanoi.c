
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>




//element pile
struct Stack
{
unsigned size;
int top;
int *array;
};


struct Stack* init_pile(unsigned size)
{
    struct Stack* stack =
        (struct Stack*) malloc(sizeof(struct Stack));
    stack -> size = size;
    stack -> top = -1;
    stack -> array =
        (int*) malloc(stack -> size * sizeof(int));
    return stack;
}


int pile_pleine(struct Stack* stack)
{
return (stack->top == stack->size - 1);
}


int pile_vide(struct Stack* stack)
{
return (stack->top == -1);
}


void empiler(struct Stack *stack, int item)
{
    if (pile_pleine(stack))
        return;
    stack -> array[++stack -> top] = item;
}


int depiler(struct Stack* stack)
{
    if (pile_vide(stack))
        return INT_MIN;
    return stack -> array[stack -> top--];
}

//afficher deplacement
void afficher_deplacement(char fromPeg, char toPeg, int disk)
{
    printf("deplacement %d de  \'%c\' vers \'%c\'\n",
        disk, fromPeg, toPeg);
}

//deplacer disk entre deux piles
void deplacer_entre_deux_tours(struct Stack *source,
            struct Stack *destination, char s, char d)
{
    int pile1 = depiler(source);
    int pile2 = depiler(destination);

    // si source est vide
    if (pile1 == INT_MIN)
    {
        empiler(source, pile2);
        // afficher_deplacement(d, s, pile2);
    }

    // si destination est vide
    else if (pile2 == INT_MIN)
    {
        empiler(destination, pile1);
        // afficher_deplacement(s, d, pile1);
    }

    // deplacement vers pile destination n'est pas permis
    else if (pile1 > pile2)
    {
        empiler(source, pile1);
        empiler(source, pile2);
        // afficher_deplacement(d, s, pile2);
    }

    // deplacement vers pile destination
    else
    {
        empiler(destination, pile2);
        empiler(destination, pile1);
        // afficher_deplacement(s, d, pile1);
    }
}

//Function de résolution recursive
void hanoi_recu(int n, char D, char A, char I){
    if(n == 1) printf("Disque 1 de %c \n", D ,A);
    else{
        //D a A
        hanoi_recu(n-1, D, I, A);
        printf("Disque %d de %c a %c \n", n, D, A);
        //I a A
        hanoi_recu(n-1, I, A, D);
    }
}

//Function de résolution iterative 
void hanoi_iter(int num_of_disks, struct Stack *A, struct Stack *B, struct Stack *C)
{

    unsigned long long i,nbr_deplacements;
    char s = 'A', d = 'C', a = 'B'; //s:source   d:destination  , a:intermediere

    //si nombre de disque est paire
    if (num_of_disks % 2 == 0)
    {
        char temp = d;
        d = a;
        a = temp;
    }
    nbr_deplacements = pow(2, num_of_disks) - 1;

    //empilement des disques dans la premiere pile
    for (i = num_of_disks; i >= 1; i--)
        empiler(A, i);

    for (i = 1; i <= nbr_deplacements; i++)
    {
        if (i % 3 == 1)
        deplacer_entre_deux_tours(A, C, s, d);

        else if (i % 3 == 2)
        deplacer_entre_deux_tours(A, B, s, a);

        else if (i % 3 == 0)
        deplacer_entre_deux_tours(B, C, a, d);
    }
}


int verification(struct Stack *C){

 int d1,d2;

 d1=depiler(C);

 while(!pile_vide(C)){

    d2=depiler(C);

    if(d1>d2) return 0;

    d1=d2;

 }

return 1;
}

void time_complexity(int debut ,int fin ){

    struct Stack *A, *B, *C;
    time_t t1,t2;
    double t=0;


    for (int i = debut ; i <= fin ; i+=5){

    A = init_pile(i);
    B = init_pile(i);
    C = init_pile(i);



    t1=clock();

    hanoi_iter(i ,A ,B ,C);
    //hanoi_recu(i ,A ,B ,C);

    t2=clock();

    t= (float)(t2-t1)/CLOCKS_PER_SEC;

    printf("nombre de disques = %d   -->  %f secondes\n\n",i,t);


    printf(verification(C)? "algorithme verifiee" : "algorithme non verifiee");


    free(A);
    free(B);
    free(C);
    
    }

}




int main()
{
    
    time_complexity(5,35);

    return 0;
}



// Pseudo code

// procedure hanoi_iter(A,B,C :Pile , n :entiers)

// nbr_deplacement =  2^n -1;

// si (n % 2 == 0 ) alors permuter (B,C);

// pour i de 1 a nbr_deplacment:

//   faire
//          si  (i % 3 == 1) alors
//                 deplacer(A, C)

//          sinon  si (i % 3 == 2) alors
//                  moveDisks(A, B)

//                 sinon si(i % 3 == 0) alors
//                       moveDisks(B, C);
//                 fsi;
//          fsi;

//     fait;




// procedure deplacer(source ,destinationination :Pile)

// debut

//          x = depiler(source);
//          y = depiler(destinationination);

//         // si source est vide
//         si (x==nil) alors emplier(source, y)
//         // si destinationination est vide
//         sinon si (y==nil)  empiler(destinationination, x)

//               sinon si (x > y) alors

//                           empiler(source, x);
//                           empiler(source, y);



//                       sinon

//                           empiler(destinationination, y);
//                           empiler(destinationination, x);

//                    fsi;
//              fsi;

//         fsi;

//   fin;


// Algorithme verification

// Entree => P :Pile qui represente le tour C
// sortie => Booleen

// Var  d1 , d2 :Entier;

// debut

// Depiler (P,d1);

// tant que (non pilevide(P))
//   faire

//      Depiler (P,d2);

//      si (d1>d2) alors Retourner  faux;

//       d1=d2;

//     fait;

//     retourner vrai;
//   fin;