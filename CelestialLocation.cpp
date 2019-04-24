#include <iostream>
#include <fstream>
#include <sstream>
//#include <math.h>
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


void nightSkyCoordinates(){ // using data from http://www.stjarnhimlen.se/comp/ppcomp.html

	string date;
	string token;
	int day;
	int month;
	int year;
	int d;

	cout << "Please enter the date for which you would like to see the night sky (mm/dd/yyyy): ";
	cin >> date; // take in user date

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

}

// call to night sky coordinates function
//int main(){
	//nightSkyCoordinates();
//}
