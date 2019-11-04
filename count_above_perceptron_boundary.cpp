#include <stdlib.h>
#include <stdio.h>
// #include <string.h>
// #include <math.h>
#include <vector>
#include <armadillo>
#include "nn_pheno_bool_0hl.hpp"
#include <bitset>
#include <random>
#include <mpi.h>
//#include <boost/dynamic_bitset.hpp>

using namespace std;

int main(int argc, char const *argv[]) {
  //string index = getenv("SLURM_ARRAY_TASK_ID");
  int world_rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int base = stoi(argv[3]);
  int n_input = stoi(argv[4]);
  int n_out = 1;
  bool center = false;

  int total_params = n_input*n_out + n_out; 

  arma_rng::set_seed_random();

  vector<double> gen(total_params);
  vec gen_w, gen_b;
  //boost::dynamic_bitset<> found_fun(pow(base,n_input));

  double sigmaw = 1.0;
  double sigmab = 0.0;

  int t;

  //ofstream datafile;
  //datafile.open (string(argv[1])+string("_")+to_string(world_rank)+string("_")+string("full_sample_net_0hl.txt"));
  vector<int> fracs;
  fracs.assign(pow(base,n_input),0);
  int N = stoi(string(argv[2]));
  for (int i = 0; i < N; i++) {
    
    gen_w = sigmaw/std::sqrt(n_input)*(arma::randn<vec>( n_input*n_out ));
    gen.insert(gen.end(),gen_w.begin(), gen_w.end());
    gen_b = sigmab*arma::randn<vec>( n_out );
    gen.insert(gen.end(),gen_b.begin(), gen_b.end()); 

    t = num_above_boundary(base, n_input, gen, center);
    fracs[t] += 1;

    gen.clear();
    //datafile << found_fun << "\n";
  }
    ofstream myfile;
     myfile.open(string(argv[1])+to_string(base)+string("_")+to_string(n_input)+string("_")+to_string(world_rank)+string("_")+string("perceptron_counts.txt"));
     int count;
      for(int j=0; j < fracs.size(); j++)
      {
        count = fracs[j];
        myfile << to_string(j) + " " + to_string(count) + "\n";
        //cout << to_string(j) + " " + to_string(count) + "\n";
      }
     myfile.close();

  //datafile.close(); 
  MPI_Finalize(); 
}

//g++ -std=c++11 sample_net.cpp -o sample_net -DARMA_DONT_USE_WRAPPER -lopenblas -llapack
