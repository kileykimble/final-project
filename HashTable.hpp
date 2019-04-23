#ifndef HW_7_HASH_TABLE
#define HW_7_HASH_TABLE
//borrowed from hw 7, thanks TA's
#include <string>
using namespace std;

// struct to store word + count combinations
struct planet
{
    string name;
    string radius; //in km
    string distance; //from sun
    string orbit_tilt;
    string rotat_period;
    string orbit_period;
    string moons;

    planet* next;
};



/* class HashTable for storing words.
 *   You will create two hash tables in your driver:
 *      - one for storing stop words
 *      - one for storing unique non-stop words
 *   Why? We can load all the stopwords into the first table.
 *   Then, we can quickly check that first hash table to see if
 *   a word is a stopword before adding it to the second.
 */
class HashTable {
  public:
    HashTable(int hashTableSize);
    ~HashTable();
    void addPlanet(planet *newplanet);
    bool isInTable(std::string word);
    void load_planets(string input);
    void planet_search(string name);

  private:
    /* member functions */
    unsigned int getHash(std::string word);
    planet* searchTable(std::string word);

    /* instance variables */
    planet** hashTable;
    int hashTableSize;
    int numItems;
    int numCollisions;
};


/* size to make your stopwords hash table */
const int STOPWORD_TABLE_SIZE = 50;

/* Required functions for use in main.
 *   you are free to also define your own helper functions
 *   for your driver in your .cpp files if you wish.
 * These are the same functions from hw2, but use a
 *   hashtable instead of an array. */

/* load stopwords into the stopwords hash table */
void getStopWords(char *ignoreWordFileName, HashTable &stopWordsTable);
/* check table to see if a word is a stopword or not */
bool isStopWord(std::string word, HashTable &stopWordsTable);

#endif
