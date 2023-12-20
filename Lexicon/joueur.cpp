#include <iostream>
using namespace std;

#include "jeu.h"

void initialiser(Joueur* joueurs, unsigned int nbJoueurs, Chaine& cTalon) {
	for (unsigned int i = 0; i < nbJoueurs; ++i) {
		joueurs[i].main = distribuer(cTalon);
		trier_main(joueurs[i].main);
		joueurs[i].id = i + 1;
		joueurs[i].points = 0;
	}
}

bool finPartie(const Joueur* joueurs, unsigned int nbJoueurs) {
	for (unsigned int i = 0; i < nbJoueurs; ++i) {
		if (joueurs[i].points >= 100)
			return true;
	}
	return false;
}

bool finTour(const Joueur* joueurs, unsigned int nbJoueurs) {
	for (unsigned int i = 0; i < nbJoueurs; ++i) {
		if (estVide(joueurs[i].main))
			return true;
	}
	return false;
}

void detruire(Joueur* joueurs) {
	delete[] joueurs;
	joueurs = nullptr;
}

void exclure(Joueur* joueurs, unsigned int& nbJoueurs) {
	unsigned newTaille = 0;
	for (unsigned int i = 0; i < nbJoueurs; ++i) {
		if (joueurs[i].points < 100)
			joueurs[newTaille++] = joueurs[i];
	}
	nbJoueurs = newTaille;
}