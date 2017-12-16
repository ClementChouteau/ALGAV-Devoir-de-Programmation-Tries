#include "Fusion.h"

// InsererCase: insère c dans t, modifiant t
//		retourne la nouvelle racine de t (dans le cas où t == nullptr)
template <typename T, template< typename, typename > class Map>
TriePatriciaNoeud<T, Map>* InsererCase(const Case<T, Map>& c, TriePatriciaNoeud<T, Map>* t) {
	if (!c.mot.empty()) {
		if (!t) {
			t = new TriePatriciaNoeud<T, Map>();
			t->noeuds[c.mot[0]] = Case<T, Map>(c);
		}
		else {
			auto& noeud = t->noeuds[c.mot[0]];

			if (noeud.mot.empty())
				t->noeuds[c.mot[0]] = Case<T, Map>(c);

			else {
				auto k = longueurPlusLongPrefixe(noeud.mot, c.mot);

				if (k < (long)c.mot.size()) {

					// CAS 1.1: noeud.mot est préfixe strict de c.mot
					if (k == (long)noeud.mot.size()) {
						Case<T, Map> c2;

						c2.mot = std::vector<T>(c.mot.begin()+k, c.mot.end());
						c2.lien = c.lien;

						bool lien = (noeud.lien != nullptr);

						noeud.lien = InsererCase(c2, noeud.lien);

						if (!lien && noeud.lien)
							noeud.lien->finmot |= true;

						c2.lien = nullptr; // hack pour éviter la destruction
					}

					// CAS 1.2: le préfixe commun est strict aux deux
					else { // k < noeud.mot.size()
						auto* t2 = new TriePatriciaNoeud<T, Map>();

						t2->noeuds[noeud.mot[k]].mot = std::vector<T>(noeud.mot.begin()+k, noeud.mot.end());
						t2->noeuds[noeud.mot[k]].lien = noeud.lien;

						t2->noeuds[c.mot[k]].mot = std::vector<T>(c.mot.begin()+k, c.mot.end());
						t2->noeuds[c.mot[k]].lien = (c.lien) ? new TriePatriciaNoeud<T, Map>(*c.lien) : nullptr;

						noeud.lien = t2;
						noeud.mot.resize(k);
					}
				}

				else { // k == c.mot.size()

					// CAS 2.1: noeud.mot est égal a c.mot
					if (c.mot.size() == noeud.mot.size()) {
						if (c.lien) {
							bool lien = (noeud.lien != nullptr);

							noeud.lien = InsererNoeud(c.lien, noeud.lien);

							if (!lien && noeud.lien)
								noeud.lien->finmot = true;
						}

						else if (noeud.lien) // && !c.lien
							noeud.lien->finmot = true;
					}

					// CAS 2.2: c.mot est préfixe strict de noeud.mot
					else { // c.mot.size() != noeud.mot.size()
						auto* t2 = new TriePatriciaNoeud<T, Map>();

						t2->noeuds[noeud.mot[k]].mot = std::vector<T>(noeud.mot.begin()+k, noeud.mot.end());
						t2->noeuds[noeud.mot[k]].lien = noeud.lien;

						noeud.mot.resize(k);
						noeud.lien = t2;

						if (c.lien)
							noeud.lien = InsererNoeud(c.lien, t2);
						else
							t2->finmot = true;
					}
				}
			}
		}
	}

	return t;
}

// InsererNoeud: insère t1 dans t2, modifiant t2
//		retourne la nouvelle racine de t2
template <typename T, template< typename, typename > class Map>
TriePatriciaNoeud<T, Map>* InsererNoeud(const TriePatriciaNoeud<T, Map>* t1, TriePatriciaNoeud<T, Map>* t2) {
	if (t1) {
		if (!t2) {
			t2 = new TriePatriciaNoeud<T, Map>(*t1);
		}
		else {
			for (const auto& p1 : t1->noeuds) {
				const auto& c1 = p1.second;
				InsererCase(c1, t2);
			}

			t2->finmot |= t1->finmot;
		}
	}

	return t2;
}

// FusionNoeud: crée un nouveau noeud et insère t1, t2 dedans
//		retourne un nouveau noeud, fusion de t1 et t2
template <typename T, template< typename, typename > class Map>
TriePatriciaNoeud<T, Map>* FusionNoeud(const TriePatriciaNoeud<T, Map> *t1, const TriePatriciaNoeud<T, Map>* t2) {
	if (t2 != nullptr) {
		return InsererNoeud(t1, new TriePatriciaNoeud<T, Map>(*t2));
	}
	else {
		if (t1 != nullptr)
			return new TriePatriciaNoeud<T, Map>(*t1);
		else
			return nullptr;
	}
}

template <typename T, template< typename, typename > class Map>
TriePatricia<T, Map> Fusion(const TriePatricia<T, Map>& t1, const TriePatricia<T, Map>& t2) {
	return TriePatricia<T, Map>::depuisRacine(FusionNoeud(t1.obtenirRacine(), t2.obtenirRacine()));
}
