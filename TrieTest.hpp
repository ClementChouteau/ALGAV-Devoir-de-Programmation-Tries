#include "TrieTest.h"

#include "Trie.h"

#include <cassert>
#include <vector>

std::vector<char> vectDeString2(std::string s) {
	return std::vector<char>(s.begin(), s.end());
}

template< typename GivenTrie >
void assertTrie() {
#ifndef NDEBUG
	Trie<char>* t = new GivenTrie();

	assert(t->ComptageMots() == 0);
	assert(t->ListeMots().size() == 0);
	assert(t->Recherche(std::vector<char>()) == false);

	t->AjoutMot(std::vector<char>({'b'}));
	assert(t->ComptageMots() == 1);
	assert(t->ListeMots().size() == 1);

	t->AjoutMot(std::vector<char>({'a'}));
	t->AjoutMot(std::vector<char>({'a'}));
	assert(t->ComptageMots() == 2);
	assert(t->ListeMots().size() == 2);

	t->AjoutMot(std::vector<char>({'c'}));
	assert(t->ComptageMots() == 3);
	assert(t->ListeMots().size() == 3);

	assert(t->Recherche(std::vector<char>({'b'})) == true);
	assert(t->Recherche(std::vector<char>({'a'})) == true);
	assert(t->Recherche(std::vector<char>({'c'})) == true);
	assert(t->Recherche(std::vector<char>({'b', 'a'})) == false);

	t->AjoutMot(std::vector<char>({'b', 'a'}));
	t->AjoutMot(std::vector<char>({'b', 'a'}));
	assert(t->ComptageMots() == 4);
	assert(t->ListeMots().size() == 4);

	assert(t->Recherche(std::vector<char>({'b', 'a'})) == true);

	t->Suppression(std::vector<char>({'a'}));
	assert(t->ComptageMots() == 3);
	assert(t->ListeMots().size() == 3);

	assert(t->Recherche(std::vector<char>({'a'})) == false);

	assert(t->Recherche(std::vector<char>({'b', 'a'})) == true);

	t->Suppression(std::vector<char>({'b'}));
	assert(t->ComptageMots() == 2);
	assert(t->ListeMots().size() == 2);

	assert(t->Recherche(std::vector<char>({'b'})) == false);
	assert(t->Recherche(std::vector<char>({'a'})) == false);
	assert(t->Recherche(std::vector<char>({'c'})) == true);
	assert(t->Recherche(std::vector<char>({'b', 'a'})) == true);

	t->AjoutMot(std::vector<char>({'b'}));
	assert(t->ComptageMots() == 3);
	assert(t->ListeMots().size() == 3);
	assert(t->Recherche(std::vector<char>({'b'})) == true);
	assert(t->Recherche(std::vector<char>({'a'})) == false);
	assert(t->Recherche(std::vector<char>({'c'})) == true);
	assert(t->Recherche(std::vector<char>({'b', 'a'})) == true);

	assert(t->Prefixe(std::vector<char>({'b'})) == 2);

	delete t;

	t = new GivenTrie();
	t->AjoutMot(std::vector<char>({'a'}));
	t->AjoutMot(std::vector<char>({'b'}));
	t->AjoutMot(std::vector<char>({'c'}));
	t->AjoutMot(std::vector<char>({'d'}));

	t->AjoutMot(std::vector<char>({'a', 'a'}));
	t->AjoutMot(std::vector<char>({'a', 'b'}));
	t->AjoutMot(std::vector<char>({'a', 'c'}));
	t->AjoutMot(std::vector<char>({'a', 'd'}));

	t->AjoutMot(std::vector<char>({'b', 'a'}));
	t->AjoutMot(std::vector<char>({'b', 'b'}));
	t->AjoutMot(std::vector<char>({'b', 'c'}));
	t->AjoutMot(std::vector<char>({'b', 'd'}));

	t->AjoutMot(std::vector<char>({'c', 'a'}));
	t->AjoutMot(std::vector<char>({'c', 'b'}));
	t->AjoutMot(std::vector<char>({'c', 'c'}));
	t->AjoutMot(std::vector<char>({'c', 'd'}));

	assert(t->ComptageMots() == 4*4);

	t = new GivenTrie();
	t->AjoutMot(std::vector<char>({'a', 'a'}));
	t->AjoutMot(std::vector<char>({'b', 'a'}));
	t->AjoutMot(std::vector<char>({'c', 'a'}));
	t->AjoutMot(std::vector<char>({'d', 'a'}));

	t->AjoutMot(std::vector<char>({'a'}));
	t->AjoutMot(std::vector<char>({'b'}));
	t->AjoutMot(std::vector<char>({'c'}));
	t->AjoutMot(std::vector<char>({'d'}));

	t->AjoutMot(std::vector<char>({'a', 'b'}));
	t->AjoutMot(std::vector<char>({'b', 'b'}));
	t->AjoutMot(std::vector<char>({'c', 'b'}));
	t->AjoutMot(std::vector<char>({'d', 'b'}));

	t->AjoutMot(std::vector<char>({'a', 'a', 'a'}));
	t->AjoutMot(std::vector<char>({'b', 'a', 'a'}));
	t->AjoutMot(std::vector<char>({'c', 'a', 'a'}));
	t->AjoutMot(std::vector<char>({'d', 'a', 'a'}));

	assert(t->ComptageMots() == 4*4);
	delete t;

	t = new GivenTrie();
	t->AjoutMot(std::vector<char>({'t', 'h', 'e'}));
	t->AjoutMot(std::vector<char>({'t', 'h', 'e'}));

	assert(t->ComptageMots() == 1);
	delete t;


	//comptageMots

	t = new GivenTrie();
	t->AjoutMot(vectDeString2("mes"));
	assert(t->ComptageMots() == 1);

	t->AjoutMot(vectDeString2("la"));
	assert(t->ComptageMots() == 2);

	t->AjoutMot(vectDeString2(","));
	assert(t->ComptageMots() == 3);

	t->Suppression(vectDeString2("pour"));
	assert(t->ComptageMots() == 3);

	t->Suppression(vectDeString2("mes"));
	assert(t->ComptageMots() == 2);

	t->Suppression(vectDeString2(","));
	assert(t->ComptageMots() == 1);

	t->Suppression(vectDeString2("la"));
	assert(t->ComptageMots() == 0);

	delete t;


	//prefixe ///////////////////////////////////////////
	t = new GivenTrie();

	assert(t->Prefixe(vectDeString2("les")) == 0);

	t->AjoutMot(vectDeString2("les"));
	assert(t->Prefixe(vectDeString2("les")) == 1);

	t->AjoutMot(vectDeString2("lesion"));
	assert(t->Prefixe(vectDeString2("les")) == 2);

	t->AjoutMot(vectDeString2("lesson"));
	assert(t->Prefixe(vectDeString2("les")) == 3);
	assert(t->Prefixe(vectDeString2("le")) == 3);

	t->AjoutMot(vectDeString2("lettre"));
	assert(t->Prefixe(vectDeString2("les")) == 3);
	assert(t->Prefixe(vectDeString2("le")) == 4);

	t->Suppression(vectDeString2("lesson"));
	t->Suppression(vectDeString2("les"));
	assert(t->Prefixe(vectDeString2("les")) == 1);
	assert(t->Prefixe(vectDeString2("le")) == 2);


	t->Suppression(vectDeString2("lettre"));
	assert(t->Prefixe(vectDeString2("les")) == 1);
	assert(t->Prefixe(vectDeString2("le")) == 1);

	t->Suppression(vectDeString2("lesion"));
	assert(t->Prefixe(vectDeString2("les")) == 0);
	assert(t->Prefixe(vectDeString2("le")) == 0);

	delete t;
#endif //NDEBUG
}


template< typename GivenTrie1, typename GivenTrie2 >
void assertClassesTrieEgaux(const std::vector< std::vector<char> >& mots) {
#ifndef NDEBUG
	GivenTrie1 t1;
	GivenTrie2 t2;

	for (const auto& mot : mots) {
		t1.AjoutMot(mot);
		t2.AjoutMot(mot);
	}

	assertInstancesTrieEgaux(t1, t2);
#endif //NDEBUG
}

template<typename T>
void assertInstancesTrieEgaux(Trie<T>& t1, Trie<T>& t2) {
#ifndef NDEBUG
	assert(t1.ComptageMots() == t2.ComptageMots());

	const std::vector< std::vector<T> > l1 = t1.ListeMots();
	const std::vector< std::vector<T> > l2 = t2.ListeMots();

	assert(l1.size() == l2.size());

	for (auto i = 0; i < (long)l1.size(); i++) {
		assert(l1[i].size() == l2[i].size());
		assert(l1[i] == l2[i]);
	}

	for (const auto& mot : l1) {
		assert(t1.Recherche(mot) == t2.Recherche(mot));

		t2.Suppression(mot);
		t1.Suppression(mot);
	}

	assert(t1.ComptageMots() == 0);
	assert(t2.ComptageMots() == 0);
#endif //NDEBUG
}
