#ifndef TRIEPERFS_H
#define TRIEPERFS_H

#include "Trie.h"

#include <string>
#include <vector>
#include <ctime>
#include <sstream>

template<typename GivenTrie>
std::string performanceLog(const std::vector< std::vector<char> >& mots) {
	std::stringstream out;

	clock_t begin_time, end_time;

	/// AJOUT DES MOTS
	begin_time = clock();
	Trie<char>* t = new GivenTrie();

	for (const auto& mot : mots) {
		t->AjoutMot(mot);
	}
	end_time = clock();
	out << "Ajout des mots: " << (float( end_time - begin_time ) /  CLOCKS_PER_SEC)*1000 << " ms" << std::endl;

	/// RECHERCHE DES MOTS
	begin_time = clock();
	for (const auto& mot : mots) {
		t->Recherche(mot);
	}
	end_time = clock();
	out << "Recherche des mots: " << (float( end_time - begin_time ) /  CLOCKS_PER_SEC)*1000 << " ms" << std::endl;

	/// COMPTAGE DES MOTS
	begin_time = clock();
	auto n = t->ComptageMots();
	end_time = clock();
	out << "Comptage des mots: " << n << " mots, " << (float( end_time - begin_time ) /  CLOCKS_PER_SEC)*1000 << " ms" << std::endl;

	/// SUPPRESSION DES MOTS
	begin_time = clock();
	for (const auto& mot : mots) {
		t->Suppression(mot);
	}

	end_time = clock();
	out << "Suppression des mots: " << (float( end_time - begin_time ) /  CLOCKS_PER_SEC)*1000 << " ms" << std::endl;

	delete t;

	return out.str();
}

#endif // TRIEPERFS_H
