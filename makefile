all:
	# g++ -std=c++11 inputcnt.cc -o inputcnt
	#g++ -std=c++11 -I /usr/local/boost_1_61_0 genstrings.cpp -o genstrings
	#g++ -std=c++11 -O3 genstrings_all.cpp -o genstrings_all
	# g++ -std=c++11 KC.cpp -o KC
	# g++ -std=c++11 genrob.cpp -o genrob
	# g++ -std=c++11 phenevol.cpp -o phenevol
	#g++ genfst.cpp -o genfst
	# g++ -std=c++11 matrixrun.cpp -o matrixrun
	#g++ -std=c++11 -O3 matrixrunfull.cpp -o matrixrunfull
	# g++ -std=c++11 -O3 n0_count.cpp -o n0_count
	# g++ -std=c++11 -O3 n0_entropy.cpp -o n0_entropy
	# g++ -std=c++11 -O3 ml_sequence.cpp -o ml_sequence
	# g++ -std=c++11 matrixstr.cpp -o matrixstr
	# g++ -std=c++11 bias.cpp -o bias
	g++ -O3 -std=c++11 KCcnt.cpp -o KCcnt
	# g++ -std=c++11 compfst.cpp -o compfst
