//April Ott, data structures, HW 1
#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

void displayMenu()
{
    cout << "Welcome to the astronomers toolkit" << endl;
    cout << "Please select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. View celestial data" << endl;
    cout << " 2. Add to the log" << endl;
    cout << " 3. Find what will be in the sky " << endl;
    cout << " 4. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}



int main(int argc, const char *argv[]){

  string fileName = argv[1]; //get filename
  string line;
  int choice;
  ifstream input(fileName); //create input stream

  /*if (input.is_open())
  {
      for (int i =0; getline(input,line); i++)//add in file
      { //while getline is applicable, load in the values
        insertIntoSortedArray(myArray, i, stoi(line)); //call the insert function with each number.

        for(int x=0; x<=i;x++) //for printing each number added
        {
          if(x == i)
          {
          cout <<myArray[x]; //cout the values
          }
          else
            cout << myArray[x] << ",";
        }
        cout << endl;
      }
      input.close(); //close file
  }
*/

  displayMenu();
  cin >> choice;
  if (choice = 1) { //if view celestial data
      /* code */
  }
  if (choice = 2) { //if view celestial data
      /* code */
  }
  if (choice = 3) { //if view celestial data
      /* code */
  }
  if (choice = 4) { //if view celestial data
    cout << "Goodbye!" << endl;
      return 0;
  }


  return 0; //exit
}
