#ifndef _JEU_
#define _JEU_

#include "dico.h"
#include "joueur.h"

void initialisation(Table& table, Chaine& cTalon, Chaine& cExposee, ConteneurJ& cJoueurs);

void destruction(Table& table, Chaine& cTalon, Chaine& cExposee, ConteneurJ& cJoueurs);

void partie(ConteneurJ& cJoueurs, Dico& dico);

void tour(Table& table, Chaine& cTalon, Chaine& cExposee, ConteneurJ& cJoueurs, Dico& dico);

void supercmd(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, char cmd, Dico& dico);

void erreur(unsigned int n);

void cmdTalon(Chaine& cTalon, Chaine& cExposee, Chaine& cJoueur);

void cmdExposee(Chaine& cExposee, Chaine& cJoueur);

void cmdPoser(Table& table, Joueur& joueur, unsigned int& nbmots, Dico& dico);

void debugPoser(Table& table, Joueur& joueur, unsigned int& nbmots, Dico& dico);

#endif