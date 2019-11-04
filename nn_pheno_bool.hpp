#include <stdlib.h>
#include <stdio.h>
// #include <string.h>
#include <math.h>
#include <vector>
#include <armadillo>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <csignal>

// #include <boost/algorithm/string/join.hpp>
// #include "split.h"

using namespace std;
using namespace arma;

vec get_base_expansion(int base, int size, int n, bool center) {
  vec output = zeros<vec>(size);
  for (int i=0; i<size; ++i) {
    if (center) {
        output(i) = base*(n%base) - (base*(base-1))/2;
    } else {
        output(i) = n%base;
    }
    n /= base;
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

boost::dynamic_bitset<> pheno(const int base, const vector<double> & nn1, vector<int> nhs, int n_layers, bool centered, string activation)
{

int n_input = nhs[0];

int first;
int last = 0;

mat Ws [n_layers];
vec bs [n_layers];
mat W;
mat b;

for (int i=0; i< n_layers; i++) {

    first = last;
    last = first + nhs[i]*nhs[i+1];
    W = slice(nn1,first,last);
    W=reshape(W,nhs[i+1],nhs[i]);
    Ws[i] = W;

    first = last;
    last = first + nhs[i+1];
    b = slice(nn1,first,last);
    b=reshape(b,nhs[i+1],1);
    bs[i] = b;

}


//vector<int> output((int)pow(2,n_input));
boost::dynamic_bitset<> output(pow(base,n_input));;
vec h;
vec zero_vecs [n_layers];
vec out;

for (int i=0; i< n_layers; i++) {
    zero_vecs[i] = zeros<vec>(nhs[i+1]);
}

for (int i = 0; i < pow(base,n_input); i++) {
    //cout << base << "\n";
    //cout << i << "\n";
    h = get_base_expansion(base, n_input, i, centered);
    //cout << h << "\n";
    for (int l=0; l< n_layers-1; l++) {
      h = Ws[l] * h + bs[l];
      if (activation == "relu")
          h = arma::max(zero_vecs[l],h);
      else if (activation == "tanh")
          h = arma::tanh(h);
    }
    out = Ws[n_layers-1] * h + bs[n_layers-1];
    //cout << Ws[n_layers-1] * h << " ";
    //cout << out << " ";
    //if (out[0] == 0.0 && i!=0) {
        //cout << Ws[0] << "\n";
    //    cout << i << "\n";
    //    //cout << out << " ";
    //    std::raise(SIGINT);

    //}
    //cout << out << " ";
    out = arma::floor((arma::sign(out)+1)/2);
    if ((bool)out(0)) output.set(i);
    else output.reset(i);
}

return output;

}

int num_above_boundary(const int & base, const vector<double> & nn1, vector<int> nhs, int n_layers, bool centered, string activation){
    boost::dynamic_bitset<> output = pheno(base, nn1, nhs, n_layers, centered, activation);
    //cout << output << "\n";
    int n_input = nhs[0];

    int count = 0;
    for (int j = 0; j < pow(base,n_input); j++) {
      if ((bool)output[j]) count += 1;
    }
    return count;
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

