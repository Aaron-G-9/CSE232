//This program was written by Aaron Goodfellow on 1/20/2017
#include <iostream>
#include <vector>
#include <stdio.h>
#include <map>
#include <stdlib.h>

using namespace std;

int main(){
	vector<int> v(10);
	map<int, int> modeMap;

  //size_t instead of int, because for loops can go above the max
  //value of ints
	for (size_t j = 0; j < v.size(); j++){
		v[j] = rand() % 100;
	}
	
	int max = v[0];
	int min = v[0];
	int mode = 0;
  int modeNum = 0;

	for (size_t i = 0; i < v.size(); i++){
    //Check for the max value
		if (v[i] > max){
			max = v[i];
		}
    //Check for the min value
		if (v[i] < min){
			min = v[i];
		}
    //Check for the mode
    if (modeMap.find(v[i]) != modeMap.end()){
      modeMap[v[i]] = modeMap.at(v[i]) + 1;
      if (modeMap.at(v[i]) > mode){
        mode = modeMap.at(v[i]);
        modeNum = v[i]; 
      }
    }else{
      modeMap.insert(make_pair(v[i], 1));
    }
  }
		
  //Printf is so much prettier than cout
	printf ("Maximum: %d \t Minimum: %d \t Mode: %d \n", max, min, modeNum);
	return 0;
}
