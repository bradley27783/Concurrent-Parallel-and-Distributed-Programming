#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>  
#include "stdio.h"
#include <vector>
#include <random>


std::vector<std::vector<int>> matrix = {{5,14,10},
                                        {7,-8,-14},
                                        {-2,9,8},
                                        {15,-6,3},
                                        {12,4,-5},
                                        {4,20,17},
                                        {-16,5,-1},
                                        {-11,3,16},
                                        {3,10,-19},
                                        {-16,7,4}};


void printMatrix(){
  for(unsigned int j = 0; j < matrix.size(); j++){
    std::cout << "Vector: " << j << "  " << "Values: " << std::flush;
    for(unsigned int i = 0; i < matrix[j].size(); i++){
      std::cout << matrix[j][i] << "  " << std::flush;
    }
    std::cout << std::endl;
  }
}


int main (void)
{
  for(unsigned int j = 0; j <= 10; j++){
    if(j == 0 || j == 5 || j == 10){
      std::cout << std::endl << "Step " << j << std::endl;
      printMatrix();
    }
    #pragma omp parallel for schedule(runtime)
    for(unsigned int i = 0; i < matrix.size(); i++){
      int randomNum = rand() % 3; //Random number between 0 and 2
      bool increment = rand() % 2; //Random number between 0 and 1
      if(increment){
        ++matrix[i][randomNum];
      }
      else{
        --matrix[i][randomNum];
      }
    }
  }


return 0;
};