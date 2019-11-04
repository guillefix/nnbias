#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "KC.h"
#include <tuple>

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
  map<string, string> output_inputs;
  ofstream myfile;
 inputs_stats.clear();
 ifstream infile(argv[1]);
 string line;
 while (getline(infile, line))
 {
   vector<string> pair = split(line, '\t');
   if (pair.size() == 2) {
     string output = pair[1];
     double input_comp = calc_KC(pair[0].c_str());
     if (input_comp > std::get<2>(inputs_stats[output])) {
        std::get<2>(inputs_stats[output]) = input_comp;
        std::get<5>(inputs_stats[output]) = pair[0];
     }
     if (input_comp < std::get<1>(inputs_stats[output]) || std::get<1>(inputs_stats[output]) == 0) {
        std::get<1>(inputs_stats[output]) = input_comp;
        std::get<4>(inputs_stats[output]) = pair[0];
     }
     std::get<0>(inputs_stats[output]) += input_comp;
     std::get<3>(inputs_stats[output]) += 1;
   }
}
     infile.close();

cout << "finished reading" << "\n";

     myfile.open (argv[2]);
      for(auto iterator = inputs_stats.begin(); iterator != inputs_stats.end(); ++iterator)
      {
        tuple<double,double,double,int,string,string> tuple = iterator->second;
        string output = iterator->first;
        //output complexity, min input complexity, max input complexity, mean input complexity, frequency
          myfile << output << "\t" << std::get<4>(tuple) << "\t" << std::get<5>(tuple) << "\t" << to_string(calc_KC(output.c_str())) + " " + to_string(std::get<1>(tuple)) + " " + to_string(std::get<2>(tuple)) + " " + to_string(std::get<0>(tuple)/std::get<3>(tuple)) + " " + to_string(std::get<3>(tuple)) + "\n";
      }
     myfile.close();
}
