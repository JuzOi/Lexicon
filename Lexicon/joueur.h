#ifndef _JOUEUR_
#define _JOUEUR_

#include "table.h"

struct Joueur {
	Chaine main;
	unsigned int id;
	unsigned int points;
};

void initialiser(Joueur* joueurs, unsigned int nbJoueurs, Chaine& cTalon);

bool finPartie(const Joueur* joueur, unsigned int nbJoueurs);

bool finTour(const Joueur* joueurs, unsigned int nbJoueurs);

void detruire(Joueur* joueurs);

void exclure(Joueur* joueurs, unsigned int& nbJoueurs);

#endif