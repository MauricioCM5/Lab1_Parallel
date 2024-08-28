//Mauricio Colque Morales
//Comparison of matrices multiplication methods
//All matrices of square size for facility purposes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <utility>

typedef int** matrix;

using std::vector;
using std::pair;
using std::min;

void reset_matrix(matrix& M, int size)
{

	M = (int **)malloc(size * sizeof(int *));
	
	for (int i = 0; i < size; ++i){
		(M)[i] = (int *)malloc(size * sizeof(int));
		for(int j = 0; j < size; ++j){
			(M)[i][j] = rand() % 100;
		}
	}

}


void free_matrix(matrix &M, int size)
{
	for (int i = 0; i < size; ++i){
		free(M[i]);
	} 
	free(M);
}





void classic_multiplication(matrix A, matrix B, matrix C, int size)
{
	for(int i = 0; i < size; ++i){
		for(int j = 0; j < size; ++j){
			C[i][j] = 0;
			for(int k = 0; k < size; ++k){
				C[i][j] += A[i][k] * B[k][j];
			}
		}
		
	}
}

void block_multiplication(matrix A, matrix B, matrix C, int size, int block_size)
{
    for (int i = 0; i < size; i += block_size) {
        for (int j = 0; j < size; j += block_size) {
            for (int k = 0; k < size; k += block_size) {
            	int max_i = min(i + block_size, size);
                for (int ii = i; ii < max_i; ++ii) {
                int max_j = min(j + block_size, size);
                    for (int jj = j; jj < max_j; ++jj) {
                   		int max_k = min(k + block_size, size);
                        for (int kk = k; kk < max_k; ++kk) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

void print_matrix(matrix A, int size)
{
	printf("Printing matrix!\n");
	for(int i = 0; i < size; ++i){
		for(int j = 0; j < size; ++j){
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
}


pair<double, vector<double>> evaluate(int size, vector<int> block_sizes)
{
	matrix A,B,C;
	clock_t start, end;
	double time_classic, time_nested;
	vector<double> block_times(block_sizes.size(),0.0);
	//int block_size = 16; 
	
	reset_matrix(A, size);
	reset_matrix(B, size);
	reset_matrix(C, size);

	//classic multiplication	
	start = clock();
	classic_multiplication(A, B, C, size);
	end = clock();
	

	time_classic = (double) (end - start) / CLOCKS_PER_SEC;
	
	
	
	for(int curr_block = 0; curr_block < block_sizes.size(); ++curr_block){
		//resetting C
		for(int i = 0; i < size; ++i)
		     for(int j = 0; j < size; ++j)
		         C[i][j] = 0;

		
		//block multiplication
		start = clock();
		block_multiplication(A, B, C, size, block_sizes[curr_block]);
		end = clock();
		
		//time_nested = (double) (end - start) / CLOCKS_PER_SEC;
		block_times[curr_block] = (double) (end - start) / CLOCKS_PER_SEC;
		
	}

	free_matrix(A, size);
   free_matrix(B, size);
   free_matrix(C, size);
    
	return {time_classic, block_times};
}	


int main()
{	

	srand(time(NULL));
	vector<int> mat_sizes = {50,100,150,200,300,500,700,900,1000,1200};
	vector<int> block_sizes = {5,10,16,20,25};
	
	printf("Comparative table - time taken in seconds\n");
	printf("-classic \t| blocks\nNo blocks\t|");
	for(int i = 0; i < block_sizes.size(); ++i){ 
		printf("%d|\t", block_sizes[i]);
	}
	
	printf("-----------------------------------\n");
	
	for(int i = 0; i < mat_sizes.size(); ++i){
		pair<double,vector<double>> taken_time = evaluate(mat_sizes[i], block_sizes); 	
		printf("%d.%f\t|", i+1, taken_time.first);
		for(auto t : taken_time.second){
			printf("%.6f|", t);
		}
		printf("\n");
	}
	
	return 0;
	
}








