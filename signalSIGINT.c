#include <stdio.h>
#include <signal.h>

// Une fonction utilisée comme handler :
// - est TOUJOURS VIDE 
// - a en paramètre void ou int.
// Dans le cas d'un int, il contiendra le code du signal.
// Dans notre cas, ce sera le code du signal SIGINT, donc 2
void hand(int signum) {
	printf(" OK, tu as appuyé sur CTRL+C\n");
	printf("Je le sais parce que je m'attendais à recevoir un signal SIGINT et que ça n'a pas loupé... \n");
	printf("...preuve ?! Voici le code signal que j'ai reçu : %d\n", signum);
	printf("... c'est 2 hein ! Donc ça veut dire SIGINT donc CTRL+C. Eh ouais mon gars.\n");
	printf("Reessaie encore\n");
	printf("Tkt, la j'arrete, je te laisse me killer tranquillou\n");
	// Redéfinit SIG_INT en lui associant le handler par défaut
	// signal() n'envoie pas de signal ! kill() le fait.
	// SIGINT correspond à CTRL+C
	// Si je ne redéfinis pas à SIGINT, je suis bon pour retrouver
	// le numéro du process et me taper un SIGKILL des familles
	// sans quoi ce process tournera indéfiniment.
	// PROCÉDURE :
	// dans un autre terminal (vu que celui-ci est bloqué) :
	// - ps -l | grep "nomprogramme"
	// - kill -9 pid
	// le tiret 9 envoie un SIGKILL
	// Le handler du SIGKILL ne peut être changé donc je suis certain de l'arrêter
	signal(SIGINT, SIG_DFL);
	// Au lieu de redéfinir le signal SIGINT, on peut tout aussi bien arrêter le programme
	// exit(0);
}

int main (void) {
	// Redéfinit SIG_INT en lui associant la fonction hand comme handler
	// signal() n'envoie pas de signal ! kill() le fait.
	// SIGINT correspond à CTRL+C
	signal(SIGINT, hand);
	// boucle infinie
	for (;;) { }
	// Cette ligne ne sera JAMAIS appelée, y a une boucle infinie avant
	return 0;
}
