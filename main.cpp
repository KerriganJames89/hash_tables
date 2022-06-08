#include "passserver.h"
#include "hashtable.h"
using namespace std;

//clang++-7 -pthread -lcrypt -std=c++11 -o main main.cpp passserver.cpp

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main()
{
  int capacity;
  char choice;

  cout << "Enter hash table capacity: ";
  cin >> capacity;

  if(capacity <= 0)
  {
    cout << "Invalid capacity; defaulting to " << cop4530::default_capacity << endl;
    capacity = cop4530::default_capacity;
  }

  PassServer server(capacity);

  while(true)
  {
    string str1 = "";
    string str2 = "";
    string str3 = "";

    Menu();
    cin >> choice; cout << endl;
    cin.ignore();

   switch(choice) 
   {
    case 'l' :
      cout << "Enter filename: ";
      cin >> str1; 

      if(server.load(str1.c_str()))
      {
        cout << "File loaded successfully" << endl;
      }

      else
      {
        cout << "Invalid filename" << endl;
      }
      break;

    case 'a' :
      cout<<"Enter username: ";
      cin >> str1;
      cin.ignore();
      cout<<"Enter password: ";
      cin >> str2;
      cin.ignore();
      
      if(server.addUser(make_pair(str1, str2)))
      {
        cout<< "User " << str1 << " added / updated" << endl;
      }

      else
      {
        cout << "Invalid username" << endl;
      }
      break;

      case 'r' :
      cout<<"Enter username: ";
      cin >> str1; cout << endl;

      if((server.removeUser(str1)))
      {
        cout << "User removed" << endl;
      }

      else
      {
        cout << "Invalid username" << endl;
      }
      break;

    case 'c' :
      cout<<"Enter username: ";
      cin >> str1;
      cin.ignore();
      cout<<"Enter old password: ";
      cin >> str2;
      cin.ignore();
      cout<<"Enter new password: ";
      cin >> str3;
      cin.ignore();
      
      if(server.changePassword((make_pair(str1, str2)), str3))
      {
        cout << "Password changed" << endl;
      }

      else
      {
        cout << "Invalid username or password" << endl;
      }
      break;

    case 'f' :
      cout<<"Enter username: ";
      cin >> str1; 

      if(server.find(str1))
      {
        cout << "User " << str1 << " found" << endl;
      }

      else
      {
        cout << "User " << str1 << " not found" << endl;
      }

      break;

    case 'd' :
      server.dump();
      cout << "Hashtable dumped" << endl;
      break;

    case 's' :
      cout << "The hashtable size is: " << server.size() << endl;
      break;

    case 'w' :
      cout << "Enter filename to write to: ";
      cin >> str1;
      
      if(server.write_to_file(str1.c_str()))
      {
        cout << "File written successfully" << endl;
      }

      else
      {
        cout << "Invalid filename" << endl;
      }
      break;

    case 'x' :
      cout << "Exiting...";
      return 0;
      break;
          
      default :
      cout << "Invalid choice" << endl;
    }
  }
}