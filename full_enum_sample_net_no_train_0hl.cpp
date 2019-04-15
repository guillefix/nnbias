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
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

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

  //discretization bits
  int disc_bits = stoi(argv[1]);

  mat geno_mat(total_params,disc_bits);
  vec geno_vec(total_params);
  //vec powers_two = { 1, 2, 4, 8 };
  vec powers_two(disc_bits);
  for (int i = 0; i < disc_bits; ++i) powers_two[i] = pow(2,i);

  ofstream datafile;
  datafile.open (string(argv[2])+to_string(world_rank)+string("_")+to_string(disc_bits)+string("_full_enum_discrete_weights_net_0hl.txt"));
  //haha long int
  long int tot_tasks = pow(2,disc_bits*total_params);
  long int rest_tasks = tot_tasks%world_size;
  long int num_tasks_init = std::min((long int)world_rank,rest_tasks)*(1+tot_tasks/world_size) + std::max((long int) 0,(long int)world_rank-rest_tasks)*(tot_tasks/world_size);
  long int num_tasks_end = std::min((long int)world_rank+1,rest_tasks)*(1+tot_tasks/world_size) + std::max((long int) 0,(long int)world_rank+1-rest_tasks)*(tot_tasks/world_size);
  for (long int i = num_tasks_init; i < num_tasks_end; i++) {
    vec discrete_geno = get_bits(i,disc_bits*total_params);
   geno_mat = conv_to<mat>::from(discrete_geno);
   geno_mat.reshape(disc_bits,total_params);
   geno_mat = geno_mat.t(); 
   geno_vec = geno_mat * powers_two;
   int shift = (pow(2,disc_bits)-1)/2.0; //7.5 for disc_bits = 4
   geno_vec = (geno_vec - shift)/shift;
   gen_w = geno_vec.subvec(0,n_input*n_out-1);
   gen_b = geno_vec.subvec(n_input*n_out,total_params-1);
    
    // for (size_t j = 0; j < hidden_neurons.size()-1; j++) {
    //   gen_w = 1/std::sqrt(hidden_neurons[j])*(arma::randn<vec>( hidden_neurons[j]*hidden_neurons[j+1] ));
    //   gen.insert(gen.end(),gen_w.begin(), gen_w.end());
    //   gen_b = arma::randn<vec>( hidden_neurons[j+1] );
    //   gen.insert(gen.end(),gen_b.begin(), gen_b.end());      
    // }

    //gen_w = sigmaw/std::sqrt(n_input)*(arma::randn<vec>( n_input*n_out ));
    gen.insert(gen.end(),gen_w.begin(), gen_w.end());
    //gen_b = sigmab*arma::randn<vec>( n_out );
    gen.insert(gen.end(),gen_b.begin(), gen_b.end()); 

    //int j = 0;

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
    //cout << conv_to<Col<int>>::from(discrete_geno).print() << "\n";
    //conv_to<Col<int>>::from(discrete_geno).t().raw_print();
    for(uword j=0; j < discrete_geno.n_elem; ++j) { datafile << discrete_geno(j); }
    datafile << "\t" << found_fun << "\n";
    //for(uword j=0; j < discrete_geno.n_elem; ++j) { cout << discrete_geno(j); }
    //cout << "\t" << found_fun << "\n";
    //datafile << found_fun << "\n";
    // for (size_t j = 0; j < p1.size(); j++) {
    //   cout << p1[j];
    // }
    // cout << "\n";
  }
  datafile.close(); 
  MPI_Finalize(); 
}

//g++ -std=c++11 sample_net.cpp -o sample_net -DARMA_DONT_USE_WRAPPER -lopenblas -llapack
