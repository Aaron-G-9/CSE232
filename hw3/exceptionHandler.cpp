//So, for this program, I wanted to go beyond what was covered in the slides a little
//I know that the slides said that one should exit out of a program gracefully if presented
//with an error. I was just curious, if the program could actually fix an array index 
//error all by itself. That would be some really cool error handling!
//I think that it will work. The alternative will be, the program
//will crash, and I should just try to handle out of bounds exceptions gracefully.

//This program was written by Aaron Goodfellow on 1/25/2017
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(void){
  //Initialize a vector of size 10
  vector<int> smallVector(10);

  for (size_t j = 0; j < smallVector.size(); j++){
    smallVector[j] = rand() % 100;
  }


  int loopLength = 12;
  bool success = false;

  while(success != true){
    try{
      //Create a for loop that iterates two too many times
      //'zu' is the key for unsigned decimal
      for (size_t i = 0; i < loopLength; i++){
        printf("Index: %zu \t Element: %d \n", i, smallVector.at(i));
      } 
      success = true;
    }catch(...){
      //try decreasing the loopLength by one
      cout << "###################################\n";
      printf("Subtracting one from loop length\n");
      cout << "###################################\n";
      loopLength--;
    }
  }
}

//It does work! I know that my catch will just catch any error at all, but the principle
//discovered still stands. C++ is capable of recovering from what would be a null pointer
//exception in Java! How cool is that :) 
