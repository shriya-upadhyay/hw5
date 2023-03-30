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

        //place floating characters in a queue
        for (unsigned int i = 0; i < floating.size(); i++) {
            floatingChars.push(floating[i]);
        }

        //count number of blanks in original word
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

//create set of characters to keep track of used_letters;
std::set<char> used_letters; 
    
    //if the current letter we are on, is greater than the length of the word, the word is full
    //check if the word is in dictionary and add if so
    if (current_ind >= current.size()) {
        if (dict.find(current)!= dict.end()) {
            words.insert(current);  
        }
        //reset the current index to 0 and return
        current_ind = 0;
        return;
	} 


    else {
        int ascii = 97;
        //if the current index is a blank -, loop through the possible letter options
        if(current[current_ind] == '-'){
            //first loop through floating characters, pushing each character to used letters through each iteration
            int n = floatingChars.size();
            for(int i = 0; i < n; i++) {
                char temp = floatingChars.front();
                if (used_letters.find(temp) != used_letters.end()) {
                    continue;
                }
                current[current_ind] = temp;
                //decrease number of blanks after replacing with a floating letter
                if (num_blanks > 0 ){
                num_blanks--;
                }
                used_letters.insert(temp);
                floatingChars.pop();
                wordle_helper(current, current_ind + 1, floatingChars, words, dict, num_blanks);
                //after recursing, reinsert the - and increase num of blanks again, and reinsert the floating chars
                current[current_ind] = '-';
                num_blanks++;
                floatingChars.push(temp);
            }


            //enter the second loop (entire alphabet) only if blanks are left in word
            if (num_blanks > floatingChars.size()) {
                while (ascii < 123) {
                    //only insert letters that haven't been tried in floating characters group
                    if (used_letters.find(ascii) != used_letters.end()) {
                        ascii++;
                        }
                        current[current_ind] = ascii; 
                        //decrease number of blanks after inserting
                        if (num_blanks > 0) {
                        num_blanks--;
                        }
                        //after recursing, reinsert dash, increase number of blanks, and increment ascii
                        wordle_helper(current, current_ind + 1, floatingChars, words, dict, num_blanks);
                        current[current_ind] = '-';
                        num_blanks++;
                        ascii++;
                }
            }
        }

        //increment current index and recurse
        current_ind++;
        wordle_helper(current, current_ind, floatingChars, words, dict, num_blanks); 
    }

}

// Define any helper functions here
