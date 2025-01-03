#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

void filling_matrix(vector<vector<int>>& matrix, int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 99);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = dist(gen);
        }
    }
}

int main() {
    int size;
    
    cin >> size;

    vector<vector<int>> matrix_A(size, vector<int>(size));
    vector<vector<int>> matrix_B(size, vector<int>(size));
    filling_matrix(matrix_A, size);
    cout << "Matrix A:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix_A[i][j] << ' ';
        }
        cout << endl;
    }
    
    filling_matrix(matrix_B, size);
    cout << "Matrix B:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix_B[i][j] << ' ';
        }
        cout << endl;

    }
    
    vector<vector<int>> result_matrix(size, vector<int>(size));
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result_matrix[i][j] = 0;
            for (int l = 0; l < size; l++) {
                result_matrix[i][j] += matrix_A[i][l] * matrix_B[l][j];   }
        }
    }
    auto end = chrono::high_resolution_clock::now(); 
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Result of multiplication:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << result_matrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "Time taken by matrix multiplication: " << duration.count() << " milliseconds" << endl;
    return 0;
}
