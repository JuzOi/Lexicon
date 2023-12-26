#ifndef _PAQUET_
#define _PAQUET_

const unsigned int MAIN = 10, NB_LETTRE = 26, NB_CARTE = 51;

struct Carte {
	char lettre;
	unsigned int points;
};

struct Paquet {
	unsigned int taille;
	Carte* carte;
};

Paquet jeu_base();

int random_nbr(int max);

void initialiser(Paquet& paquet, unsigned int taille);

void ecrire(Paquet& paquet, unsigned int index, const Carte& carte);

void echanger(Carte& c1, Carte& c2);

void melanger(Paquet& paquet);

void detruire(Paquet& paquet);

void trier(Paquet& paquet);

#endif