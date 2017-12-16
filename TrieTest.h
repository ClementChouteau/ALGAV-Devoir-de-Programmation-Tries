#ifndef TRIE_TEST_HPP
#define TRIE_TEST_HPP

#include "Trie.h"

#include <vector>
#include <string>

template<typename GivenTrie>
void assertTrie();

template<typename GivenTrie1, typename GivenTrie2>
void assertClassesTrieEgaux(const std::vector< std::vector<char> >&);

template<typename T>
void assertInstancesTrieEgaux(Trie<T>& t1, Trie<T>& t2);

#include "TrieTest.hpp"

#endif // TRIE_TEST_HPP
