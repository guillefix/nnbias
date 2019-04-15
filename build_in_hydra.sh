#!/bin/bash

module load gcc/5.4.0
module load armadillo
module load openblas/openblas
module load openmpi/1.8.7-gcc

#mpic++ -std=c++11 -O3 -static-libgcc -static-libstdc++ sample_net.cpp -o sample_net -DARMA_DONT_USE_WRAPPER -lopenblas -L/users/guillefix/bias/nn_bias/bias_cpp/lapack-3.8.0 -llapack
#mpic++ -std=c++11 -static-libgcc -static-libstdc++ sample_net.cpp -o sample_net_new -DARMA_DONT_USE_WRAPPER -lopenblas -L/users/guillefix/bias/nn_bias/bias_cpp/lapack-3.8.0 -llapack
#mpic++ -std=c++11 -O3 -static-libgcc -static-libstdc++ abi_from_sample.cpp -o abi_from_sample -DARMA_DONT_USE_WRAPPER -lopenblas -L/users/guillefix/bias/nn_bias/bias_cpp/lapack-3.8.0 -llapack
#mpic++ -std=c++11 -O3 -static-libgcc -static-libstdc++ sample_net_no_train.cpp -o sample_net_no_train -DARMA_DONT_USE_WRAPPER -lopenblas -L/users/guillefix/bias/nn_bias/bias_cpp/lapack-3.8.0 -llapack
#g++ -std=c++11 -O3 -static-libgcc -static-libstdc++ sample_net_no_train.cpp -o sample_net_no_train -DARMA_DONT_USE_WRAPPER -lopenblas -L/users/guillefix/bias/nn_bias/bias_cpp/lapack-3.8.0 -llapack
#mpic++ -std=c++11 -O3 -static-libgcc -static-libstdc++ sample_net_no_train_1hl.cpp -o sample_net_no_train_1hl -DARMA_DONT_USE_WRAPPER -lopenblas -L/users/guillefix/bias/nn_bias/bias_cpp/lapack-3.8.0 -llapack
#mpic++ -std=c++11 -O3 -static-libgcc -static-libstdc++ sample_net_no_train_0hl.cpp -o sample_net_no_train_0hl -DARMA_DONT_USE_WRAPPER -lopenblas -L/users/guillefix/bias/nn_bias/bias_cpp/lapack-3.8.0 -llapack
#mpic++ -std=c++11 -O3 -static-libgcc -static-libstdc++ sample_net_no_train_2hl.cpp -o sample_net_no_train_2hl_testing -DARMA_DONT_USE_WRAPPER -lopenblas -L/users/guillefix/bias/nn_bias/bias_cpp/lapack-3.8.0 -llapack
#mpic++ -std=c++11 -O3 -static-libgcc -static-libstdc++ full_enum_sample_net_no_train_0hl.cpp -o full_enum_sample_net_no_train_0hl -DARMA_DONT_USE_WRAPPER -lopenblas -L/users/guillefix/bias/nn_bias/bias_cpp/lapack-3.8.0 -llapack

#g++ -O3 -std=c++11 KCcnt.cpp -o KCcnt
g++ -O3 -std=c++11 KCcnt_plus.cpp -o KCcnt_plus
