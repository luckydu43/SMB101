#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// On crée un tableau de int
int tableau[2];


// En définissant un handler au signal SIGUSR1, en cas de levée de ce signal, le programme
// fils peut continuer après sa pause, qui est levée par un signal SIGUSR1 à notre demande.
void handlerSigUSR1(int signum) {
	int r;
	printf("----fils----On ferme la deuxième valeur du tube\n");
	close(tableau[1]);
	printf("----fils----On lit la première valeur du tube\n");
	read (tableau[0], &r, sizeof(r));
	printf("----fils----On ferme la première valeur du tube\n");
	close (tableau[0]);
	printf("----fils----Valeur lue : %d\n", r);
}
int main() {
	printf("Ecriture avec lecteur par le père pour le fils\n");
	// On définit p entier.
	int p;
	//On initialise le int s à 34
	int s=34;
	// On place le tableau dans un tube grâce à la fonction pipe
	pipe(tableau);

	// A ce moment, on crée un processus fils, doublon exact du père...
	p = fork();

	//... à la seule différence que fork() renvoie une valeur 0 à p si le processus est le 
	//fils.
	// On exploite ceci ici :
	if (p==0) {
		//p ne vaut 0 que si c'est le processus fils, cette condition ne concerne donc pas
		//le père.
		signal (SIGUSR1, handlerSigUSR1);
		pause();
	} else {
		// p ne vaut pas 0 si c'est le processus père, cette condition ne concerne donc
		// pas le fils.
		
		// Essentiel ! Il faut une pause. Autrement, le programme père finit avant
		// que le programme fils ne soit prêt à recevoir le signal SIGUSR1
		printf("Attente d'une seconde...\n");
		sleep(1);

		printf("----père----On ferme la première valeur du tube\n");
		close (tableau[0]);
		printf("----père----On écrit la valeur %d dans la deuxième valeur du tube\n", s);
		write(tableau[1], &s, sizeof(s));  // Ceci lève un SIGPIPE, signal d'écriture sans lecteur
		printf("----père----On ferme la deuxième valeur du tube\n");
		close (tableau[1]);
		printf("----père----écriture terminée\n");
		// On lance un signal SIGUSR1 au processus numéro p, donc 0, donc le fils.
		kill(p, SIGUSR1);
	}
	printf("Fin du programme\n");
}
