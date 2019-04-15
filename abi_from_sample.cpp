#include <stdlib.h>
#include <stdio.h>
// #include <string.h>
// #include <math.h>
#include <vector>
#include <armadillo>
#include "nn_pheno_bool_2hl.hpp"
#include <bitset>
#include <random>
#include <mpi.h>
#include <iostream> 

using namespace std;

template< size_t size>
typename std::bitset<size> random_bitset( double p = 0.5) {

    typename std::bitset<size> bits;
    std::random_device rd;
    std::mt19937 gen( rd());
    std::bernoulli_distribution d( p);

    for( int n = 0; n < size; ++n) {
        bits[ n] = d( gen);
    }

    return bits;
}


template< size_t size, size_t m=size/2>
typename std::bitset<size> random_bitset_noreplace () {

    typename std::bitset<m> ones;
    typename std::bitset<size-m> zeros;
    ones.set(); zeros.reset();

    string allbits = ones.to_string()+zeros.to_string();

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (allbits.begin(), allbits.end(), std::default_random_engine(seed));

    typename std::bitset<size> result(allbits);

    return result;
}

int main(int argc, char const *argv[]) {
  //string index = getenv("SLURM_ARRAY_TASK_ID");
  int world_rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int n_input = 7, nh_1 = 40, nh_2 = 40, n_out = 1;
  int m=64;

  // vector<int> hidden_neurons = {n_input, nh_1, nh_2, n_out};
  int total_params = n_input*nh_1 + nh_1 + nh_1*nh_2 + nh_2 + nh_2*n_out + n_out;

  arma_rng::set_seed_random();

  vector<double> gen(total_params);
  vec gen_w, gen_b;
  // vector<bool> p1;
  string fun_string = argv[2];
  string comp = argv[3];
  //string training_set_string = argv[4];
  bitset<128> fun (fun_string);
  //bitset<128> training_set (training_set_string);
  bitset<128> training_set = random_bitset_noreplace<128,64>();
  bitset<128> found_fun;
  bitset<128> agreements;
  string line;

  ofstream datafile;
  datafile.open (string("abi_samples/")+string(argv[1])+string("_")+to_string(world_rank)+string("_")+comp+string("_")+string("abi_sample_net_2hl.txt"));
  datafile << "#" << training_set << "\n" << "#" << fun << "\n";
  //ifstream samplefile(argv[4]);
  ifstream samplefile(string("sampled_funs/")+string(argv[1])+string("_")+to_string(world_rank)+string("_")+string("full_sample_net_2hl.txt"));
  if (samplefile.is_open()) {
  while ( getline(samplefile,line)) {
    found_fun = bitset<128>(line); 
    //cout << found_fun.to_string() << "\n";
    agreements = ~(fun^found_fun);
    if ( ((~training_set)|agreements).all() ) {
      datafile << found_fun << "\t" << 1-(float)(agreements.count()-m)/(128-m) << "\n";
    }
  }
  samplefile.close();
  }
  else { cout <<  "Unable to open file"; }
  //for (int i = 0; i < stoi(string(argv[2])); i++) {
  //}
  datafile.close(); 
  MPI_Finalize(); 
}

//g++ -std=c++11 sample_net.cpp -o sample_net -DARMA_DONT_USE_WRAPPER -lopenblas -llapack
