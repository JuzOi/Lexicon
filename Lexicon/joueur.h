#ifndef _JOUEUR_
#define _JOUEUR_

#include "table.h"

struct Joueur {
	Chaine main;
	unsigned int id;
	unsigned int points;
};

struct ConteneurJ {
	Joueur* joueur;
	unsigned int nbJoueurs;
};

void initialiser(ConteneurJ& cJoueurs, unsigned int nbJoueurs);

void distribution(ConteneurJ& cJoueurs, Chaine& cTalon);

bool finPartie(const ConteneurJ& cJoueurs);

bool finTour(const ConteneurJ& cJoueurs);

void detruire(ConteneurJ& cJoueurs);

void exclure(ConteneurJ& cJoueurs);

#endif