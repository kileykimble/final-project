//April Ott, Final project data structures
#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


void display_planet(string name)
{
//    cout << "display planet called, 14"<<endl;
    fstream input_celestial;
    input_celestial.open("planet_data.csv",ios::in); //create input stream

    string whole_line = "";
    string temp;
    string word = "";
    vector <string> row;
    int count=0;
    bool found = false;

    while (input_celestial >> temp) {
        //cout << "temp is : " << temp << endl;
        row.clear(); //clear the std::vector<int> v;
        getline(input_celestial,whole_line);
        stringstream ss(temp); //call a stringstream on inputted line

        while(getline(ss,word,',')){ //while in the line, push each word to vector
            row.push_back(word); //push to vector
        //    cout << "got here " << "word is: "<<word<< endl;
        }

        if (name == row[0]) { //check names. comparing 1st index of vector
            found = true;
            cout << "!-------------------------------!" <<endl;
            cout << "Planet Details: " << " \n";
            cout << "Name: " << row[0] << "\n";
            cout << "Radius in km: " << row[1] << "\n";
            cout << "Distance from the sun(km): " << row[4] << "\n";
            cout << "Orbital tilt: " << row[6] << "\n";
            cout << "Rotational period: " << row[10] << "\n";
            cout << "Orbit period: " << row[11] << "\n";
            cout << "!-------------------------------!" <<endl;
            return;
        }
        else{
        //    cout << "not found in this line, looping"<< endl;
            continue; //loop if not found
        }

    }
    if(found == false){ //at end of file, call this if its not there
        cout << "Planet not found" << endl;
    }
}


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

  string inputName = argv[1]; //get filename
  string outputName = argv[2]; //get filename

  string line = "";
  ifstream input(inputName); //create input stream
  /*if (input.is_open()) //runs to load in all the data from the input data
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


int choice;
while (choice !=4) //MENU LOOP
{
  displayMenu();
  cin >> choice;

  if (choice == 1)
  { //if view celestial data
  //cout << "user called view celestial data!"<< endl;
  //ifstream input_celestial("planet_data.csv"); //create input stream
  string celestial_choice = "";
  cout << "Please enter the planet's name"<<endl;
  cin >> celestial_choice;
  display_planet(celestial_choice); //call the search and print function


  }

  if (choice == 2)
  { //if adding a new log
   ofstream output(outputName, fstream::app); //create output stream, appending to
    if (output.is_open())
    {
      string newlog = ""; //take in date, and the whole log, add to the output file
      string newdate = "";

      cout << "Please enter the date of your new log"<< endl;
      while(newdate.empty())
      { //borrowed from hw 5 -april
         getline(cin, newdate);
      }
      output << "Log entry: " << newdate <<  "\n";

      cout << "Please enter your log"<< endl;
      while(newlog.empty())
      {
         getline(cin, newlog);
      }
      output << newlog << "\n"; //create new line hopefully
      output << "+---------------------------------------------------------------------------------------------+" << "\n";
      cout << "Log added!" << endl;
      cout << "+-----------------------+" << endl;
      output.close();//need to work for some dumb reason
  }

  }
  if (choice == 3)
  { //if view night sky
  cout << "user called night sky function!"<< endl;

  }

  if (choice == 4)
  { //if exiting
    cout << "Goodbye!" << endl;
      return 0;
  }
  if(choice != 1 && choice != 2 && choice != 3 && choice != 4){
      return 0;
  }

}
  return 0; //exit
}
