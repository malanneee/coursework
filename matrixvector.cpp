#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <stdexcept>

using namespace std;

// Заполнение матрицы случайными числами
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

// Заполнение вектора случайными числами
void filling_vector(vector<int>& vec, int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 99);

    for (int i = 0; i < size; i++) {
        vec[i] = dist(gen);
    }
}

// Умножение матрицы на вектор
vector<int> multiplication_matrix_vector(const vector<vector<int>>& matrix, const vector<int>& vec) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    if (vec.size() != cols) {
        throw runtime_error("Matrix columns and vector size are incompatible for multiplication.");
    }

    vector<int> result(rows, 0);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

int main() {
    int rows, cols;
    cout << "Enter number of rows of the matrix: ";
    cin >> rows;
    cout << "Enter number of columns of the matrix (and size of vector): ";
    cin >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));
    vector<int> vec(cols);

    filling_matrix(matrix, rows, cols);
    filling_vector(vec, cols);

    cout << "Matrix:" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << ' ';
        }
        cout << endl;
    }

    cout << "Vector:" << endl;
    for (int val : vec) {
        cout << val << ' ';
    }
    cout << endl;

    auto start = chrono::high_resolution_clock::now();
    vector<int> result;
    try {
        result = multiplication_matrix_vector(matrix, vec);
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Result (matrix × vector):" << endl;
    for (int val : result) {
        cout << val << ' ';
    }
    cout << endl;

    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    return 0;
}
