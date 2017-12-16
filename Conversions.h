#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <TrieHybride.h>
#include <TriePatricia.h>

template<typename T, template<typename, typename> class Map>
TrieHybride<T> Convertir(const TriePatricia<T, Map>&);

template<typename T, typename Equilibrage, template<typename, typename> class Map>
TriePatricia<T, Map> Convertir(const TrieHybride<T, Equilibrage>&);

#include "Conversions.hpp"

#endif // CONVERSIONS_H
