#include <stdio.h>
#include <unistd.h>

void zing(){
	char *a;
	if ((a = getlogin()) == NULL){
		printf("Failed to get login\n");
	}

	write(1,"Hi ",3);
	write(1,a,2*sizeof(a));
	write(1,"!\n",2);
}
