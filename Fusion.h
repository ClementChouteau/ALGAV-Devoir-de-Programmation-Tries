#ifndef FUSION_H
#define FUSION_H

#include "TriePatricia.h"

template <typename T, template<typename, typename> class Map>
TriePatricia<T, Map> Fusion(const TriePatricia<T, Map>& t1, const TriePatricia<T, Map>& t2);

#include "Fusion.hpp"

#endif // FUSION_H
