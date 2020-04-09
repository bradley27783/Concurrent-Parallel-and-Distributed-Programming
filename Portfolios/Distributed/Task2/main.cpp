#include <iostream>
#include "mpi.h"
#include "omp.h"
#include <cstring>
#include <thread>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


std::vector<std::string> poem;

void readFile(std::string filename) {
  std::string line;
  std::fstream file;
  file.open(filename);
  if(file.is_open()) { //Checks if file is open
    while (!file.eof()) { //Iterates till end of file (eof)
      std::getline(file,line);
      poem.push_back(line);
    }
  }
}


void print(std::vector<std::string> vect, std::string title,int node){
  std::cout << "Rank: " << node << " - " << title << std::endl;
  for(unsigned int i = 0; i < vect.size(); i++){
    std::cout << vect[i] << " " << std::flush;
  }
  std::cout << std::endl << std::endl;
}

int main(int argc, char** argv) {
  
  readFile("to_the_rain.txt");

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  char node_name[MPI_MAX_PROCESSOR_NAME];
  int rank,size, namelen;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(node_name, &namelen);
  memset(node_name+namelen,0,MPI_MAX_PROCESSOR_NAME-namelen);

  if(rank < poem.size()){
    std::vector<std::string> words;
    std::string word = "";
    for(unsigned int i = 0; i < poem[rank].size(); i++){
      if(poem[rank][i] == ' '){
        words.push_back(word);
        word = "";
      } 
      else if(i == poem[rank].size()-1){
        word += poem[rank][i];
        words.push_back(word);
        word = "";
      }
      else{
        word += poem[rank][i];
      }
    }
    print(words,"Before",rank);
    sleep(1);
    for(unsigned int i = 0; i < 5; i++)//Shuffle 5 times
      std::random_shuffle(words.begin(), words.end());
    print(words,"After",rank);
  }

if (rank ==0){
  }
  

  MPI_Finalize();
  //std::cout << "Total Cores: " << totalCores << std::endl;
}