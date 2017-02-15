//This file was written by Aaron Goodfellow on 2/14/2017 (yep - that's Valentine's Day) 
//
//2. Write a program that creates a file of data in the form of the temperature Reading type defined in §10.5. For testing, fill the file with at least 50 “temperature readings.” Call this program store_temps.cpp and the file it creates raw_temps.txt.
//

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

struct Reading {        // a temperature reading
  int hour;             // hour after midnight [0:23]
  double temperature;   // in Fahrenheit
};

vector<int> generateTemps(){
  //Create random number generator
  default_random_engine generator;
  normal_distribution<double> distribution(55.0, 15.0);
  //Create vector
	vector<int> temperatures(55);

	for (size_t i = 0; i < 54; i++){
    temperatures[i] = distribution(generator);
    cout << i << "\t" << temperatures[i] << endl;
  }
  return temperatures;
}

vector<int> generateHours(){
  //Create vector
	vector<int> hours(55);

	for (size_t i = 0; i < 54; i++){
		hours[i] = rand() % 23;
    cout << i << "\t" << hours[i] << endl;
  }
  return hours;
}

int main(){
  generateTemps();
  generateHours();
}
