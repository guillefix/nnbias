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

template <typename T>
vec get_bits(T n, int size) {
  vec output = zeros<vec>(size);
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

int n_input = 7, n_out = 1;

int first = 0;
int last = n_input*n_out;
mat W1(slice(nn1,first,last));
W1=reshape(W1,n_out,n_input);

first = last;
last = first + n_out;
vec b1(slice(nn1,first,last));

// b3.print();

vec zeros_1 = zeros<vec>(n_out);
// vec zeros_2 = zeros<vec>(nh_2);

//vector<int> output((int)pow(2,n_input));
bitset<128> output;

for (int i = 0; i < pow(2,n_input); i++) {
  vec input = get_bits(i, n_input);
  vec out = W1 * input + b1;
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

vector<double> take_step(vector<double> gen, double step_size) {
  vec gen1 = arma::conv_to<vec>::from(gen);
  bool candidate_not_found = true;
  int n_input = 7, nh_1 = 20, n_out = 1;
  int n_params = n_input*nh_1 + nh_1 + nh_1*n_out + n_out;
  int param_blocks [6] = {n_input*nh_1, nh_1, nh_1*n_out, n_out};
  int input_dims [6] = {n_input, n_input, nh_1, nh_1};
  int activation [6] = {0,0,1,1}; //0 is sign, 1 is relu. The choice affects the activation range chosen as per Xavier initialization convention
  double a [2] = {std::sqrt(3)*std::sqrt(2), std::sqrt(3)};
  vector<double> gen2;

  arma_rng::set_seed_random();

  int MAX_ITERS = 10000;
  int iter = 0;

  while (candidate_not_found && iter < MAX_ITERS) {
    gen2 = arma::conv_to<vector<double>>::from(gen1 + step_size*arma::randn<vec>( n_params ));

    vector<double>::iterator first = gen2.begin();
    vector<double>::iterator last = gen2.begin();
    candidate_not_found = false;
    for (size_t i = 0; i < 4; i++) {
      first = last;
      last = first + param_blocks[i];
      if ( any_of(first, last, [a,input_dims,activation,i](int x){return std::abs(x) > a[activation[i]]/(std::sqrt(input_dims[i]));}) ) {
        candidate_not_found = true;
        // vector<double> newVec(first, last);
        // for (std::vector<double>::const_iterator i = newVec.begin(); i != newVec.end(); ++i)
        //   std::cout << to_string(*i) << ' ';
        // cout << "\n";
        // cout << to_string(i)<<"\n";
      }
    }
    iter++;
  }
  if (iter >= MAX_ITERS)
    cout << "Max number of iterations reached in trying to find mutation candidate\n";
  return gen2;
}
