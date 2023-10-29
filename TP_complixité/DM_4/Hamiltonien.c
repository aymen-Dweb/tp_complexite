#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define V 9



void dfs_voy_com(int graph[][V], bool v[], int currPos, int n, int count, int cost, int *ans)
{
    // a la fin return to check la valeur minumum
    if (count == n && graph[currPos][0]) {
        if(*ans>cost + graph[currPos][0]){
            *ans=cost + graph[currPos][0];
        }
        
        return;
    }
    
    //n nmbr de sommets //parcour de graphe et verifier si le noeud et deja visité 
    for (int i = 0; i < n; i++) {
        if (!v[i] && graph[currPos][i]) {
            v[i] = true;
            dfs_voy_com(graph, v, i, n, count + 1, cost + graph[currPos][i], ans);
            v[i] = false;
        }
    }
}


int main()
{
    // nombre de niveau
    int n = 9; int i ;

    int graph[][V] = {
        {0,10,0,0,0,0,0,50,15},
        {10,0,15,10,0,0,0,0,20},
        {0,15,0,10,10,20,0,0,0},
        {0,10,10,0,15,0,10,0,30},
        {0,0,10,15,0,10,0,0,0},
        {0,0,20,0,10,0,10,20,0},
        {0,0,0,10,0,10,0,15,0},
        {50,0,0,0,0,0,15,0,20},
        {15,20,0,30,0,0,0,20,0}
    };

    //init
    bool v[n];
    for ( i = 0; i < n; i++) {v[i] = false;}
    v[0] = true;
    int ans = 1000;

    // Find the minimum weight Hamiltonian Cycle
    dfs_voy_com(graph, v, 0, n, 1, 0, &ans);

    //printf("la plus courte distance est %d\n",min);
    printf("\n\n----> la plus courte distance est %d\n\n\n",ans); 

    return 0;
}
