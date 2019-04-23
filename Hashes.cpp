#include "HashTable.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

unsigned int HashTable::getHash(string word){
  unsigned int hashValue = 5381;
  int length = word.length();
  for (int i=0;i<length;i++)
  {
  hashValue=((hashValue<<5)+hashValue) + word[i];
  }
  hashValue %= hashTableSize;
  return hashValue;
}


HashTable::HashTable(int hashTableSize){
  hashTable = new planet*[hashTableSize]; //create array
  this->hashTableSize = hashTableSize; //as suggested on piazaa


  for (int i = 0; i < hashTableSize; i++) {
    hashTable[i] = NULL; //set all to null
    }
}



HashTable::~HashTable(){ //delete all
}


void HashTable::addPlanet(planet *newplanet){
//    cout << "added planet: " << newplanet->name << endl;

  int index = getHash(newplanet->name) ;
  planet* spot = hashTable[index]; //start at the head
  planet* prev = NULL;
  numItems++;


  if (spot !=NULL) { //if theres something in the index already
    numCollisions++;
  }

  while (spot != NULL) { //go to the end of the LL
    prev = spot;
    spot = spot->next;
  }

  if (spot == NULL) { //when its empty
    if (prev == NULL)
    { //if it needs to be first on the list

      hashTable[index] = newplanet;
//      cout << "added planet to index: "<< index <<" name: " << newplanet->name << endl;
    //  cout << "calling view index in add function" << endl;
      view_index(newplanet->name);
      return;
    }
    prev->next = newplanet;
  }
}


void HashTable::view_index(string name){



    int index = getHash(name);
   cout << "index in view index is "<< hashTable[index]->name<<" index is "<< index<< endl;
}

planet* HashTable::searchTable(string word,int index){ //word == name
cout << "searching planet:  " << word << endl;
cout << "calling view index in search function" << endl;
view_index(word);

planet* temp;

  bool found = false;
  if (word == "Sun") {
      int index = getHash("Sun");
     cout << "index name is "<< hashTable[index]->name<<" index is "<< index<< endl;
     temp = hashTable[index];
     cout<< "temp name now "<< temp->name << endl;
  }
  if (word == "Mercury") {
      int index = getHash("Mercury");
      temp = hashTable[index];
  }
  if (word == "Venus") {
      int index = getHash("Venus");
      temp = hashTable[index];
  }
  if (word == "Earth") {
      int index = getHash("Earth");
      temp = hashTable[index];
  }
  if (word == "Mars") {
      int index = getHash("Mars");
      temp = hashTable[index];
  }
  if (word == "Jupiter") {
      int index = getHash("Jupiter");
      temp = hashTable[index];
  }
  if (word == "Saturn") {
      int index = getHash("Saturn");
      temp = hashTable[index];
  }
  if (word == "Uranus") {
      int index = getHash("Uranus");
      temp = hashTable[index];
  }
  if (word == "Neptune") {
      int index = getHash("Neptune");
      temp = hashTable[index];
  }


 //cout << "22222 name at index is " << (hashTable[index])->name << endl;

 // cout << "name at index is " << (hashTable[index])->name << endl;
 // cout << "temps name is " << temp->name << endl;
  //cout << "search hash calculated is: " << index << endl;

    if (temp->name == word) {
        found = true;
        cout << "!-------------------------------!" <<endl;
        cout << "Planet Details: " << " \n";
        cout << "Name: " << temp->name << "\n";
        cout << "Radius in km: " << temp->radius << "\n";
        cout << "Distance from the sun(km): " << temp->distance << "\n";
        cout << "Orbital tilt: " << temp->orbit_tilt << "\n";
        cout << "Rotational period: " << temp->rotat_period << "\n";
        cout << "Orbit period: " << temp->orbit_period << "\n";
        cout << "!-------------------------------!" <<endl;
      return temp;
    }
    else{
      temp=temp->next;
    }

  if (found == false) {
      cout << "Planet not found." << endl;
        return NULL;
  }
  return NULL;

}
void HashTable::planet_search(string name){
     int index = getHash(name);
     view_index(name);
     cout << "from search function part 1" << endl;
     searchTable(name,index);
    //cout << "temp name 111 is " << temp->name;
}

void HashTable::load_planets(string input)
{
    cout << "Loading planets! .... .. . ." << endl;
    vector <string> row; //temp for each row
    planet *tempP = new planet;
    string temp;
    fstream input_celestial;
    input_celestial.open("planet_data.csv",ios::in); //create input stream

    string whole_line = "";
    string word = "";
    int count=0;

    while (input_celestial >> temp) {
    //    cout << "temp is : " << temp << endl;
        if (temp == "//#") {
            return;
        }
        row.clear(); //clear the std::vector<int> v;
        stringstream ss(temp); //call a stringstream on inputted line

        while(getline(ss,word,',')){ //while in the line, push each word to vector
            row.push_back(word); //push to vector
        //    cout << "got here " << "word is: "<<word<< endl;
        }
             tempP->name = row[0];
             tempP->radius = row[1]; //add in all the data
             tempP->distance = row[4];
             tempP->orbit_tilt = row[6];
             tempP->rotat_period = row[10];
             tempP->orbit_period = row[11];
             int index = getHash(tempP->name);
             addPlanet(tempP); //call add funtion'

             cout << "calling view index" << endl;
             view_index(tempP->name);
             row.clear();


        }
        return;
}

bool HashTable::isInTable(string word){ //planets are indexed by name

  int index = getHash(word); //get index on name
  planet* temp;
  temp = hashTable[index];
  while (temp != NULL) {
    if (temp->name == word) {
      return true;
    }
    else{
      temp=temp->next;
    }
  }
  return false;
}







//
