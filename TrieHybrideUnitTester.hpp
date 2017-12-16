#ifndef TRIEHYBRIDEUNITTESTER_HPP
#define TRIEHYBRIDEUNITTESTER_HPP

#include "TrieHybride.h"

#include <cassert>
#include <vector>

std::vector<unsigned char> vectDeString(std::string s) {
	return std::vector<unsigned char>(s.begin(), s.end());
}


void testerTrieHybride() {

	//comptageNil
	TrieHybride<unsigned char> t;

	assert(t->ComptageNil() == 0);

	t->AjoutMot(vectDeString("les"));
	assert(t->ComptageNil() == 7);

	t->AjoutMot(vectDeString("la"));
	assert(t->ComptageNil() == 9);

	t->Suppression(vectDeString("les"));
	assert(t->ComptageNil() == 7);

	t->Suppression(vectDeString("la"));
	assert(t->ComptageNil() == 3);

	delete t;




	//hauteur

	TrieHybride<unsigned char> t;

	assert(t->Hauteur() == 0);

	t->AjoutMot(vectDeString("la"));
	assert(t->Hauteur() == 2);

	t->AjoutMot(vectDeString("pour"));
	assert(t->Hauteur() == 5);


	t->AjoutMot(vectDeString("mou"));
	assert(t->Hauteur() == 5);

	t->Suppression(vectDeString("pour"));
	assert(t->Hauteur() == 5);

	t->Suppression(vectDeString("la"));
	assert(t->Hauteur() == 5);

	t->Suppression(vectDeString("mou"));
	assert(t->Hauteur() == 0);

	delete t;






	//profondeur moyenne

	TrieHybride<unsigned char> t;

	assert(t->ProfondeurMoyenne() == 0);

	t->AjoutMot(vectDeString("les"));
	assert(t->ProfondeurMoyenne() == 3);

	t->AjoutMot(vectDeString("mous"));
	assert(t->ProfondeurMoyenne() == 4);

	t->AjoutMot(vectDeString("prend"));
	assert(t->ProfondeurMoyenne() == 5);

	t->Suppression(vectDeString("mous"));
	assert(t->ProfondeurMoyenne() == 5);

	t->Suppression(vectDeString("les"));
	assert(t->ProfondeurMoyenne() == 7);

	t->Suppression(vectDeString("prend"));
	assert(t->ProfondeurMoyenne() == 0);

	delete t;


}

#endif // TRIEHYBRIDEUNITTESTER_HPP
