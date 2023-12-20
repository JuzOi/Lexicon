#ifndef _JEU_
#define _JEU_

#include "table.h"
#include "dico.h"

struct Joueur {
	Chaine main;
	unsigned int id;
	unsigned int points;
};

void initialisation(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur* joueurs, unsigned int nbJoueurs);

void destruction(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur* joueurs, unsigned int nbJoueurs);

bool finPartie(const Joueur* joueur, unsigned int nbJoueurs);

bool finTour(const Joueur* joueurs, unsigned int nbJoueurs);

void partie(Joueur* joueurs, unsigned int& nbJoueurs, Dico& dico);

void tour(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur* joueurs, unsigned int nbJoueurs, Dico& dico);

void supercmd(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int nbmots, char cmd, Dico& dico);

void erreur(unsigned int n);

void detruire(Joueur* joueurs);

void exclure(Joueur* joueurs, unsigned int& nbJoueurs);

void cmdTalon(Chaine& cTalon, Chaine& cExposee, Chaine& cJoueur);

void cmdExposee(Chaine& cExposee, Chaine& cJoueur);

void cmdPoser(Table& table, Joueur& joueur, unsigned int& nbmots, Dico& dico);

void debugPoser(Table& table, Joueur& joueur, unsigned int& nbmots, Dico& dico);

#endif