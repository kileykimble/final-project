//April Ott, Kiley Kimble, Nathan Reed Final project data structures
//currently complete: display planet function

//g++ -std=c++11 main.cpp -o a
//./a log.txt planet_data.txt



#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "structs.hpp"
#include "HashTable.hpp"
#include<bits/stdc++.h>
using namespace std;


void display_planet(string name) //
{
//    cout << "display planet called, 14"<<endl;
    fstream input_celestial;
    input_celestial.open("planet_data.csv",ios::in); //create input stream

    string whole_line = "";
    string temp;
    string word = "";
    vector <string> row; //temp for each row
    vector <string> memory; //holds all the data
    int count=0;
    bool found = false;

    while (input_celestial >> temp) {
        //cout << "temp is : " << temp << endl;
        row.clear(); //clear the std::vector<int> v;
        getline(input_celestial,whole_line);
        memory.push_back(temp);
        stringstream ss(temp); //call a stringstream on inputted line

        std::vector<string>::iterator it;
        it = std::find(memory.begin(),memory.end(),name); //use find funtion on the memory vector
        if (it !=memory.end()) {
            stringstream s(temp); //if found in overal memory, output
        }

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

void load_logs(vector <Log> all_logs) //. Loads in every log in the csv file and stores it in a vector of log structs
{
    fstream input_logs;
    string temp_load;
    input_logs.open("log.csv",ios::in); //create input stream

    string input_date;
    string input_title; //to load into the struct
    string input_data;
    string word;
    int iterator=0; //janky but idk
    struct Log newlog;

    while (input_logs >> temp_load) { //while active

        stringstream ss(temp_load); //call a stringstream on inputted line

        while(getline(ss,word,',')){ //while in the line, push each word to vector
            if (iterator==0) {
                newlog.date = word;
                cout << "date inputted is : " << word << endl;
            }
            if (iterator==1) {
                newlog.title = word;
                cout << "title inputted is : " << word << endl;
            }
            if (iterator==2) {
                newlog.all_data = word;
                cout << "data inputted is : " << word << endl;
            }
            if (iterator==3) {
                all_logs.push_back(newlog); //push to vector
                cout << "pushed"<<endl;
                iterator=0;
            }
            iterator++;
        //    cout << "got here " << "word is: "<<word<< endl;
        }

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

  vector <Log> all_logs; //temp for each row
  //load_logs(all_logs);



int choice;
while (choice !=4) //MENU LOOP
{
  displayMenu();
  cin >> choice;

  if (choice == 1)
  { //if view celestial data
  string celestial_choice = "";
  cout << "Please enter the planet's name, currently stored are:" << endl;
  cout<< "The Sun, Mercury, Venus, Earth, Mars, Jupiter, Uranus and Neptune"<<endl;
  cin >> celestial_choice;
  display_planet(celestial_choice); //call the search and print function
  }

  if (choice == 2)
  { //if adding a new log
   ofstream output(outputName, fstream::app); //create output stream, appending to
    if (output.is_open())
    {
      string new_data = ""; //take in date, and the whole log, add to the output file
      string newdate = "";
      string newtitle = "";

      cout << "Please enter the date of your new log (mm,dd,yy)"<< endl;
      while(newdate.empty())
      { //borrowed from hw 5 -april
         getline(cin, newdate);
      }
      output << "Log entry date: " << newdate <<  "\n"; //output to the output file
      cout << "Please enter the title of your new log"<< endl;
      while(newtitle.empty())
      { //borrowed from hw 5 -april
         getline(cin, newtitle);
      }
      output << "Title: " << newtitle <<  "\n";

      cout << "Please enter your log"<< endl;
      while(new_data.empty())
      {
         getline(cin, new_data);
      }

      output <<"Data: "<< new_data << "\n"; //create new line hopefully
      output << "+---------------------------------------------------------------------------------------------+" << endl;;
      cout << "+-----------------------+" << endl;
      cout << "Log added!" << endl;
      cout << "+-----------------------+" << endl;

      Log newlog;
      newlog.title=newtitle; //load data into a new struct then push it to the vector that holds all the logs.
      newlog.date=newdate;
      newlog.all_data = new_data;
      all_logs.push_back(newlog);

      output.close();//needed to work
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
