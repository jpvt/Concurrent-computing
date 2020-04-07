#include <iostream>
#include <time.h>
#include <string.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>

#define NUM_THREADS 5

using namespace std;

class Monitor{

    fstream file;
    string datapath;
    mutex mutex_monitor;

    public:
        Monitor(string datapath);
        void MonitorWrite(string data);
        void MonitorDisplay();

};

Monitor::Monitor(string datapath){
    time_t tempo = time(NULL);
    char * hour = ctime(&tempo);
    int endStr = strlen(hour) - 1;
    int i = 0;
    
    hour[endStr] = '\0';
    while(hour[i] != '\0'){

        if(hour[i] == ' ')
            hour[i] = '-';

        i++;
    }

    string datetime(hour);

    this->datapath = datetime + " - " + datapath;

}

void Monitor::MonitorWrite(string data){

    mutex_monitor.lock();
    
    this->file.open(this->datapath, ios::app);
	
    time_t tempo = time(NULL);
    char * hour = ctime(&tempo);
    int endStr = strlen(hour) - 1;
    hour[endStr] = '\0';
    string datetime(hour);
    this->file << datetime << ": " << data << "\n";
	
    this->file.close();
    
    mutex_monitor.unlock();

}

void Monitor::MonitorDisplay(){
    string line;
    this->file.open(this->datapath, ios::in);

    while(getline(this->file,line))
        cout << line << '\n';
}

int main(){
    
    Monitor monitor_1("log.txt");
    Monitor monitor_2("log2.txt");

    thread threads[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++){
        if(i%2 == 0){
            threads[i] = thread(&Monitor::MonitorWrite, &monitor_1, "ABRACADABRA");
        }else{
            threads[i] = thread(&Monitor::MonitorWrite, &monitor_2, "SIMSALABIM");
        }
    }

   for(int i = 0; i < NUM_THREADS; i++){
       threads[i].join();
   }

    cout << "Monitor 1:\n";
	monitor_1.MonitorDisplay();
	cout << "Monitor 2:\n";
	monitor_2.MonitorDisplay(); 
    return 0;
}