#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

void filling_sparse_matrix(vector<vector<int>>& matrix, int size, float sparsity) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 99);
    uniform_real_distribution<float> rand_float(0.0, 1.0);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (rand_float(gen) > sparsity) {
                matrix[i][j] = dist(gen);  
            }
            else {
                matrix[i][j] = 0;  
            }
        }
    }
}

vector<vector<int>> multiply_sparse(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    vector<vector<int>> C(size, vector<int>(size, 0));  
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            
            if (A[i][j] != 0 && B[j][i] != 0) {
                for (int k = 0; k < size; ++k) {
                    if (A[i][k] != 0 && B[k][j] != 0) { 
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
    }
    return C;
}

int main() {
    cout << "Enter the size of the matrices: ";
    int size;
    cin >> size;

    cout << "Enter the sparsity (0.0 to 1.0, where 1.0 is fully sparse): ";
    float sparsity;
    cin >> sparsity;

    vector<vector<int>> matrix_A(size, vector<int>(size, 0));
    vector<vector<int>> matrix_B(size, vector<int>(size, 0));

    filling_sparse_matrix(matrix_A, size, sparsity);
    filling_sparse_matrix(matrix_B, size, sparsity);

    cout << "Matrix A:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix_A[i][j] << ' ';
        }
        cout << endl;
    }

    cout << "Matrix B:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix_B[i][j] << ' ';
        }
        cout << endl;
    }

    vector<vector<int>> result_matrix(size, vector<int>(size, 0));

    auto start = chrono::high_resolution_clock::now();
    result_matrix = multiply_sparse(matrix_A, matrix_B, size);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Result of multiplication:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << result_matrix[i][j] << ' ';
        }
        cout << endl;
    }

    cout << "Time taken by sparse matrix multiplication: " << duration.count() << " milliseconds" << endl;
    return 0;
}
