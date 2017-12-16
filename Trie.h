#ifndef TRIE_H
#define TRIE_H

#include <vector>

/// \class Trie
/// \brief Interface de structure de donnée trie, ensemble de mots supportant l'insertion, la suppression et la recherche.
/// \warning Ne garantie pas le stockage du mot vide.
template<typename T>
class Trie {
public:
	virtual ~Trie() {}

	virtual bool Recherche(const std::vector<T>&) const = 0;
	virtual long ComptageMots() const = 0;
	virtual std::vector< std::vector<T> > ListeMots() const = 0;
	virtual long Prefixe(const std::vector<T>&) const = 0;

	virtual void Suppression(const std::vector<T>&) = 0;
	virtual void AjoutMot(const std::vector<T>&) = 0;
};

#endif // TRIE_H
