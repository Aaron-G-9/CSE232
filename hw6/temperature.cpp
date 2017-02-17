//This file was written by Aaron Goodfellow on 2/14/2017 (yep - that's Valentine's Day) 
//
//2. Write a program that creates a file of data in the form of the temperature Reading type defined in §10.5. For testing, fill the file with at least 50 “temperature readings.” Call this program store_temps.cpp and the file it creates raw_temps.txt.
//

#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

struct Reading {        // a temperature reading
  int hour;             // hour after midnight [0:23]
  double temperature;   // in Fahrenheit
} readings[54];

//This method generates the temperatures that we're going to be adding to our Reading struct
vector<int> generateTemps(){
  //Create random number generator
  default_random_engine generator;
  normal_distribution<double> distribution(55.0, 15.0);
  //Create vector
	vector<int> temperatures(55);

	for (size_t i = 0; i < 54; i++){
    temperatures[i] = distribution(generator);
  }
  return temperatures;
}

//This method generates the hours that we're going to be adding to our Reading struct
vector<int> generateHours(){
  //Create vector
	vector<int> hours(55);

	for (size_t i = 0; i < 54; i++){
		hours[i] = rand() % 23;
  }
  return hours;
}


int main(){
  ofstream outputFile;
  outputFile.open("raw_temps.txt");
  vector<int> temps = generateTemps();
  vector<int> hours = generateHours();

	for (size_t i = 0; i < 54; i++){
    readings[i].temperature = temps.at(i);    
    readings[i].hour = hours.at(i);    
    outputFile << "Temperature: " <<  readings[i].temperature << "\t Time: " << readings[i].hour << endl;
  }
}
