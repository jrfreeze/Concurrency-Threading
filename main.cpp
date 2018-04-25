//
//  main.cpp
//  FancyThreads
//
//  Created by Joshua on 3/12/18.
//  Copyright © 2018 Joshua. All rights reserved.
//

#include <iostream>
#include <random>
#include <time.h>
#include <thread>
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

const int tosses = 250000000;   // total number of coin tosses
int heads[20], tails[20];       // global arrays to hold number or heads/tails in a given thread

// Function toss takes as parameters the number of the thread (to use in the heads and tails arrays
// and the number of coin tosses per thread. It then tosses the coin that number of times while
// counting the number of heads and tails.
void toss(int threadnum, int tossesPer) {
    default_random_engine dre;
    uniform_int_distribution<int> Tosser(0,1);  // define random number generator for coin tosses
    heads[threadnum] = tails[threadnum] = 0;    // initialize number of heads & tails to 0 each time
    for (int j=0; j< tossesPer; ++j) {
        if (Tosser(dre)) ++heads[threadnum];    // increment number of heads, OR
        else ++tails[threadnum];                // increment number of tails.
    }
}

int main() {
    time_t start,finish;       // variables to hold the start and end time. Difference is total time.
    int headtotal = 0, tailtotal = 0;   // sum of the number of heads and tails in all threads
    int tossesPer;  // tosses per thread = total  number of tosses / number of threads
    vector<thread> threads; // thread vector to hold the active threads

    // each time through this loop tests a given number of threads
        for (int numthreads = 1; numthreads <= 12; numthreads += 1) {
        tossesPer = tosses/numthreads;  // determine number of tosses per thread
        start = time(0); // set start time

        // populate threads vector with the proper number of threads
        for(int i = 0; i < numthreads; ++i){
            threads.push_back(thread(toss, i, tossesPer)); // open a thread with parameters holding
                                                           // the thread number and tosses to be performed
        }
        // Join all the threads in the vector called threads
        for(auto& thread : threads){
            thread.join();}

        finish = time(0); // record the finish time
        
        // Sum up total heads and tails from all threads
        for (int j=0; j<numthreads; ++j) {
            headtotal += heads[j];
            tailtotal += tails[j];  }
        
        // Print out data for the current thread count
        cout << "Threads: " << setw(2) << numthreads;
        cout << "  Seconds: " << setw(2) << finish-start;
        cout << "  Flips: " << headtotal + tailtotal << endl;
        cout << "Heads: " << headtotal << "     Tails: " << tailtotal << endl;
        headtotal = tailtotal = 0;  // reset head and tail count after each time through the loop
        while (!(threads.empty())) { // empty the threads vector after each time through the loop
            threads.pop_back();  }

        }  // end loop for the current number of threads
    
return 0; }
