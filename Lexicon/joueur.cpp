#include <iostream>
using namespace std;

#include "jeu.h"

void initialiser(ConteneurJ& cJoueurs, unsigned int nbJoueurs) {
	cJoueurs.nbJoueurs = nbJoueurs;
	cJoueurs.joueur = new Joueur[nbJoueurs];
	for (unsigned int i = 0; i < nbJoueurs; ++i) {
		cJoueurs.joueur[i].id = i + 1;
		cJoueurs.joueur[i].points = 0;
	}
}

void distribution(ConteneurJ& cJoueurs, Chaine& cTalon) {
	for (unsigned int i = 0; i < cJoueurs.nbJoueurs; ++i) {
		cJoueurs.joueur[i].main = distribuer(cTalon);
		trierPaquet(cJoueurs.joueur[i].main);
	}
}

bool finPartie(const ConteneurJ& cJoueurs) {
	for (unsigned int i = 0; i < cJoueurs.nbJoueurs; ++i) {
		if (cJoueurs.joueur[i].points >= 100)
			return true;
	}
	return false;
}

bool finTour(const ConteneurJ& cJoueurs) {
	for (unsigned int i = 0; i < cJoueurs.nbJoueurs; ++i) {
		if (estVide(cJoueurs.joueur[i].main))
			return true;
	}
	return false;
}

void detruire(ConteneurJ& cJoueurs) {
	delete[] cJoueurs.joueur;
	cJoueurs.joueur = nullptr;
}

void exclure(ConteneurJ& cJoueurs) {
	unsigned int  j = 0;
	for (unsigned int i = 0; i < cJoueurs.nbJoueurs; ++i) {
		if (cJoueurs.joueur[i].points < 100)
			cJoueurs.joueur[j++] = cJoueurs.joueur[i];
	}
	cJoueurs.nbJoueurs = j;
}