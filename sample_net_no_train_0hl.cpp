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

//template<size_t s1,size_t s2>
//void injectLoop( std::bitset<s1>& bs1,const std::bitset<s2>& bs2,int start=s1-s2)
//{
//        for(size_t i=0;i<s2;i++)
//                    bs1[i+start]=bs2[i];
//}


int main(int argc, char const *argv[]) {
  //string index = getenv("SLURM_ARRAY_TASK_ID");
  int world_rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int n_input = 7, n_out = 1;
  //int m=64;

  // vector<int> hidden_neurons = {n_input, nh_1, nh_2, n_out};
  int total_params = n_input*n_out + n_out; 

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

  double sigmaw = 1.0;
  double sigmab = 1.0;

    //char a;

    //std::bitset<8*total_params> discrete_geno;


  ofstream datafile;
  datafile.open (string(argv[1])+string("_")+to_string(world_rank)+string("_")+string("full_sample_net_0hl.txt"));
  for (int i = 0; i < stoi(string(argv[2])); i++) {
    
    // for (size_t j = 0; j < hidden_neurons.size()-1; j++) {
    //   gen_w = 1/std::sqrt(hidden_neurons[j])*(arma::randn<vec>( hidden_neurons[j]*hidden_neurons[j+1] ));
    //   gen.insert(gen.end(),gen_w.begin(), gen_w.end());
    //   gen_b = arma::randn<vec>( hidden_neurons[j+1] );
    //   gen.insert(gen.end(),gen_b.begin(), gen_b.end());      
    // }

    gen_w = sigmaw/std::sqrt(n_input)*(arma::randn<vec>( n_input*n_out ));
    gen.insert(gen.end(),gen_w.begin(), gen_w.end());
    gen_b = sigmab*arma::randn<vec>( n_out );
    gen.insert(gen.end(),gen_b.begin(), gen_b.end()); 

    int j = 0;

    //for (std::vector<double>::const_iterator i = gen.begin(); i != gen.end(); ++i) {
    //    //std::cout << *i << ' ';
    //    if (j == 0) i = i * std::sqrt(n_input);
    //    a = (short int) (std::max(std::min(50*w,127.0),-128.0));
    //    std::bitset<8> x(a);
    //    injectBitset(discrete_geno,x);
    //    std::cout<<discrete_geno.to_string<char,std::char_traits<char>,std::allocator<char> >()<<std::endl;
    //    j = (j+1)%2;
    //}

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
