#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define Lambda 9
#define Mu 10

#define EPSILON 1e-5
#define MAXEVENT 1000000	//taille max de l'echeancier
#define MAXTEMPS 5000	//cond d'arret

double temps = 0;
long int n = 0;		//nb de clients dans la file a l'instant temps
int compteur = 0;	//cond d'arret 2
double cumule = 0;

typedef struct Event {
	int type; //0 pour arrive 1 pour sortie
	double date;
	int etat; //0 pour non traité 1 pour non traité
}event;

typedef struct Echeancier {
	event TAB[MAXEVENT];
	int taille;
}echeancier;

echeancier Ech;

double Exponnentielle(int lbda) {
	double r = (double)random()/RAND_MAX;	//entre 0 et 1
	
	while(r==0 || r==1) {	//tant que x vaut 0 ou 1 on refait un random
		r = (double)random()/RAND_MAX;
	}
	return -log(r)/(lbda*1.0); // - log(u)/lamda, avec U = unif(0,1)
}

void Ajouter_Ech(event e) {
	if(Ech.taille < MAXEVENT) {
		Ech.Tab[Ech.taille] = e;
		Ech.taille++;
		printf("Taille = %d\n", Ech.taille);
	}
	else (printf("echeancier PLEIN");)
}

void Init Ech(){
	event e;
	e.type = 0;
	e.date = 0;
	e.etat = 0;
	Ech.taille = 0;
	Ajouter_Ech(e);
}

void Arrive_Event(event e) {
	printf("execution Arrivé Client\n");
	n++;
	
	event e1;
	e1.type = 0;
	e1.date = e.date + Exponnentielle(Lambda);
	e1.etat = 0;
	
	Ajouter_Ech(e1);
	
	if (n == 1) {
		event e2;
		e2.type = 1;
		e2.date = e.date + Exponnentielle(Mu);
		e2.etat = 0;
		
		Ajouter_Ech(e2);
	}
	
	temps = e.date;
	
}

void Service_Event(event e)	//service = Mu
{
	if (n>0) {
		n--;
		e.type = 1;
		e.date = e.date + Exponnentielle(Mu);
		e.etat = 0;
		
		Ajouter_Ech(e1);
	}
	temps = e.date;
}

event Extraire() {
	int i,imin;
	event min;
	
	for (i = 0; i < Ech.taille; i++) {
		if(Ech.Tab[i].etat == 0) {
			min = Ech.Tab[i];
			imin = i;
			break;
		}
	}
	for (i = 0; i < Ech.taille; i++) {
		if(min.date > Ech.Tab[i].date && Ech.Tab[i].etat == 0) {
			min = Ech.Tab[i];
			imin = i;
		}
	}
	
	Ech.Tab[imin].etat = 1;
	return min;
}

	
	
