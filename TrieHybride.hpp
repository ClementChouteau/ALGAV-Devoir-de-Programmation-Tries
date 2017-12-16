#include "TrieHybride.h"

#include <algorithm>
#include <iostream>
#include <sstream>

template <typename T, typename Equilibrage>
TrieHybrideNoeud<T, Equilibrage>::TrieHybrideNoeud(T l) {
	this->l = l;
	finmot = false;
	g = nullptr;
	c = nullptr;
	d = nullptr;
}

template <typename T, typename Equilibrage>
TrieHybrideNoeud<T, Equilibrage>::~TrieHybrideNoeud(){
	if (g != nullptr)
		delete g;
	if (d != nullptr)
		delete d;
	if (c != nullptr)
		delete c;
}

template <typename T, typename Equilibrage>
bool TrieHybrideNoeud<T, Equilibrage>::estFeuille() const {
	return (!g) && (!c) && (!d);
}

template <typename T, typename Equilibrage>
long TrieHybrideNoeud<T, Equilibrage>::tailleEnMemoire() const {
	long somme = sizeof(TrieHybrideNoeud<T, Equilibrage>);

	if (g) somme += g->tailleEnMemoire();
	if (c) somme += c->tailleEnMemoire();
	if (d) somme += d->tailleEnMemoire();

	return somme;
}

template <typename T, typename Equilibrage>
TrieHybride<T, Equilibrage>::TrieHybride() {
	t = nullptr;
}

template <typename T, typename Equilibrage>
TrieHybride<T, Equilibrage>::TrieHybride(TrieHybrideNoeud<T, Equilibrage>* t) {
	this->t = t;
}

template <typename T, typename Equilibrage>
TrieHybride<T, Equilibrage>::~TrieHybride() {
	if (t != nullptr){
		delete t;
	}
}

template <typename T, typename Equilibrage>
TrieHybrideNoeud<T, Equilibrage>* TrieHybride<T, Equilibrage>::obtenirRacine() const {
	return t;
}

// "mot" suppos� non vide
template <typename T, typename Equilibrage>
bool RechercheNoeud(TrieHybrideNoeud<T, Equilibrage>* t, const std::vector<T>& mot, long i) {
	if (t == nullptr)
		return false;

	if (mot[i] < t->l)
		return RechercheNoeud(t->g, mot, i);
	if (t->l < mot[i])
		return RechercheNoeud(t->d, mot, i);

	// else (mot[i] == t->l)
	if (i == (long)mot.size() - 1)
		return (t->finmot);

	return RechercheNoeud(t->c, mot, i+1);
}

template <typename T, typename Equilibrage>
bool TrieHybride<T, Equilibrage>::Recherche(const std::vector<T>& mot) const {
	if (mot.empty())
		return false;

	return RechercheNoeud(t, mot, 0);
}

template <typename T, typename Equilibrage>
long ComptageMotsNoeud(TrieHybrideNoeud<T, Equilibrage>* t) {
	if (t == nullptr)
		return 0;
	else {
		return ((t->finmot) ? 1 : 0) + ComptageMotsNoeud(t->g) + ComptageMotsNoeud(t->c) + ComptageMotsNoeud(t->d);
	}
}

template <typename T, typename Equilibrage>
long TrieHybride<T, Equilibrage>::ComptageMots() const {
	return ComptageMotsNoeud(t);
}

template <typename T, typename Equilibrage>
long ComptageNilsNoeud(TrieHybrideNoeud<T, Equilibrage>* t) {
	if (t == nullptr)
		return 1;
	else {
		return ComptageNilsNoeud(t->g) + ComptageNilsNoeud(t->c) + ComptageNilsNoeud(t->d);
	}
}

template <typename T, typename Equilibrage>
long TrieHybride<T, Equilibrage>::ComptageNils() const {
	return ComptageNilsNoeud(t);
}

template <typename T, typename Equilibrage>
long HauteurNoeud(TrieHybrideNoeud<T, Equilibrage>* t) {
	if (t == nullptr)
		return 0;
	else {
		return std::max({1+HauteurNoeud(t->g), HauteurNoeud(t->c), 1+HauteurNoeud(t->d)});
	}
}

template <typename T, typename Equilibrage>
long TrieHybride<T, Equilibrage>::Hauteur() const {
	return HauteurNoeud(t);
}

template <typename T, typename Equilibrage>
long PrefixeNoeud(TrieHybrideNoeud<T, Equilibrage>* t, const std::vector<T>& mot, long i) {
	if (t == nullptr)
		return 0;

	if (mot[i] < t->l)
		return PrefixeNoeud(t->g, mot, i);
	if (t->l < mot[i])
		return PrefixeNoeud(t->d, mot, i);

	// else (mot[i] == t->l)
	if (i == (long)mot.size() - 1)
		return (t->finmot) + ComptageMotsNoeud(t->c);

	return PrefixeNoeud(t->c, mot, i+1);
}

template <typename T, typename Equilibrage>
long TrieHybride<T, Equilibrage>::Prefixe(const std::vector<T>& mot) const {
	if (!mot.empty())
		return PrefixeNoeud(t, mot, 0);
	else
		return ComptageMots();
}

template <typename T, typename Equilibrage>
TrieHybrideNoeud<T, Equilibrage>*  CreerLigneNoeud(const std::vector<T>& mot, long i) {
	long n = mot.size();

	if (i >= n)
		return nullptr;

	TrieHybrideNoeud<T, Equilibrage>* racine = new TrieHybrideNoeud<T, Equilibrage>(mot[i]);
	racine->finmot = true;

	TrieHybrideNoeud<T, Equilibrage>* pred = racine;
	for (long j = i+1; j < n; j++) {

		TrieHybrideNoeud<T, Equilibrage>* noeud = new TrieHybrideNoeud<T, Equilibrage>(mot[j]);
		noeud->finmot = true;

		pred->c = noeud;
		pred->finmot = false;

		pred = noeud;
	}

	return racine;
}

/// @pre L'arbre t, et le paramètre mot est supposé non vide.
/// @return Retourne la nouvelle racine de t (qui peut changer si il y un équilibrage actif).
template <typename T, typename Equilibrage>
TrieHybrideNoeud<T, Equilibrage>* AjouterMotNoeud(TrieHybrideNoeud<T, Equilibrage>* t, const std::vector<T>& mot, long i) {
	TrieHybrideNoeud<T, Equilibrage>** sousArbre;

	if (mot[i] < t->l)
		sousArbre = &t->g;

	else if (t->l < mot[i])
		sousArbre = &t->d;

	else { // (mot[i] == t->l)
		if (i == (long)mot.size()-1) {
			t->finmot = true;
			return t;
		}
		i++;
		sousArbre = &t->c;
	}

	if (*sousArbre) {
		if (sousArbre != &t->c)
			*sousArbre = Reequilibrer(AjouterMotNoeud(*sousArbre, mot, i));
		else
			*sousArbre = AjouterMotNoeud(*sousArbre, mot, i);
	}
	else
		*sousArbre = CreerLigneNoeud<T, Equilibrage>(mot, i);

	return Reequilibrer(t);
}

template <typename T, typename Equilibrage>
void TrieHybride<T, Equilibrage>::AjoutMot(const std::vector<T>& mot) {
	if (t) {
		t = AjouterMotNoeud(t, mot, 0);
	}
	else
		t = CreerLigneNoeud<T, Equilibrage>(mot, 0);
}

// retourne nullptr si l'arbre a �t� supprim� enti�rement
template <typename T, typename Equilibrage>
TrieHybrideNoeud<T, Equilibrage>* SuppressionNoeud(TrieHybrideNoeud<T, Equilibrage>* t, const std::vector<T>& mot, long i) {
	// TODO: SUPPRIMER LES NOEUDS QUI N'ONT RIEN AU CENTRE
	if (t) {
		if (i == (long)mot.size()-1 && t->l == mot[i]) {
			t->finmot = false;
		}

		else {
			if (mot[i] < t->l)
				t->g = SuppressionNoeud(t->g, mot, i);
			else if (t->l < mot[i])
				t->d = SuppressionNoeud(t->d, mot, i);
			else // (mot[i] == t->l)
				t->c = SuppressionNoeud(t->c, mot, i+1);
		}

		if (!t->finmot && t->estFeuille()) {
			delete t;
			t = nullptr;
		}
	}

	return t;
}

template <typename T, typename Equilibrage>
void TrieHybride<T, Equilibrage>::Suppression(const std::vector<T>& mot) {
	t = SuppressionNoeud(t, mot, 0);
}


template <typename T, typename Equilibrage>
void ListeMotsNoeud(TrieHybrideNoeud<T, Equilibrage>* t, std::vector< std::vector<T> >& liste, std::vector<T>& pile) {
	if (t) {
		ListeMotsNoeud(t->g, liste, pile);

		pile.push_back(t->l);

		if (t->finmot)
			liste.push_back(pile);

		ListeMotsNoeud(t->c, liste, pile);

		pile.pop_back();

		ListeMotsNoeud(t->d, liste, pile);
	}
}

template <typename T, typename Equilibrage>
std::vector< std::vector<T> > TrieHybride<T, Equilibrage>::ListeMots() const {
	std::vector< std::vector<T> > liste;
	std::vector<T> pile;

	ListeMotsNoeud(t, liste, pile);

	return liste;
}

template <typename T, typename Equilibrage>
void ProfondeurMoyenneNoeud(TrieHybrideNoeud<T, Equilibrage>* t, long& sommeHauteur, long& finMots, long hauteur) {
	if (t) {
		hauteur++;
		if (t->finmot) {
			finMots++;
			sommeHauteur += hauteur;
		}

		ProfondeurMoyenneNoeud(t->g, sommeHauteur, finMots, hauteur);

		ProfondeurMoyenneNoeud(t->c, sommeHauteur, finMots, hauteur);

		ProfondeurMoyenneNoeud(t->d, sommeHauteur, finMots, hauteur);
	}
}

template <typename T, typename Equilibrage>
long TrieHybride<T, Equilibrage>::ProfondeurMoyenne() const {
	long sommeHauteur = 0;
	long finMots = 0;

	ProfondeurMoyenneNoeud(t, sommeHauteur, finMots, 0);
	if (!finMots)
		return 0;
	return sommeHauteur/finMots;
}

template <typename T, typename Equilibrage>
long TrieHybride<T, Equilibrage>::tailleEnMemoire() const {
	long somme = sizeof(TrieHybride<T, Equilibrage>);
	if (t) somme += t->tailleEnMemoire();

	return somme;
}

template <typename P>
std::string pointeurVersString(P* p) {
	std::stringstream ss;
	ss << static_cast<const void*>(p);
	return ss.str();
}

template <typename T, typename Equilibrage>
void genererGraphVizNoeud(TrieHybrideNoeud<T, Equilibrage>* t, std::string& graph) {
	if (t) {
		if (t->g) {
			graph += "{\"" + pointeurVersString(t) + "\"";
			graph += "[label=\"";
			graph += (char) t->l;
			graph += "\"";
			if (t->finmot)
				graph += " fillcolor=grey style=filled";
			graph += " fontsize=40";
			graph += "]}";
			graph += " -> ";
			graph += "{\"" + pointeurVersString(t->g) + "\"";
			graph += "[label=\"";
			graph += (char) t->g->l;
			graph += "\"";
			if (t->g->finmot)
				graph += " fillcolor=grey style=filled";
			graph += " fontsize=40";
			graph += "]}";
			graph += " [color=red]";
			graph += ";\n";
		}
		if (t->c) {
			graph += "{\"" + pointeurVersString(t) + "\"";
			graph += "[label=\"";
			graph += (char) t->l;
			graph += "\"";
			if (t->finmot)
				graph += " fillcolor=grey style=filled";
			graph += " fontsize=40";
			graph += "]}";
			graph += " -> ";
			graph += "{\"" + pointeurVersString(t->c) + "\"";
			graph += "[label=\"";
			graph += (char) t->c->l;
			graph += "\"";
			if (t->c->finmot)
				graph += " fillcolor=grey style=filled";
			graph += " fontsize=40";
			graph += "]}";
			graph += " [color=green]";
			graph += ";\n";
		}
		if (t->d) {
			graph += "{\"" + pointeurVersString(t) + "\"";
			graph += "[label=\"";
			graph += (char) t->l;
			graph += "\"";
			if (t->finmot)
				graph += " fillcolor=grey style=filled";
			graph += " fontsize=40";
			graph += "]}";
			graph += " -> ";
			graph += "{\"" + pointeurVersString(t->d) + "\"";
			graph += "[label=\"";
			graph += (char) t->d->l;
			graph += "\"";
			if (t->d->finmot)
				graph += " fillcolor=grey style=filled";
			graph += " fontsize=40";
			graph += "]}";
			graph += " [color=blue]";
			graph += ";\n";
		}

		genererGraphVizNoeud(t->g, graph);
		genererGraphVizNoeud(t->c, graph);
		genererGraphVizNoeud(t->d, graph);
	}
}

template <typename T, typename Equilibrage>
std::string TrieHybride<T, Equilibrage>::genererGraphViz() {
	std::string graph;
	graph += "digraph";
	graph += "{";
	genererGraphVizNoeud(t, graph);
	graph += "}";

	return graph;
}
