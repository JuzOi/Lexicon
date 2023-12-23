#include <iostream>
using namespace std;

#include "jeu.h"

void initialisation(Table& table, Chaine& cTalon, Chaine& cExposee, ConteneurJ& cJoueurs) {
	Paquet pTalon = jeu_base();
	melanger(pTalon);
	cTalon = convertir(pTalon);
	detruire(pTalon);

	initialiser(cExposee);
	debut(cTalon);
	inserer(cExposee, lire(cTalon));
	supprimer(cTalon);

	initialiser(table, 1, 2);
	distribution(cJoueurs, cTalon);
}

void destruction(Table& table, Chaine& cTalon, Chaine& cExposee, ConteneurJ& cJoueurs) {
	detruire(table);
	detruire(cTalon);
	detruire(cExposee);
	detruire(cJoueurs);
}

void partie(ConteneurJ& cJoueurs, Dico& dico) {
	Table table;
	Chaine cTalon;
	Chaine cExposee;

	while (!finPartie(cJoueurs)){
		initialisation(table, cTalon, cExposee, cJoueurs);
		tour(table, cTalon, cExposee, cJoueurs, dico);
	}

	cout << "La partie est finie" << endl;
	exclure(cJoueurs);
	destruction(table, cTalon, cExposee, cJoueurs);
}

void tour(Table& table, Chaine& cTalon, Chaine& cExposee, ConteneurJ& cJoueurs, Dico& dico) {
	char cmd;
	unsigned int nbmots = 0;
	while(!finTour(cJoueurs)){
		for (unsigned int i = 0; i < cJoueurs.nbJoueurs; ++i) {
			cout << "*" << " Joueur " << cJoueurs.joueur[i].id << " (" << lire(cExposee).lettre << ") ";
			afficher(cJoueurs.joueur[i].main);
			if (nbmots)
				afficher(table, nbmots);

			cout << "> ";
			cin >> cmd;

			if (!cin || (cmd != 'E' && cmd != 'T' && cmd != 'P' &&  cmd != 'D'))
				erreur(1);
			else
				supercmd(table, cTalon, cExposee, cJoueurs.joueur[i], nbmots, cmd, dico);
		}
	}
	cout << "Le tour est fini" << endl << " *Scores" << endl;
	for (unsigned int i = 0; i < cJoueurs.nbJoueurs; ++i) {
		cJoueurs.joueur[i].points = comptePoints(cJoueurs.joueur[i].main);
		cout << "Joueur " << cJoueurs.joueur[i].id << " : " << cJoueurs.joueur[i].points << " points" << endl;
	}
}

void supercmd(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, char cmd, Dico& dico) {
	switch (cmd) {
	case 'E':
		cmdExposee(cExposee, joueur.main);
		break;
	case 'T':
		cmdTalon(cTalon, cExposee, joueur.main);
		break;
	case 'P':
		cmdPoser(table, joueur, nbmots, dico);
		break;
	case 'D':
		debugPoser(table, joueur, nbmots, dico);
		break;
	default:
		erreur(1);
		break;
	}
}

void erreur(unsigned int n) {
	switch (n)
	{
	case 1:
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Coup invalide, recommencez" << endl;
		break;
	case 2:
		cout << "Mot invalide, vous passez votre tour" << endl;
		break;
	default:
		break;
	}
}

void cmdTalon(Chaine& cTalon, Chaine& cExposee, Chaine& main) {
	char mot;
	cin >> mot;
	if (!cin || !rechercherLettre(main, mot)) {
		erreur(1);
	}
	else {
		inserer(cExposee, lire(main));
		ecrire(main, lire(cTalon));
		supprimer(cTalon);
		trier_main(main);
	}
}

void cmdExposee(Chaine& cExposee, Chaine& main) {
	char mot;
	cin >> mot;
	if (!cin || !rechercherLettre(main, mot)) {
		erreur(1);
	}
	else {
		Carte tmp = lire(main);
		ecrire(main, lire(cExposee));
		ecrire(cExposee, tmp);
		trier_main(main);
	}
}

void cmdPoser(Table& table, Joueur& joueur, unsigned int& nbmots, Dico& dico) {
	char* mot = new char[NB_LETTRE];
	cin >> mot;
	if (!cin)
		erreur(1);
	else {
		if (!rechercherDico(dico, mot)) {
			joueur.points += 3;
			erreur(2);
		}
		else {
			Chaine cPoser;
			initialiser(cPoser);
			for (unsigned int i = 0; i < strlen(mot); ++i) {
				if (rechercherLettre(joueur.main, mot[i])) {
					inserer(cPoser, lire(joueur.main));
					suivant(cPoser);
					supprimer(joueur.main);
				}
				else {
					joueur.points += 3;
					detruire(cPoser);
					erreur(2);
				}
			}
			ecrire(table, nbmots++, cPoser);
		}
	}
	delete[] mot;
}

void debugPoser(Table& table, Joueur& joueur, unsigned int& nbmots, Dico& dico) {
	char* mot = new char[NB_LETTRE];
	cin >> mot;
	if (!cin)
		erreur(1);
	else {
		Chaine cPoser;
		initialiser(cPoser);
		for (unsigned int i = 0; i < strlen(mot); ++i) {
			if (rechercherLettre(joueur.main, mot[i])) {
				inserer(cPoser, lire(joueur.main));
				suivant(cPoser);
				supprimer(joueur.main);
			}
			else {
				erreur(2);
				joueur.points += 3;
				detruire(cPoser);
				return;
			}
		}
		ecrire(table, nbmots++, cPoser);
	}
	delete[] mot;
}