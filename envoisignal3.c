#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int t[2];
void hand (int s) {
int r;
printf("lecture du tube\n");
close (t[1]);
read (t[0], &r, sizeof(r));
close (t[0]);
printf("valeur lue: %d\n", r);
}

void main() {

 int p; int s=34;
pipe(t);
p=fork();
if (p==0) {
signal (SIGUSR1, hand);
pause();
}
else {
//ecriture sans lecteur
printf("debut ecriture de %d\n", s);
close (t[0]);
write (t[1], &s, sizeof(s));
close (t[1]);
printf("ecriture terminee\n");
kill(p, SIGUSR1);
}
}
