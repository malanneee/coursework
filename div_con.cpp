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

vector<vector<int>> adding(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    vector<vector<int>> C(size, vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

vector<vector<int>> subtraction(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    vector<vector<int>> C(size, vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

void multiply(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
    }
    else {
        int new_size = size / 2;

        vector<vector<int>> A11(new_size, vector<int>(new_size));
        vector<vector<int>> A12(new_size, vector<int>(new_size));
        vector<vector<int>> A21(new_size, vector<int>(new_size));
        vector<vector<int>> A22(new_size, vector<int>(new_size));

        vector<vector<int>> B11(new_size, vector<int>(new_size));
        vector<vector<int>> B12(new_size, vector<int>(new_size));
        vector<vector<int>> B21(new_size, vector<int>(new_size));
        vector<vector<int>> B22(new_size, vector<int>(new_size));

        for (int i = 0; i < new_size; ++i) {
            for (int j = 0; j < new_size; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + new_size];
                A21[i][j] = A[i + new_size][j];
                A22[i][j] = A[i + new_size][j + new_size];
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + new_size];
                B21[i][j] = B[i + new_size][j];
                B22[i][j] = B[i + new_size][j + new_size];
            }
        }

       
        vector<vector<int>> M1(new_size, vector<int>(new_size));
        vector<vector<int>> M2(new_size, vector<int>(new_size));
        vector<vector<int>> M3(new_size, vector<int>(new_size));
        vector<vector<int>> M4(new_size, vector<int>(new_size));
        vector<vector<int>> M5(new_size, vector<int>(new_size));
        vector<vector<int>> M6(new_size, vector<int>(new_size));
        vector<vector<int>> M7(new_size, vector<int>(new_size));

        vector<vector<int>> temp1(new_size, vector<int>(new_size));
        vector<vector<int>> temp2(new_size, vector<int>(new_size));

        temp1 = adding(A11, A22, new_size);  
        temp2 = adding(B11, B22, new_size);  
        multiply(temp1, temp2, M1, new_size);  

        temp1 = adding(A21, A22, new_size);  
        multiply(temp1, B11, M2, new_size);  

        temp2 = subtraction(B12, B22, new_size); 
        multiply(A11, temp2, M3, new_size); 

        temp2 = subtraction(B21, B11, new_size);  
        multiply(A22, temp2, M4, new_size);  

        temp1 = adding(A11, A12, new_size);  
        multiply(temp1, B22, M5, new_size);  

        temp1 = subtraction(A21, A11, new_size);  
        temp2 = adding(B11, B12, new_size);  
        multiply(temp1, temp2, M6, new_size);  

        temp1 = subtraction(A12, A22, new_size);  
        temp2 = adding(B21, B22, new_size);  
        multiply(temp1, temp2, M7, new_size);  
        vector<vector<int>> C11(new_size, vector<int>(new_size));
        vector<vector<int>> C12(new_size, vector<int>(new_size));
        vector<vector<int>> C21(new_size, vector<int>(new_size));
        vector<vector<int>> C22(new_size, vector<int>(new_size));

        C11 = adding(M1, M4, new_size);  
        C11 = subtraction(C11, M5, new_size);  
        C11 = adding(C11, M7, new_size);  

        C12 = adding(M3, M5, new_size);  

        C21 = adding(M2, M4, new_size);  

        C22 = adding(M1, M3, new_size);  
        C22 = subtraction(C22, M2, new_size);  
        C22 = adding(C22, M6, new_size);  

        for (int i = 0; i < new_size; ++i) {
            for (int j = 0; j < new_size; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + new_size] = C12[i][j];
                C[i + new_size][j] = C21[i][j];
                C[i + new_size][j + new_size] = C22[i][j];
            }
        }
    }
}

int main() {
    cout << "Enter the size. It must be even" << endl;
    int size;
    cin >> size;
    if (size % 2 != 0) {
        cout << "Error. The size must be even.";
        return 1;
    }

    vector<vector<int>> matrix_A(size, vector<int>(size));
    vector<vector<int>> matrix_B(size, vector<int>(size));
    filling_matrix(matrix_A, size);
    filling_matrix(matrix_B, size);

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

    vector<vector<int>> result_matrix(size, vector<int>(size));

    auto start = chrono::high_resolution_clock::now();
    multiply(matrix_A, matrix_B, result_matrix, size);
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
