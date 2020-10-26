#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void hand (int s) {
printf("signal num: %d -ecriture non autorisee car pas de lecteur\n", s);
}

void main() {

 int t[2];
int s=34;
pipe(t);
//ecriture sans lecteur
printf("debut ecriture\n");
signal (SIGPIPE, hand);
close (t[0]);
write (t[1], &s, sizeof(s)); // signal SIGPIPE genere
close (t[1]);
printf("ecriture terminee\n");
}
