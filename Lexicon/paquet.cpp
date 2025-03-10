#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

#include <algorithm>
#include "paquet.h"

int random_nbr(int max);

void ecrire(Paquet& paquet, unsigned int index, const Carte& carte);

void echanger(Carte& c1, Carte& c2);

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

void echanger(Carte& c1, Carte& c2) {
	Carte tmp = c1;
	c1 = c2;
	c2 = tmp;
}

void melanger(Paquet& paquet) {
	for (unsigned int i = paquet.taille - 1; i > 0; --i) {
		int rdm = random_nbr(paquet.taille);
		echanger(paquet.carte[i], paquet.carte[rdm]);
	}
}

void detruire(Paquet& paquet) {
	paquet.taille = 0;
	delete[] paquet.carte;
	paquet.carte = nullptr;
}

void trier(Paquet& paquet) {
	sort(paquet.carte, paquet.carte + paquet.taille, [](const Carte& carte1, const Carte& carte2) {
		return tolower(carte1.lettre) < tolower(carte2.lettre);
		});
}