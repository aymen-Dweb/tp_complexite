#include<stdio.h>
#include<time.h>
#include<math.h>




int algo1 (long int nbr){

for (long int i=2 ; i<=nbr-1; i++){
      
      if(nbr % i == 0) return 0;
      
}

return 1;
}

int algo2 (long int nbr){

for ( long int i=2 ; i<=nbr/2; i++){
      
      if(nbr % i == 0) return 0;
      
}

return 1;
}

int algo3 (long int nbr){

if((nbr != 2) && (nbr%2 == 0)) return 0;

else{

if (nbr != 2){

for ( long int i=3 ; i<=nbr-2; i+=2){
      
      if(nbr % i == 0) return 0;
    
                                   }
             }
     }
     
return 1;     
}


int algo4 (long int nbr){

if((nbr != 2) && (nbr%2 == 0)) return 0;

else{

if (nbr != 2){

for ( long int i=3 ; i<=nbr/2; i+=2){
      
      if(nbr % i == 0) return 0;
    
                                   }
             }
     }
return 1;  
}

int algo5 (long int nbr){



for ( long int i=2 ; i<=sqrt(nbr); i++){
      
      if(nbr % i == 0) return 0;
      
}
return 1;
}

int algo6 (long int nbr){

if((nbr != 2) && (nbr%2 == 0)) return 0;

else{

if (nbr != 2){

for ( long int i=3 ; i<=sqrt(nbr); i+=2){
      
      if(nbr % i == 0) return 0;
    
                                   }
             }
     }
return 1;  
}


// la tache 1 du tp

void tache01(){

long int primes[5]= {7919,104729,24512053,1705483033,531652262162};

double delta;

clock_t t1,t2;


for (int i =0 ;i<3;i++){

printf("-------------------------------------\n");
printf("le nombre premier  => %ld\n",primes[i]);
printf("-------------------------------------\n\n");
///////////


printf("algo 1 :");

t1 =clock();

algo1(primes[i]);

t2 = clock();

delta = (t2-t1)/CLOCKS_PER_SEC;

printf(" %f \n\n",delta);

///////////////

printf("algo 2 :");

t1 =clock();

algo2(primes[i]);

t2 = clock();

delta = (t2-t1)/CLOCKS_PER_SEC;

printf(" %f \n\n",delta);

//////////////

printf("algo 3 :");

t1 =clock();

algo3(primes[i]);

t2 = clock();

delta = (t2-t1)/CLOCKS_PER_SEC;

printf(" %f \n\n",delta);

////////////////

printf("algo 4 :");

t1 =clock();

algo4(primes[i]);

t2 = clock();

delta = (t2-t1)/CLOCKS_PER_SEC;

printf(" %f \n\n",delta);

/////////////

printf("algo 5 :");

t1 =clock();

algo5(primes[i]);

t2 = clock();

delta = (t2-t1)/CLOCKS_PER_SEC;

printf(" %f \n\n",delta);

/////////////
printf("algo 6 :");

t1 =clock();

algo6(primes[i]);

t2 = clock();

delta = (t2-t1)/CLOCKS_PER_SEC;

printf(" %f \n\n",delta);

}



}




int main(){

//tester les algo
/*
printf(algo1(7919) ==1 ? "premier\n":"non premier\n");
printf(algo2(7919) ==1 ? "premier\n":"non premier\n");
printf(algo3(7919) ==1 ? "premier\n":"non premier\n");
printf(algo4(7919) ==1 ? "premier\n":"non premier\n");
printf(algo5(7919) ==1 ? "premier\n":"non premier\n");
printf(algo6(7919) ==1 ? "premier\n":"non premier\n");
*/


tache01();




}
