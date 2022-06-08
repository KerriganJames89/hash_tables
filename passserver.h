#ifndef PASSSERVER_H
#define PASSSERVER_H

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
#include "hashtable.h"

using namespace std;
using namespace cop4530;

class PassServer
  {
  public:
    PassServer(size_t size);
    ~PassServer();
    
    bool find(const string &k) const;

    bool addUser(const pair<string, string> & key_value);
    bool addUser(pair<string, string> && key_value);
    bool removeUser(const string & k);
    bool changePassword(const pair<string, string> &p, const string &newpasswd);
    void clear();

    bool load(const char *filename);
    void dump() const;
    bool write_to_file(const char *filename) const;

    size_t size() const;

  private:
    HashTable<string, string> passwords;
    string encrypt(const string & str);
  };

#endif
