#include "TriePatricia.h"

#include <algorithm>
#include <iostream>

#include <cassert>

template <typename T, template< typename, typename > class Map>
Case<T, Map>::Case() {
	lien = nullptr;
}

template <typename T, template< typename, typename > class Map>
Case<T, Map>::~Case() {
	if (lien) {
		delete lien;
	}
}

template <typename T, template< typename, typename > class Map>
Case<T, Map>::Case(const Case<T, Map>& other) {
	mot = other.mot;
	lien = (other.lien) ? new TriePatriciaNoeud<T, Map>(*other.lien) : nullptr;
}

template <typename T, template< typename, typename > class Map>
Case<T, Map>& Case<T, Map>::operator=(const Case<T, Map>& rhs) {
	mot = rhs.mot;
	lien =
			(rhs.lien) ?
				new TriePatriciaNoeud<T, Map>(*rhs.lien)
		: nullptr;

	return *this;
}

template <typename T, template< typename, typename > class Map>
long Case<T, Map>::tailleEnMemoire() const {
	long n = sizeof(Case<T, Map>);

	n += sizeof(std::vector<T>) + mot.size() * sizeof(T);

	if (lien)
		n += lien->tailleEnMemoire();

	return n;
}

template <typename T, template< typename, typename > class Map>
TriePatriciaNoeud<T, Map>::TriePatriciaNoeud() {
	finmot = false;
}

template <typename T, template< typename, typename > class Map>
TriePatriciaNoeud<T, Map>::TriePatriciaNoeud(std::vector<T> mot) {
	finmot = (mot.empty());

	if (!mot.empty())
		noeuds[mot[0]].mot = mot;
}

template <typename T, template< typename, typename > class Map>
TriePatriciaNoeud<T, Map>::TriePatriciaNoeud(const TriePatriciaNoeud<T, Map>& other) {
	finmot = other.finmot;
	noeuds = other.noeuds;
}

template <typename T, template< typename, typename > class Map>
bool TriePatriciaNoeud<T, Map>::estFeuille() const {
	if (finmot)
		return false;

	for (const auto& p : noeuds) {
		const auto& c = p.second;
		if (!c.mot.empty())
			return false;
		}

	return true;
}

template <typename T, template< typename, typename > class Map>
long TriePatriciaNoeud<T, Map>::tailleEnMemoire() const {
	auto n = sizeof(TriePatriciaNoeud<T, Map>);

	for (const auto& p : noeuds) {
		const auto& c = p.second;
		n += c.tailleEnMemoire();
	}

	return n;
}

template <typename T, template< typename, typename > class Map>
std::vector< Case<T, Map> > noeudsTries(const Map<T, Case<T, Map>>& noeuds) {
	std::vector< Case<T, Map> > noeuds_tries;
	noeuds_tries.reserve(noeuds.size());
	for (const auto& p : noeuds) {
		auto c = p.second;
		if (!c.mot.empty())
			noeuds_tries.push_back(c);
	}
	std::sort(noeuds_tries.begin(), noeuds_tries.end(),
			  [](const Case<T, Map> & c1, const Case<T, Map> & c2)
	{
		return c1.mot[0] < c2.mot[0];
	});

	return noeuds_tries;
}


template <typename T, template< typename, typename > class Map>
TriePatricia<T, Map>::TriePatricia() {
	t = nullptr;
}

template <typename T, template< typename, typename > class Map>
TriePatricia<T, Map>::~TriePatricia() {
	if (t != nullptr){
		delete t;
	}
}

template <typename T, template< typename, typename > class Map>
TriePatricia<T, Map> TriePatricia<T, Map>::depuisRacine(TriePatriciaNoeud<T, Map>* t) {
	TriePatricia<T, Map> _t;
	_t.t = t;

	return _t;
}

template <typename T, template< typename, typename > class Map>
TriePatriciaNoeud<T, Map>* TriePatricia<T, Map>::obtenirRacine() const {
	return t;
}


// longueur du plus long préfixe
template<typename T>
long longueurPlusLongPrefixe(const std::vector<T>& mot1, const std::vector<T>& mot2, long i = 0) {
	auto k = 0;
	for (auto j = 0; j < (long)mot1.size() && i+j < (long)mot2.size(); j++) {
		if (mot1[j] != mot2[i+j])
			break;
		k++;
	}

	return k;
}

template <typename T, template< typename, typename > class Map>
bool RechercheNoeud(TriePatriciaNoeud<T, Map>* t, const std::vector<T>& mot, long i) {
	auto n = static_cast<long>(mot.size());

	if (!t)
		return (i == n);

	if (i == n)
		return t->finmot;

	auto k = longueurPlusLongPrefixe(t->noeuds[mot[i]].mot, mot, i);
	return (k == 0) ? false : RechercheNoeud(t->noeuds[mot[i]].lien, mot, i+k);
}

template <typename T, template< typename, typename > class Map>
bool TriePatricia<T, Map>::Recherche(const std::vector<T>& mot) const {
	if (t)
		return RechercheNoeud(t, mot, 0);
	else
		return false;
}

template <typename T, template< typename, typename > class Map>
long ComptageMotsNoeud(const TriePatriciaNoeud<T, Map>* t) {
	long n = (t->finmot);

	for (const auto& p : t->noeuds) {
		const auto& c = p.second;
		if (!c.mot.empty()) {
			if (!c.lien)
				n++;
			else
				n += ComptageMotsNoeud(c.lien);
		}
	}

	return n;
}

template <typename T, template< typename, typename > class Map>
long TriePatricia<T, Map>::ComptageMots() const {
	if (t)
		return ComptageMotsNoeud(t);
	else
		return 0;
}

template <typename T, template< typename, typename > class Map>
void ListeMotsNoeud(TriePatriciaNoeud<T, Map>* t, std::vector< std::vector<T> >& liste, std::vector<T>& pile) {
	if (!t)
		return;

	if (t->finmot)
		liste.push_back(pile);

	for (const auto& c : noeudsTries<T, Map>(t->noeuds)) {

		auto n = pile.size();
		auto k = c.mot.size();

		if (!c.mot.empty()) {
			pile.resize(n+k);

			std::copy(std::begin(c.mot), std::end(c.mot), std::begin(pile)+n);

			if (!c.lien) {
				liste.push_back(pile);
			}
			else {
				ListeMotsNoeud(c.lien, liste, pile);
			}
			pile.resize(n);
		}

	}
}

template <typename T, template< typename, typename > class Map>
std::vector< std::vector<T> > TriePatricia<T, Map>::ListeMots() const {
	std::vector< std::vector<T> > liste;
	std::vector<T> pile;

	ListeMotsNoeud(t, liste, pile);

	return liste;
}

template <typename T, template< typename, typename > class Map>
long ComptageNilsNoeud(TriePatriciaNoeud<T, Map>* t) {
	if (!t)
		return 1;


	long n = 0;
	for (const Case<T, Map>& c : t->noeuds) {
		n += ComptageNilsNoeud(c.lien);
	}
	return n;
}

template <typename T, template< typename, typename > class Map>
long TriePatricia<T, Map>::ComptageNils() const {
	return ComptageNilsNoeud(t);
}

template <typename T, template< typename, typename > class Map>
long HauteurNoeud(TriePatriciaNoeud<T, Map>* t) {
	if (!t)
		return 0;

	long h = 0;
	for (const Case<T, Map>& c : t->noeuds) {
		h = std::max(h, 1+HauteurNoeud(c.lien));
	}

	return h;
}

template <typename T, template< typename, typename > class Map>
long TriePatricia<T, Map>::Hauteur() const {
	return HauteurNoeud(t);
}

template <typename T, template< typename, typename > class Map>
void ProfondeurMoyenneNoeud(TriePatriciaNoeud<T, Map>* t, long& sommeHauteur, long& finMots, long hauteur) {
	if (t) {
		hauteur++;
		bool contientFinMot = (t->finmot);

		for (const Case<T, Map>& c : t->noeuds)
			if (!c.mot.empty()) {
				if (c.lien)
					ProfondeurMoyenneNoeud(c.lien, sommeHauteur, finMots, hauteur);
				else {
					contientFinMot = true;
				}
			}

		if (contientFinMot) {
			finMots++;
			sommeHauteur += hauteur;
		}
	}
}

template <typename T, template< typename, typename > class Map>
long TriePatricia<T, Map>::ProfondeurMoyenne() const {
	long sommeHauteur = 0;
	long finMots = 0;

	ProfondeurMoyenneNoeud(t, sommeHauteur, finMots, 0);
	if(!finMots)
		return 0;
	return sommeHauteur/finMots;
}

template <typename T, template< typename, typename > class Map>
long PrefixeNoeud(TriePatriciaNoeud<T, Map>* t, const std::vector<T>& mot, long i) {
	long n = mot.size();
	if (i >= n)
		return ComptageMotsNoeud(t);

	auto& noeud = t->noeuds[mot[i]];

	if (noeud.mot.empty())
		return 0;

	long k = longueurPlusLongPrefixe(noeud.mot, mot, i);

	// cas particulier du noeud vide comptant pour 1
	if (!noeud.lien)
		return (i+k == n);

	// CAS1: .mot est une préfixe de mot
	if (k == (long)noeud.mot.size()) {
		return PrefixeNoeud(noeud.lien, mot, i+k);
	}
	// CAS2: le plus grand préfixe entre mot et .mot != .mot
	else {
		// CAS2.1: ... égal a mot
		if (i+k == n)
			return ComptageMotsNoeud(noeud.lien);

		// CAS2.1: ... préfixe strict de mot
	}

	return 0;
}

template <typename T, template< typename, typename > class Map>
long TriePatricia<T, Map>::Prefixe(const std::vector<T>& mot) const {
	if (t)
		return PrefixeNoeud(t, mot, 0);
	else
		return 0;
}

template <typename T, template< typename, typename > class Map>
TriePatriciaNoeud<T, Map>* SuppressionNoeud(TriePatriciaNoeud<T, Map>* t, const std::vector<T> mot, long i) {
	if (t) {
		long n = mot.size();
		if (i >= n) {
			t->finmot = false;
		}
		else {
			auto& noeud = t->noeuds[mot[i]];
			if (!noeud.mot.empty()) {
				long k = longueurPlusLongPrefixe(noeud.mot, mot, i);

				// noeud.mot est préfixe de mot
				if (k == (long)noeud.mot.size()) {

					// CA1: préfixe strict
					if (i+k < n) {
						if (noeud.lien) {
							noeud.lien = SuppressionNoeud(noeud.lien, mot, i+k);
							if (!noeud.lien)
								noeud.mot.clear();
						}
					}

					// CAS2: égal
					else {
						if (noeud.lien) {
							noeud.lien = SuppressionNoeud(noeud.lien, mot, i+k);
							if (!noeud.lien)
								noeud.mot.clear();
						}
						else
							noeud.mot.clear();
					}
				}
			}
		}

		if (t->estFeuille()) {
			delete t;
			t = nullptr;
		}
	}

	return t;
}

template <typename T, template< typename, typename > class Map>
void TriePatricia<T, Map>::Suppression(const std::vector<T>& mot) {
	t = SuppressionNoeud(t, mot, 0);
}

template <typename T, template< typename, typename > class Map>
TriePatriciaNoeud<T, Map>* AjoutMotNoeud(TriePatriciaNoeud<T, Map>* t, const std::vector<T>& mot, long i) {
	long n = mot.size();

	Case<T, Map>& noeud = t->noeuds[mot[i]];
	if (noeud.mot.empty()) {
		noeud.mot = std::vector<T>(mot.begin()+i, mot.end());
		return t;
	}

	long k = longueurPlusLongPrefixe(noeud.mot, mot, i);

	// CAS1: .mot est une préfixe de mot
	if (k == (long)noeud.mot.size()) {

		// CAS1.1: ... préfixe strict
		if (i+k < n) {
			if (!noeud.lien) {
				noeud.lien = new TriePatriciaNoeud<T, Map>(std::vector<T>(mot.begin()+i+k, mot.end()));
				noeud.lien->finmot = true;
			}
			else
				noeud.lien = AjoutMotNoeud(noeud.lien, mot, i+k);
		}

		// CAS1.2: ... égal
		else if (noeud.lien) {
			noeud.lien->finmot = true;
		}
	}
	// CAS2: le plus grand préfixe entre mot et .mot != .mot
	else {
		TriePatriciaNoeud<T, Map>* t2 = new TriePatriciaNoeud<T, Map>();

		t2->noeuds[noeud.mot[k]].mot = std::vector<T>(noeud.mot.begin()+k, noeud.mot.end());
		t2->noeuds[noeud.mot[k]].lien = noeud.lien;
		noeud.lien = t2;

		// CAS2.1: ... égal a mot
		if (i+k == n)
			t2->finmot = true;
		// CAS2.1: ... préfixe strict de mot
		else
			t2->noeuds[mot[i+k]].mot = std::vector<T>(mot.begin()+i+k, mot.end());

		noeud.mot.resize(k);
	}

	return t;
}

template <typename T, template< typename, typename > class Map>
void TriePatricia<T, Map>::AjoutMot(const std::vector<T>& mot) {
	if (t)
		t = AjoutMotNoeud(t, mot, 0);
	else
		t = new TriePatriciaNoeud<T, Map>(std::vector<T>(mot.begin(), mot.end()));
}

template <typename T, template< typename, typename > class Map>
long TriePatricia<T, Map>::tailleEnMemoire() const {
	return sizeof(t) + (t != nullptr)  ? t->tailleEnMemoire() : 0;
}

template <typename T, template< typename, typename > class Map>
void genererGraphVizNoeud(TriePatriciaNoeud<T, Map>* t, std::string& graph) {
	if (t != nullptr) {
		graph += "\"" + pointeurVersString(t) + "\"";
		graph += " [label=\"";
		if (t->finmot)
			graph += "V";
		else
			graph += "X";
		graph += "";
		for (const auto& p : t->noeuds) {
			const auto& c = p.second;
			if (!c.mot.empty())
				graph += "|{" + std::string(c.mot.begin(), c.mot.end()) + "|<" + "" + pointeurVersString(&c.lien) + "" + ">}";
		}
		graph += "\"];\n";

		for (const auto& p : t->noeuds) {
			const auto& c = p.second;
			if (!c.mot.empty() && c.lien != nullptr)
				graph += "\"" + pointeurVersString(t) + "\"" + ":" + "\"" + pointeurVersString(&c.lien) + ":c" + "\"" + " -> " + "\"" + pointeurVersString(c.lien) + "\"" + ";\n";
		}

		for (const auto& p : t->noeuds) {
			const auto& c = p.second;
			if (!c.mot.empty() && c.lien != nullptr)
				genererGraphVizNoeud(c.lien, graph);
		}
	}
}

template <typename T, template< typename, typename > class Map>
std::string TriePatricia<T, Map>::genererGraphViz() {
	std::string graph;
	graph += "digraph";
	graph += "{";
	graph += " edge [label=\" \" tailclip=false arrowtail=dot dir=both]; node [shape=record];\n";

	genererGraphVizNoeud(t, graph);
	graph += "}";

	return graph;
}
