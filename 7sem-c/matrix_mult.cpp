



#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <ctime>

std::vector<std::vector<int>> mat_multiplication(const std::vector<std::vector<int>> &a,
                          const std::vector<std::vector<int>> &b) {

    std::vector<std::vector<int>> c(a.size(), std::vector<int>(b[0].size(), 0));

    for(int i = 0; i < a.size(); ++i) {
        if (i % 100 == 0) {
            std::cout << i << "column\n";
        }
        for (int j = 0; j < b[0].size(); ++j) {
            for (int k = 0; k < a[0].size(); ++k)
                c[i][j] += a[i][k] * b[k][j]; // ТАК НЕ ПИСАТЬ
        }
    }

    return c;
}

std::vector<std::vector<int>> tr_mat_multiplication(const std::vector<std::vector<int>> &a,
                          const std::vector<std::vector<int>> &b) {

    std::vector<std::vector<int>> c(a.size(), std::vector<int>(b[0].size(), 0));

    for(int i = 0; i < a.size(); ++i) {
        if (i % 100 == 0) {
            std::cout << i << "column\n";
        }
        for (int j = 0; j < b[0].size(); ++j) {
            for (int k = 0; k < a[0].size(); ++k)
                c[i][j] += a[i][k] * b[j][k]; //// ПИСАТЬ ТАК
        }
    }
    return c;
}

std::vector<std::vector<int>> construct_random_matrix(int n, int m) {
    std::vector<std::vector<int>> mat(n, std::vector<int>(m));
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != m; ++j) {
            mat[i][j] = std::rand() % 1000;
        }
    }
    return mat;
}

std::vector<std::vector<int>> transpose_matrix(const std::vector<std::vector<int>> &mat) {
    std::vector<std::vector<int>> tr_mat(mat[0].size(), std::vector<int>(mat.size()));
    for (int i = 0; i != mat.size(); ++i) {
        for (int j = 0; j != mat[0].size(); ++j) {
            tr_mat[j][i] = mat[i][j];
        }
    }
    return tr_mat;
}
void print_matrix(const std::vector<std::vector<int>> &mat) {
    std::cout << "============\n";
    for (int i = 0; i != mat.size(); ++i) {
        for (int j = 0; j != mat[0].size(); ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "============\n";
}

int main() {
    srand (time(nullptr));
    int n, m;
    std::cin >> n >> m;
    auto mat1 = construct_random_matrix(n, m);
    auto mat2 = construct_random_matrix(n, m);
    auto tr_mat2 = transpose_matrix(mat2);

    auto start = std::chrono::system_clock::now();
    auto mat_res1 = mat_multiplication(mat1, mat2);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "First method finished, elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::system_clock::now();
    auto mat_res2 = tr_mat_multiplication(mat1, tr_mat2);
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;

    std::cout << "Second method finished, elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
