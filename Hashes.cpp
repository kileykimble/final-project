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
  int index = getHash(newplanet->name);
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
      return;
    }
    prev->next = temp;
  }
}



  void getStopWords(char *ignoreWordFileName, HashTable &stopWordsTable){

      ifstream input(ignoreWordFileName); //start ifstream
      string word = "";
      while(getline(input,word)){
        stopWordsTable.addWord(word);
      }

  }


int HashTable::getNumCollisions(){
  return numCollisions;
}
int HashTable::getNumItems(){
  return numItems;

}


vector <wordItem> sorterHelper(vector <wordItem> n_list, int x){

    wordItem temp;    //sort helper, iterate and sort the vector
    for (int i = 0; i < x-1; i++) {
        for (int j = 0; j < x-i-1; j++) {
            if (n_list[j].count < n_list[j+1].count) { //comparator
                temp = n_list[j];
                n_list[j] = n_list[j+1];   //if values needs to switch
                n_list[j+1] = temp;
            }
        }
    }
    return n_list;
}


void HashTable::printTopN(int n){

    vector <wordItem> n_list; //create std::vector<int> v;
    wordItem *temp = new wordItem;
    temp->count = 1;
    temp->next = NULL;
    int counter = 0;

    for (int i = 0; i < hashTableSize; i++) {
        temp = hashTable[i]; //start at the beginning
        while (temp!=NULL) { //while not at the end
            n_list.push_back(*temp);
            temp = temp->next;
            counter++;
        }
    }

    n_list = sorterHelper(n_list, counter); //call sorterHelper

    for (int r = 0; r < n; r++) {
       cout <<std::fixed << setprecision(4)<<(float)n_list[r].count/getTotalNumWords() << " - " << n_list[r].word << endl;
    }
}

int HashTable::getTotalNumWords(){

  int total = 0;
  wordItem* temp;

  for (int i = 0; i < hashTableSize; i++) {
    temp = hashTable[i];
    while (temp!=NULL) {
      total = total + temp->count;
      temp = temp->next;
    }
  }
  return total;
}

planet* HashTable::searchTable(string word){ //word == name

  int index = getHash(word);
  planet* temp;
  temp = hashTable[index];

  while (temp != NULL) {
    if (temp->name == word) {
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
  }
  cout << "Planet not found."
    return NULL;
}
void HashTable::planet_search(string name){
    planet *temp = searchTable(name);
}

void load_planets(string input)
{
    cout << "Loading planets! .... .. . ." << endl;
    vector <string> row; //temp for each row
    planet *temp = new planet;
    fstream input_celestial;
    input_celestial.open("planet_data.csv",ios::in); //create input stream

    string whole_line = "";
    string word = "";
    int count=0;

    while (input_celestial >> temp) {
        //cout << "temp is : " << temp << endl;
        row.clear(); //clear the std::vector<int> v;
        stringstream ss(temp); //call a stringstream on inputted line

        while(getline(ss,word,',')){ //while in the line, push each word to vector
            row.push_back(word); //push to vector
        //    cout << "got here " << "word is: "<<word<< endl;
        }
             temp->name = row[0];
             temp->radius = row[1]; //add in all the data
             temp->distance = row[4];
             temp->orbit_tilt = row[6];
             temp->rotat_period = row[10];
             temp->orbit_period = row[11];
             HashTable::addPlanet(temp); //call add funtion
        }
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

void HashTable::incrementCount(string word){
    wordItem *temp = searchTable(word);
    while (temp !=NULL) {
        if (temp->word == word) {
            temp->count++; //add one
        }
        else{
            temp=temp->next; //go to next
        }
    }

}


bool isStopWord(std::string word, HashTable &stopWordsTable){

      if (stopWordsTable.isInTable(word)) {
        return true;
      }
      else{
       return false;
     }
}











//
