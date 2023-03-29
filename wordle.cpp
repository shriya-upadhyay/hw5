#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <queue>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle_helper(std::string& current, unsigned int current_ind, std::queue<char>& floatingChars, std::set<std::string>& words, const std::set<std::string>& dict, unsigned int num_blanks);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
        std::set<std::string> words;
		string curr = in;
        std::queue<char> floatingChars;
        for (unsigned int i = 0; i < floating.size(); i++) {
            floatingChars.push(floating[i]);
        }

        unsigned int num_blanks = 0;
        for (unsigned int i = 0; i < in.size(); i++) {
        if (in[i] == '-') {
            num_blanks++;
            }
        }
        wordle_helper(curr, 0, floatingChars, words, dict, num_blanks);
		return words;
}

void wordle_helper(std::string& current, unsigned int current_ind, std::queue<char>& floatingChars, std::set<std::string>& words, const std::set<std::string>& dict, unsigned int num_blanks)
{

std::set<char> used_letters; 
//std:: cout << "current: " << current << endl;
//std:: cout << "current_ind: " << current_ind <<endl;
//std:: cout << "current size is: " << current.size() << endl;
    
    if (current_ind >= current.size()) {
        if (dict.find(current)!= dict.end()) {
            //cout << floatingChars.size() << endl;
            words.insert(current);  
        }
        current_ind = 0;
        return;
	} 


else {
  int ascii = 97;
    if(current[current_ind] == '-'){
        int n = floatingChars.size();
        for(unsigned int i = 0; i < n; i++) {
            char temp = floatingChars.front();
            if ( used_letters.find(temp) != used_letters.end()) {
                continue;
            }
            current[current_ind] = temp;
            if (num_blanks > 0 ){
             num_blanks--;
             }
            //std::cout << "index " << current_ind << " is " << current[current_ind]  << std:: endl;
            used_letters.insert(temp);
            floatingChars.pop();
            wordle_helper(current, current_ind + 1, floatingChars, words, dict, num_blanks);
            current[current_ind] = '-';
            num_blanks++;
            floatingChars.push(temp);
            //floatingChars.erase(std::remove(floatingChars.begin(), floatingChars.end(), temp), floatingChars.end());
        }

        //cout << num_blanks << endl;
        //cout << floatingChars.size() << endl;


        if (num_blanks > floatingChars.size()) {
        while (ascii < 123) {
            if (used_letters.find(ascii) != used_letters.end()) {
                ascii++;
                }
                current[current_ind] = ascii; 
                if (num_blanks > 0) {
                num_blanks--;
                }
                wordle_helper(current, current_ind + 1, floatingChars, words, dict, num_blanks);
                current[current_ind] = '-';
                num_blanks++;
                ascii++;
        }
        }
    }
    current_ind++;
    wordle_helper(current, current_ind, floatingChars, words, dict, num_blanks); 
    }

}

// Define any helper functions here
