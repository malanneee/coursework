#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <stdexcept>

using namespace std;

void filling_matrix(vector<vector<int>>& matrix, int rows, int cols) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 99);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = dist(gen);
        }
    }
}

vector<vector<int>> multiplication_row_col(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rows_A = A.size();
    int cols_A = A[0].size();
    int rows_B = B.size();
    int cols_B = B[0].size();

    if (cols_A != rows_B) {
        throw runtime_error("Incompatible matrix dimensions for multiplication.");
    }

    vector<vector<int>> result_multi(rows_A, vector<int>(cols_B, 0));
    for (int i = 0; i < rows_A; ++i) {
        for (int j = 0; j < cols_B; ++j) {
            for (int k = 0; k < cols_A; ++k) {
                result_multi[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result_multi;
}

int main() {
    cout << "Enter the number of rows for matrix A: ";
    int size_rowsA;
    cin >> size_rowsA;
    cout << "Enter the number of columns for matrix A: ";
    int size_colsA;
    cin >> size_colsA;

    cout << "Enter the number of rows for matrix B: ";
    int size_rowsB;
    cin >> size_rowsB;
    cout << "Enter the number of columns for matrix B: ";
    int size_colsB;
    cin >> size_colsB;

    vector<vector<int>> matrix_A(size_rowsA, vector<int>(size_colsA));
    vector<vector<int>> matrix_B(size_rowsB, vector<int>(size_colsB));

    filling_matrix(matrix_A, size_rowsA, size_colsA);
    cout << "Matrix A:" << endl;
    for (int i = 0; i < size_rowsA; i++) {
        for (int j = 0; j < size_colsA; j++) {
            cout << matrix_A[i][j] << ' ';
        }
        cout << endl;
    }

    filling_matrix(matrix_B, size_rowsB, size_colsB);
    cout << "Matrix B:" << endl;
    for (int i = 0; i < size_rowsB; i++) {
        for (int j = 0; j < size_colsB; j++) {
            cout << matrix_B[i][j] << ' ';
        }
        cout << endl;
    }

    vector<vector<int>> result_matrix;
    auto start = chrono::high_resolution_clock::now();
    try {
        result_matrix = multiplication_row_col(matrix_A, matrix_B);
    } catch (const runtime_error& error) {
        cerr << "Error: " << error.what() << endl;
        return 1; 
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Result of multiplication:" << endl;
    for (int i = 0; i < result_matrix.size(); i++) {
        for (int j = 0; j < result_matrix[0].size(); j++) {
            cout << result_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Time taken by matrix multiplication: " << duration.count() << " milliseconds" << endl;
    return 0;
}
