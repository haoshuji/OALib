#ifndef PARAMETER_H
#define PARAMETER_H
// #include "Global.h"
#include <string>
#include <iostream>
using namespace std;
class CParameter
{
	public:
	//initialize by constructor and set by argv
	size_t num_alg, num_fold, index_binary_class;
	size_t num_que, num_ticks, time_ticks;
	
	int *permutation;
	//0 \leq bbq_k \leq 1, 
	double  b_start, b_start2,b;
	
	double *w;
	//vec Sigma_vec;

	bool Mul2Bin, Norm2One;

	double PAI_C, PAII_C;
	double AROW_r, AROW_eta; 		//parameters proposed in our algorithms
	double AROWC_r; 				//parameter r in crammer AROW algorithm
	bool find_PAI_C, find_PAII_C;
	bool find_AROW_r, find_AROW_eta;
	bool find_AROWC_r;

	double que_increase_speed,que_increase_speed2;
	bool Full_Matrix;
	bool F1_or_acc;

	CParameter();

	void ImportParameters(std::string file_fullpath);

	void Generate_permutation(int n);

	void Initialize(int d, int n);
	
	void Reset(int d, int n);

	~CParameter();
	
};

#endif
