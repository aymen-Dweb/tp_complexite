#include<stdio.h> 
#include<stdlib.h>
#include<malloc.h>
#include <time.h>

struct noeud
{
    int val;
    struct noeud *suivant;
};

void *freelist(struct noeud *a)
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

void *addtofile(struct noeud **a, int x)
{
    struct noeud *q;
    q = malloc(sizeof(struct noeud));
    q->val = x;
    q->suivant = NULL;


    if (*a != NULL) /* La file n'est pas vide */
    {
        struct noeud *elementActuel = *a;
        while (elementActuel->suivant != NULL)
            {
                elementActuel = elementActuel->suivant;
            }
        elementActuel->suivant = q;
    }
    else /* La file est vide, notre élément est le premier */
    {
        *a = q;
    }
}

void *addtopile(struct noeud **a, int x)
{
    struct noeud *q;
    q = malloc(sizeof(struct noeud));

    q->val = x;
    q->suivant = *a;
    *a = q;
}

void range_insert(int n, struct noeud **a)
{
    int i = n;
    while(i > 0)
    {
        addtopile(a, i); 
        i--;
    }
}

void range_append(int n, struct noeud **a)
{
    int i = 1;
    while(i < n+1)
    {
        addtofile(a, i); 
        i++;
    }
}
 
void *display(struct noeud *a)
{
    struct noeud *q;
    if (a == NULL)
    {
        printf("---------------- EMPTY LIST! ---------------- \n");
    }
    else
    {
        q = a;
        while (q != NULL)
        {
            int i=i+1;
            printf("la valeur [%d] = %d \n", i, q->val);
            
            q = q->suivant;
        }
    }
}

void TimeInsert(int n, struct noeud **a){
    clock_t t1, t2;
    double delta;

    t1 = clock();
    range_insert(n, a);
    t2 = clock();
    delta = (float)(t2 - t1) / CLOCKS_PER_SEC;
    printf("---> le temps dexecution 'RANGE_INSERT' === %f milliseconde", delta*1000);
}

void TimeAppend(int n, struct noeud **a){
    clock_t t1, t2;
    double delta;

    t1 = clock();
    range_append(n, a);
    t2 = clock();
    delta = (float)(t2 - t1) / CLOCKS_PER_SEC;
    printf("---> le temps dexecution 'RANGE_APPEND' ===  %f milliseconde \n", delta*1000);
}

int main()
{
    struct noeud *head=NULL;
    int n;
    printf("\nDonner la taille de la liste ----> \t");
    scanf("%d",&n);

do
{
    TimeAppend(n, &head);
    //printf("la chaine with 'RANGE_APPEND'------------------------------------------- :\n");
    //display(head);
    head=freelist(head);

    TimeInsert(n, &head);
    //printf("la chaine with 'RANGE_INSERT'------------------------------------------- :\n");
    //display(head);
    head=freelist(head);

    printf("\n\nDonner la taille de la liste ----> \t");
    scanf("%d",&n);
    
} while (n!=0);

    printf("------------------------------------------ FIN ----------------------------");
    return 0;
}