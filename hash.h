#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        int numW = k.length()/6;
        if (k.length()%6 != 0){
          numW++;
        }
        unsigned long long w[5] = {0};
        for (int i = 0; i < 5; ++i) {
          if (5 - numW > i){
            w[i] = 0;
            std::cout << "w[" << i << "] = " << w[i] << std::endl;
          }
          else if (5 - numW == i){
            int end = k.length()%6;
            if (end == 0){
              end = 6;
            }
            int start = 0;
            for (int j = end - 1; j >= 0; j--){
               w[i] += pow(36, j) * letterDigitToNumber(k[start]);
               start++;
            }
            std::cout << "w[" << i << "] = " << w[i] << std::endl;
          }
          else{
            int start = k.length()%6 + 6 * (numW - 6 + i);
            for (int j = 5; j >= 0; j--){
               w[i] += pow(36, j) * letterDigitToNumber(k[start + 5 - j]);
            }
            std::cout << "w[" << i << "] = " << w[i] << std::endl;
          }
        }

        unsigned long long h = 0;
        for (int i = 0; i < 5; ++i) {
            h += rValues[i] * w[i] ;
        }

        return h;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= '0' && letter <= '9') {
            return 26 + (letter - '0');
        } else {
            letter = std::tolower(letter);
            return letter - 'a';
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
