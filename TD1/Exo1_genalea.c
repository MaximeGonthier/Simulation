#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int bernoulli(double p) {
	double r = (double)random()/RAND_MAX;
	if (r < p) {
		return 1;
	}
	return 0;
}

int nb_arrivees (double p0, double p2) {
	double p1 = 1 - p0 - p2;
	double r = (double)random()/RAND_MAX;
	
	if(r < p0) {
		return 0; }
		else { if (r < p0 + p1) { return p1;}
			else { return 2; }
			}
		
}

int main() {
	
	srandom(getpid() + time(NULL));
	
	for(int i = 0; i < 10; i++){
		long int a = random()%10;
		printf("%ld\n",a);
	}
	
}
