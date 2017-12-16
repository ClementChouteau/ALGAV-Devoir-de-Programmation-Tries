#ifndef TRIE_HYBRIDE_HPP
#define TRIE_HYBRIDE_HPP

#include "Trie.h"
#include "Sizeable.h"
#include "Equilibrage.h"

#include <string>

template <typename T, typename Equilibrage = None>
class TrieHybrideNoeud {
public:
	TrieHybrideNoeud(T);
	~TrieHybrideNoeud();

	bool estFeuille() const;

	long tailleEnMemoire() const;

	T l;
	bool finmot;
	TrieHybrideNoeud<T, Equilibrage>* g;
	TrieHybrideNoeud<T, Equilibrage>* c;
	TrieHybrideNoeud<T, Equilibrage>* d;

	Equilibrage e;
};

template <typename T, typename Equilibrage = None>
class TrieHybride : public Trie<T>, public Sizeable {
public:
	TrieHybride();
	TrieHybride(TrieHybrideNoeud<T, Equilibrage>*);
	~TrieHybride();

	TrieHybrideNoeud<T, Equilibrage>* obtenirRacine() const;

	bool Recherche(const std::vector<T>&) const override;
	long ComptageMots() const override;
	std::vector< std::vector<T> > ListeMots() const override;
	long Prefixe(const std::vector<T>&) const override;
	void Suppression(const std::vector<T>&) override; // ATTENTION
	void AjoutMot(const std::vector<T>&) override;

	long ComptageNils() const;
	long Hauteur() const;
	long ProfondeurMoyenne() const;

	long tailleEnMemoire() const;

	std::string genererGraphViz();

private:
	TrieHybrideNoeud<T, Equilibrage>* t;
};

#include "TrieHybride.hpp"

#endif // TRIE_HYBRIDE_HPP
