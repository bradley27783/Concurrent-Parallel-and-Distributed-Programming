#include <iostream>
#include "mpi.h"
#include "omp.h"
#include <cstring>
#include <thread>
#include <unistd.h>
#include <fstream>
#include <algorithm>


int getCpuCores(){
  return std::thread::hardware_concurrency();
}

void getCpuClock(char* node){
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    int count = 0;
    while (!cpuinfo.eof()){
        std::getline(cpuinfo,line);
        if(line.find("cpu MHz") != std::string::npos){
          std::cout << node << " Core: " << count << " @ "<< line.substr(line.find(":") + 1) << std::endl;
          count++;
        }
    }
}


void getMemory(char* node){
    std::ifstream cpuinfo("/proc/meminfo");
    std::string line;
    while (!cpuinfo.eof()){
        std::getline(cpuinfo,line);
        if(line.find("MemTotal") != std::string::npos){
          std::string mem = line.substr(line.find(":") + 1);
          mem.erase(remove_if(mem.begin(), mem.end(), isspace), mem.end()); //Remove whitespace
          std::cout << node << " Memory Size: " << mem << std::endl;
        }
    }
}


int main(int argc, char** argv) {
  int coreSum = 0;


  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  char node_name[MPI_MAX_PROCESSOR_NAME];
  int rank,size, namelen;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(node_name, &namelen);
  memset(node_name+namelen,0,MPI_MAX_PROCESSOR_NAME-namelen);

  int cores = getCpuCores();
  std::cout << node_name << " Core count:  " << cores << std::endl;
  getCpuClock(node_name);
  getMemory(node_name);

  MPI_Reduce(&cores, &coreSum, 1, MPI_FLOAT, MPI_SUM, 0,MPI_COMM_WORLD);
  
if (rank ==0){
  std::cout << "Total Cores Availible: " << coreSum << std::endl;
  }
  

  MPI_Finalize();
  //std::cout << "Total Cores: " << totalCores << std::endl;
}