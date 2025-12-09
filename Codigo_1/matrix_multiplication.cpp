#include <iostream>
#include <vector>
#include <chrono> 
#include <random> 
#include <iomanip> 
#include <omp.h>  


void initializeMatrix(std::vector<std::vector<double>>& matrix, int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 10.0); 

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
}


void printMatrix(const std::vector<std::vector<double>>& matrix, int N) {
    if (N > 10) {
        std::cout << "La matriz es demasiado grande para imprimirla." << std::endl;
        return;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << std::fixed << std::setprecision(2) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void multiplyMatricesSequential(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B,
    std::vector<std::vector<double>>& C,
    int N) {

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0.0; 
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


void multiplyMatricesParallelOpenMP(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B,
    std::vector<std::vector<double>>& C,
    int N) {

    // Indica que el bucle "for" inmediatamente siguiente debe ser paralelizado.
    // Cada hilo trabajará en un subconjunto de las iteraciones del bucle más externo (filas).
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0.0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int N = 500; 
        

    std::cout << "Iniciando multiplicación de matrices de " << N << "x" << N << std::endl;

    // Declarar e inicializar matrices
    std::vector<std::vector<double>> A(N, std::vector<double>(N));
    std::vector<std::vector<double>> B(N, std::vector<double>(N));
    std::vector<std::vector<double>> C_seq(N, std::vector<double>(N)); // Resultado secuencial
    std::vector<std::vector<double>> C_par(N, std::vector<double>(N)); // Resultado paralelo

    std::cout << "Inicializando matrices A y B..." << std::endl;
    initializeMatrix(A, N);
    initializeMatrix(B, N);
    std::cout << "Matrices inicializadas." << std::endl;

   
    std::cout << "\nEjecutando versión secuencial..." << std::endl;
    auto start_seq = std::chrono::high_resolution_clock::now();
    multiplyMatricesSequential(A, B, C_seq, N);
    auto end_seq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_seq = end_seq - start_seq;
    std::cout << "Tiempo secuencial: " << duration_seq.count() << " segundos." << std::endl;

    
    std::cout << "\nEjecutando versión paralela con OpenMP..." << std::endl;
    auto start_par = std::chrono::high_resolution_clock::now();
    multiplyMatricesParallelOpenMP(A, B, C_par, N);
    auto end_par = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_par = end_par - start_par;
    std::cout << "Tiempo paralelo (OpenMP): " << duration_par.count() << " segundos." << std::endl;

   
    bool same_results = true;    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            
            if (std::abs(C_seq[i][j] - C_par[i][j]) > 1e-9) {
                same_results = false;
                break;
            }
        }
        if (!same_results) break;
    }

    if (same_results) {
        std::cout << "\nResultados secuenciales y paralelos coinciden." << std::endl;
    } else {
        std::cout << "\n¡ADVERTENCIA! Los resultados secuenciales y paralelos NO coinciden." << std::endl;
    }

    
    std::cout << "\nMatriz C (secuencial):" << std::endl;
    printMatrix(C_seq, N);

    return 0;
}