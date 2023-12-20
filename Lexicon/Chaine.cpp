/**
 * @file Chaine.cpp
 * @brief Projet sem06-tp-Cpp1
 * @author l'équipe pédagogique
 * @version 1 25/01/05
 * Composant de chaîne d'items avec simple chaînage
 * Structures de données et algorithmes - DUT1 Paris 5
 */

#include <iostream>
#include <cassert>
using namespace std;

#include <algorithm>
#include "Chaine.h"

/** 
 * brief Initialisation d'une chaîne vide
 * la liste est allouée en mémoire dynamique
 * @see detruire, la liste est à désallouer en fin d’utilisation
 * @param[out] c : la chaîne
 */
void initialiser(Chaine& c) {
    c.tete = NULL;
    c.courant = &c.tete;
}

/** 
 * brief Désallocation d'une chaîne
 * @see initialiser, la liste a déjà été allouée en mémoire dynamique
 * @param[out] c : la chaîne
 */
void detruire(Chaine& c) {
    debut(c);
    while (!estVide(c)) 
        supprimer(c);
}

/**
 * @brief Test de chaîne vide
 * @param[in] c : la chaîne testée
 * @return true si c est vide, false sinon
 */
bool estVide(const Chaine& c) {
    return c.tete == NULL;
}

/**
 * @brief Insertion d'un élément avant le maillon courant
 * Le nouveau maillon devient le maillon courant 
 * @param[in,out] c : la chaîne
 * @param[in] elem : l'élément inséré
 */
void inserer(Chaine& c, const Carte& elem) {
    Maillon* m = new Maillon;
    m->elem = elem;
    m->suiv = *(c.courant);
    *(c.courant) = m;
}

/**
 * @brief Suppression du maillon courant
 * @param[in,out] c : la chaîne
 * @pre Le maillon courant existe et ce n'est pas la fin de la chaîne
 */
void supprimer(Chaine& c) {
    assert(!estFin(c));
	// Compléter le code .......................................................
    Maillon* maillon = *(c.courant);
    *(c.courant) = maillon->suiv;
    delete maillon;
}

/**
 * @brief Modification de l'élément stocké dans le maillon courant
 * @param[in,out] c : la chaîne
 * @param[in] elem : l'élément à écrire
 * @pre Le maillon courant existe et ce n'est pas la fin de la chaîne
 */
void ecrire(Chaine& c, const Carte& elem) {
    assert(!estFin(c));
    (*(c.courant))->elem = elem;
}

/**
 * @brief Lecture de l'élément stocké dans le maillon courant 
 * @param[in] c : la chaîne
 * @return l'élément lu
 * @pre Le maillon courant existe et ce n'est pas la fin de la chaîne
 */
Carte lire(const Chaine& c) {
    assert(!estFin(c));
    return (*(c.courant))->elem;
}

/**
 * @brief Positionnement du maillon courant en début de chaîne
 * @param[in,out] c : la chaîne
 */
void debut(Chaine& c) {
    c.courant = &(c.tete);
}

/**
 * @brief Test de debut de chaine
 * @param[in] c : la chaîne testée
 * @return true si le maillon courant est le début de chaîne, false sinon
 */
bool estDebut(const Chaine& c) {
    return c.courant == &(c.tete);
}

/**
 * @brief Positionnement du maillon courant en fin de chaîne
 * @param[in,out] c : la chaîne
 * @return true si le maillon courant est la fin de chaîne, false sinon
 */
void fin(Chaine& c) {
    while (!estFin(c))
        suivant(c);
}

/**
 * @brief Test de fin de chaîne
 * @param[in] c : la chaîne testée
 * @return true si le maillon courant est la fin de chaîne, false sinon.
 */
bool estFin(const Chaine& c) {
    return *(c.courant) == NULL;
}

/**
 * @brief Positionnement du maillon courant au maillon suivant
 * @param[in,out] c : la chaîne
 * @pre Le maillon courant existe et ce n'est pas la fin de la chaîne
 */
void suivant(Chaine& c) {
    assert(!estFin(c));
    c.courant = &((*(c.courant))->suiv);
}

Chaine convertir(const Paquet& paquet) {
    Chaine cPaquet;
    initialiser(cPaquet);
    for (unsigned int i = 0; i < paquet.taille; ++i) {
        inserer(cPaquet, paquet.carte[paquet.taille - i - 1]);
    }
    debut(cPaquet);
    return cPaquet;
}

void afficher(Chaine& c) {
    debut(c);
    while (!estFin(c)) {
        cout << lire(c).lettre;
        suivant(c);
    }
    cout << endl;
}

Chaine distribuer(Chaine& c) {
    Chaine cPaquet;
    initialiser(cPaquet);
    debut(c);
    for (unsigned int i = 0; i < MAIN; ++i) {
        inserer(cPaquet, lire(c)); 
        supprimer(c);
    }
    return cPaquet;
}

bool comparer(const Carte& carte1, const Carte& carte2) {
    return carte1.lettre < carte2.lettre;
}

unsigned int longueur(Chaine& c) {
    unsigned int nb = 0;
    debut(c);
    while (!estFin(c)) {
        ++nb;
        suivant(c);
    }
    return nb;
}

void trier_main(Chaine& c) {
    unsigned int nb = longueur(c);
    Paquet pTriee;
    initialiser(pTriee, nb);
    debut(c);
    for (unsigned int i = 0; i < nb; ++i) {
        pTriee.carte[i] = lire(c);
        suivant(c);
    }
    trier(pTriee);
    debut(c);
    for (unsigned int i = 0; i < nb; ++i) {
        ecrire(c, pTriee.carte[i]);
        suivant(c);
    }
    detruire(pTriee);
}

unsigned int comptePoints(Chaine& c) {
    unsigned int somme = 0;
    debut(c);
    while (!estFin(c)) {
        somme += lire(c).points;
        suivant(c);
    }
    return somme;
}

bool rechercherLettre(Chaine& c, char lettre) {
    debut(c);
    while (!estFin(c) && lire(c).lettre != lettre) {
        suivant(c);
    }
    return !estFin(c);
}

bool rechercherMot(Chaine& c, char* mot) {
    for (; *mot; ++mot) {
        if (!rechercherLettre(c, *mot))
            return false;
    }
    return true;
}