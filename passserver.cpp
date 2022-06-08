#include "passserver.h"


PassServer::PassServer(size_t size) : passwords(size)
{

}

PassServer::~PassServer()
{
 passwords.clear();
}

//Adds a new user to the hashtable
bool PassServer::addUser(const pair<string, string> & p)
{
	string pass = encrypt(p.second);

  pair <string, string> user(p.first, pass);

  //cout<<"test3\n";
  return(passwords.insert(user));
}

//Adds a new user to the hashtable
bool PassServer::addUser(pair<string, string> && p)
{
  p.second = encrypt(p.second);
  //cout<<"test4\n";
  return passwords.insert(move(p));
}

//Removes a user from the hashtable
bool PassServer::removeUser (const string & k)
{
  return passwords.remove(k);
}

//Changes an exisiting user's password
bool PassServer::changePassword (const pair<string, string> & p, const string& newpasswd)
{
  if(p.second == newpasswd)
	{
		return false;
	}
  
  pair <string, string> newPass(p.first, newpasswd);

	return addUser(newPass);
}

//Checks if user is in hashtable
bool PassServer::find( const string & user) const
{
  //cout<<"testfind";
  return passwords.contains(user);
}

//Loads hashtable entries from a file
bool PassServer::load(const char * file)
{
  return passwords.load(file);
}

//Dumps the hashtable entries into a file
bool PassServer::write_to_file (const char * file) const
{
  
  return passwords.write_to_file(file);
}

//Dumps the hashtable structure and entries to screen
void PassServer::dump () const
{
	return passwords.dump();
}

//Returns the size of the hashtable
size_t PassServer::size() const
{
	return passwords.vectorSize();
}

//Encrypts the password
string PassServer::encrypt(const string & str)
{
	char salt[] = "$1$########";
	string encrypt = crypt(str.c_str(), salt);
	encrypt.replace(0, 12, "");
	return encrypt;
}
