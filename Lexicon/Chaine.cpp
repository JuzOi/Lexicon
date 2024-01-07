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
#include "chaine.h"

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

void convertirP(Chaine& c, const Paquet& p) {
    debut(c);
    for (unsigned int i = 0; i < p.taille; ++i)
        inserer(c, p.carte[p.taille - i - 1]);
}

void convertirC(Chaine& c, Paquet& p) {
    debut(c);
    unsigned int i = 0;
    while (!estVide(c)) {
        p.carte[i++] = lire(c);
        supprimer(c);
    }
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

unsigned int longueur(Chaine& c) {
    unsigned int nb = 0;
    debut(c);
    while (!estFin(c)) {
        ++nb;
        suivant(c);
    }
    return nb;
}

void trierPaquet(Chaine& c) {
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

bool rechercherLettre(Chaine& c, const char lettre) {
    debut(c);
    while (!estFin(c) && lire(c).lettre != lettre)
        suivant(c);
    return !estFin(c);
}

void reinserer(Chaine& c1, Chaine& c2) {
    debut(c1);
    debut(c2);
    while (!estFin(c2)) {
        inserer(c1, lire(c2));
        supprimer(c2);
    }
    trierPaquet(c1);
}

bool rechercherMot(Chaine& c1, Chaine& c2, const char* mot) {
    for ( ; *mot != '\0'; ++mot) {
        if (rechercherLettre(c1, *mot)) {
            inserer(c2, lire(c1));
            suivant(c2);
            supprimer(c1);
        }
        else {
            return false;
        }
    }
    return true;
}

bool peutRemplacer(Chaine& motAChanger, const char* nouveauMot, Chaine& mainJoueur) {
    if (longueur(motAChanger) != strlen(nouveauMot))
        return false;
    Chaine tmp;
    initialiser(tmp);
    debut(motAChanger);
    while (!estFin(motAChanger)) {
        if (lire(motAChanger).lettre != *nouveauMot && !rechercherLettre(mainJoueur, *nouveauMot))
            fin(motAChanger);
        else {
            if (rechercherLettre(mainJoueur, *nouveauMot)) {
                inserer(tmp, lire(mainJoueur));
                supprimer(mainJoueur);
            }
            suivant(motAChanger);
            ++nouveauMot;
        }
    }
    reinserer(mainJoueur, tmp);
    detruire(tmp);
    return estFin(motAChanger) && (*nouveauMot == '\0');
}

void remplacer(Chaine& motAChanger, const char* nouveauMot, Chaine& mainJoueur) {
    debut(motAChanger);
    while (!estFin(motAChanger)) {
        if (rechercherLettre(mainJoueur, *nouveauMot)) {
            Carte tmp = lire(mainJoueur);
            ecrire(mainJoueur, lire(motAChanger));
            ecrire(motAChanger, tmp);
        }
        suivant(motAChanger);
        ++nouveauMot;
    }
    trierPaquet(mainJoueur);
}

bool peutCompleter(Chaine& motAChanger, const char* nouveauMot, Chaine& mainJoueur) {
    if (longueur(motAChanger) >= strlen(nouveauMot))
        return false;
    Chaine tmp;
    initialiser(tmp);
    debut(motAChanger);
    for (; *nouveauMot != '\0'; ++nouveauMot) {
        if (!rechercherLettre(mainJoueur, *nouveauMot) && (estFin(motAChanger) || lire(motAChanger).lettre != *nouveauMot)) {
            reinserer(mainJoueur, tmp);
            detruire(tmp);
            return false;
        }
        else {
            if (!estFin(motAChanger) && lire(motAChanger).lettre == *nouveauMot)
                suivant(motAChanger);
            else {
                inserer(tmp, lire(mainJoueur));
                supprimer(mainJoueur);
            }
        }
    }
    reinserer(mainJoueur, tmp);
    detruire(tmp);
    return estFin(motAChanger);
}

void completer(Chaine& motAChanger, const char* nouveauMot, Chaine& mainJoueur) {
    debut(motAChanger);
    for (; *nouveauMot != '\0'; ++nouveauMot) {
        if (rechercherLettre(mainJoueur, *nouveauMot) && (estFin(motAChanger) || lire(motAChanger).lettre != *nouveauMot)) {
            inserer(motAChanger, lire(mainJoueur));
            supprimer(mainJoueur);
        }
        suivant(motAChanger);
    }
}