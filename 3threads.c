/* Trois_Th.c*/
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int compteur[3];

/* fonction executeepar chaque thread */
void *fonc_thread (void *k){
printf("Thread numero %d \n",(int) k);
for(;;)
compteur[(int) k]++;
}

main() {
int i, num;

pthread_t tid[3];

 // creation des 3 threads
for(num=0;num<3;num++) {
pthread_create(&tid[num], 0, fonc_thread,(void*) num);
printf("Main: thread numero%d creee: id = %p\n",num, tid[num]);
}
usleep(10000); /* attente de 10 ms */
printf("Affichage des compteurs\n");
for(i=0;i<20; i++) {
printf("%d \t%d \t%d\n", compteur[0], compteur[1], compteur[2]);
usleep(1000);
/* attente de 1 ms entre 2 affichages */
}
exit(0);
}
