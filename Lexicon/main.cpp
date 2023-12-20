#include <iostream>
#include <fstream> // pour ifstream
#include <iomanip> // pour setw
#pragma warning(disable : 4996)

using namespace std;

#include "paquet.h"
#include "chaine.h"
#include "jeu.h"
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
		cout << "le 1er parametre est '" << argv[1] << "'" << endl;
		sscanf(argv[1], "%u", &nbJoueurs);
	}
	else
		cout << "il n'y a pas de parametre" << endl;

	ifstream in("ods4.txt");

	Dico dico;
	initialiser(dico, NB_MOTS, NB_LETTRE);
	if (in)
		chargerDico(dico, in);
	in.close();

	while (nbJoueurs >= 2) {
		Joueur* joueurs = new Joueur[nbJoueurs];
		partie(joueurs, nbJoueurs, dico);
	}

	detruire(dico);

	return 0;
}
