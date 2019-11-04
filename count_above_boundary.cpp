#include <stdlib.h>
#include <stdio.h>
// #include <string.h>
// #include <math.h>
#include <vector>
#include <armadillo>
#include "nn_pheno_bool.hpp"
#include <bitset>
#include <random>
#include <mpi.h>
#include <cstdlib>
#include "cxxopts.hpp"
//#include <boost/dynamic_bitset.hpp>

using namespace std;

int main(int argc, char *argv[]) {
    cxxopts::Options options("Count above boundary", "Get t counts of a fully connected neural network");
    options.add_options()
        ("p,prefix","Prefix for saving files", cxxopts::value<std::string>())
        ("N,Nsamples","Number of samples of the random neural net", cxxopts::value<int>())
        ("base","The number of points on a side of the lattice used as inputs", cxxopts::value<int>()->default_value("2"))
        ("sigmaw", "Weight variance", cxxopts::value<float>()->default_value("1.0"))
        ("sigmab", "bias variance", cxxopts::value<float>()->default_value("0.0"))
        ("bshift", "bias shift", cxxopts::value<float>()->default_value("0.0"))
        ("arch", "architecture of fully connected network, specified as input dimension, layer widths, and output dimension", cxxopts::value<std::string>())
        ("activation", "activation to use (relu/tanh)", cxxopts::value<std::string>()->default_value("relu"))
        ("centered", "whether to center the inputs")
        ("h,help", "Print help and exit.")
        ;
  //string index = getenv("SLURM_ARRAY_TASK_ID");
  int world_rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  auto result = options.parse(argc, argv);
    if (result["help"].as<bool>()) {
        cout << options.help({""}) << std::endl;
        exit(0);
    }
  string prefix = result["prefix"].as<string>();
  int N = result["Nsamples"].as<int>();
  int base = result["base"].as<int>();
  float sigmaw = result["sigmaw"].as<float>();
  float sigmab = result["sigmab"].as<float>();
  float bshift = result["bshift"].as<float>();
  string arch = result["arch"].as<string>();
  string activation = result["activation"].as<string>();
  bool centered = result["centered"].as<bool>();

  int n_layers = 0;
  vector<int> nhs;
  int pos = 0, new_pos;
  while (arch.find(",", pos) != std::string::npos) {
    new_pos = arch.find(",", pos);
    //cout << arch.substr(pos,new_pos-pos) << "\n" ;
    nhs.push_back(stoi(arch.substr(pos,new_pos-pos)));
    n_layers += 1;
    pos = new_pos+1;
  }
    new_pos = arch.find(",", pos);
    //cout << arch.substr(pos,new_pos-pos) << "\n" ;
    nhs.push_back(stoi(arch.substr(pos,new_pos-pos)));
    //n_layers += 1;
    pos = new_pos+1;
  //cout << nhs[0] << " " << nhs[1] << " " << nhs[2] << " " << nhs[3] << "\n";
  int n_input = nhs[0];
  int total_params = 0;
  for (int i=0; i< n_layers; i++) {
      total_params += nhs[i]*nhs[i+1]+nhs[i+1];
      //cout << total_params << "\n";
  }
  //cout << total_params << "\n";

  arma_rng::set_seed_random();

  vector<double> gen(total_params);
  vector<double>::iterator it;
  //vector<double> gen;
  vec gen_w, gen_b;
  //boost::dynamic_bitset<> found_fun(pow(base,n_input));
  int t;

  //ofstream datafile;
  //datafile.open (string(argv[1])+string("_")+to_string(world_rank)+string("_")+string("full_sample_net_0hl.txt"));
  vector<int> fracs;
  fracs.assign(pow(base,n_input)+1,0);
  for (int i = 0; i < N; i++) {
    
    it=gen.begin();
    for (int l=0; l< n_layers; l++) {
        gen_w = sigmaw/std::sqrt(nhs[l])*(arma::randn<vec>( nhs[l]*nhs[l+1] ));
        //gen.insert(gen.end(),gen_w.begin(), gen_w.end());
        //std::n_copy(gen_w.begin(),nhs[l]*nhs[l+1],it);
        //for (std::vector<double>::iterator ii = gen.begin(); ii != gen.end(); ++ii)
        //        std::cout << *ii << ' ';
        //cout << "\n";
        //getchar();
        std::copy(gen_w.begin(),gen_w.end(),it);
        //for (std::vector<double>::iterator ii = gen.begin(); ii != gen.end(); ++ii)
        //        std::cout << *ii << ' ';
        //cout << "\n";
        //getchar();
        it+=nhs[l]*nhs[l+1];
        if (l==n_layers-1) {
            gen_b = bshift+(sigmab*arma::randn<vec>( nhs[l+1] ));
        } else {
            gen_b = 0.0+(sigmab*arma::randn<vec>( nhs[l+1] ));
        }
        //gen.insert(gen.end(),gen_b.begin(), gen_b.end()); 
        //std::n_copy(gen_b.begin(),nhs[l+1],it);
        std::copy(gen_b.begin(),gen_b.end(),it);
        it+=nhs[l+1];
    }


    t = num_above_boundary(base, gen, nhs, n_layers, centered, activation);
    fracs[t] += 1;

    //gen.clear();
    //datafile << found_fun << "\n";
  }
    ofstream myfile;
    string filename = prefix + string("_") + to_string(world_rank) + string("_") + to_string(base);
    for (int i=0; i< n_layers+1; i++) {
        filename += string("_") + to_string(nhs[i]);
    }
    filename += "_" + to_string(sigmaw) + "_" + to_string(sigmab);
    filename += "_" + activation;
    if (centered) filename += "_centered";
    filename += string("_t_counts.txt");
     myfile.open(filename);
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
