#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int d;
char r[30]="";

void hand (int s) {
        printf("Lecture du fichier\n");
        d=open("file.txt",  O_RDONLY);
        printf("Je suis le processus fils (lecteur):%d\n",getpid());
        read(d, &r,21);
        printf("info lue:%s\n", r);
        close(d);
}

int  main() {
	int p;
	if (fork()==0) {
		signal (SIGUSR1,hand);
		pause();
		//sleep(10);
	} else {
		d=open("file.txt", O_CREAT | O_WRONLY,0640);
		printf("Je suis le processus pere (ecrivain):%d\n",getpid());
		write(d,"je suis eleve du Cnam", 21);
		close(d);
		printf("ecritureterminee\n");
		kill(p,SIGUSR1);
		wait(NULL);
	}
}
