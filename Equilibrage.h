#ifndef EQUILIBRAGE_H
#define EQUILIBRAGE_H

#include <cassert>

template <typename T, typename Equilibrage>
class TrieHybrideNoeud;

class None {
};

template <typename T>
inline TrieHybrideNoeud<T, None>* Reequilibrer(TrieHybrideNoeud<T, None>* t) { return t; }

class AVL {
public:
	long h = 1;
};

template <typename T>
TrieHybrideNoeud<T, AVL>*  Reequilibrer(TrieHybrideNoeud<T, AVL>*);

#include "Equilibrage.hpp"

#endif // EQUILIBRAGE_H
