#ifndef TRIESTDSET_H
#define TRIESTDSET_H

#include "Trie.h"

#include <set>

template <typename T>
class TrieStdSet: public Trie<T> {
public:
	bool Recherche(const std::vector<T>& mot) const override {
		return set.find(mot) != set.end();
	}

	long ComptageMots() const {
		return set.size();
	}

	std::vector< std::vector<T> > ListeMots() const override {
		return std::vector< std::vector<T> >(set.begin(), set.end());
	}

	long Prefixe(const std::vector<T>&) const override {
		assert(0);
		return -1;
	}

	void Suppression(const std::vector<T>& mot) override {
		set.erase(mot);
	}

	void AjoutMot(const std::vector<T>& mot) override {
		set.insert(mot);
	}

private:
	std::set< std::vector<T> > set;
};


#endif // TRIESTDSET_H
