#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <semaphore.h>
#include<pthread.h>

sem_t S;
int d2; char r[30]="";
int d1;

void * Lecture (void) {
sem_wait(&S);
d2=open("file.txt", O_RDONLY);
read(d2, &r, 21) ;
printf("thread - info lue :%s\n", r) ;
close(d2) ;
}

void * Ecriture (void) {
d1=open("file.txt", O_WRONLY);
write(d1, "je suis eleve du Cnam", 21) ;
close(d1) ;
printf(" thread ecriture: fin de l'ecriture \n");
sem_post(&S);
}

main()
{

pthread_t th1, th2;
/* creation et initialisation des semaphores*/
sem_init(&S, 0, 0);
/* creation des threads */
pthread_create(&th1, 0, (void*) Lecture, NULL);
pthread_create(&th2, 0, (void*) Ecriture, NULL);
/* attente de terminaison */
pthread_join(th1, NULL);
pthread_join(th2, NULL);
/* suppression des semaphores*/
sem_destroy(&S);

}
