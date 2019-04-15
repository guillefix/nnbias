#include <stdlib.h>
#include <stdio.h>
// #include <string.h>
#include <math.h>
#include <vector>
#include <armadillo>
#include <bitset>

// #include <boost/algorithm/string/join.hpp>
// #include "split.h"

using namespace std;
using namespace arma;

vec get_bits(int n, int size) {
  vec output = zeros<vec>(size); //before I forgot to put zeros here, which was a serious bug!
  int i = 0;
  while (n > 0) {
    output(i) = n%2;
    n /= 2;
    ++i;
  }
  return output;
}

vector<double> slice(const vector<double>& v, int start=0, int end=-1) {
    int oldlen = v.size();
    int newlen;

    if (end == -1 or end >= oldlen){
        newlen = oldlen-start;
    } else {
        newlen = end-start;
    }

    vector<double> nv;
    // vector<int> nv(newlen);

    for (int i=0; i<newlen; i++) {
      // nv[i] = v[start+i];
        nv.push_back(v[start+i]);
    }
    return nv;
}

bitset<128> pheno(const vector<double> & nn1)
{

int n_input = 7, nh_1 = 40, nh_2 = 40, n_out = 1;

int first = 0;
int last = n_input*nh_1;
mat W1(slice(nn1,first,last));
W1=reshape(W1,nh_1,n_input);

first = last;
last = first + nh_1;
vec b1(slice(nn1,first,last));

first = last;
last = first + nh_1*nh_2;
mat W2(slice(nn1,first,last));
W2=reshape(W2,nh_2,nh_1);

first = last;
last = first + nh_2;
vec b2(slice(nn1,first,last));

first = last;
last = first + nh_2*n_out;
mat W3(slice(nn1,first,last));
W3=reshape(W3,n_out,nh_2);

first = last;
last = first + n_out;
vec b3(slice(nn1,first,last));
// b3.print();

vec zeros_1 = zeros<vec>(nh_1);
vec zeros_2 = zeros<vec>(nh_2);

//vector<int> output((int)pow(2,n_input));
bitset<128> output;

for (int i = 0; i < pow(2,n_input); i++) {
  vec input = get_bits(i, n_input);
  vec h1 = W1 * input + b1;
  h1 = arma::max(zeros_1,h1);
  vec h2 = W2 * h1 + b2;
  h2 = arma::max(zeros_2,h2);
  vec out = W3 * h2 + b3;
  // out.print();
  out = arma::floor((arma::sign(out)+1)/2);
  if ((bool)out(0)) output.set(i);
  else output.reset(i);
}

return output;

}

int dist(vector<int> p1, vector<int> p2) {
  if (p1.size() != p2.size()) {
    cout << "Sizes of phenos don't match\n";
    return INT_MAX;
  } else {
    int dist = 0;
    for (size_t i = 0; i < p1.size(); i++) {
      if (p1[i] != p2[i]) dist++;
    }
    return dist;
  }
}

