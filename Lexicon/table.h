#ifndef _TABLE_
#define _TABLE_

#include "chaine.h"


/** @brief Conteneur d'items alloués en mémoire dynamique
 *  de capacité extensible suivant un pas d'extension
 */
struct Table {
	unsigned int capacite;
	unsigned int pasExtension;
	Chaine* mot;
};

void initialiser(Table& t, unsigned int c, unsigned int p);

void detruire(Table& t);

void ecrire(Table& t, unsigned int i, const Chaine& mot);

void afficher(const Table& t, unsigned int n);

#endif