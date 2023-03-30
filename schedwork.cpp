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

    size_t n = avail.size();
    size_t k = avail[0].size();


    std::map<unsigned int, int> usedWorkers;

		for (unsigned int i = 0; i < k; i++) {
			usedWorkers[i] = 0;
		}

        for (unsigned int i = 0; i < n; i++ ){
            std::vector<unsigned int> k (dailyNeed, -1);
            sched.push_back(k);
        }

    return schedulehelper(0, 0, dailyNeed, n, k, maxShifts, usedWorkers, avail, sched);
    // Add your code below

}

bool schedulehelper(size_t row, size_t col, size_t d, size_t n, size_t k, const size_t maxShifts, std::map<unsigned int, int> usedWorkers, const AvailabilityMatrix& avail, DailySchedule& sched) {
    if (row == n) {
        return true;
    }
        for (Worker_T i = 0; i < k; i++) {
            sched[row][col] = i;
            usedWorkers[i]++;
            if (isValid(row, col, i, k, maxShifts, usedWorkers, avail, sched)) {
                if (col + 1 == d ) {
                    if (schedulehelper(row + 1, 0, d, n, k, maxShifts, usedWorkers, avail, sched)) {
                        return true;
                    }
                }

                else {
                    if (schedulehelper(row, col+1, d, n, k, maxShifts, usedWorkers, avail, sched) ) {
                        return true;
                    }
                }
            }

            else {
                usedWorkers[i]--;
            }
        }
        sched[row][col] = -1;
        return false;

}

bool isValid(size_t row, size_t col, size_t i, size_t k, const size_t maxShifts, std::map<unsigned int, int> usedWorkers, const AvailabilityMatrix& avail, DailySchedule& sched) {
    if (i == INVALID_ID) {
        return false;
    }
    
    unsigned int shifts = usedWorkers[i];
    if (!(avail[row][i]) || shifts > maxShifts) {
        return false;
    }

    return true;

}


