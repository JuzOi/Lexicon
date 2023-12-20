#include <iostream>
#include <fstream>
#include <iomanip>
#pragma warning(disable : 4996)

using namespace std;

#include "dico.h"

void initialiser(Dico& dico, unsigned int nbmots, unsigned int nblettres) {
    dico.mot = new char* [nbmots];
    for (unsigned int i = 0; i < nbmots; ++i)
        dico.mot[i] = new char[nblettres];
    dico.nbmots = nbmots;
    dico.nblettres = nblettres;
}

bool rechercherDico(Dico& dico, char* mot) {
    unsigned int deb = 0;
    unsigned int fin = NB_MOTS-1;
    unsigned int mil = (fin + deb) / 2;
    while (deb <= fin ) {
        if (strcmp(dico.mot[mil], mot) == 0)
            return true;
        else {
            if (strcmp(dico.mot[mil], mot) < 0)
                deb = mil + 1;
            else
                fin = mil - 1;
        }
        mil = (fin + deb) / 2;
    }
    return false;
}

void chargerDico(Dico& dico, istream& in) {
    unsigned int nb = 0;
    char s[NB_LETTRE];

    in >> setw(NB_LETTRE) >> s;
    while (in) {
        strncpy(dico.mot[nb], s, strlen(s) + 1);
        ++nb;
        in >> setw(NB_LETTRE) >> s;
    }
}

void detruire(Dico& dico) {
    for (unsigned int i = 0; i < dico.nbmots; ++i) {
        delete[] dico.mot[i];
        dico.mot[i] = nullptr;
    }
    delete[] dico.mot;
    dico.mot = nullptr;
}

void afficher(Dico& dico) {
    for (unsigned int i =0 ; i < dico.nbmots; ++i)
        cout << dico.mot[i] << endl;
}