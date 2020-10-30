#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int d1;
	d1=open("file.txt", O_WRONLY);
	write(d1, "je suis eleve du Cnam", 21);
	close(d1);	

	int d2;
	charr[30];
	d2=open("file.txt", O_RDONLY);
	read(d2, &r,21);
	printf("info lue:%s\n", r);
	close(d2);

return 0;
}

