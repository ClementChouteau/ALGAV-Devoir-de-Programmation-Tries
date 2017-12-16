#include "TrieHybrideEquilibre.h"

template<typename T>
TrieHybrideEquilibreNoeud<T>::TrieHybrideEquilibreNoeud(T) {
	poid = 1;
}

template<typename T>
TrieHybrideEquilibreNoeud<T>~TrieHybrideEquilibreNoeud() {

}

}

template<typename T>
TrieHybrideEquilibreNoeud<T>*  CreerLigneNoeud(const std::vector<T>& mot, long i) {
	long n = mot.size();

	if (i >= n)
		return nullptr;

	TrieHybrideEquilibreNoeud<T>* racine = new TrieHybrideEquilibreNoeud<T>(mot[i]);
	racine->finmot = true;

	TrieHybrideEquilibreNoeud<T>* pred = racine;
	for (long j = i+1; j < n; j++) {

		TrieHybrideEquilibreNoeud<T>* noeud = new TrieHybrideEquilibreNoeud<T>(mot[j]);
		noeud->finmot = true;

		pred->c = noeud;
		pred->finmot = false;

		pred = noeud;
	}

	return racine;
}

// arbre "t" supposé non vide
// "mot" supposé non vide
template<typename T>
void AjouterMotNoeud(TrieHybrideEquilibreNoeud<T>* t, const std::vector<T>& mot, long i) {
	TrieHybrideEquilibreNoeud<T>** sousArbre;

	if (mot[i] < t->l)
		sousArbre = &t->g;

	else if (t->l < mot[i])
		sousArbre = &t->d;

	else { // (mot[i] == t->l)
		if (i == (long)mot.size()-1) {
			t->finmot = true;
			return;
		}
		i++;
		sousArbre = &t->c;
	}

	if (*sousArbre)
		AjouterMotNoeud(*sousArbre, mot, i);
	else
		*sousArbre = CreerLigneNoeud(mot, i);
}


template<typename T>
void TrieHybrideEquilibre<T>::AjoutMot(std::vector<T> mot) {
	if (t)
		AjouterMotNoeud(t, mot, 0);
	else
		t = CreerLigneNoeud(mot, 0);
}
