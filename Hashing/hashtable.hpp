
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size){
   currentSize = 0;
   int siz = prime_below(size);
   if(siz == 0){                           //sets the size to prime below 101 by default
      theLists.resize(default_capacity);   //if prime below size is 0 sets to default
   }
   else theLists.resize(siz);
}

template <typename K, typename V>
HashTable<K, V>::~HashTable(){
  makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const{
   auto& search2 = theLists[myhash(k)];
   for(auto& search1 : search2){
      if(search1.first == k){
         return true;                      //uses myhash to find which list the key would be in,
      }                                    //then uses auto to iterate through that list searching the first
   }                                       //value of every kv pair searching to find a key match
   return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V>& kv) const{
   auto& search2 = theLists[myhash(kv.first)];

   for(auto& search1 : search2){           //This function operates the same as the previous,
      if(search1.first == kv.first && search1.second == kv.second){// but compares both k and v instead of k
         return true;
      }
   }
   return false;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V>& kv){
   if(match(kv)) return false;             //returns false if kv pair already exists
   auto& search2 = theLists[myhash(kv.first)];

   if(contains(kv.first)){                 //if the key already exists in the ht
     for (auto& search1 : search2){
        if(search1.first == kv.first) search1.second == kv.second;
        return true;
     }                                     //if there is a key match then the v values are matched to each other
   }
   else{
      search2.push_back(kv);               //uses the list adt push back to add the kv pair to the right list
      currentSize++;
      if(currentSize > theLists.size()) rehash();
      return true;
   }
   return false;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv){
   if(match(kv)) return false;             //returns false if kv pair already exists
   auto& search2 = theLists[myhash(kv.first)];

   if(contains(kv.first)){                 //if the key already exists in the ht
     for (auto& search1 : search2){
        if(search1.first == kv.first) std::swap(search1.first, kv.first);
        return true;
     }                                     //if there is a key match then the v values are matched to each other
   }
   else{
      search2.push_back(std::move(kv));    //uses the list adt push back to add the kv pair to the right list
      currentSize++;
      if(currentSize > theLists.size()) rehash();
      return true;
   }
   return false;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K& k){

  if (contains(k) != true) return false;   //if the kv pair cannot be found exits the function
  auto& search = theLists[myhash(k)];
  int p = 0;

  for (auto& search1 : search){
     if(search1.first == k){
        auto itr = search.begin();         //if the key to be deleted is found, an iterator pointing to
        for (int i = 0; i < p; i++)itr++;  //that list is made,and then replaced with the same list but
        itr = search.erase(itr);           //with the value replaced
    	--currentSize;
    	return true;
     }
     p++;
  }
  return false;
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char* filename){
  std::ifstream infile;
  infile.open(filename);
  if (!infile){                            //using the ifstream object we open the passed in file
     cout << "File could not found or is inacessible.\n";
     return false;                         //if the file cannot be opened an error message is left and the function terminates
  }
  std::string str1,str2;

  while (std::getline(infile,str2)){       //loops through each line of text in file
     std::pair<K, V> cpair;                //holds they key value from each line
     std::istringstream str3(str2);
     int index = 0;

     while (str3 >> str1){
        if (index == 0) cpair.first = str1;//in case of first word on line
        else if (index == 1) cpair.second = str1;   //in case second word on line
        else{
           cout << "Function terminated. Each line must contain 2 strings, one key and one value";
           return false;
        }
     index++;
     }
  insert(cpair);                           // the new key value pair read is inserted
  }
  infile.close();
  return true;
}

template <typename K, typename V>
void HashTable<K, V>::dump() const{

   for (int i = 0; i < theLists.size(); i++){            //loops through linked lists
      cout << "index" << i << ": ";
      auto itr = theLists[i].begin();

      for (auto& curlist : theLists[i]){                 //iterates through the linked lists
         if (itr != theLists[i].begin()) cout << " , ";
         cout << curlist.first << " " << curlist.second; // print eack KV pair out
         itr++;
      }
      cout << "\n";
   }
}

template <typename K, typename V>
std::size_t HashTable<K, V>::size() const{
   return currentSize;
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename) const{

  std::ofstream writeout;
  writeout.open(filename);

  if(!writeout){
    cout << "File Creation Failed: " << filename << endl;
    return false;
  }

  int index = static_cast<int>(size());
  for(auto & curlist : theLists){
     for(auto & Keyval : curlist){
        writeout << Keyval.first <<"-"<< Keyval.second;
        if(index > 1){
           writeout << "\n";
           index--;
        }
     }
  }
  writeout.close();
  return true;
}

template <typename K, typename V>
void HashTable<K, V>::makeEmpty(){
  if (currentSize == 0){
     return;                                          //in case the hash table is already empty
  }
  else{
    for (auto& thisList : theLists){                   //calls the library clear function for
       thisList.clear();                               //all the linked lists in the hash table
    }
    currentSize = 0;
  }
}

template <typename K, typename V>
void HashTable<K, V>::rehash(){
   auto list1 = theLists;
   theLists.resize(prime_below(5 * theLists.size()));   //increases hash table size
   makeEmpty();                                        //empty h
   for (auto & list2 : list1){                          //iterates through new empty
                                                       //hash table putting values in
      for (auto & i : list2){
 	insert(std::move(i));
      }
   }
}
template <typename K, typename V>
std::size_t HashTable<K, V>::myhash(const K& k) const{
  static std::hash<K> hf;                             // from slides, applies hashing function
   return hf(k) % theLists.size();
}


template <typename K, typename V>
void HashTable<K, V>::clear(){ 
   makeEmpty();
}



















template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n)
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

template <typename K, typename V>
void HashTable<K, V>::setPrimes(vector<unsigned long> & vprimes)
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

