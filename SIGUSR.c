#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

void main(void) {
	pid_t p;
	int etat;
	// p = fork() crée un processus fils, doublon du père
	// p vaut 0 seulement si c'est le processus fils.
	// Le code suivant ne concerne donc pas le père.
	if ((p=fork()) == 0) { /* processus fils qui boucle */
		while (1);
		exit(2);
	}
	// Le père peut donc exécuter le code suivant.
	/* processus pere */
	// Il attend 2 secondes
	sleep(2);

	printf("envoi de SIGUSR1 au fils %d\n", p);
	
	// Il envoie un signal au fils. Le traitement par défaut est un arrêt.
	kill(p, SIGUSR1);
	// bloque l'appelant (pere) et selectionne le fils
	// Il attend pour son fils mais son fils s'arrête. Il peut alors,
	// après l'arrêt du fils, passer à la ligne suivante.
	p = waitpid(p, &etat, 0);
	printf("etat du fils %d : %d\n", p, etat >> 8);
}
