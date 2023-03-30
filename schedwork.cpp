#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool schedulehelper(size_t row, size_t col, size_t d, size_t n, size_t k, const size_t maxShifts, std::map<unsigned int, int> usedWorkers, const AvailabilityMatrix& avail, DailySchedule& sched);
bool isValid(size_t row, size_t col, size_t i, size_t k, const size_t maxShifts, std::map<unsigned int, int> usedWorkers, const AvailabilityMatrix& avail, DailySchedule& sched);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

	//keep track of n (days) and k ()
    size_t n = avail.size();
    size_t k = avail[0].size();


    std::map<unsigned int, int> usedWorkers;

        //initalize map to keep track of worker ids and how many shifts they have worked
		for (unsigned int i = 0; i < k; i++) {
			usedWorkers[i] = 0;
		}

        //initalize schedule with all -1 instead of possible worker ids
        for (unsigned int i = 0; i < n; i++ ){
            std::vector<unsigned int> k (dailyNeed, -1);
            sched.push_back(k);
        }

    return schedulehelper(0, 0, dailyNeed, n, k, maxShifts, usedWorkers, avail, sched);

}

bool schedulehelper(size_t row, size_t col, size_t d, size_t n, size_t k, const size_t maxShifts, std::map<unsigned int, int> usedWorkers, const AvailabilityMatrix& avail, DailySchedule& sched) {
    //return if we have reached the end, aka a path has been found
    if (row == n) {
        return true;
    }

    //loop through possible worker ids and assign worker id to current spot and increment the number of shifts that worker has worked in the map
    for (Worker_T i = 0; i < k; i++) {
        sched[row][col] = i;
        usedWorkers[i]++;
        //if the current placing is valid, recurse
        if (isValid(row, col, i, k, maxShifts, usedWorkers, avail, sched)) {
            //recurse to next row if in last column of a row
            if (col + 1 == d ) {
                if (schedulehelper(row + 1, 0, d, n, k, maxShifts, usedWorkers, avail, sched)) {
                    return true;
                }
            }

            //recurse to next column in row
            else {
                if (schedulehelper(row, col+1, d, n, k, maxShifts, usedWorkers, avail, sched) ) {
                    return true;
                }
            }
        }

        //if invalid, decrement the number of shifts worked
        else {
            usedWorkers[i]--;
        }
    }

    //if we reach the end of possible values without finding a valid solution, return false and reset the value of the current spot
        sched[row][col] = -1;
        return false;

}

//checks if current worker being placed in current spot is valid

bool isValid(size_t row, size_t col, size_t i, size_t k, const size_t maxShifts, std::map<unsigned int, int> usedWorkers, const AvailabilityMatrix& avail, DailySchedule& sched) {
    //return false if the current worker id is invalid
    if (i == INVALID_ID) {
        return false;
    }
    
    //return false if the worker is not available during the current time or if the worker has worked more than the maxshifts already
    unsigned int shifts = usedWorkers[i];
    if (!(avail[row][i]) || shifts > maxShifts) {
        return false;
    }

    return true;

}


