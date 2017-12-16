#include "Conversions.h"

#include <iostream>

template<typename T, template<typename, typename> class Map>
TrieHybrideNoeud<T>* ConvertirNoeudPversH(const TriePatriciaNoeud<T, Map>* t) {
	TrieHybrideNoeud<T>* racine = nullptr;

	if (t) {
		TrieHybrideNoeud<T>* noeud = nullptr;
		for (const auto& c : noeudsTries<T, Map>(t->noeuds)) {

			if (!c.mot.empty()) {

				// ajouter nouveau noeud avec la lettre mot[0]
				if (!racine)
					noeud = racine = new TrieHybrideNoeud<T>(c.mot[0]);
				else
					noeud = noeud->d = new TrieHybrideNoeud<T>(c.mot[0]);

				// ajouter le reste du mot
				noeud->c = CreerLigneNoeud<T, None>(c.mot, 1); // (met finmot a true)

				// ajouter récursivement les mots de c.lien (ou une fin de mot)
				TrieHybrideNoeud<T>* fin = noeud;
				while (fin->c) fin = fin->c;

				if (c.lien) {
					fin->c = ConvertirNoeudPversH<T, Map>(c.lien);
					fin->finmot = (c.lien->finmot);
				}
				else
					fin->finmot = true;
			}
		}
	}

	return racine;
}

template<typename T, template<typename, typename> class Map>
TrieHybride<T> Convertir(const TriePatricia<T, Map>& t) {
	return TrieHybride<T>(ConvertirNoeudPversH<T, Map>(t.obtenirRacine()));
}

// On suppose que toute branche du trie hybride contient au moins un mot
template<typename T, typename Equilibrage, template<typename, typename> class Map>
TriePatriciaNoeud<T, Map>* ConvertirNoeudHversP(const TrieHybrideNoeud<T, Equilibrage>* x, TriePatriciaNoeud<T, Map>* t = nullptr, std::vector<T> mot = std::vector<T>()) {
	if (x) {
		if (!t)
			t = new TriePatriciaNoeud<T, Map>();

		TriePatriciaNoeud<T, Map>* t2 = t;

		// CAS1: fin de mot en x
		if (x->finmot) {
			Case<T, Map>* noeud_c = nullptr;

			// création du noeud de branchement
			if (!mot.empty()) {
				Case<T, Map>& noeud = t->noeuds[mot[0]];
				noeud.mot = mot;

				if (x->g || x->d) {
					t2 = noeud.lien = new TriePatriciaNoeud<T, Map>(std::vector<T>({x->l}));
					noeud_c = &t2->noeuds[x->l];
				}
				else { // (!x->g && !x->d)
					noeud.mot.push_back(x->l);
					noeud_c = &noeud;
				}
			}

			else { // mot.empty()
				noeud_c = &t->noeuds[x->l];
				noeud_c->mot = std::vector<T>({x->l});
			}

			if (x->c) {
				noeud_c->lien = ConvertirNoeudHversP<T, Equilibrage, Map>(x->c);
				noeud_c->lien->finmot = true;
			}

			mot.clear();
		}


		// CAS2: pas de fin de mot en x
		else {
			int nbBranches = (x->g != nullptr) + (x->c != nullptr) + (x->d != nullptr);
			if (nbBranches > 0) {
				// création du noeud de branchement
				if (nbBranches >= 2 && !mot.empty()) {
					Case<T, Map>& noeud = t->noeuds[mot[0]];

					noeud.mot = mot;
					t2 = noeud.lien = new TriePatriciaNoeud<T, Map>();

					mot.clear();
				}

				if (x->c) {
					mot.push_back(x->l);
					ConvertirNoeudHversP<T, Equilibrage, Map>(x->c, t2, mot);
					mot.pop_back();
				}
			}
		}

		// ajouts récursifs
		ConvertirNoeudHversP<T, Equilibrage, Map>(x->g, t2, mot);
		ConvertirNoeudHversP<T, Equilibrage, Map>(x->d, t2, mot);
	}


	return t;
}

template<typename T, typename Equilibrage, template<typename, typename> class Map>
TriePatricia<T, Map> Convertir(const TrieHybride<T, Equilibrage>& t) {
	return TriePatricia<T, Map>::depuisRacine(ConvertirNoeudHversP<T, Equilibrage, Map>(t.obtenirRacine()));
}
