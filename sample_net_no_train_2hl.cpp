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
  //int m=64;

  vector<int> hidden_neurons = {n_input, nh_1, nh_2, n_out};
  int total_params = n_input*nh_1 + nh_1 + nh_1*nh_2 + nh_2 + nh_2*n_out + n_out;

  arma_rng::set_seed_random();

  vector<double> gen(total_params);
  vec gen_w, gen_b;
  // vector<bool> p1;
  //string fun_string = argv[3];
  //bitset<128> fun (fun_string);
  //string comp = argv[4];
  //bitset<128> training_set = random_bitset_noreplace<128,64>();
  bitset<128> found_fun;
  //bitset<128> agreements;

  //double sigmaw = std::sqrt(3);
  double sigmaw = 1.0;
  double sigmab = 1.0;

  string dist_type = argv[3];

  ofstream datafile;
  datafile.open (string("sampled_funs/")+string(argv[1])+string("_")+to_string(world_rank)+string("_")+to_string(sigmaw)+string("_")+to_string(sigmab)+string("_")+dist_type+string("_")+string("_sample_net_2hl.txt"));
  for (int i = 0; i < stoi(string(argv[2])); i++) {

    if (dist_type=="gauss_largebias")
    {
    
    for (size_t j = 0; j < hidden_neurons.size()-1; j++) {
      gen_w = sigmaw/std::sqrt(hidden_neurons[j])*(arma::randn<vec>( hidden_neurons[j]*hidden_neurons[j+1] ));
      gen.insert(gen.end(),gen_w.begin(), gen_w.end());
      gen_b = sigmab*arma::randn<vec>( hidden_neurons[j+1] );
      gen.insert(gen.end(),gen_b.begin(), gen_b.end());      
    }
    }
    else if (dist_type=="uniform_smallbias")
    {

    sigmaw = std::sqrt(3);
    sigmab = std::sqrt(3);
    for (size_t j = 0; j < hidden_neurons.size()-1; j++) {
      gen_w = 2*sigmaw/std::sqrt(hidden_neurons[j])*(arma::randu<vec>( hidden_neurons[j]*hidden_neurons[j+1] ) - 0.5);
      gen.insert(gen.end(),gen_w.begin(), gen_w.end());
      gen_b = 2*sigmab/std::sqrt(hidden_neurons[j])*(arma::randu<vec>( hidden_neurons[j+1] ) - 0.5);
      gen.insert(gen.end(),gen_b.begin(), gen_b.end());      
    }
    }
    else if (dist_type=="gauss_smallbias")
    {

    for (size_t j = 0; j < hidden_neurons.size()-1; j++) {
      gen_w = sigmaw/std::sqrt(hidden_neurons[j])*(arma::randn<vec>( hidden_neurons[j]*hidden_neurons[j+1] ));
      gen.insert(gen.end(),gen_w.begin(), gen_w.end());
      gen_b = sigmab/std::sqrt(hidden_neurons[j])*(arma::randn<vec>( hidden_neurons[j+1] ));
      gen.insert(gen.end(),gen_b.begin(), gen_b.end());      
    }
    }
    else if (dist_type=="uniform_largebias")
    {
    sigmaw = std::sqrt(3);
    sigmab = std::sqrt(3);
    for (size_t j = 0; j < hidden_neurons.size()-1; j++) {
      gen_w = 2*sigmaw/std::sqrt(hidden_neurons[j])*(arma::randu<vec>( hidden_neurons[j]*hidden_neurons[j+1] ) - 0.5);
      gen.insert(gen.end(),gen_w.begin(), gen_w.end());
      gen_b = 2*sigmab*(arma::randu<vec>( hidden_neurons[j+1] ) - 0.5);
      gen.insert(gen.end(),gen_b.begin(), gen_b.end());      
    }
    }
    else if (dist_type=="gauss_largeweight_largebias")
    {
    
    for (size_t j = 0; j < hidden_neurons.size()-1; j++) {
      gen_w = sigmaw*(arma::randn<vec>( hidden_neurons[j]*hidden_neurons[j+1] ));
      gen.insert(gen.end(),gen_w.begin(), gen_w.end());
      gen_b = sigmab*arma::randn<vec>( hidden_neurons[j+1] );
      gen.insert(gen.end(),gen_b.begin(), gen_b.end());      
    }
    }
    else if (dist_type=="uniform_largeweight_largebias")
    {
    
    sigmaw = std::sqrt(3);
    sigmab = std::sqrt(3);
    for (size_t j = 0; j < hidden_neurons.size()-1; j++) {
      gen_w = 2*sigmaw*(arma::randu<vec>( hidden_neurons[j]*hidden_neurons[j+1] ) - 0.5);
      gen.insert(gen.end(),gen_w.begin(), gen_w.end());
      gen_b = 2*sigmab*(arma::randu<vec>( hidden_neurons[j+1] ) - 0.5);
      gen.insert(gen.end(),gen_b.begin(), gen_b.end());      
    }
    }

    //for (std::vector<double>::const_iterator i = gen.begin(); i != gen.end(); ++i)
    //std::cout << *i << ' ';

    found_fun = pheno(gen);

    gen.clear();
    datafile << found_fun << "\n";
    // for (size_t j = 0; j < p1.size(); j++) {
    //   cout << p1[j];
    // }
    // cout << "\n";
  }
  datafile.close(); 
  MPI_Finalize(); 
}

//g++ -std=c++11 sample_net.cpp -o sample_net -DARMA_DONT_USE_WRAPPER -lopenblas -llapack
