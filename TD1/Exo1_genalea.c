#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


int main() {
	
	srandom(getpid() + time(NULL));
	
	for(int i = 0; i < 10; i++){
		long int a = random();
		printf("%ld\n",a);
	}
}
