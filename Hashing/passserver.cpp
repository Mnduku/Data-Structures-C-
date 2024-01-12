#include "passserver.h"

// Xian: in a shell, type "man crypt", and the MD5 can be found (which uses 22 characters of the password), and the usage will be shown as well.
// Note that it takes c_str, char [], not string directly as the input arguments. 
string PassServer::encrypt(const string & str) {
        char salt[] = "$1$########";
        char * password = new char [35];
        strcpy(password,crypt(str.c_str(), salt));

        string pword(password);
        string delim = "$";
        int pos = pword.find(delim, 0);
        pos = pword.find(delim, pos+1);
        pos = pword.find(delim, pos+1);
        pword.erase(0, pos+1);
        return pword;
	/*char salt[] = "$1$########";
	string ret = crypt(str.c_str(), salt);
	return ret.substr(1, 22);*/
}

PassServer::PassServer(std::size_t size){
   h = HashTable<string,string>(size);           //calls hashtable default constructor
}

PassServer::~PassServer(){
   h.clear();
}

bool PassServer::load(const char* filename){
   return h.load(filename);                    //loads the file, returns false if doesnt work
}

bool PassServer::addUser(std::pair<std::string, std::string> & kv){
   if (h.contains(kv.first) != true){
     std::pair<std::string, std::string> temp = kv;      //a temp variable holds the kv which
     temp.second = encrypt(temp.second);              //is then encrypted before insertion
     return h.insert(temp);
   }
   else return false;                                  //if insertion failed.
   return false;
}

bool PassServer::addUser(std::pair<std::string, std::string> && kv){
   if (h.contains(kv.first) != true){
     std::pair<std::string, std::string> temp = std::move(kv);      //a temp variable holds the kv which
     temp.second = encrypt(temp.second);              //is then encrypted before insertion
     return h.insert(temp);
   }
   else return false;                                  //if insertion failed.
   return false;
}

bool PassServer::removeUser(const std::string & k){
    return(h.remove(k));                            //calls hash table remove function
}

bool PassServer::find(const std::string & user) const{
   return h.contains(user);                                //calls hashtable find user func
}

void PassServer::dump() const{                          //calls hashtable dump func
   h.dump();
}

std::size_t PassServer::size() const{
   return h.size();
}

bool PassServer::write_to_file(const char* filename) const{
   return h.write_to_file(filename);                           //calls hashtable write to file function
}


bool PassServer::changePassword(const std::pair<std::string, std::string> & p, const std::string& newpassword){
  if(h.contains(p.first) != true){
     return false;
  }                                            //cannot change a pw that doesnt exist
  else{
     std::pair<std::string, std::string> temp = p;
     temp.second = encrypt(temp.second);

     if(h.match(temp) != true){
        return false;
     }
     else{                                      //this function checks for existance of the pw to be changed,                                                //then encrypts the new pw and replaced the old one wiith it
      std::string pw = encrypt(newpassword);
      temp.second = pw;
      return h.insert(temp); // new pw inserted
     }
  }
  return false;
}
