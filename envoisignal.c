#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
void hand(int signum)
{
printf("appui sur Ctrl-C\n");
printf("Arret au prochain coup\n");
signal(SIGINT, SIG_DFL);
}
*/

int main(void)
{
signal(SIGINT, SIG_IGN);
while(1);
return 0;
}
