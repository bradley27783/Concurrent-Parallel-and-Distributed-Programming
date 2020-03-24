#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>  
#include "stdio.h"
#include <vector>
#include <fstream>


void getCores(){
  int cores = omp_get_num_procs();
  std::cout << "Cores: " << cores << std::endl;
}

void getClock() {
    system("cat /proc/cpuinfo | grep -m1 'MHz'");
}

void getRam() {
    system("cat /proc/meminfo | grep 'MemTotal:'");
}

void getHome(){
    std::cout << "Home Folder Size: " << std::flush;
    system("du -sh $home");
}


int main (void){
  getCores();
  getClock();
  getRam();
  getHome();
  return 0;
};
