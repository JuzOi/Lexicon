#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include <algorithm>
#include "paquet.h"

Paquet jeu_base() {
	const unsigned int quantite[NB_LETTRE] = { 2, 2, 2, 2, 5, 1, 2, 2, 4, 1, 1, 2, 1, 3, 2, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 1 };
	const Carte carte[NB_LETTRE] = { {'A', 10}, {'B', 2}, {'C', 8}, {'D', 6}, {'E', 10}, {'F', 2}, {'G', 4}, {'H', 8}, {'I', 10}, {'J', 6}, {'K', 8}, {'L', 8},
		{'M', 8}, {'N', 8}, {'O', 8}, {'P', 8}, {'Q', 4}, {'R', 8}, {'S', 8}, {'T', 8}, {'U', 8}, {'V', 8}, {'W', 8}, {'X', 2}, {'Y', 4}, {'Z', 2} };
	
	Paquet paquet;
	initialiser(paquet, NB_CARTE);
	unsigned int somme = 0;
	for (unsigned int i = 0; i < NB_LETTRE; ++i) {
		for (unsigned int j = 0; j < quantite[i]; ++j) 
			ecrire(paquet, somme++, carte[i]);
	}
	return paquet;
}

int random_nbr(int max) {
	return rand() % max;
}

void initialiser(Paquet& paquet, unsigned int taille) {
	paquet.taille = taille;
	paquet.carte = new Carte[taille];
}

void ecrire(Paquet& paquet, unsigned int index, const Carte& carte) {
	paquet.carte[index] = carte;
}

void melanger(Paquet& paquet) {
	srand(time(NULL));
	for(unsigned int i = paquet.taille; i > 0; --i){
		int rdm = random_nbr(NB_CARTE);
		Carte tmp = paquet.carte[i - 1];
		paquet.carte[i - 1] = paquet.carte[rdm];
		paquet.carte[rdm] = tmp;
	}
}

void detruire(Paquet& paquet) {
	paquet.taille = 0;
	delete[] paquet.carte;
	paquet.carte = nullptr;
}

void trier(Paquet& paquet) {
	sort(paquet.carte, paquet.carte + MAIN, [](const Carte& carte1, const Carte& carte2) {
		return carte1.lettre < carte2.lettre;
		});
}