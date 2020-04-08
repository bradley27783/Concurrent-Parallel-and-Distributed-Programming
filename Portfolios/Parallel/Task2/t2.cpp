#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>  
#include "stdio.h"
#include <vector>


std::vector<int> vect = {1,2,3,4,5,6,7,8,9,10};

int main (void)
{
  #pragma omp parallel for schedule(runtime)
  for(int i = 0; i < vect.size(); i++){
    std::cout << "Thread Num: " << omp_get_thread_num() << "  Value: " << vect[i] << std::endl;
  }


return 0;
};