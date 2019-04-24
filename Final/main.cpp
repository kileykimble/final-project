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
#include "graphs.hpp"
#include<bits/stdc++.h>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
using namespace std;
struct planetLocation{ // struct that stores coordinates of a planet on a date
	float longitude;
	float inclination;
};

enum {Mercury, Venus, Mars, Jupiter, Saturn, Uranus, Neptune}; // enumeration of array

planetLocation planetArr[7]; // array of structs of planet locations

float degToRad = M_PI/180; // quick variable to convert degrees to radians
float radToDeg = 180/M_PI; // quick variable to convert radians to degrees


float meanAnomaly(float m, float n, float d){ //function to calculate mean anomaly
	float anomaly = m + (n*d);
	while(anomaly-360>0){
		anomaly = anomaly - 360;
	}
	return anomaly; // return mean anomaly
}


float distanceToSun(float num, float e, float mean){ // function to calculate the planet's distance from the sun
	double distance;
	float M = degToRad*mean; // convert to radians to use cos() function
	distance = num/(1+(e*cos(M)));
	return distance; // return distance
}

float helioCoordinateX(float r, float o, float m, float i, float w){ // function to calculate the heliocentric x coordinate value
	float O = degToRad*o; // conversions to radians to use trig functions
	float M = degToRad*m;
	float I = degToRad*i;
	float W = degToRad*w;
	float x = r*(cos(O)*cos(W + M) - sin(O)*cos(I)*sin(W+M));
	return x; // return x coordinate
}

float helioCoordinateY(float r, float o, float m, float i, float w){ // function to calculate the heliocentric y coordinate value
	float O = degToRad*o; // conversions to radians to use trig functions
	float M = degToRad*m;
	float I = degToRad*i;
	float W = degToRad*w;
	float y = r*(sin(O)*cos(W+M)+cos(O)*cos(I)*sin(W+M));
	return y; // return y coordinate
}

float helioCoordinateZ(float r, float m, float i, float w){ // function to calculate the heliocentric z coordinate value
	float M = degToRad*m; // conversions to radians to use trig functions
	float I = degToRad*i;
	float W = degToRad*w;
	float z = r*(sin(I)*sin(W + M));
	return z; // return z coordinate
}

float ra(float lat, float lon){ // function to calculate the right ascension (longitude coordinate) of the planet on the celestial globe
	float Lat = degToRad*lat; // convert to radians to use trig
	float Lon = degToRad*lon;
	float E = degToRad*23.4397;
	float RA = atan2(sin(Lon)*cos(E)-tan(Lat)*sin(E), cos(Lon));
	return RA; // return right ascension value
}

float dec(float lat, float lon){ // function to calculate the declination (latitude coordinate) of the planet of the celestial globe
	float Lat = degToRad*lat; // convert to radians to use trig
	float Lon = degToRad*lon;
	float E = degToRad*23.4397;
	float Dec = asin(sin(Lat)*cos(E)+cos(Lat)*sin(E)*sin(Lon));
	return Dec; // return declination value
}


void calcMercury(int date, float x, float y, float z){ // function to perform coordinate calculations for the planet Mercury
	int d = date;
	float earthX = x;
	float earthY = y;
	float earthZ = z;
	float n = 4.092317; // n
	float a = 0.38710; // length of semimajor axis
	float e = 0.20563; // eccentricity of orbit
	float i = 7.005; // ecliptic latitude of ascending node of orbit
	float w = 29.125; // inclination of orbit - shows tilt of orbit compared to ecliptic
	float o = 48.331; // ecliptic longitude of ascending node
	float m = 174.795; // anomaly at date 0
	float distNum = 0.37073; // used to calculate distance from sun

	float mAnomaly = meanAnomaly(m, n, d); // mean anomaly

	float r = distanceToSun(distNum, e, mAnomaly); // distance to sun


	float helioX = helioCoordinateX(r, o, mAnomaly, i, w); // heliocentric x coordinate
	float helioY = helioCoordinateY(r, o, mAnomaly, i, w); // y coordinates
	float helioZ = helioCoordinateZ(r, mAnomaly, i, w); // z coordinates

	// geocentric coordinates take into account the position of the earth //
	float X = helioX - earthX; // geocentric x coordinate
	float Y = helioY - earthY; // geocentric y coordinate
	float Z = helioZ - earthZ; // geocentric z coordinate

	float dist = sqrt(X*X + Y*Y + Z*Z); // distance between planet and Earth

	float eclLon = atan2(Y,X); // geocentric ecliptic longitude
	float eclLat = asin(Z/dist); // geocentric ecliptic latitude

	float RA = ra(eclLat, eclLon)*radToDeg; // calculates right ascension
	float Dec = dec(eclLat, eclLon)*radToDeg; // calculates declination


    planetArr[Mercury].longitude =  RA; // store in struct in array
    planetArr[Mercury].inclination = Dec; // store in struct in array
}

void calcVenus(int date, float x, float y, float z){ // function to perform coordinate calculations for the planet Venus
	// see full descriptions of function calls in calcMercury() function
	int d = date;
	float earthX = x;
	float earthY = y;
	float earthZ = z;
	float n = 1.602136;
	float a = 0.72333;	// length of semimajor axis
	float e = 0.00677; // eccentricity of orbit
	float i = 3.395; // ecliptic longitude of ascending node of orbit
	float w = 54.884; // inclination of orbit - shows tilt of orbit compared to ecliptic
	float o = 76.680;
	float m = 50.416; // anomaly at date 0
	float distNum = 0.72330;

   	float mAnomaly = meanAnomaly(m, n, d);

	float r = distanceToSun(distNum, e, mAnomaly);


	float helioX = helioCoordinateX(r, o, mAnomaly, i, w);
	float helioY = helioCoordinateY(r, o, mAnomaly, i, w);
	float helioZ = helioCoordinateZ(r, mAnomaly, i, w);

	float X = helioX - earthX;
	float Y = helioY - earthY;
	float Z = helioZ - earthZ;
	float dist = sqrt(X*X + Y*Y + Z*Z);

	float eclLon = atan2(Y,X) * 180/M_PI;
	float eclLat = asin(Z/dist) * 180/M_PI;

	float RA = ra(eclLat, eclLon)*radToDeg;
	float Dec = dec(eclLat, eclLon)*radToDeg;


    planetArr[Venus].longitude =  RA;
    planetArr[Venus].inclination = Dec;
}

void calcMars(int date, float x, float y, float z){ // function to perform coordinate calculations for the planet Mars
	// see full descriptions of function calls in calcMercury() function
	int d = date;
	float earthX = x;
	float earthY = y;
	float earthZ = z;
	float n = 0.524039;
	float a = 1.52368;	// length of semimajor axis
	float e = 0.09340; // eccentricity of orbit
	float i = 1.850; // ecliptic longitude of ascending node of orbit
	float w = 286.502; // inclination of orbit - shows tilt of orbit compared to ecliptic
	float o = 49.558;
	float m = 19.373; // anomaly at date 0
	float distNum = 1.51039;

  	float mAnomaly = meanAnomaly(m, n, d); // mean anomaly

	float r = distanceToSun(distNum, e, mAnomaly); // distance to sun


	float helioX = helioCoordinateX(r, o, mAnomaly, i, w);
	float helioY = helioCoordinateY(r, o, mAnomaly, i, w);
	float helioZ = helioCoordinateZ(r, mAnomaly, i, w);

	float X = helioX - earthX;
	float Y = helioY - earthY;
	float Z = helioZ - earthZ;
	float dist = sqrt(X*X + Y*Y + Z*Z);

	float eclLon = atan2(Y,X) * radToDeg;
	float eclLat = asin(Z/dist) * radToDeg;

	float RA = ra(eclLat, eclLon);
	float Dec = dec(eclLat, eclLon);


    planetArr[Mars].longitude =  RA;
    planetArr[Mars].inclination = Dec;
}

void calcJupiter(int date, float x, float y, float z){ // // function to perform coordinate calculations for the planet Jupiter
	// see full descriptions of function calls in calcMercury() function
	int d = date;
	float earthX = x;
	float earthY = y;
	float earthZ = z;
	float n = 0.083056; // n
	float a = 5.20260;	// length of semimajor axis
	float e = 0.04849; // eccentricity of orbit
	float i = 1.303; // ecliptic latitude of ascending node of orbit
	float w = 273.867; // inclination of orbit - shows tilt of orbit compared to ecliptic
	float o = 100.464; // ecliptic longitude of ascending node
	float m = 20.020; // anomaly at date 0
	float distNum = 5.19037; // used to calculate the distance from the sun

	float mAnomaly = meanAnomaly(m, n, d); // call to mean anomaly


	float r = distanceToSun(distNum, e, mAnomaly); // call to distance to sun


	float helioX = helioCoordinateX(r, o, mAnomaly, i, w); // heliocentric x coordinate
	float helioY = helioCoordinateY(r, o, mAnomaly, i, w); // y coordinates
	float helioZ = helioCoordinateZ(r, mAnomaly, i, w); // z coordinates


	float X = helioX - earthX;
	float Y = helioY - earthY;
	float Z = helioZ - earthZ;
	float dist = sqrt(X*X + Y*Y + Z*Z);

	float eclLon = atan2(Y,X)*radToDeg; // finds the ecliptical longitude
	float eclLat = asin(Z/dist)*radToDeg; // finds ecliptical latitude

	float RA = ra(eclLat, eclLon)*radToDeg; // right ascension
	float Dec = dec(eclLat, eclLon)*radToDeg; // declination


    planetArr[Jupiter].longitude =  RA;
    planetArr[Jupiter].inclination = Dec;
}

void calcSaturn(int date, float x, float y, float z){ // function to perform coordinate calculations for the planet Saturn
	// see full descriptions of function calls in calcMercury() function
	int d = date;
	float earthX = x;
	float earthY = y;
	float earthZ = z;
	float n = 0.033371;
	float a = 9.55491;
	float e = 0.05551;
	float i = 2.489;
	float w = 339.391;
	float o = 113.666;
	float m = 317.021;
	float distNum = 9.52547;


 	float mAnomaly = meanAnomaly(m, n, d); // mean anomaly

	float r = distanceToSun(distNum, e, mAnomaly); // distance to sun


	float helioX = helioCoordinateX(r, o, mAnomaly, i, w); // heliocentric x coordinate
	float helioY = helioCoordinateY(r, o, mAnomaly, i, w); // y coordinates
	float helioZ = helioCoordinateZ(r, mAnomaly, i, w); // z coordinates

	float X = helioX - earthX;
	float Y = helioY - earthY;
	float Z = helioZ - earthZ;
	float dist = sqrt(X*X + Y*Y + Z*Z);

	float eclLon = atan2(Y,X) * radToDeg;
	float eclLat = asin(Z/dist) * radToDeg;

	float RA = ra(eclLat, eclLon);
	float Dec = dec(eclLat, eclLon);


    planetArr[Saturn].longitude =  RA;
    planetArr[Saturn].inclination = Dec;
}

void calcUranus(int date, float x, float y, float z){ // function to perform coordinate calculations for the planet Uranus
	// see full descriptions of function calls in calcMercury() function
	int d = date;
	float earthX = x;
	float earthY = y;
	float earthZ = z;
	float n = 0.011698;
	float a = 19.21845;	// length of semimajor axis
	float e = 0.04630; // eccentricity of orbit
	float i = 0.773; // ecliptic longitude of ascending node of orbit
	float w = 98.999; // inclination of orbit - shows tilt of orbit compared to ecliptic
	float o = 74.006; //
	float m = 141.050; // anomaly at date 0
	float distNum = 19.17725;


	float mAnomaly = meanAnomaly(m, n, d); // mean anomaly

	float r = distanceToSun(distNum, e, mAnomaly); // distance to sun


	float helioX = helioCoordinateX(r, o, mAnomaly, i, w); // heliocentric x coordinate
	float helioY = helioCoordinateY(r, o, mAnomaly, i, w); // y coordinates
	float helioZ = helioCoordinateZ(r, mAnomaly, i, w); // z coordinates

	float X = helioX - earthX;
	float Y = helioY - earthY;
	float Z = helioZ - earthZ;
	float dist = sqrt(X*X + Y*Y + Z*Z);

	float eclLon = atan2(Y,X) * radToDeg;
	float eclLat = asin(Z/dist) * radToDeg;

	float RA = ra(eclLat, eclLon);
	float Dec = dec(eclLat, eclLon);


    planetArr[Uranus].longitude =  RA;
    planetArr[Uranus].inclination = Dec;
}


void calcNeptune(int date, float x, float y, float z){ // function to perform coordinate calculations for the planet Neptune
	// see full descriptions of function calls in calcMercury() function
	int d = date;
	float earthX = x;
	float earthY = y;
	float earthZ = z;
	float n = 0.005965;
	float a = 30.11039;	// length of semimajor axis
	float e = 0.00899; // eccentricity of orbit
	float i = 1.770; // ecliptic longitude of ascending node of orbit
	float w = 276.340; // inclination of orbit - shows tilt of orbit compared to ecliptic
	float o = 131.784; //
	float m = 256.225; // anomaly at date 0
	float distNum = 30.10796;

	float mAnomaly = meanAnomaly(m, n, d); // mean anomaly

	float r = distanceToSun(distNum, e, mAnomaly); // distance to sun


	float helioX = helioCoordinateX(r, o, mAnomaly, i, w); // heliocentric x coordinate
	float helioY = helioCoordinateY(r, o, mAnomaly, i, w); // y coordinates
	float helioZ = helioCoordinateZ(r, mAnomaly, i, w); // z coordinates

	float X = helioX - earthX;
	float Y = helioY - earthY;
	float Z = helioZ - earthZ;
	float dist = sqrt(X*X + Y*Y + Z*Z);

	float eclLon = atan2(Y,X) * radToDeg;
	float eclLat = asin(Z/dist) * radToDeg;

	float RA = ra(eclLat, eclLon);
	float Dec = dec(eclLat, eclLon);


    planetArr[Neptune].longitude =  RA;
    planetArr[Neptune].inclination = Dec;
}


planetLocation* nightSkyCoordinates(string date){ // using data from http://www.stjarnhimlen.se/comp/ppcomp.html
	string token;
	int day;
	int month;
	int year;
	int d;

  	istringstream iss(date);

 	getline(iss, token, '/'); // extract month from input date
  	month = stoi(token);
  	getline(iss, token, '/'); // extract day from input date
  	day = stoi(token);
  	getline(iss, token, '/'); // extract year from input date
  	year = stoi(token);


	d = (year - 2000)*365 + (month-1)*30 + day; // gives the number of days past Jan 1st, 2000
	// calculations for reference point Earth
	float earth_i = 0;
	float earth_w = 288.064;
	float earth_o = 174.873;
	float earth_n = .985608;
	float earth_m = 357.529;
	float earth_e = .01671;
	float earth_distNum = .999972;
	float earth_mAnomaly = meanAnomaly(earth_m, earth_n, d);
	float earth_r = distanceToSun(earth_distNum, earth_e, earth_mAnomaly); // distance to sun
	float earth_X = helioCoordinateX(earth_r, earth_o, earth_mAnomaly, earth_i, earth_w); // heliocentric x coordinate
	float earth_Y = helioCoordinateY(earth_r, earth_o, earth_mAnomaly, earth_i, earth_w); // y coordinates
	float earth_Z = helioCoordinateZ(earth_r, earth_mAnomaly, earth_i, earth_w); // z coordinates

	// call to all of the planet functions to fill the array of structs
	calcMercury(d, earth_X, earth_Y, earth_Z);
	calcVenus(d, earth_X, earth_Y, earth_Z);
	calcMars(d, earth_X, earth_Y, earth_Z);
	calcJupiter(d, earth_X, earth_Y, earth_Z);
	calcSaturn(d, earth_X, earth_Y, earth_Z);
	calcUranus(d, earth_X, earth_Y, earth_Z);
	calcNeptune(d, earth_X, earth_Y, earth_Z);
  return planetArr;

}
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
  planetLocation *pl;
  string date;
  string lats;
  string longs;
  double lat;
  double longi;
  string inputName = argv[1]; //get filename
  string outputName = argv[2]; //get filename
  string line = "";
  ifstream input(inputName); //create input stream
  HashTable table = HashTable(1023);
  vector <Log> all_logs; //temp for each row
  //load_logs(all_logs);

  table.load_planets(inputName); //load in stuff
//test push?

string choices;
int choice;
while (choice !=4) //MENU LOOP
{
  displayMenu();
  getline(cin, choices);
  choice = stoi(choices);

  if (choice == 1)
  { //if view celestial data
  string celestial_choice = "";
  cout << "Please enter the planet's name, currently stored are:" << endl;
  cout<< "The Sun, Mercury, Venus, Earth, Mars, Jupiter, Uranus and Neptune"<<endl;
  getline(cin, celestial_choice);
 // display_planet(celestial_choice); //call the search and print function
    planet *temp;
    //display_planet(celestial_choice);
    table.planet_search(celestial_choice);
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
    cout << "Please enter the date for which you would like to see the night sky (mm/dd/yyyy): " << endl;
    getline(cin, date);
    pl = nightSkyCoordinates(date);
    cout << "Please enter Latitude" << endl;
    getline(cin, lats);
    cout << "Please enter Longitude" << endl;
    getline(cin, longs);
    lat = stod(lats);
    longi = stod(longs);
    Graph g = Graph();
    g.addVertex("me", 0, 0, 0, 0);
    g.addVertex("Mercury", lat, longi, pl[0].inclination*.5, fmod((pl[0].longitude), 180));
    g.addVertex("Venus", lat, longi, pl[1].inclination*.5, fmod((pl[1].longitude), 180));
    g.addVertex("Mars", lat, longi, pl[2].inclination*.5, fmod((pl[2].longitude), 180));
    g.addVertex("Jupiter", lat, longi, pl[3].inclination*.5, fmod((pl[3].longitude), 180));
    g.addVertex("Saturn", lat, longi, pl[4].inclination*.5, fmod((pl[4].longitude), 180));
    g.addVertex("Uranus", lat, longi, pl[5].inclination*.5, fmod((pl[5].longitude), 180));
    g.addVertex("Neptune", lat, longi, pl[6].inclination*.5, fmod((pl[6].longitude), 180));
    g.addEdge("me", "Mercury");
    g.addEdge("me", "Venus");
    g.addEdge("me", "Mars");
    g.addEdge("me", "Jupiter");
    g.addEdge("me", "Saturn");
    g.addEdge("me", "Uranus");
    g.addEdge("me", "Neptune");
    cout << g.findSeen("me");
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
