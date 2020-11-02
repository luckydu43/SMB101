/* prodconsThread.c avec des threads*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

#define Ncases 10   /* nbr de cases du tampon */

int Tampon[Ncases]; /* Tampon a N cases*/
sem_t Snvide, Snplein;/* les semaphores*/

void * Producteur(void) {
    int i, queue = 0, MessProd;
    srand(pthread_self());
    for (i=0; i<20; i++) {
        sleep(rand()%3);   /* fabrique le message */
        MessProd = rand() % 10000;
        printf("Product %d\n",MessProd);
        sem_wait(&Snvide);
        Tampon[queue]=MessProd;
        sem_post(&Snplein);
        queue=(queue+1)%Ncases;
    }
    pthread_exit(0);
}

void * Consommateur(void) {
    int tete=0, MessCons, i;
    srand(pthread_self());
    for(i=0; i<20; i++) {
        sem_wait(&Snplein);
        MessCons= Tampon[tete];
        sem_post(&Snvide);
        tete=(tete+1)%Ncases;
        printf("\t\tConsomm%d \n",MessCons);
        sleep(rand()%3);   /* traite le message */
    }
    pthread_exit(0);
}

int main(void) {
    pthread_t th1, th2;
    /* creation et initialisation des semaphores*/
    sem_init(&Snvide, 0, Ncases);
    sem_init(&Snplein, 0, 0);
    /* creation des threads  */
    pthread_create(&th1, 0, (void*) Producteur, NULL);
    pthread_create(&th2, 0, (void*) Consommateur, NULL);
    /* attente de terminaison */
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    /* suppression des semaphores*/
    sem_destroy(&Snplein);
    sem_destroy(&Snvide);
    return (0);
}
