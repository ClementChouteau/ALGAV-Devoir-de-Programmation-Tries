#ifndef TRIEHYBRIDEEQUILIBRE_H
#define TRIEHYBRIDEEQUILIBRE_H

#include "TrieHybride.h"

template <typename T>
class TrieHybrideEquilibreNoeud : public TrieHybrideNoeud<T> {
public:
	TrieHybrideEquilibreNoeud(T);
	~TrieHybrideEquilibreNoeud();

	long poid;
};

template <typename T>
class TrieHybrideEquilibre : public TrieHybride<T> {
public:
	TrieHybrideEquilibre();
	TrieHybrideEquilibre(TrieHybrideEquilibreNoeud<T>*);
	~TrieHybride();

	//void Suppression(std::vector<T>); // BONUS
	void AjoutMot(std::vector<T>);

private:
	TrieHybrideEquilibreNoeud<T>* t; // PROBLEMEM ICI
};

#endif // TRIEHYBRIDEEQUILIBRE_H
