#include <iostream>
#include <fstream> // pour ifstream
#include <iomanip> // pour setw
#pragma warning(disable : 4996)

using namespace std;

#include "paquet.h"
#include "chaine.h"
#include "jeu.h"
#include "joueur.h"
#include "dico.h"

/* 
   argc -> nombre de paramètres sur la ligne de commande (+ 1)
   argv -> paramètres de la ligne de commande 
           (argv[0] : la cde, argv[1] : le 1er paramètre, etc)
*/
int main(int argc, const char* argv[]) {
	// parametre sur la ligne de commande
	unsigned int nbJoueurs = 0;
	if (argc >= 2) {
		cout << "(Commandes valides : TEPRC)" << endl;
		sscanf(argv[1], "%u", &nbJoueurs);
	}
	else
		cout << "il n'y a pas de parametre" << endl;

	ifstream in("ods4.txt");

	srand(time(NULL));

	Dico dico;
	initialiser(dico, NB_MOTS, NB_LETTRE);

	if (in) {
		chargerDico(dico, in);
		in.close();

		ConteneurJ cJoueurs;
		if (nbJoueurs >= 2 && nbJoueurs <= 4) {
			initialiser(cJoueurs, nbJoueurs);
			while (cJoueurs.nbJoueurs >= 2) {
				partie(cJoueurs, dico);
			}
			detruire(cJoueurs);
		}
	}

	detruire(dico);

	return 0;
}
