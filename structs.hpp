/****************************************************************/
/*                                       */
/****************************************************************/
/*  MODIFY ANYTHING! =]            */
/****************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


struct Log
{
  string date;
  string title; // just a simple struct to hold each log
  string all_data;
};


struct planet
{
    string name;
    string radius; //in km
    string distance; //from sun
    string orbit_tilt;
    string rotat_period;
    string orbit_period;
    string moons;
};
