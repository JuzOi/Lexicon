#ifndef _JEU_
#define _JEU_

#include "dico.h"
#include "joueur.h"

void initialisation(Table& table, Chaine& cTalon, Chaine& cExposee, ConteneurJ& cJoueurs);

void destruction(Table& table, Chaine& cTalon, Chaine& cExposee);

void partie(ConteneurJ& cJoueurs, const Dico& dico);

void tour(Table& table, Chaine& cTalon, Chaine& cExposee, ConteneurJ& cJoueurs, unsigned int& i, unsigned int& nbmots, const Dico& dico);

void afficherEtat(const Table& table, const Chaine& cExposee, Joueur& joueur, const unsigned int& nbmots);

void reprise(Chaine& cTalon, Chaine& cExposee);

void supercmd(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico);

void erreur(unsigned int n, Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico);

void cmdTalon(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico);

void cmdExposee(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico);

void cmdPoser(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico);

void cmdRemplacer(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico);

void cmdCompleter(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico);

#endif