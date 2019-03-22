#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#define EPSILON 1e-5

long int temps = 1;
long int tempsvide = 0;
long int n = 0;	//nombre de clients dans la file a l'instant temps
long int cumul = 0; //nombre de clients au totale a l'instant temps
int arret = 1e6;	//cond d'aret
int compteur = 0; //cond d'arret

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

void Arrive_Event(){
	n += nb_arrivees(0.4,0.35); //une arrivée

	cumule += n; //pour calculer la moyenne
}

void Service_Event() {
	if (n > 0) // un service a enlever
	{
		n--;
		arret--;
	}


void Simulateur(FILE*f1) {
	//long double OldNmoyen
	long double Nmoyen;
	
	while (arret > 0) //Condition_arret(OldNmoyen,Nmoyen) == 0)
	 {
		Arrive_Event();
		//OldNmoyen = Nmoyen;
		Nmoyen = (long double)cumule/temps;
		fprintf(f1, "%5ld   %Lf \n", temps, Nmoyen);
		//File_vide();
		Service_Event();
		temps++;
	}
	//printf("P(n = 0) = %f \n",(double)tempsvide/temps);
}

//~ void fileattente() {
	//~ int nbclients = 10;
	//~ clientsortie = 0;
	//~ while (clientsortie < 100) {
		//~ nbclients+=nb_arrivees(0.4, 0.35)
	//~ }
//~ }

int main(int argc, char *argv[]) {
	
	FILE f1 = fopen("Simulation_CST.data","w");
	srandom(getpid() + time(NULL));
	Simulateur(f1);
	fclose(f1);
	exit(0);
	
	//~ for(int i = 0; i < 10; i++){
		//~ long int a = random()%10;
		//~ printf("%ld\n",a);
	//~ }
	
}
