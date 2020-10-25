#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <fcntl.h>


struct donnees { int nb; int total; };
struct donnees *commun;
int id;

void hand(int s) {
printf("---\n");
shmdt((char*) commun); /* détachement du segment */
shmctl(id, IPC_RMID, NULL); /* suppression segment */
exit(0);

}

int main(void) {

 key_t cle; // dans stdlib.h

int reponse;
cle = ftok("toto.txt", 12);
id = shmget(cle, sizeof(struct donnees), IPC_CREAT | IPC_EXCL | 0666);
commun = (struct donnees *) shmat(id, NULL, 0); // shm.h
commun->nb = 0;
commun->total = 0;
signal(SIGINT, hand);
while(1) {
printf("+ ");
scanf("%d", &reponse);
commun->nb++;
commun->total += reponse;
printf("sous-total %d = %d\n", commun->nb, commun->total);
}
return 0;
}
