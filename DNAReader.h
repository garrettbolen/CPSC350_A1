#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

/*
The DNAReader class serves as an environment for each file to have their own
input stream that stores variables to keep track of the nucleotide counts and
also to define functions to do all the necessary calculations per file.
*/
class DNAReader{
  public:
    //The constructor will take in a filename as a string
    DNAReader(string);

    //All the necessary functions for the assignment are here
    int sum();
    double mean();
    double var();
    double sd();
    int count(string, char);
    int count(string, string);
    void to_upper(string&);

    //This variable will be the input stream that will read from the file
    ifstream inFS;

    //Each of these variables will store the specified nucleotide/bigram count
    int countA;
    int countG;
    int countC;
    int countT;
    int countAA;
    int countAC;
    int countAT;
    int countAG;
    int countCA;
    int countCC;
    int countCT;
    int countCG;
    int countTA;
    int countTC;
    int countTT;
    int countTG;
    int countGA;
    int countGC;
    int countGT;
    int countGG;

};
