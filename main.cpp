#include "TrieHybride.h"
#include "TrieTest.h"
#include "TriePatricia.h"
#include "Conversions.h"
#include "Fusion.h"
#include "TriePerfs.h"
#include "TrieStdSet.h"

#include <iostream>
#include <fstream>
#include <string>

#include <ctime>

std::vector< std::vector<char> > obtenirMotsFichier(std::vector< std::string > nomsFichiers);
std::vector< std::vector<char> > decouper(std::string phrase);
void genererGraphes(const std::vector< std::vector<char> >& mots);

int main() {
	std::ios_base::sync_with_stdio(false);

	/// GENERATION GRAPHES
	const auto phrase = "A quel genial professeur de dactylographie sommes nous redevables de la superbe phrase ci dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?";
	genererGraphes(decouper(phrase));

	/// TESTS
	std::vector< std::string > nomsFichiers =
	{
		"../Shakespeare/1henryiv.txt",
		"../Shakespeare/1henryvi.txt",
		"../Shakespeare/2henryiv.txt",
		"../Shakespeare/2henryvi.txt",
		"../Shakespeare/3henryvi.txt",
		"../Shakespeare/allswell.txt",
		"../Shakespeare/asyoulikeit.txt",
		"../Shakespeare/cleopatra.txt",
		"../Shakespeare/comedy_errors.txt",
		"../Shakespeare/coriolanus.txt",
		"../Shakespeare/cymbeline.txt",
		"../Shakespeare/hamlet.txt",
		"../Shakespeare/henryviii.txt",
		"../Shakespeare/henryv.txt",
		"../Shakespeare/john.txt",
		"../Shakespeare/julius_caesar.txt",
		"../Shakespeare/lear.txt",
		"../Shakespeare/lll.txt",
		"../Shakespeare/macbeth.txt",
		"../Shakespeare/measure.txt",
		"../Shakespeare/merchant.txt",
		"../Shakespeare/merry_wives.txt",
		"../Shakespeare/midsummer.txt",
		"../Shakespeare/much_ado.txt",
		"../Shakespeare/othello.txt",
		"../Shakespeare/pericles.txt",
		"../Shakespeare/richardiii.txt",
		"../Shakespeare/richardii.txt",
		"../Shakespeare/romeo_juliet.txt",
		"../Shakespeare/taming_shrew.txt",
		"../Shakespeare/tempest.txt",
		"../Shakespeare/timon.txt",
		"../Shakespeare/titus.txt",
		"../Shakespeare/troilus_cressida.txt",
		"../Shakespeare/twelfth_night.txt",
		"../Shakespeare/two_gentlemen.txt",
		"../Shakespeare/winters_tale.txt"
	};
	const auto mots = obtenirMotsFichier(nomsFichiers);

	#ifndef NDEBUG
	assertTrie< TrieHybride<char> >();
	assertTrie< TrieHybride<char, AVL> >();
	assertTrie< TriePatricia<char> >();
	#endif // NDEBUG

	/// BENCHS
	std::cout << "TrieHybride<char>" << std::endl << performanceLog< TrieHybride<char> >(mots) << std::endl;
	std::cout << "TrieHybride<char, AVL>" << std::endl << performanceLog< TrieHybride<char, AVL> >(mots) << std::endl;
	std::cout << "TriePatricia<char>" << std::endl << performanceLog< TriePatricia<char> >(mots) << std::endl;
	std::cout << "TrieStdSet<char>" << std::endl << performanceLog< TrieStdSet<char> >(mots) << std::endl;

	/// FUSION
	{
		TrieHybride<char> t0;
		for (auto i = 0; i < (long)mots.size(); i++)
			t0.AjoutMot(mots[i]);

		clock_t begin_time, end_time;

		begin_time =  clock();
		TriePatricia<char> t1;
		for (auto i = 0; i < (long)mots.size()/2; i++)
			t1.AjoutMot(mots[i]);
		end_time =  clock();
		std::cout << "TrieHybride<char> (1/2) AjoutMot: " << t1.ComptageMots() << " " << (float( end_time - begin_time ) /  CLOCKS_PER_SEC)*1000 << " ms" << std::endl;

		begin_time =  clock();
		TriePatricia<char> t2;
		for (auto i = mots.size()/2; i < mots.size(); i++)
			t2.AjoutMot(mots[i]);
		end_time =  clock();
		std::cout << "TrieHybride<char> (2/2) AjoutMot: " << t2.ComptageMots() << " " << (float( end_time - begin_time ) /  CLOCKS_PER_SEC)*1000 << " ms" << std::endl;

		begin_time =  clock();
		TriePatricia<char> t3 = Fusion(t1, t2);
		end_time =  clock();
		std::cout << "Fusion TrieHybride<char> (1/2) (2/2): " << t3.ComptageMots() << " " << (float( end_time - begin_time ) /  CLOCKS_PER_SEC)*1000 << " ms" << std::endl;

		assertInstancesTrieEgaux(t0, t3);
	}

	std::cout << std::endl;

	/// CONVERSIONS
	{
		TrieHybride<char> t1;
		for (auto i = 0; i < (long)mots.size(); i++)
			t1.AjoutMot(mots[i]);

		clock_t begin_time, end_time;

		begin_time =  clock();
		TriePatricia<char> t2 = Convertir<char, None, UnorderedMap>(t1);
		end_time =  clock();
		std::cout << "Conversion TrieHybride<char> => TriePatricia<char>: " << t2.ComptageMots() << " " << (float( end_time - begin_time ) /  CLOCKS_PER_SEC)*1000 << " ms" << std::endl;

		begin_time =  clock();
		TrieHybride<char> t3 = Convertir(t2);
		end_time =  clock();
		std::cout << "Conversion TriePatricia<char> => TrieHybride<char>: " << t3.ComptageMots() << " " << (float( end_time - begin_time ) /  CLOCKS_PER_SEC)*1000 << " ms" << std::endl;

		assertInstancesTrieEgaux(t2, t3);
	}

	std::cout << std::endl;

	/// TESTS LONGS
	assertClassesTrieEgaux< TrieHybride<char>, TrieStdSet<char> >(mots);
	assertClassesTrieEgaux< TrieHybride<char, AVL>, TrieHybride<char> >(mots);
	assertClassesTrieEgaux< TriePatricia<char>, TrieHybride<char> >(mots);

	std::cout << "Terminé" << std::endl;

	return 0;
}

std::vector< std::vector<char> > decouper(std::string phrase) {
	std::vector< std::vector<char> > mots;
	std::istringstream iss(phrase);

	std::string mot;
	while (iss >> mot)
		mots.push_back(std::vector<char>(mot.begin(), mot.end()));

	return mots;
}

std::vector< std::vector<char> > obtenirMotsFichier(std::vector< std::string > nomsFichiers) {
	std::vector< std::vector<char> > mots;

	for (std::string nomFichier : nomsFichiers) {
		std::ifstream fichier;
		fichier.open(nomFichier, std::ifstream::in);

		std::string mot;
		while (fichier >> mot) {
			std::vector<char> mot_vec(mot.begin(), mot.end());
			mots.push_back(mot_vec);
		}

		fichier.close();
	}

	mots.shrink_to_fit();
	return mots;
}

void genererGraphes(const std::vector< std::vector<char> >& mots) {
	TrieHybride<char> t1;
	TrieHybride<char, AVL> t2;
	TriePatricia<char>t3;

	for (const auto& mot : mots) {
		t1.AjoutMot(mot);
		t2.AjoutMot(mot);
		t3.AjoutMot(mot);
	}

	std::ofstream out1("TrieHybride.dot");
	out1 << t1.genererGraphViz();

	std::ofstream out2("TrieHybrideAVL.dot");
	out2 << t2.genererGraphViz();

	std::ofstream out3("TriePatricia.dot");
	out3 << t3.genererGraphViz();
}
