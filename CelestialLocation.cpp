#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


struct planetLocation{

	float longitude;
	float inclination;
};

enum {Mercury, Venus, Mars, Jupiter, Saturn, Uranus, Neptune};

planetLocation planetArr[7];


float meanAnomaly(float m, float n, float d){
	float anomaly;
	anomaly = m + (n*d);
	return anomaly;
}


void calcMercury(int date){
	int d = date;
	float n = 4.092317; // n
	float a = 0.38710; // length of semimajor axis
	float e = 0.20563; // eccentricity of orbit
	float i = 7.005; // ecliptic longitude of ascending node of orbit
	float w = 29.125; // inclination of orbit - shows tilt of orbit compared to ecliptic
	float o = 48.331; // 
	float m = 174.795; // anomaly at date 0
	float mAnomaly = meanAnomaly(m, n, d); // mean anomaly
	float tAnomaly = trueAnomaly(m, e);


    planetArr[Mercury].longitude =  48.3313 + 3.24587E-5 * d;
    planetArr[Mercury].inclination = 7.0047 + 5.00E-8 * d;
}

void calcVenus(int d){
	float n = 1.602136;
    planetArr[Venus].longitude =  76.6799 + 2.46590E-5 * d;
    planetArr[Venus].inclination = 3.3946 + 2.75E-8 * d;
}

void calcMars(int d){
	float n = 0.524039;
    planetArr[Mars].longitude =  49.5574 + 2.11081E-5 * d;
    planetArr[Mars].inclination = 1.8497 - 1.78E-8 * d;
}

void calcJupiter(int d){
	float n = 0.083056;
    planetArr[Jupiter].longitude =  100.4542 + 2.76854E-5 * d;
    planetArr[Jupiter].inclination = 1.3030 - 1.557E-7 * d;
}

void calcSaturn(int d){
	float n = 0.033371;
    planetArr[Saturn].longitude =  113.6634 + 2.38980E-5 * d;
    planetArr[Saturn].inclination = 2.4886 - 1.081E-7 * d;
}
 
void calcUranus(int d){
	float n = 0.011698;
    planetArr[Uranus].longitude =  74.0005 + 1.3978E-5 * d;
    planetArr[Uranus].inclination = 0.7733 + 1.9E-8 * d;
}

void calcNeptune(int d){
	float n = 0.005965;
    planetArr[Neptune].longitude =  131.7806 + 3.0173E-5 * d;
    planetArr[Neptune].inclination = 1.7700 - 2.55E-7 * d;
}

void nightSkyCoordinates(){ // using data from http://www.stjarnhimlen.se/comp/ppcomp.html

	string date;
	string token;
	int day;
	int month;
	int year;
	int d;

	cout << "Please enter the date for which you would like to see the night sky (mm/dd/yyyy): " << endl;
	cin >> date;

  	istringstream iss(date);
 	
 	getline(iss, token, '/');
  	month = stoi(token);
  	getline(iss, token, '/');
  	day = stoi(token);
  	getline(iss, token, '/');
  	year = stoi(token);


	d = (year - 2000)*365 + (month-1)*30 + day;
	
	calcMercury(d);
	calcVenus(d);
	calcMars(d);
	calcJupiter(d);
	calcSaturn(d);
	calcUranus(d);
	calcNeptune(d);

}

int main(){
	nightSkyCoordinates();
}