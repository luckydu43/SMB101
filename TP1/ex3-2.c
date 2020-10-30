#include <fcntl.h>

int d2;
charr[30];
d2=open("file.txt", O_RDONLY);
read(d2, &r,21);
printf("info lue:%s\n", r);
close(d2);
