#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <ctime>
#include <cstring>
using namespace std;

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
        HASH_INDEX_T w[5] ={0};
        //each 6 letters
        int cnt = 4;
        for(int i=k.length() - 1;i>=0;i-=6)
        {
          int len;//current length
          len = std::min(i+1,6);
          unsigned long long temp = 0;
          int ts = 36;
          for(int j = i; j>=i-len+1;j--)//traverse backward that string
          {
            if(j==i)
            temp += letterDigitToNumber(k[j]);
            else
            {
              temp += ts*letterDigitToNumber(k[j]);
              ts*=36;
            }
          }
          w[cnt] = temp;
          cnt--;
        }
        unsigned long long h = 0;
        for (int i = 0; i < 5; i++)
        {
          cout<<"W["<<i<<"] = "<<w[i]<<endl;
            h += w[i]*rValues[i];
        }
        return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (isalpha(letter)) 
        {
          letter = tolower(letter);
          return letter - 'a';
        } 
        else if (isdigit(letter)) 
        {
        return letter - '0' + 26;
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
