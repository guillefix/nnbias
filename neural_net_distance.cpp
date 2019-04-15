#include <stdlib.h>
#include <stdio.h>
// #include <string.h>
// #include <math.h>
#include <vector>
#include <armadillo>
#include "nn_pheno.hpp"

using namespace std;

int main(int argc, char const *argv[]) {

  int n_input = 7, nh_1 = 20, nh_2 = 20, n_out = 1;

  int n_params = n_input*nh_1 + nh_1 + nh_1*nh_2 + nh_2 + nh_2*n_out + n_out;

  arma_rng::set_seed_random();

  vec gen1_arma = std::sqrt(3)*std::sqrt(2)/std::sqrt(20)*(2*arma::randu<vec>( n_params )-1);
  vector<double> gen1 = arma::conv_to<vector<double>>::from(gen1_arma);
  // vector<double> gen2 = arma::conv_to<vector<double>>::from(gen1_arma + 0.001*arma::randn<vec>( n_params ));
  vector<double> gen2 = take_step(gen1, 0.01*std::sqrt(3)*std::sqrt(2)/std::sqrt(20));

  //print geno
  // for (size_t i = 0; i < gen.size(); i++) {
  //   cout << to_string(gen[i]) + "\n";
  // }

  vector<int> p1 = pheno(gen1);
  vector<int> p2 = pheno(gen2);

  for (size_t i = 0; i < p1.size(); i++) {
    cout << p1[i];
  }
  cout << "\n";

  for (size_t i = 0; i < p2.size(); i++) {
    cout << p2[i];
  }
  cout << "\n";

  cout << "Distance: " << dist(p1,p2) << "\n";

}

//g++ -std=c++11 neural_net_distance.cpp -o nn_dist -DARMA_DONT_USE_WRAPPER -lopenblas -llapack
