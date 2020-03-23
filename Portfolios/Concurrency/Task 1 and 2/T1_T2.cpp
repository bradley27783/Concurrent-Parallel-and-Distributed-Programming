#include <iostream>
#include <cmath>
#include <cstdlib>
#include <thread>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <mutex>
#include <chrono>

using namespace std;
//GLOBAL VARIBLES
mutex mtx;
int pos = 0;
int prevPos = -1;
vector<string> poem;
bool running = true;

void readFile(string filename) {
    string line;
    fstream file;
    file.open(filename);

    if(file.is_open()) { //Checks if file is open
        while (!file.eof()) { //Iterates till end of file (eof)
	    getline(file,line);
        poem.push_back(line);
        }
    }
}


void increment(){
    int poemSize = poem.size();
    while(pos <= poemSize){
        if(prevPos == pos){
            mtx.lock();
            /* START OF CRITICAL SECTION */
            pos++;
            /* END OF CRITICAL SECTION */
            mtx.unlock();
        }
    }
}

void print(){
    int poemSize = poem.size();
    while (pos <= poemSize)
        if(prevPos != pos){
            mtx.lock();
            /* START OF CRITICAL SECTION */
            prevPos = pos;
            cout << poem[pos] << endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            /* END OF CRITICAL SECTION */
            mtx.unlock();
        }
}


int main (void){
    readFile("to_the_rain.txt");

    thread t1(print);
    thread t2(increment);
    t1.join();
    t2.join();

    return 0;
}