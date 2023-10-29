#include<stdio.h> 
#include<stdlib.h>
#include<malloc.h>
#include <time.h>

struct noeud_list
{
    struct noeud *val;
    struct noeud_list *suivant;
};
struct noeud
{
    int val;
    struct noeud *suivant;
};

int taille_list(struct noeud *a);
void *creation(struct noeud *a, int x)
{
    a = malloc(sizeof(struct noeud));

    a->val = x;

    a->suivant = NULL;
    return a;
}

void *freelist1(struct noeud *a)
{
    struct noeud *q, *p;
    q = a;

    while (q != NULL)
    {
        p = q->suivant;
        free(q);
        q = p;
    }
    return NULL;
}

void *freelist2(struct noeud_list *a)
{
    struct noeud_list *a2=a;
    struct noeud_list *q, *p;
    for (int i = 0; i < 100; i++)
    {
     a->val=freelist1(a->val);
    }
    q = a2;
    while (q != NULL)
    {
        p = q->suivant;
        free(q);
        q = p;
    }
    return NULL;
}

void *display(struct noeud *a)
{
    struct noeud *q;
    if (a == NULL)
    {
        printf("chaine vide \n");
    }
    else
    {
        q = a;
        while (q != NULL)
        {
            printf("la valeur egale a %d \n", q->val);
            q = q->suivant;
        }
    }
}
void *addtofile(struct noeud **a, int x)
{
    struct noeud *q;

    q = malloc(sizeof(struct noeud));
    q->suivant = *a;
    q->val = x;
    *a = q;
}

void *addtofile2(struct noeud_list **head, struct noeud *a)
{
    struct noeud_list *q;

    q = malloc(sizeof(struct noeud_list));
    q->suivant = *head;
    q->val = a;
    *head = q;
}

void randlist(int n, struct noeud **a)
{
    for (int i = 0; i < n; i++)
    {
        addtofile(a, ((rand() % 100)));
    }
}

int chercheMax(struct noeud *a)
{ 
    int max=0;

    while(a!=NULL)
    {
       if(a->val>max)
       {
        max=a->val;
       }
       a=a->suivant;
    }
    
    return max;
 }

 void GlobalList(struct noeud_list **head)
 {
     struct noeud *tete=NULL;
     int n = 10;
     for (int i = 0; i < 100; i++)
     {
        randlist(n,&tete);
        n=n+10;
        addtofile2(head,tete);
        tete=NULL;
    }
 }

 void *display2(struct noeud_list *a)
 {
     struct noeud_list *q;
     int i=1;
     if (a == NULL)
     {
         printf("chaine vide \n");
     }
     else
     {
         q = a;
         while (q != NULL)
         {
            printf("la chaine %d , d'une taille de %d \n",i++,taille_list(q->val));
            display(q->val);
            //printf("la taile de la list est : %d",taille_list(q->val));
            printf("\n");
            q = q->suivant;
         }
     }
 }

 void *maxlists(struct noeud_list *a)
 {
     clock_t t1, t2;
     double delta;
     int max;
     struct noeud_list *q;
     int i = 1;
     if (a == NULL)
     {
         printf("chaine vide \n");
     }
     else
     {
         q = a;
         while (q != NULL)
         {
             printf("la chaine %d :\n", i++);
             t1 = clock();
             printf("le max est egale a : %d ", chercheMax(q->val));
             //max=chercheMax(q->val);
             t2 = clock();
             delta = (float)(t2 - t1) / CLOCKS_PER_SEC;
             printf("---&--- le temps dexecution est egale a : %f milliseconde", delta*1000);
             printf("\n");
             q = q->suivant;
         }
     }
 }

 int taille_list(struct noeud *a)
 {
    int i=0;
    while(a!=NULL)
    {
        i++;
        a=a->suivant;
    }
    return i;
 }
   
   
 int main()
{
    struct noeud_list *head=NULL;
    GlobalList(&head);
    //display2(head);
    maxlists(head);
    head=freelist2(head);
    return 0;
}