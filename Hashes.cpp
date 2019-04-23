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
  hashTable = new wordItem*[hashTableSize]; //create array
  this->hashTableSize = hashTableSize; //as suggested on piazaa


  for (int i = 0; i < hashTableSize; i++) {
    hashTable[i] = NULL; //set all to null
    }
}



HashTable::~HashTable(){ //delete all
}


void HashTable::addPlanet(planet newplanet){
  int index = getHash(newplanet.name);
  Planet* spot = hashTable[index]; //start at the head
  Planet* temp = new planet;
  Planet* prev = NULL;
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
      hashTable[index] = temp;
      return ;
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

wordItem* HashTable::searchTable(string word){

  int index = getHash(word);
  wordItem* temp;
  temp = hashTable[index];

  while (temp != NULL) {
    if (temp->word == word) {
      return temp;
    }
    else{
      temp=temp->next;
    }
  }
    return NULL;
}

bool HashTable::isInTable(string word){

  int index = getHash(word);
  wordItem* temp;
  temp = hashTable[index];
  while (temp != NULL) {
    if (temp->word == word) {
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
