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
#include <condition_variable>
#include <array>

using namespace std;
//GLOBAL VARIBLES
mutex mtx;
condition_variable condVar;
vector<string> poem;

vector<char> data;
unsigned int poem_pos = 0;
int controlID = 1;
int chunk = 3;
vector<string> transferredPoem;


class Buffer{
public:
    int buffer_pos = 0;
    array<char,10> buffer = {};
    int buffer_size = buffer.max_size()-1;
    
    bool add(char val){
        if(buffer_pos <= buffer_size){
            buffer[buffer_pos] = val;
            //cout << "Adding: '" << buffer[buffer_pos] << "'  to buffer index: " << buffer_pos << endl;
            buffer_pos++;
            return true;
        }
        return false;
    }

    char remove(int index){
        char val = buffer[index];
        buffer_pos--;
        return val;
    }

    void bufferShift(){
        int diff = chunk;
        int index = 0;
        for(int i = diff; i <= buffer_size; i++){
            buffer[index] = buffer[index+diff];
            buffer[index+diff] = '\0';
            index++;
        }
    }
};

Buffer bufferobj;

int producer(){
    const int TID = 1;

    for(;;){
        unique_lock<mutex> lck(mtx);
        while(controlID != TID)
            condVar.wait(lck);
        lck.unlock();
        if(poem_pos < data.size()){
            for(int i = bufferobj.buffer_pos; i <= bufferobj.buffer_size; i++){
                lck.lock();
                bufferobj.add(data[poem_pos]);
                poem_pos++;
                lck.unlock();
                //sleep(1);                   
            }
        }
        lck.lock();
        controlID = 2;
        lck.unlock();
        condVar.notify_all();
    }
    return 1;
}

int consumer(){
    const int TID = 2;
    string recieved;
    for(;;){
        unique_lock<mutex> lck(mtx);
        while(controlID != TID)
            condVar.wait(lck);
        lck.unlock();
        
        if (poem_pos >= data.size() && bufferobj.buffer_pos <= 0) {
            lck.lock();
            cout << "Transfer Complete" << endl;
            lck.unlock();
            for(unsigned int i = 0; i < transferredPoem.size(); i++){
                lck.lock();
                cout << transferredPoem[i] << endl;
                lck.unlock();
            }
            exit(0);
        }
        for(int i = 0; i < chunk; i++){
            lck.lock();
            char character = bufferobj.remove(i);
            lck.unlock();
            if (character == '#') {
                transferredPoem.push_back(recieved);
                recieved = "";
                lck.lock();
                cout << endl << endl << "Current Poem" << endl;
                lck.unlock();
                for(unsigned int i = 0; i < transferredPoem.size(); i++){
                    lck.lock();
                    cout << transferredPoem[i] << endl;
                    lck.unlock();
                }
                cout << endl;
            }
            else {
                recieved.push_back(character);
                lck.lock();
                cout << character << flush;
                lck.unlock();
                this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        lck.lock();
        bufferobj.bufferShift();
        controlID = 1;
        lck.unlock();
        condVar.notify_all();
    }
    return 1;
}

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

void loadData(){
    for(unsigned int i = 0; i < poem.size(); i++){
        for(unsigned int j = 0; j < poem[i].size(); j++){
            data.push_back(poem[i][j]);
        }
        data.push_back('#');
    }
}


int main (){
    readFile("to_the_rain.txt");
    loadData();
    thread t3(producer);
    thread t4(consumer);
    t3.join();
    t4.join();

    return 0;
}