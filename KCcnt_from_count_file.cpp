#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "KC.h"
#include <tuple>
#include <boost/algorithm/string.hpp>

// #include <stdio.h>

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

using namespace std;

int main (int argc, char** argv) {
  map<string, int> inputs_stats;
  ofstream myfile;
 inputs_stats.clear();
 //ifstream infile(argv[1]);
 string line;
 //while (getline(infile, line))
 vector<string> linearr;
 for (std::string line; std::getline(std::cin, line);) {
     boost::trim_left(line);
     boost::split(linearr,line,boost::is_any_of(" "));
     inputs_stats[linearr[1]] = stoi(linearr[0]);
 }
 //infile.close();

cout << "finished reading" << "\n";

     //myfile.open (argv[2]);
     myfile.open (argv[1]);
      for(auto iterator = inputs_stats.begin(); iterator != inputs_stats.end(); ++iterator)
      {
        int freq = iterator->second;
        string output = iterator->first;
        //output, output complexity, frequency
          myfile << output + " " + to_string(calc_KC(output.c_str())) + " " + to_string(freq) + "\n";
      }
     myfile.close();
}
