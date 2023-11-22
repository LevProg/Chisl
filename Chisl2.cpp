#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#define N 10
#define M 10

using namespace std;
using namespace chrono;


vector<vector<vector<double>>> matrix(9, vector<vector<double>>(M, vector<double>(N, 0)));
vector<vector<double>> vectors(9, vector<double>(N, 0));

double Random(int per, int i) {
    srand(time(0) + per + i * 10);
    return 1 + (rand() % (2 * per + 1) - per) * pow(10, -2);
}

void ReadData() {
    ifstream file1("C:/Users/Aser/Desktop/matrix.txt");
    ifstream file2("C:/Users/Aser/Desktop/result.txt");
    for (int i = 0; i < 9; i++) {
        for (int n = 0; n < N; n++) {
            file2 >> vectors[i][n];
            for (int m = 0; m < M; m++) {
                file1 >> matrix[i][n][m];
            }
        }
    }
}
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}
vector<double> GaussianMethod(vector<vector<double>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i = 0; i < n; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(matrix[k][i]) > abs(matrix[maxRow][i])) {
                maxRow = k;
            }
        }
        swap(matrix[i], matrix[maxRow]);
        for (int k = i + 1; k < n; ++k) {
            double factor = matrix[k][i] / matrix[i][i];
            for (int j = i; j < m; ++j) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }
    vector<double> result(n);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < m - 1; ++j) {
            matrix[i][m - 1] -= matrix[i][j] * result[j];
        }
        result[i] = matrix[i][m - 1] / matrix[i][i];
    }
    return result;
}

double FindMaxElement(vector<double> vector) {
    double maxelement = vector[0];
    for (int i = 0; i < 9; i++) {
        if (vector[i] > maxelement) maxelement = vector[i];
    }
    return maxelement;
}

double CalculateEpps(vector<double> MethodSolution, vector<double> Solution) {
    double maxElementMethod = FindMaxElement(MethodSolution);
    double maxElement = FindMaxElement(Solution);
    return fabs(maxElementMethod - maxElement);
}
int main()
{
    ReadData();
    vector<double>loss(9, 0);
    for (int i = 0; i < 9; i++) {
        auto start = high_resolution_clock::now();
        auto solution = GaussianMethod(matrix[i]);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        loss[i]= CalculateEpps(solution, vectors[i]);
        cout << i+1 <<'\t'<< duration.count() <<'\t'<< loss[i] << endl;
    }
    int obusl = 0;
    ofstream file3("res3.txt");
    for (int per = 1; per < 6; per++) {
        for (int j = 0; j < 50; j++) {
            for (int i = 0; i < M; i++) {
                matrix[obusl][i][N - 1] = matrix[obusl][i][N - 1] * Random(per, i);
            }
            auto solution = GaussianMethod(matrix[obusl]);
            double loss_ot=abs(loss[obusl]-CalculateEpps(solution, vectors[obusl]))/CalculateEpps(solution, vectors[obusl]);
            file3 << loss_ot << endl;
        }
    }
}
