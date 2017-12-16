#include "Equilibrage.h"

#include <algorithm>
#include <cassert>

#include <iostream>

template<typename T>
inline long Hauteur(TrieHybrideNoeud<T, AVL>* x) {
	return (x) ? x->e.h : 0;
}

/// @return Retourne false ssi l'arbre est déséquilibré au niveau courant.
template<typename T>
bool verifierEquilibre(TrieHybrideNoeud<T, AVL>* x) {
	if (!x) return true;

	// problème sur le noeud courant
	return (std::abs(Hauteur(x->g) - Hauteur(x->d)) <= 1);
}

template<typename T>
inline void recalculerHauteur(TrieHybrideNoeud<T, AVL>* x) {
	x->e.h = 1 + std::max(Hauteur(x->g), Hauteur(x->d));
}

template<typename T>
TrieHybrideNoeud<T, AVL>*  RotationD(TrieHybrideNoeud<T, AVL>* x) {
	TrieHybrideNoeud<T, AVL>* y = x->g;

	TrieHybrideNoeud<T, AVL>* A = x->g->g;
	TrieHybrideNoeud<T, AVL>* B = x->g->d;
	TrieHybrideNoeud<T, AVL>* C = x->d;

	y->g = A;
	y->d = x;
	x->g = B;
	x->d = C;

	recalculerHauteur(y);
	recalculerHauteur(x);

	return y;
}

template<typename T>
TrieHybrideNoeud<T, AVL>*  RotationG(TrieHybrideNoeud<T, AVL>* x) {
	TrieHybrideNoeud<T, AVL>* y = x->d;

	TrieHybrideNoeud<T, AVL>* A = x->g;
	TrieHybrideNoeud<T, AVL>* B = x->d->g;
	TrieHybrideNoeud<T, AVL>* C = x->d->d;

	y->g = x;
	y->d = C;
	x->g = A;
	x->d = B;

	recalculerHauteur(x);
	recalculerHauteur(y);

	return y;
}

template <typename T>
bool  VerifierEquilibrage(TrieHybrideNoeud<T, AVL>* x) {
	if (!x)
		return true;

	if (!verifierEquilibre(x)) {
		return false;
	}
	else return VerifierEquilibrage(x->g) && VerifierEquilibrage(x->d);

}

/// @return Retourne la nouvelle racine de l'arbre t rééquilibré.
/// @pre On suppose que les arbre t->g et t->d sont déjà équilibrés.
template<typename T>
inline TrieHybrideNoeud<T, AVL>*  Reequilibrer(TrieHybrideNoeud<T, AVL>* x) {
	recalculerHauteur(x);

	assert(verifierEquilibre(x->g));
	assert(verifierEquilibre(x->d));


	if (x && std::abs(Hauteur(x->g) - Hauteur(x->d)) > 1) {

		assert(!verifierEquilibre(x));

		if (Hauteur(x->g) > Hauteur(x->d)) {
			if (Hauteur(x->g->g) > Hauteur(x->g->d)) {
				x =  RotationD(x);
			}
			else {
				x->g = RotationG(x->g);
				recalculerHauteur(x);
				x =  RotationD(x);
			}
		}
		else { // Hauteur(t->g) < Hauteur(t->d))
			if (Hauteur(x->d->d) > Hauteur(x->d->g)) {
				x = RotationG(x);
			}
			else {
				x->d = RotationD(x->d);
				recalculerHauteur(x);
				x =  RotationG(x);
			}
		}
	}

	assert(verifierEquilibre(x));

	return x;
}
