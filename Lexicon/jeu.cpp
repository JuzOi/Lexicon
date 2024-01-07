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

void partie(ConteneurJ& cJoueurs, const Dico& dico) {
	Table table;
	Chaine cTalon;
	Chaine cExposee;

	while (!finPartie(cJoueurs) && cJoueurs.nbJoueurs >= 2) {
		unsigned int nbmots = 0;
		unsigned int i = 0;
		initialisation(table, cTalon, cExposee, cJoueurs);
		tour(table, cTalon, cExposee, cJoueurs, i, nbmots, dico);
	}

	cout << "La partie est finie" << endl;
	exclure(cJoueurs);
	destruction(table, cTalon, cExposee);
}

void tour(Table& table, Chaine& cTalon, Chaine& cExposee, ConteneurJ& cJoueurs, unsigned int& i, unsigned int& nbmots, const Dico& dico) {
	if (!finTour(cJoueurs) && cJoueurs.nbJoueurs >= 1){
		afficherEtat(table, cExposee, cJoueurs.joueur[i], nbmots);

		if (estVide(cTalon))
			reprise(cTalon, cExposee);

		supercmd(table, cTalon, cExposee, cJoueurs.joueur[i], nbmots, dico);

		if (finPartie(cJoueurs))
			exclure(cJoueurs);

		if (++i >= cJoueurs.nbJoueurs)
			i = 0;
		tour(table, cTalon, cExposee, cJoueurs, i, nbmots, dico);
	}
	else {
		cout << "Le tour est fini" << endl << "* Scores" << endl;
		for (unsigned int i = 0; i < cJoueurs.nbJoueurs; ++i) {
			cJoueurs.joueur[i].points += comptePoints(cJoueurs.joueur[i].main);
			cout << "Joueur " << cJoueurs.joueur[i].id << " : " << cJoueurs.joueur[i].points << " points" << endl;
		}
	}
}

void afficherEtat(const Table& table, const Chaine& cExposee, Joueur& joueur, const unsigned int& nbmots) {
	cout << endl << "*" << " Joueur " << joueur.id << " (" << lire(cExposee).lettre << ") ";
	afficher(joueur.main);
	if (nbmots)
		afficher(table, nbmots);

	cout << "> ";
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

void supercmd(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico) {
	char cmd;
	cin >> cmd;
	if (cin.fail() || cin.peek() != ' ')
		erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
	else {
		switch (cmd) {
		case 'E':
			cmdExposee(table, cTalon, cExposee, joueur, nbmots, dico);
			break;
		case 'T':
			cmdTalon(table, cTalon, cExposee, joueur, nbmots, dico);
			break;
		case 'P':
			cmdPoser(table, cTalon, cExposee, joueur, nbmots, dico);
			break;
		case 'R':
			cmdRemplacer(table, cTalon, cExposee, joueur, nbmots, dico);
			break;
		case 'C':
			cmdCompleter(table, cTalon, cExposee, joueur, nbmots, dico);
			break;
		default:
			erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
			break;
		}
	}
}

void erreur(unsigned int n, Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico) {
	switch (n)
	{
	case 1:
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Coup invalide, recommencez" << endl;
		afficherEtat(table, cExposee, joueur, nbmots);
		supercmd(table, cTalon, cExposee, joueur, nbmots, dico);
		break;
	case 2:
		cout << "Mot invalide, vous passez votre tour" << endl;
		joueur.points += 3;
		break;
	default:
		break;
	}
}

void cmdTalon(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico) {
	char mot;
	cin >> mot;
	if (cin.fail() || cin.peek() != '\n')
		erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
	else {
		bool lettreTrouvee = rechercherLettre(joueur.main, mot);
		if (!lettreTrouvee)
			erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
		else {
			inserer(cExposee, lire(joueur.main));
			ecrire(joueur.main, lire(cTalon));
			supprimer(cTalon);
			trierPaquet(joueur.main);
		}
	}

}

void cmdExposee(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico) {
	char mot;
	cin >> mot;
	if (cin.fail() || cin.peek() != '\n')
		erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
	else {
		bool lettreTrouvee = rechercherLettre(joueur.main, mot);
		if (!lettreTrouvee)
			erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
		else {
			Carte tmp = lire(joueur.main);
			ecrire(joueur.main, lire(cExposee));
			ecrire(cExposee, tmp);
			trierPaquet(joueur.main);
		}
	}
}

void cmdPoser(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico) {
	char* mot = new char[NB_LETTRE];
	cin >> mot;
	if (cin.fail() || cin.peek() != '\n')
		erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
	else {
		Chaine cPoser;
		initialiser(cPoser);
		bool motTrouvee = rechercherMot(joueur.main, cPoser, mot);
		if (!motTrouvee || !rechercherDico(dico, mot)) {
			reinserer(joueur.main, cPoser);
			detruire(cPoser);
			if (!motTrouvee)
				erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
			else
				erreur(2, table, cTalon, cExposee, joueur, nbmots, dico);
		}
		else {
			ecrire(table, nbmots++, cPoser);
		}
	}
	delete[] mot;
}

void cmdRemplacer(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico) {
	unsigned int numero;
	char* mot = new char[NB_LETTRE];
	cin >> numero;
	if (cin.fail() || cin.peek() != ' ' || numero <= 0 || numero > nbmots)
		erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
	else {
		cin >> mot;
		if (cin.fail() || cin.peek() != '\n' || longueur(table.mot[numero - 1]) != strlen(mot))
			erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
		else {
			if (rechercherDico(dico, mot)){
				if (!peutRemplacer(table.mot[numero - 1], mot, joueur.main))
					erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
				else
					remplacer(table.mot[numero - 1], mot, joueur.main);
			}
			else
				erreur(2, table, cTalon, cExposee, joueur, nbmots, dico);
		}
	}
	delete[] mot;
}

void cmdCompleter(Table& table, Chaine& cTalon, Chaine& cExposee, Joueur& joueur, unsigned int& nbmots, const Dico& dico) {
	unsigned int numero;
	char* mot = new char[NB_LETTRE];
	cin >> numero;
	if (cin.fail() || cin.peek() != ' ' || numero <= 0 || numero > nbmots)
		erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
	else {
		cin >> mot;
		if (cin.fail() || cin.peek() != '\n' || longueur(table.mot[numero - 1]) >= strlen(mot))
			erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
		else {
			if (rechercherDico(dico, mot)){
				if (!peutCompleter(table.mot[numero - 1], mot, joueur.main))
					erreur(1, table, cTalon, cExposee, joueur, nbmots, dico);
				else
					completer(table.mot[numero - 1], mot, joueur.main);
			}
			else
				erreur(2, table, cTalon, cExposee, joueur, nbmots, dico);
		}
	}
	delete[] mot;
}