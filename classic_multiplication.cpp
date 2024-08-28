#include <iostream>
#include <cstdlib>
#include <ctime>

const int N = 500; 

void multiplication(int A[][N], int B[][N], int C[][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[N][N];
    int B[N][N];
    int C[N][N];

    std::srand(std::time(0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = std::rand() % 100;
            B[i][j] = std::rand() % 100;
        }
    }

    multiplication(A, B, C);


    return 0;
}

