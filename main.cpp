#include <iostream>
#include <string>
using namespace std;
#include "Diary.h"

int main() {
string userFile = "./settings/userList.dat";
string dataFile = "./data/entriesList.txt";

//Diary Creation
Diary dd("Daily Diary");

//Load Users
if (!dd.loadUsers(userFile)) {
  cout << "ERR: Cannot load users from " << userFile << endl;
  return 1;
}

//Load Diary Entries
if (!dd.loadEntries(dataFile)) {
  cout << "ERR: Cannot load entries from " << dataFile << endl;
  return 1;
}

dd.login();
dd.run();

//Export + Save Entries
if (!dd.saveEntries(dataFile)) {
  cout << "ERR: Cannot load entries from " << dataFile << endl;
  return 1;
}

  return 0;
}



/* External Things:

//int main(int argc, char* argv[]) {}
//verify messages & user files are given 

if (argc != 3) {
  cout << "Usage: " << argv[0] << "user_file data_file" << endl;
  return 1;
}
*/
//string userFile = argv[1];
//string dataFile = argv[2];
