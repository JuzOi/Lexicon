#include <iostream>
#include <cassert>
using namespace std;

#include "table.h"

/**Z
 * @brief Initialise un conteneur d'items
 * Allocation en m�moire dynamique du conteneur d'items
 * de capacit� (capa) extensible par pas d'extension (p)
 * @see detruire, pour sa d�sallocation en fin d'utilisation
 * @param[out] c : le conteneur d'items
 * @param [in] capa : capacit� du conteneur
 * @param [in] p : pas d'extension de capacit�
 * @pre capa>0 et p>0
 */
void initialiser(Table& t, unsigned int capa, unsigned int p) {
	assert((capa > 0) && (p > 0));
	t.capacite = capa;
	t.pasExtension = p;
	t.mot = new Chaine[capa];
}

/**
 * @brief D�salloue un conteneur d'items en m�moire dynamique
 * @see initialiser, le conteneur d'items a d�j� �t� allou�
 * @param[out] c : le conteneur d'items
 */
void detruire(Table& t) {
	delete[] t.mot;
	t.mot = NULL;
}

Chaine lire(Table& t, unsigned int i) {
	return t.mot[i];
}

/**
 * @brief Ecrire un item dans un conteneur d'items
 * @param[in,out] c : le conteneur d'items
 * @param[in] i : la position o� ajouter/modifier l'item
 * @param[in] it : l'item � �crire
 */
void ecrire(Table& t, unsigned int i, const Chaine& mot) {
	if (i >= t.capacite) {
		unsigned int newTaille = (i + 1) * t.pasExtension;
		Chaine* newC = new Chaine[newTaille];

		for (unsigned int i = 0; i < t.capacite; ++i)
			newC[i] = t.mot[i];

		delete[] t.mot;
		t.mot = newC;
		t.capacite = newTaille;
	}
	t.mot[i] = mot;
}



void afficher(const Table& t, unsigned int nb) {
	for (unsigned int i = 0; i < nb; ++i) {
		cout << i + 1 << " - ";
		afficher(t.mot[i]);
	}
}