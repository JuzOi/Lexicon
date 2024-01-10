#ifndef _DICO_
#define _DICO_

#include "paquet.h"

const int NB_MOTS = 369085;

struct Dico {
	char** mot;
	unsigned int capa;
};

void initialiser(Dico& dico, unsigned int nbmots, unsigned int nblettres);

bool rechercherDico(const Dico& dico, char* mot);

void chargerDico(Dico& dico, istream& in);

void detruire(Dico& dico);

#endif