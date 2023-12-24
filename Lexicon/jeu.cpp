#include <iostream>
using namespace std;

#include "jeu.h"

void initialisation(Table& table, Chaine& cTalon, Chaine& cExposee, ConteneurJ& cJoueurs) {
	Paquet pTalon = jeu_base();
	melanger(pTalon);
	initialiser(cTalon);
	convertirP(cTalon, pTalon);
	detruire(pTalon);

	initialiser(cExposee);
	inserer(cExposee, lire(cTalon));
	supprimer(cTalon);

	initialiser(table, 1, 2);
	distribution(cJoueurs, cTalon);
}

void destruction(Table& table, Chaine& cTalon, Chaine& cExposee) {
	detruire(table);
	detruire(cTalon);
	detruire(cExposee);
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
	destruction(table, cTalon, cExposee);
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

			afficher(cTalon);
			afficher(cExposee);
			debut(cTalon);
			debut(cExposee);

			cout << "> ";
			cin >> cmd;

			if (!cin || (cmd != 'E' && cmd != 'T' && cmd != 'P' &&  cmd != 'D'))
				erreur(1);
			else
				supercmd(table, cTalon, cExposee, cJoueurs.joueur[i], nbmots, cmd, dico);

			if (estVide(cTalon))
				reprise(cTalon, cExposee);
		}
	}
	cout << "Le tour est fini" << endl << " *Scores" << endl;
	for (unsigned int i = 0; i < cJoueurs.nbJoueurs; ++i) {
		cJoueurs.joueur[i].points = comptePoints(cJoueurs.joueur[i].main);
		cout << "Joueur " << cJoueurs.joueur[i].id << " : " << cJoueurs.joueur[i].points << " points" << endl;
	}
}

void reprise(Chaine& cTalon, Chaine& cExposee) {
	while (!estVide(cExposee)) {
		inserer(cTalon, lire(cExposee));
		supprimer(cExposee);
	}
	Paquet pTalon;
	initialiser(pTalon, longueur(cTalon));
	convertirC(cTalon, pTalon);
	melanger(pTalon);
	convertirP(cTalon, pTalon);

	inserer(cExposee, lire(cTalon));
	supprimer(cTalon);

	detruire(pTalon);
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
		debugPoser(cTalon, cExposee);
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
		trierPaquet(main);
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
		trierPaquet(main);
	}
}

void cmdPoser(Table& table, Joueur& joueur, unsigned int& nbmots, Dico& dico) {
	char* mot = new char[NB_LETTRE];
	cin >> mot;
	if (!cin)
		erreur(1);
	else {
		Chaine cPoser = rechercherMot(joueur.main, mot);
		if (!rechercherDico(dico, mot) || estVide(cPoser)) {
			if (!estVide(cPoser))
				reinserer(joueur.main, cPoser);
			joueur.points += 3;
			detruire(cPoser);
			erreur(2);
		}
		else {
			ecrire(table, nbmots++, cPoser);
		}
	}
	delete[] mot;
}

void debugPoser(Chaine& cTalon, Chaine& cExposee) {
	inserer(cExposee, lire(cTalon));
	supprimer(cTalon);
}