#include <iostream>
#include <cmath>
#include <cstdlib>
#include <thread>
#include <fstream>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <array>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

mutex mtx;
condition_variable condVar;
int threadControlInt = 1;
int solvedCount = 0;
const int MAX_WHEELS = 6;


void logger(string input){
    ofstream file;
    file.open("log.txt", ios_base::app);
    
    if(file.is_open()){
        file << input << endl;
    }
    file.close();
}


void statusHandler(const int wheelID, vector<int> sequence, bool finished);

void raiseWheel(int wheelID, vector<int> sequence){
    using namespace std::this_thread;
    const int tID = 7;
    std::unique_lock<std::mutex> lck(mtx);
    while (threadControlInt!=tID) {
        condVar.wait(lck);
    }
    lck.unlock();
    cout << "Attempting to raise wheel " << wheelID << endl;
    logger("Attempting to raise wheel " + to_string(wheelID));
    sleep_for(std::chrono::seconds(2));
    bool successful = rand() % 2;
    if(successful){
        cout << "Attempt successful" << endl << endl;
        logger("Attempt successful");
        lck.lock();
        solvedCount++;
        lck.unlock();
    }
    else{
        cout << "Attempt unsuccessful" << endl;
        logger("Attempt unsuccessful");
        sequence.erase(sequence.begin());
    }
    lck.lock();
    threadControlInt = 13;
    lck.unlock();
    thread t13(statusHandler,wheelID,sequence,successful);
    t13.join();
    condVar.notify_all();
}
void lowerWheel(int wheelID, vector<int> sequence){
    using namespace std::this_thread;
    const int tID = 8;
    std::unique_lock<std::mutex> lck(mtx);
    while (threadControlInt!=tID) {
        condVar.wait(lck);
    }
    lck.unlock();
    cout << "Attempting to lower wheel " << wheelID << endl;
    logger("Attempting to lower wheel " + to_string(wheelID));
    sleep_for(std::chrono::seconds(2));
    bool successful = rand() % 2;
    if(successful){
        cout << "Attempt successful" << endl << endl;
        logger("Attempt successful");
        lck.lock();
        solvedCount++;
        lck.unlock();
    }else{
        cout << "Attempt unsuccessful" << endl;
        logger("Attempt unsuccessful");
        sequence.erase(sequence.begin());
    }
    lck.lock();
    threadControlInt = 13;
    lck.unlock();
    thread t13(statusHandler,wheelID,sequence,successful);
    t13.join();
    condVar.notify_all();
}

void accelerate(int wheelID, vector<int> sequence){
    using namespace std::this_thread;
    const int tID = 9;
    std::unique_lock<std::mutex> lck(mtx);
    while (threadControlInt!=tID) {
        condVar.wait(lck);
    }
    lck.unlock();
    cout << "Attempting to accelerate wheels for " << wheelID << endl;
    logger("Attempting to accelerate wheels for " + to_string(wheelID));
    sleep_for(std::chrono::seconds(2));
    bool successful = rand() % 2;
    if(successful){
        cout << "Attempt successful" << endl << endl;
        logger("Attempt successful");
        lck.lock();
        solvedCount++;
        lck.unlock();

    }else{
        cout << "Attempt unsuccessful" << endl;
        logger("Attempt unsuccessful");
        sequence.erase(sequence.begin());
    }
    lck.lock();
    threadControlInt = 13;
    lck.unlock();
    thread t13(statusHandler,wheelID,sequence,successful);
    t13.join();
    condVar.notify_all();
}

void moveSlowly(int wheelID, vector<int> sequence){
    using namespace std::this_thread;
    const int tID = 10;
    std::unique_lock<std::mutex> lck(mtx);
    while (threadControlInt!=tID) {
        condVar.wait(lck);
    }
    lck.unlock();
    cout << "Attempting to move wheels slowly for the wheel " << wheelID << endl;
    logger("Attempting to move wheels slowly for the wheel " + to_string(wheelID));
    sleep_for(std::chrono::seconds(2));
    bool successful = rand() % 2;
    if(successful){
        cout << "Attempt successful" << endl << endl;
        logger("Attempt successful");
        lck.lock();
        solvedCount++;
        lck.unlock();
    }else{
        cout << "Attempt unsuccessful" << endl;
        logger("Attempt unsuccessful");
        sequence.erase(sequence.begin());
    }
    lck.lock();
    threadControlInt = 13;
    lck.unlock();
    thread t13(statusHandler,wheelID,sequence,successful);
    t13.join();
    condVar.notify_all();
}
void moveAround(int wheelID, vector<int> sequence){
    using namespace std::this_thread;
    const int tID = 11;
    std::unique_lock<std::mutex> lck(mtx);
    while (threadControlInt!=tID) {
        condVar.wait(lck);
    }
    lck.unlock();
    cout << "Attempting to move around obstacle for wheel " << wheelID << endl;
    logger("Attempting to move around obstacle for the wheel " + to_string(wheelID));
    sleep_for(std::chrono::seconds(2));
    bool successful = rand() % 2;
    if(successful){
        cout << "Attempt successful" << endl << endl;
        logger("Attempt successful");
        lck.lock();
        solvedCount++;
        lck.unlock();
    }else{
        cout << "Attempt unsuccessful" << endl;
        logger("Attempt unsuccessful");
        sequence.erase(sequence.begin());
    }
    lck.lock();
    threadControlInt = 13;
    lck.unlock();
    thread t13(statusHandler,wheelID,sequence,successful);
    t13.join();
    condVar.notify_all();
}

void contactEarth(int wheelID, vector<int> sequence){
    using namespace std::this_thread;
    const int tID = 12;
    std::unique_lock<std::mutex> lck(mtx);
    while (threadControlInt!=tID) {
        condVar.wait(lck);
    }
    lck.unlock();
    cout << "Attempting to contact earth for wheel" << wheelID << endl;
    logger("Attempting to contact earth " + to_string(wheelID));
    sleep_for(std::chrono::seconds(2));
    bool successful = rand() % 2;
    if(successful){
        cout << "Attempt successful" << endl << endl;
        logger("Attempt successful");
        lck.lock();
        solvedCount++;
        lck.unlock();
    }else{
        cout << "Attempt unsuccessful" << endl;
        cout << "Failed to find a solution" << endl << endl;
        logger("Attempt unsuccessful");
        logger("Failed to find a solution");
    }
    lck.lock();
    threadControlInt = 13;
    lck.unlock();
    thread t13(statusHandler,wheelID,sequence,true);
    t13.join();
    condVar.notify_all();
}

int wheelSensor(const int wheelID) {
    srand(time(NULL));
    const int random = rand() % 3 + 1;
    if(random == 1){
        string str = "Wheel " + to_string(wheelID) + " has encountered an issue";
        cout << str << endl;
        logger(str);
        return wheelID;
    }
    else{
        string str = "Wheel " + to_string(wheelID) + " did not encounter an issue";
        cout << str << endl;
        logger(str);
        return 0;
    }
}

string statusDecoder(int wheelID){
    array<string,6> scenarios = {"stuck", "free wheeling", "large bump", "drops", "sinking", "unstable ground"};
    const int sceneSize = scenarios.size();
    const int statusID = rand() % sceneSize + 0;
    string scenario  = scenarios[statusID];
    string str = "The problem encountered is '" + scenario + "' ";
    logger(str);
    cout << str << endl;
    return scenarios[statusID];
}

vector<int> statusSequence(string status){
    if(status == "stuck") return {7,8,9,12};
    else if(status == "free wheeling") return {7,8,9,12};
    else if(status == "large bump") return {7,11,12};
    else if(status == "drops") return {7,11,10,12};
    else if(status == "sinking") return {10,7,12};
    else if(status == "unstable ground") return {11,10,12};
    else return {12};
}

void statusHandler(const int wheelID, vector<int> sequence, bool finished){
    using namespace std::this_thread;
    const int tID = 13;
    std::unique_lock<std::mutex> lck(mtx);
    while (threadControlInt!=tID) {
        condVar.wait(lck);
    }
    lck.unlock();
    sleep_for(std::chrono::seconds(2));
    if(sequence.size() == 0 || finished){
        lck.lock();
        if(wheelID == MAX_WHEELS) threadControlInt = 1;
        else threadControlInt = wheelID+1;
        lck.unlock();
        condVar.notify_all();
    }
    else{
        lck.lock();
        threadControlInt = sequence[0];
        lck.unlock();
        condVar.notify_all();
        
        int value = sequence[0];
        if(value == 7){
            thread t7(raiseWheel,wheelID,sequence);
            t7.join();
        }
        else if(value == 8){
            thread t8(lowerWheel,wheelID,sequence);
            t8.join();            
        }
        else if(value == 9){
            thread t9(accelerate,wheelID,sequence);
            t9.join();
        }
        else if(value == 10){
            thread t10(moveSlowly,wheelID,sequence);
            t10.join();
        }
        else if(value == 11){
            thread t11(moveAround,wheelID,sequence);
            t11.join();
        }
        else if(value == 12){
            thread t12(contactEarth,wheelID,sequence);
            t12.join();
        }
        else{
            thread t12(contactEarth,wheelID,sequence);
            t12.join();
        }
    }
}


void wheel(int wheelID){
    using namespace std::this_thread;
    std::unique_lock<std::mutex> lck(mtx);
    while (threadControlInt!=wheelID) {
        condVar.wait(lck);
    }
    lck.unlock();
    sleep_for(std::chrono::seconds(2));
    
    int wheelStatus = wheelSensor(wheelID);
    
    if(wheelStatus == 0){
        lck.lock();
        if(wheelID == MAX_WHEELS) threadControlInt = 1;
        else threadControlInt = wheelID+1;
        lck.unlock();
        condVar.notify_all();
    } 
    else{
        string status = statusDecoder(wheelID);
        vector<int> sequence = statusSequence(status);
        lck.lock();
        threadControlInt = 13;
        lck.unlock();
        thread t13(statusHandler,wheelID,sequence,false);
        t13.join();
        condVar.notify_all();
    }
}

int main(void) {
    logger("");
    logger("--- STARTING A NEW LOG SESSION ---");
    while(solvedCount < 5){ //Iterate until it has solved 10 problems
        for(int i = 1; i <= MAX_WHEELS; i++){
            thread t(wheel,i); //Create 6 threaded wheels
            t.join();
        }
    }

    return 0;

}