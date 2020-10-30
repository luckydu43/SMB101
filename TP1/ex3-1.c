#include <fcntl.h>

int d1;
d1=open("file.txt", O_WRONLY);
write(d1, "je suis eleve du Cnam", 21);
close(d1);
