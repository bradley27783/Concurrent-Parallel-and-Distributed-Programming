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

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  char node_name[MPI_MAX_PROCESSOR_NAME];
int rank,size, namelen;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(node_name, &namelen);
  memset(node_name+namelen,0,MPI_MAX_PROCESSOR_NAME-namelen);
  int headNode = 0;
  
  int cores = getCpuCores();
  std::cout << node_name << " Core count:  " << cores << std::endl;
  getCpuClock(node_name);
  getMemory(node_name);

  int send_cores = cores;
  int received_cores;

  if (rank != 0) {   
    MPI_Send(&send_cores, 1, MPI_INT, headNode, 0, MPI_COMM_WORLD);
    std::cout << "> " <<node_name<<" Sent " << send_cores << "  To  node"<< headNode << std::endl;
  }
  MPI_Barrier(MPI_COMM_WORLD);
  
  if(rank == headNode){
    int coreSum = cores;
    for(int i = 1; i < size; i++){
      MPI_Recv(&received_cores, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      coreSum += received_cores;
      std::cout << "> Number: " << received_cores << " Received by "<< node_name<< std::endl;
    }
    std::cout << "Core sum = " << coreSum << std::endl;
  }

  
  MPI_Finalize();
}