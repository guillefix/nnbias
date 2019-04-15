#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "KC.h"

using namespace std;
// #include <boost/lexical_cast.hpp>

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

int main (int argc, char** argv) {
  int N1 = atoi(argv[1]);
  int N2 = atoi(argv[2]);
  bool remop = false;
  for (int j = 0; j < argc; j++)
    if (argv[j] == "-r") remop = true;
  // int no = atoi(argv[2]); //output size
  // printf("complexity: %f\n", calc_KC(argv[1]));
  // printf("hi %d",1);

  for( int i = N1; i < N2; i++)
   {
     ifstream infile;
     infile.open("inputcnts/" + to_string(i));
     ofstream outfile;
     outfile.open("comp/" + to_string(i));
     string line;
     while (getline (infile,line))
     {
        vector<string> tokens = split(line, '\t');
        string output = tokens[0];
        string cnt = tokens[1];
        // if (output.length() != no) {continue;}
        outfile << calc_KC(output.c_str()) << ' ' << cnt << '\n';

     }
     infile.close();
     outfile.close();
     if (remop) {
       if( remove( ("inputcnts/" + to_string(i)).c_str() ) != 0 ) {
         perror( "Error deleting file" );
       }
     }
   }
   return 0;
}
