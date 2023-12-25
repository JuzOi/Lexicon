#ifndef CHAINE_H_
#define CHAINE_H_

/**
 * @file Chaine.h
 * @brief Projet sem06-tp-Cpp1
 * @author l'équipe pédagogique
 * @version 1 25/01/05
 * Composant de chaîne d'items avec simple chaînage
 * Structures de données et algorithmes - DUT1 Paris 5
 */

#include "paquet.h"

/** Type Maillon avec le principe du simple chaînage (maillon suivant)
 */
struct Maillon {
    Carte elem;     // Elément (du maillon) de la liste chaînée
    Maillon* suiv; // Pointeur sur le maillon suivant
};

/** Type Chaine 
 *  Repères du début de chaîne et du  maillon courant
 */
struct Chaine {
    Maillon* tete;     // Pointeur sur le maillon de tête
    Maillon** courant; // Superpointeur (pointeur du pointeur) 
    				   // désignant le maillon courant		   		   
};

/** 
 * brief Initialisation d'une chaîne vide
 * la liste est allouée en mémoire dynamique
 * @see detruire, la liste est à désallouer en fin d’utilisation
 * @param[out] c : la chaîne
 */
void initialiser(Chaine& c);

/** 
 * brief Désallocation d'une chaîne
 * @see initialiser, la liste a déjà été allouée en mémoire dynamique
 * @param[out] c : la chaîne
 */
void detruire(Chaine& c);

/**
 * @brief Test de chaîne vide
 * @param[in] c : la chaîne testée
 * @return true si c est vide, false sinon
 */
bool estVide(const Chaine& c);

/**
 * @brief Insertion d'un élément avant le maillon courant
 * Le nouveau maillon devient le maillon courant 
 * @param[in,out] c : la chaîne
 * @param[in] elem : l'élément inséré
 */
void inserer(Chaine& c, const Carte& elem);

/**
 * @brief Suppression du maillon courant
 * @param[in,out] c : la chaîne
 * @pre Le maillon courant existe et ce n'est pas la fin de la chaîne
 */
void supprimer(Chaine& c);

/**
 * @brief Modification de l'élément stocké dans le maillon courant
 * @param[in,out] c : la chaîne
 * @param[in] elem : l'élément à écrire
 * @pre Le maillon courant existe et ce n'est pas la fin de la chaîne
 */
void ecrire(Chaine& c, const Carte& elem);

/**
 * @brief Lecture de l'élément stocké dans le maillon courant 
 * @param[in] c : la chaîne
 * @return l'élément lu
 * @pre Le maillon courant existe et ce n'est pas la fin de la chaîne
 */
Carte lire(const Chaine& c);

/**
 * @brief Positionnement du maillon courant en début de chaîne
 * @param[in,out] c : la chaîne
 */
void debut(Chaine& c);

/**
 * @brief Test de debut de chaine
 * @param[in] c : la chaîne testée
 * @return true si le maillon courant est le début de chaîne, false sinon
 */
bool estDebut(const Chaine& c);

/**
 * @brief Positionnement du maillon courant en fin de chaîne
 * @param[in,out] c : la chaîne
 * @return true si le maillon courant est la fin de chaîne, false sinon
 */
void fin(Chaine& c);

/**
 * @brief Test de fin de chaîne
 * @param[in] c : la chaîne testée
 * @return true si le maillon courant est la fin de chaîne, false sinon.
 */
bool estFin(const Chaine& c);

/**
 * @brief Positionnement du maillon courant au maillon suivant
 * @param[in,out] c : la chaîne
 * @pre Le maillon courant existe et ce n'est pas la fin de la chaîne
 */
void suivant(Chaine& c);




void convertirP(Chaine& c, const Paquet& paquet);

void convertirC(Chaine& c, Paquet& p);

void afficher(Chaine& c);

Chaine distribuer(Chaine& c);

unsigned int longueur(Chaine& c);

void trierPaquet(Chaine& c);

unsigned int comptePoints(Chaine& c);

bool rechercherLettre(Chaine& c, const char lettre);

void reinserer(Chaine& c1, Chaine& c2);

bool comparer(Chaine& c, const char* mot);

void rechercherMot(Chaine& c1, Chaine& c2, const char* mot);

bool verifMot(Chaine& cRemplacer, Chaine& cEchanger, Chaine& cTable, Chaine& cJoueur, char* mot);

#endif /*CHAINE_H_*/
