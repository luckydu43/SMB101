#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

/*TD 30102020 : Ex.2 :OK*/
int main(void)
{
int p; int d1; int d2; char r[30];
p = fork();


 if(p == 0) {
d1=open("file.txt", O_WRONLY);
write(d1, "je suis eleve du Cnam", 21) ;
close(d1) ;
}


 if(p > 0)
{
wait(NULL);
d2=open("file.txt", O_RDONLY);
read(d2, &r, 21) ;
printf("info lue :%s\n", r) ;
close(d2) ;
}


if(p < 0)printf("Probleme de creation par fork()\n");


 return 0;
}

