#include <iostream>
using namespace std;

#include "jeu.h"

void initialisation(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur* joueurs, unsigned int nbJoueurs) {
	Paquet pTalon = jeu_base();
	melanger(pTalon);
	cTalon = convertir(pTalon);
	detruire(pTalon);

	initialiser(cExposee);
	debut(cTalon);
	inserer(cExposee, lire(cTalon));
	supprimer(cTalon);

	initialiser(table, 1, 2);
	for (unsigned int i = 0; i < nbJoueurs; ++i) {
		joueurs[i].main = distribuer(cTalon);
		trier_main(joueurs[i].main);
		joueurs[i].id = i + 1;
		joueurs[i].points = 0;
	}
}

void destruction(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur* joueurs, unsigned int nbJoueurs) {
	detruire(table);
	detruire(cTalon);
	detruire(cExposee);
	for (unsigned int i = 0; i < nbJoueurs; ++i)
		detruire(joueurs[i].main);
}

bool finPartie(const Joueur* joueurs, unsigned int nbJoueurs) {
	for (unsigned int i = 0; i < nbJoueurs; ++i) {
		if (joueurs[i].points >= 100)
			return true;
	}
	return false;
}

bool finTour(const Joueur* joueurs, unsigned int nbJoueurs) {
	for (unsigned int i = 0; i < nbJoueurs; ++i) {
		if (estVide(joueurs[i].main))
			return true;
	}
	return false;
}

void partie(Joueur* joueurs, unsigned int& nbJoueurs, Dico& dico) {
	Table table;
	Chaine cTalon;
	Chaine cExposee;

	initialisation(table, cTalon, cExposee, joueurs, nbJoueurs);

	while (!finPartie(joueurs, nbJoueurs))
		tour(table, cTalon, cExposee, joueurs, nbJoueurs, dico);

	cout << "La partie est finie" << endl;
	exclure(joueurs, nbJoueurs);
	destruction(table, cTalon, cExposee, joueurs, nbJoueurs);
}

void tour(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur* joueurs, unsigned int nbJoueurs, Dico& dico) {
	char cmd;
	unsigned int nbmots = 0;
	while(!finTour(joueurs, nbJoueurs)){
		for (unsigned int i = 0; i < nbJoueurs; ++i) {
			cout << "*" << " Joueur " << joueurs[i].id << " (" << lire(cExposee).lettre << ") ";
			afficher(joueurs[i].main);
			if (nbmots)
				afficher(table, nbmots);

			cout << "> ";
			cin >> cmd;

			if (!cin || (cmd != 'E' && cmd != 'T' && cmd != 'P' &&  cmd != 'D')) {
				erreur(1);
			}
			else
				supercmd(table, cTalon, cExposee, joueurs[i], nbmots, cmd, dico);
		}
	}
	cout << "Le tour est fini" << endl << "*Scores" << endl;
	for (unsigned int i = 0; i < nbJoueurs; ++i) {
		joueurs[i].points = comptePoints(joueurs[i].main);
		cout << "Joueur " << joueurs[i].id << " : " << joueurs[i].points << " points" << endl;
	}
}

void supercmd(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int nbmots, char cmd, Dico& dico) {
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

void detruire(Joueur* joueurs) {
	delete[] joueurs;
	joueurs = nullptr;
}

void exclure(Joueur* joueurs, unsigned int& nbJoueurs) {
	unsigned newTaille = 0;
	for (unsigned int i = 0; i < nbJoueurs; ++i) {
		if (joueurs[i].points < 100)
			joueurs[newTaille++] = joueurs[i];
	}
	nbJoueurs = newTaille;
}

void cmdTalon(Chaine& cTalon, Chaine& cExposee, Chaine& cJoueur) {
	char mot;
	cin >> mot;
	if (!cin || !rechercherLettre(cJoueur, mot)) {
		erreur(1);
	}
	else {
		inserer(cExposee, lire(cJoueur));
		ecrire(cJoueur, lire(cTalon));
		supprimer(cTalon);
		trier_main(cJoueur);
	}
}

void cmdExposee(Chaine& cExposee, Chaine& cJoueur) {
	char mot;
	cin >> mot;
	if (!cin || !rechercherLettre(cJoueur, mot)) {
		erreur(1);
	}
	else {
		Carte tmp = lire(cJoueur);
		ecrire(cJoueur, lire(cExposee));
		ecrire(cExposee, tmp);
		trier_main(cJoueur);
	}
}

void cmdPoser(Table& table, Joueur& joueur, unsigned int& nbmots, Dico& dico) {
	char* mot = new char[NB_LETTRE];
	cin >> mot;
	if (!cin)
		erreur(1);
	else {
		if (!rechercherDico(dico, mot) || !rechercherMot(joueur.main, mot)) {
			erreur(2);
			joueur.points += 3;
		}
		else {
			Chaine cPoser;
			initialiser(cPoser);
			for (unsigned int i = 0; i <= strlen(mot); ++i) {
				if (rechercherLettre(joueur.main, mot[i])) {
					inserer(cPoser, lire(joueur.main));
					suivant(cPoser);
					supprimer(joueur.main);
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
		if (!rechercherDico(dico, mot) || !rechercherMot(joueur.main, mot)) {
			erreur(2);
			joueur.points += 3;
		}
		else {
			Chaine cPoser;
			initialiser(cPoser);
			for (unsigned int i = 0; i <= strlen(mot); ++i) {
				if (rechercherLettre(joueur.main, mot[i])) {
					inserer(cPoser, lire(joueur.main));
					suivant(cPoser);
					supprimer(joueur.main);
				}
			}
			ecrire(table, nbmots++, cPoser);
		}
	}
	delete[] mot;
}