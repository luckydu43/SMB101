#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// En définissant un handler au signal SIGPIPE, en cas de levée de ce signal, le programme
// peut continuer, sans être stoppé par le comportement par défaut du signal.
// On peut toujours l'arrêter, cf la ligne en commentaire dans ce handler
void handlerSigpipe(int signum) {
	printf("UN SIGPIPE A ETE LEVE !!!!!!\n");
	// exit(0);
}
int main() {

	// On redéfinit le handler par défaut du signal SIGPIPE.
	signal(SIGPIPE, handlerSigpipe);
	// On crée un tableau de int
	int tableau[2];
	//On initialise le int s à 34
	int s=34;
	// On place le tableau dans un tube grâce à la fonction pipe
	pipe(tableau);

	printf("Ecriture sans lecteur\n");
	
	printf("------------On ferme l'accès à la première valeur du tube\n");
	close (tableau[0]);
	printf("------------On écrit dans la deuxième valeur du tube\n");
	write(tableau[1], &s, sizeof(s));  // Ceci lève un SIGPIPE, signal d'écriture sans lecteur
	printf("------------On ferme l'accès à la deuxième valeur du tube\n");
	close (tableau[1]);
	printf("écriture terminée\n");
}
