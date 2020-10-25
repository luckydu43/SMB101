#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void Hand_sigfpe() {
printf("\nErreur division par 0 !\n");
exit(1);
}
main() {
int a, b, Resultat;
signal(SIGFPE, Hand_sigfpe);
printf("Taper a : "); scanf("%d", &a);
printf("Taper b : "); scanf("%d", &b);
Resultat = a/b;
printf("La division de a par b = %d\n", Resultat);
}
