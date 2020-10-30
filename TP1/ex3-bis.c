#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int  main() {
    int d;
    char r[30];

    if (fork()==0) {
        d=open("file.txt", O_CREAT | O_WRONLY,0640);
        printf("Je suis le processus fils (ecrivain):%d\n",getpid());
        write(d,"je suis eleve du Cnam", 21);
        close(d);
    } else {
	wait(NULL);
        d=open("file.txt",  O_RDONLY);
        printf("Je suis le processus père(lecteur):%d\n",getpid());
        read(d, &r,21);
        printf("info lue:%s\n", r);
        close(d);
    }
}
