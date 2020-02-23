#include "DNAReader.h"

int main(int argc, char const *argv[]) {

  //Seeding the random number generator for later use
  srand((unsigned)time(NULL));

  //This checks if the user did not enter enough arguments
  if(argc < 2)
  {
    cout << "Invalid number of arguments." << endl;
    return 1;
  }

  //This is a test input stream to see if the file exists
  ifstream test;
  test.open(argv[1]);

  //This if-else will check if the file exists. If it does, the test stream will be closed
  if(!test.is_open()){
    cout << "Could not open file." << endl;
    return 1;
  }
  else{
    test.close();
  }

  //The argument at index 1 will be used as the file name
  string filename = argv[1];

  //And output filestream is opened to "garrettbolen.out" and some basic info is printed
  ofstream outFS;
  outFS.open("garrettbolen.out");
  outFS << "Garrett Bolen" << endl << "2324654" << endl << "CPSC-350-02" << endl << endl;
  outFS << "FILENAME: " << filename << endl << endl;

  //This initializes the variable to be used as the while condition at the end of this loop
  string input = "";

  do{

    //A new instance of DNAReader is created using the file name inputed
    DNAReader* dr = new DNAReader(filename);

    //All the necessary calculations are done using the class methods
    double sum = (double)dr->sum();
    double mean = dr->mean();
    double var = dr->var();
    double sd = dr->sd();

    //The calculations are printed to the file using outFS
    outFS << "Length of DNA string calculations:" << endl;
    outFS << "The total sum is: " << sum << endl;
    outFS << "The mean is: " << mean << endl;
    outFS << "The variance is: " << var << endl;
    outFS << "The standard deviation is: " << sd << endl << endl;

    //The probabilities are calculated using the sum and count variables and printed to the file
    outFS << "Probabilities of each nucleotide and nucleotide bigrams:" << endl;
    double probA = dr->countA/sum;
    double probG = dr->countG/sum;
    double probC = dr->countC/sum;
    double probT = dr->countT/sum;

    outFS << "A: " << probA << endl;
    outFS << "G: " << probG << endl;
    outFS << "C: " << probC << endl;
    outFS << "T: " << probT << endl;
    outFS << "AA: " << dr->countAA/sum << endl;
    outFS << "AC: " << dr->countAC/sum << endl;
    outFS << "AT: " << dr->countAT/sum << endl;
    outFS << "AG: " << dr->countAG/sum << endl;
    outFS << "CA: " << dr->countCA/sum << endl;
    outFS << "CC: " << dr->countCC/sum << endl;
    outFS << "CT: " << dr->countCT/sum << endl;
    outFS << "CG: " << dr->countCG/sum << endl;
    outFS << "TA: " << dr->countTA/sum << endl;
    outFS << "TC: " << dr->countTC/sum << endl;
    outFS << "TT: " << dr->countTT/sum << endl;
    outFS << "TG: " << dr->countTG/sum << endl;
    outFS << "GA: " << dr->countGA/sum << endl;
    outFS << "GC: " << dr->countGC/sum << endl;
    outFS << "GT: " << dr->countGT/sum << endl;
    outFS << "GG: " << dr->countGG/sum << endl << endl;

    //A few variables are initialized for the gaussian distribution calculation
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double d = 0.0;
    const double pi = 3.14159265358979323846;

    //This loop will generate 1000 randomized DNA strings to be printed to the file
    for(int i = 0; i < 1000; ++i){
      string temp = "";

      //a and b are set equal to random values between [0,1)
      a = (double)rand()/RAND_MAX;
      b = (double)rand()/RAND_MAX;

      //c is calculated with a and b, then d is calculated using c and the standard dev and mean calculated above
      c = sqrt(-2 * log(a)) * cos(2 * pi * b);
      d = sd * c + mean;

      //This for loop determines which letter will go next in the string of length d
      for(int i = 0; i < int(d); ++i){

        //The variable prob represents a roll of the dice essentially to see if it will be A,G,C or T
        double prob = (double)rand()/RAND_MAX;

        //These if statements determine which letter it will be using the probabilities calculated above
        if(prob >= 0 && prob < probA)
          temp += "A";
        else if(prob >= probA && prob < (probA + probG))
          temp += "G";
        else if(prob >= (probA + probG) && prob < (probA + probG + probC))
          temp += "C";
        else
          temp += "T";
      }
      //The string is printed to the file
      outFS << temp << endl;
    }

    outFS << endl;
    //The file stream used in dr is closed and the object is deleted
    dr->inFS.close();
    delete dr;

    //Here, the user's input is retrived and stored in the variable input
    cout << "Input another file? Type 'Y' to continue or 'N' to quit:" << endl;
    cin >> input;

    if(input == "y" || input == "Y"){

      //If the user enters 'y', they are prompted to enter another file name
      cout << "Enter the name of the file to be processed: " << endl;
      cin >> filename;

      //The next few lines serve as the same test done before to see if the file exists
      ifstream test;
      test.open(filename);

      //If it doesn't, the program will exit
      if(!test.is_open()){
        cout << "Invalid file name." << endl;
        return 1;
      }
      else{
        test.close();
      }

      //The old output filestream is closed and a new one is opened in append mode
      outFS.close();
      outFS.open("garrettbolen.out", ios::app);
      outFS << "FILENAME: " << filename << endl << endl;

    }

  }while(input == "y" || input == "Y");

  //The output filestream is closed once the user decides to exit
  outFS.close();
  return 0;
}
