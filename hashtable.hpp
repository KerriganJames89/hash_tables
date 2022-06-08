
/*Create a hash table, where the size of the vector is set to prime_below(size) (where size is 
default to 101), where prime_below() is a private member function of the HashTable and provided to you.*/
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size)
{
  hashVector.resize(prime_below(size));
}

//Delete all elements in hash table
template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
  //fine as is
}

//check if key k is in the hash table
template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const
{
  for (const auto &itPair : hashVector[myhash(k)])
  {
    if (itPair.first == k)
    {
      return true;
    }
  }

  return false;
}

//check if key-value pair is in the hash table.
template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv)
{
  for (const auto &itPair : hashVector[myhash(kv.first)])
  {
    if (itPair.first == kv && itPair.second == kv)
    {
      return true;
    }
  }

  return false;
}

/* add the key-value pair kv into the hash table. Don't add if kv is already 
in the hash table. If the key is the hash table but with a different value, 
the value should be updated to the new one with kv. Return true if kv is inserted or the
value is updated; return false otherwise (i.e., if kv is in the hash table).*/
template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv)
{

  auto &mylist = hashVector[myhash(kv.first)];
  
  for(auto &itPair : mylist)
  {
    if(kv.first == itPair.first)
    {
      if(kv.second == itPair.second) 
      {
        return false;
      }

      itPair.second = kv.second;
      //cout<<"test1 : " << itPair.second;
      return true;
    }
  }

  mylist.push_back(kv);


  if(hashVector.size() < mylist.size())
  {
    rehash();
  }

  //cout<<"test2";

  return true;
}

//move version of insert
template <typename K, typename V>
bool HashTable<K, V>::insert (std::pair<K, V> && kv)
{
  auto &mylist = hashVector[myhash(kv.first)];
  
  for(auto &itPair : mylist)
  {
    if(kv.first == itPair.first)
    {
      if(kv.second == itPair.second) 
      {
        return false;
      }

      //cout<<"test6";

      itPair.second = std::move(kv.second);
      return true;
    }
  }

  mylist.push_back(kv);

  if(hashVector.size() < mylist.size())
  {
    rehash();
  }

  //cout<<"test5";
  return true;
}

/*delete the key k and the corresponding value if it is in the hash table. 
Return true if k is deleted, 
return false otherwise (i.e., if key k is not in the hash table)*/
template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
  bool type = 0;

  auto &mylist = hashVector[myhash(k)];

  for(auto it = mylist.begin(); it != mylist.end();) 
  {
    if((*it).first == k) 
    {
      it = mylist.erase(it);
      type = 1;
    }

    else ++it;
  }

  return type;
}

//delete all elements in the hash table
template <typename K, typename V>
void HashTable<K, V>::clear()
{
  makeEmpty();
}

/*load the content of the file with name filename into the hash table. In the file, 
each line contains a single pair of key and value, separated by a white space.*/
template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
{
  ifstream file;
  file.open(filename);
  string line;

  if(file.fail())
  {
    return false;
  }
  
  string buffer = "";
  string k = "";

  while (!file.eof())
  {
    getline(file, line);

    for(int i = 0; i < line.length(); i++)
    {
      //if not a space, add to buffer
      if(!isspace(line[i]))
      {
      buffer += line[i];
      }

      //if space then buff key
      else if(k.length() == 0)
      {
        k = buffer;
        buffer = "";
      }
    }

    //insert both key and value into pair
    insert(make_pair(k, buffer));
    k = "";
    buffer = "";

  }
  
  file.close();
  return true;
}

/*display all entries in the hash table. If an entry contains multiple key-value pairs, 
separate them by a semicolon character (:) (see the provided executable for the exact output format).*/
template <typename K, typename V>
void HashTable<K, V>::dump() const
{
  for(int i = 0; i < hashVector.size(); i++) 
  {
    cout << i << ": ";

    if(!hashVector[i].empty())
    {
      for(auto it = hashVector[i].begin(); it != hashVector[i].end(); ++it)
      {
        if(it != hashVector[i].begin())
        {
          cout << " : "; 
        }

        cout << (*it).first << " " << (*it).second;
      }
    }
    cout << endl;
  }
}



/*write all elements in the hash table into a file with name filename. Similar to the file format
in the load function, each line contains a pair of key-value pair, separated by a white space.*/
template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const
{
  ofstream file;
  file.open(filename);

  if(!file.fail())
  {
    return false;
  }

  for (const auto &itList : hashVector)
  {
    for (const auto &itPair : itList)
    {
      file << itPair.first << " " << itPair.second << endl;
    }
  }

  file.close();
  return true;
}


//Private Helper Functions

/* delete all elements in the hash table. The public
interface clear() will call this function*/
template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
  for(auto l : hashVector) 
  {
    l.clear();
  }
}

/*Rehash function. Called when the number of elements 
in the hash table is greater than the size of the vector*/
template <typename K, typename V>
void HashTable<K, V>::rehash()
{
  auto tempVector = hashVector;
  int newSize = prime_below(hashVector.size() * 2);

	hashVector.resize(newSize);

	clear();

  for (const auto &itList : tempVector)
  {
    for (const auto &itPair : itList)
    {
     insert(move(itPair));
    }
  }
}

//return the index of the vector entry where k should be stored.
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const
{

  //some code from stackoverflow but cant get it to work; I'm not sure if we were provided the full code for type template hashes, but I looked everywhere. This code would have worked with string and int values I believe

  /*const char *k_data = reinterpret_cast<const char *>(&k);
  size_t hashval = 0;

  for(size_t i=0; i<sizeof(k); ++i, ++k_data) {
    hashval = *k_data + 31 * hashval;
  }

  return hashval % hashVector.size();*/

  hash<K> newHash; 

	return newHash(k) % hashVector.size();
}

template <typename K, typename V>
size_t HashTable<K, V>::vectorSize() const
{
  return hashVector.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}
