#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <crypt.h>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <cstdlib>
#include <cstring>

using namespace std;

namespace cop4530
{

template <typename K, typename V>
class HashTable;

// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;


// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;

template <typename K, typename V>
class HashTable
  {
  public:

    HashTable();
    HashTable(size_t n);
    ~HashTable();

    bool contains(const K & k) const;
    bool match(const std::pair<K, V> &kv);
    bool load(const char *filename);
    bool remove(const K & k);
    bool insert(const std::pair<K, V> & kv);
    bool insert (std::pair<K, V> && kv);
    void clear();
    void dump() const;
    bool write_to_file(const char *filename) const;
    size_t vectorSize() const;

  private:

    vector<list<pair<K, V>>> hashVector;
    size_t length;

    void makeEmpty();
    void rehash();
    size_t myhash(const K &k) const;
    unsigned long prime_below (unsigned long);
    void setPrimes(vector<unsigned long>&);
  };
#include "hashtable.hpp"
}

#endif
