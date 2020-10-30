#include <stdio.h>
#include <unistd.h>

int main(){
	// Le père fait ça
	int p1, p2, p3;
	p1=fork();
	// Le père et p1 font ça, p1 va donc créer un fork p2, on l'appellera p1.p2
	p2=fork();
	// Le père, p1, p2 et p1.p2 font ça
	if (p2==0) {
		// Le père et p1 ne rentrent pas ici parce qu'ils ont créé un fork.
		// p2 et p1.p2 vont par contre créer un fork, qu'on appellera p2.p3 et
		// p1.p2.p3 respectivement
		p3=fork();
	}
	// Le programme se termine avec donc 6 processus : père, p1, p2, p1.p2, p2.p3 et p1.p2.p3
	printf("je suis un process crée\n");
return 0;
}

