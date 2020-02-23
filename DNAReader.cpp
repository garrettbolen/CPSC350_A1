#include "DNAReader.h"

//The constructor takes in a file name to be used in an input file stream
DNAReader::DNAReader(string filename){

  //Each count is initialized to 0 within the constructor
  countA = 0;
  countG = 0;
  countC = 0;
  countT = 0;
  countAA = 0;
  countAC = 0;
  countAT = 0;
  countAG = 0;
  countCA = 0;
  countCC = 0;
  countCT = 0;
  countCG = 0;
  countTA = 0;
  countTC = 0;
  countTT = 0;
  countTG = 0;
  countGA = 0;
  countGC = 0;
  countGT = 0;
  countGG = 0;

  //The variable inFS is used to open the file stream
  inFS.open(filename);

  //This string will store each line as the file is read
  string line = "";

  //This while loop iterates through the file using inFS
  while(getline(inFS, line)){

    //The to_upper function (defined below) converts the whole string to uppercase
    to_upper(line);

    //Each count variable is updated using the count function (defined below)
    countA += count(line, 'A');
    countG += count(line, 'G');
    countC += count(line, 'C');
    countT += count(line, 'T');
    countAA += count(line, "AA");
    countAC += count(line, "AC");
    countAT += count(line, "AT");
    countAG += count(line, "AG");
    countCA += count(line, "CA");
    countCC += count(line, "CC");
    countCT += count(line, "CT");
    countCG += count(line, "CG");
    countTA += count(line, "TA");
    countTC += count(line, "TC");
    countTT += count(line, "TT");
    countTG += count(line, "TG");
    countGA += count(line, "GA");
    countGC += count(line, "GC");
    countGT += count(line, "GT");
    countGG += count(line, "GG");

  }

  /*
  This block will appear everytime the file is iterated through. It ensures
  that after each iteration the file stream will know to start at the top for
  the next iteration
  */
  inFS.clear();
  inFS.seekg(0);
}

//This function returns the number of times a char appears in a given string
int DNAReader::count(string s, char c){
  int count = 0;
  for(int i = 0; i < s.size(); ++i){
    if(s[i] == c)
      count++;
  }
  return count;
}

//This function returns the number of times a string appears in another string
int DNAReader::count(string main, string sub){
  int count = 0;
  for(int i = 0; i < main.size(); ++i){
    string temp = "";
    for(int j = 0; j < sub.size(); ++j){
      temp += main[j+i];
    }
    if(temp == sub)
      count++;
  }
  return count;
}

//This function converts all characters in a string to uppercase
void DNAReader::to_upper(string& s){
  for(int i = 0; i < s.size(); ++i)
    s[i] = toupper(s[i]);
}

//This function will iterate through a file and return the total number of characters
int DNAReader::sum(){
  int sum = 0;
  string line = "";
  while(getline(inFS, line)){
    sum += line.size() - 1;
  }

  inFS.clear();
  inFS.seekg(0);

  return sum;
}

//This function uses the sum and divides it by the number of lines to return the mean
double DNAReader::mean(){
  int s = sum();
  string line = "";
  double numLines = 0.0;
  while(getline(inFS, line)){
    numLines += 1;
  }

  inFS.clear();
  inFS.seekg(0);

  return s/numLines;
}

//This function does some basic math to figure out and return the variance
double DNAReader::var(){
  double m = mean();
  double diffSqr = 0.0;
  double diffSum = 0.0;
  int numLines = 0;
  string line = "";
  while(getline(inFS, line)){
    diffSqr = pow((m - (line.size() - 1)),2);
    numLines += 1;
    diffSum += diffSqr;

  }

  inFS.clear();
  inFS.seekg(0);

  return diffSum/numLines;
}

//This function simply takes the square root of the variance to return standard deviation
double DNAReader::sd(){
  return sqrt(var());
}
