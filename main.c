#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void freeMatrix(double** A, int n) {
    if (A != NULL) {
        for (int i = 0; i< n; i++) {
            if (A[i] != NULL) {
                free(A[i]);
            }
        }
        free(A);
    }
}

void transpose(double** Q, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = Q[i][j];
            Q[i][j] = Q[j][i];
            Q[j][i] = temp;
        }
    }
}

void matrixMultiplication(double** Q, double** A, double** R, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            R[i][j] = 0;
            for (int k = 0; k < n; k++) {
                R[i][j] += Q[i][k] * A[k][j];
            }
        }
    }
}

void multiplyingVectorByScalar(double* vector, int n, double scalar) {
    for(int i = 0; i < n; i++) {
        vector[i] *= scalar;
    }
}

double normalizeVector(double* vector, int n) {
    double norma = 0;
    for(int i = 0; i < n; i++) {
        norma += vector[i] * vector[i];
    }
    return sqrt(norma);
}

void unitizeVector(double* vector, int n) {
    multiplyingVectorByScalar(vector, n, 1 / normalizeVector(vector, n));
}

void vectorsSubtraction(double* vector1, double* vector2, int n) {
    for(int i = 0; i < n; i++) {
        vector1[i] -= vector2[i];
    }
}

double scalarProduct(double* vector1, double* vector2, int n) {
    double result = 0;
    for(int i = 0; i < n; i++) {
        result += vector1[i] * vector2[i];
    }
    return result;
}

void processGS(double** A, double** Q, int n) {
    transpose(A, n);

    double** G = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        G[i] = (double*)malloc(n * sizeof(double));
    }

    for(int i = 0; i < n; i++) {
        memcpy(G[i], A[i], n * sizeof(double));
        for(int j = 0; j < i; j++) {
            multiplyingVectorByScalar(G[j], n, (scalarProduct(A[i], Q[j], n) / scalarProduct(Q[j], Q[j], n)));
            vectorsSubtraction(G[i], G[j], n);
            memcpy(G[j], Q[j], n * sizeof(double));
        }
        memcpy(Q[i], G[i], n*sizeof(double));
    }
    freeMatrix(G, n);
    transpose(A, n);
    transpose(Q, n);
}

void findQMatrix(double** A, double** Q, int n) {

    processGS(A, Q, n);;

    transpose(Q, n);
    for(int i = 0; i < n; i++) {
        unitizeVector(Q[i], n);
    }
    transpose(Q, n);
}

void findRMatrix(double** A, double** Q, double** R, int n) {
    transpose(Q, n);
    matrixMultiplication(Q, A, R, n);
}

void writeMatrixToFile(double** A, int n, FILE* fout) {
    fprintf(fout, "%d %d\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(fout, "%lf ", A[i][j]);
        }
        fprintf(fout, "\n");
    }
}

double count_determinant(double** A, int n) {

    double** a = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        a[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            a[i][j] = A[i][j];
        }
    }
    
    double tmp, d;
    int znak = 1;
    
    if(n == 1) {
        freeMatrix(a, n);
        return a[0][0];
    } 
     
    int flag = 0; 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            if (a[j][i] == 0) { 
                flag += 1; 
            } 
        } 
        if (flag == n){ 
            freeMatrix(a, n);
            return 0; 
        } 
        flag = 0; 
    } 
     
    for (int i = 0; i < n - 1; i++) { 
        if (a[i][i] == 0) { 
            for (int j = i + 1; j < n; j++) { 
                if (a[j][i] != 0) { 
                    for (int k = 0; k < n; k++) { 
                        double tmp = a[i][k]; 
                        a[i][k] = a[j][k]; 
                        a[j][k] = tmp; 
                    } 
                    znak *= (-1); 
                } 
            } 
        } 
        for (int j = i + 1; j < n; j++) { 
            tmp = -a[j][i] / a[i][i]; 
            for (int k = 0; k < n; k++)  
                a[j][k] += a[i][k] * tmp; 
        } 
    } 
    
    d = 1; 
    for (int i = 0; i < n; i++) { 
        d *= a[i][i]; 
    } 
    if(d == 0){ 
        
        return 0; 
    } 
    d *= znak; 

    freeMatrix(a, n);
    return d;
}

int main(int argc, char* argv[]) { 
    
    char* input_file_name;
    char* output_file_name;

    if (argc < 4) {
        printf("Неверное количество аргументов");
        return 0;
    }
    
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'i') {
                input_file_name = argv[i + 1];
            }
            else if (argv[i][1] == 'o') {
                output_file_name = argv[i + 1];
            }
        }
    }
    
    FILE* input_file = fopen(input_file_name, "r");
    FILE* output_file = fopen(output_file_name, "w");
    if(input_file == NULL || output_file == NULL) {
        printf("Не удалось открыть файл");
        return 0;
    }
    
    int n;
    int m;

    if (fscanf(input_file, "%d %d", &m, &n) != 2) {
        printf("Неверные значения размерности матрицы ");
        fclose(input_file);
        fclose(output_file);
        return 0;
    }
    if (n <= 0 || m <= 0) {
        printf("Данной матрицы не существует");
        fclose(input_file);
        fclose(output_file);
        return 0;
    }
    if (m != n) {
        printf("Для данной матрицы не существует QR-разложения");
        fclose(input_file);
        fclose(output_file);
        return 0;
    }

    double** A = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc(n * sizeof(double));
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(input_file, "%lf", &A[i][j]) == 0) {
                printf("Входные данные содержат недопустимые значения или символы");
                freeMatrix(A, n);
                fclose(input_file);
                fclose(output_file);
                return 0;
            }
        }
    }

    if (count_determinant(A, n) == 0) {
        printf("Для данной матрицы не существует QR-разложения");
        freeMatrix(A, n);
        fclose(input_file);
        fclose(output_file);
        return 0;
    }

    double** Q = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        Q[i] = (double*)malloc(n * sizeof(double));
    }

    findQMatrix(A, Q, n);
    writeMatrixToFile(Q, n, output_file);

    double** R = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        R[i] = (double*)malloc(n * sizeof(double));
    }

    findRMatrix(A, Q, R, n);
    writeMatrixToFile(R, n, output_file);

    freeMatrix(A, n);
    freeMatrix(Q, n);
    freeMatrix(R, n);

    fclose(input_file);
    fclose(output_file);

    return 0;
}
