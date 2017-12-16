#ifndef TRIE_PATRICIA_HPP
#define TRIE_PATRICIA_HPP

#include "Trie.h"
#include "Sizeable.h"

#include <string>
#include <unordered_map>

template< class Key, class T >
using UnorderedMap = std::unordered_map<Key, T>;

template <typename T, template< typename, typename > class Map>
class TriePatriciaNoeud;

template <typename T, template< typename, typename > class Map>
class Case {
public:
	Case();
	~Case();
	Case(const Case<T, Map>&);
	Case<T, Map>& operator=(const Case<T, Map>& rhs);

	long tailleEnMemoire() const;

	std::vector<T> mot;
	TriePatriciaNoeud<T, Map>* lien;
};

// Noeuds est un conteneur de Case<T>,
// il doit comporter des itérateurs qui itèrent sur des pair<T, Case<T>>
// l'opérateur &[] qui crée une nouvelle case, l'insère et la retourne
// et constant const& [] const qui retourne la case
// un opérateur= d'affectation

template <typename T, template< typename, typename > class Map>
class TriePatriciaNoeud {
public:
	TriePatriciaNoeud();
	TriePatriciaNoeud(std::vector<T>);

	TriePatriciaNoeud(const TriePatriciaNoeud<T, Map>&);

	bool estFeuille() const;

	long tailleEnMemoire() const;

	bool finmot;
	Map<T, Case<T, Map>> noeuds;
};


template <typename T, template< typename, typename > class Map>
std::vector< Case<T, Map> > noeudsTries(const Map<T, Case<T, Map>>&);

// hack pour les Map qui ont des arguments par défaut en plus de template< typename, typename >
// https://stackoverflow.com/questions/5301706/default-values-in-templates-with-template-arguments-c

template <typename T, template< typename, typename > class Map = UnorderedMap>
class TriePatricia: public Trie<T>, public Sizeable {
public:
	TriePatricia();
	~TriePatricia();

	static TriePatricia<T, Map> depuisRacine(TriePatriciaNoeud<T, Map>*);

	TriePatriciaNoeud<T, Map>* obtenirRacine() const;

	bool Recherche(const std::vector<T>&) const override;
	long ComptageMots() const override;
	std::vector< std::vector<T> > ListeMots() const override;
	long Prefixe(const std::vector<T>&) const override;
	void Suppression(const std::vector<T>&) override;
	void AjoutMot(const std::vector<T>&) override;

	long ComptageNils() const;
	long Hauteur() const;
	long ProfondeurMoyenne() const; // TODO

	long tailleEnMemoire() const;

	std::string genererGraphViz();

private:
	TriePatriciaNoeud<T, Map>* t;
};

#include "TriePatricia.hpp"

#endif // TRIE_PATRICIA_HPP
