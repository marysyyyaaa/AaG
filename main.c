#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double scalar_multiply(double* vector1, double* vector2, int n) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        result += vector1[i] * vector2[i];
    }
    return result;
}

double* multiply_scalar_on_vector(double* vector, int n, double scalar) {
    double* result;
    for (int i = 0; i < n; i++) {
        result[i] = vector[i] * scalar;
    }
    return result;
}

void vector_minus_vector(double* vector1, double* vector2, int n) {
    for (int i = 0; i < n; i++) {
        vector1[i] -= vector2[i];
    }
}

double* summand_for_GS(double* vector_f, double* vector_g, int n) {
    double numerator = scalar_multiply(vector_f, vector_g, n);
    double denumerator = scalar_multiply(vector_g, vector_g, n) * scalar_multiply(vector_g, vector_g, n);
    return multiply_scalar_on_vector(vector_g, n, (numerator / denumerator));
}

void gramm_schmidt(double** Q, double** A, int n) {
    for (int i = 0; i < n; i++) {
        memcpy(Q[i], A[i], n);
        for (int j = 0; j < i; j++) {
            vector_minus_vector(Q[i], summand_for_GS(A[i], Q[j], n), n);
        }
    }
}

void write_matrix_to_file(double** A, int n, FILE* fout) {
    fprintf(fout, "%d %d\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(fout, "%f ", A[j][i]);
        }
        fprintf(fout, "\n");
    }
}

void find_R_matrix(double** R, double** Q, double** A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            R[i][j] = 0;
            for (int k = 0; k < n; k++) {
                R[i][j] += Q[k][i] * A[k][j]; 
            }
        }
    }
}

double count_determinant(double** a, int n) {
    double tmp, d;
    int znak = 1;
    
    if(n == 1) { 
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
    return d;
}

int main(int argc, char* argv[]) { 
    
    char* input_file_name;
    char* output_file_name;
    
    if (argc < 5) {
        printf("Неверное количество аргументов");
        return 0;
    }
    
    for (int i = 1; i <= argc; i++) {
        if (argv[i] == "-i") {
            input_file_name = argv[i + 1];
        } else if (argv[i] == "-o") {
            output_file_name = argv[i + 1];
        }
    }
    
    FILE* input_file = fopen(input_file_name, "r");
    FILE* output_file = fopen(output_file_name, "w");
    if(input_file == NULL || output_file == NULL) {
        printf("Не удалось открыть файл");
        return 0;
    }
    
    int m;
    int n;
    
    if (fscanf(input_file, "%d %d", &m, &n) == 0) {
        printf("Неверные значения размерности матрицы");
        return 0;
    }
    if (n <= 0 || m <= 0) {
        printf("Данной матрицы не существует");
        return 0;
    }
    if (m != n) {
        printf("Для данной матрицы не существует QR-разложения");
        return 0;
    }
    
    double** A = (double**)malloc(n*sizeof(double*));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(input_file, "%lf ", &A[j][i]) == 0) {
                printf("Входные данные содержат недопустимые значения или символы");
                return 0;
            }
        }
    }
    
    if (count_determinant(A, n) == 0) {
        printf("Для данной матрицы не существует QR-разложения");
        return 0;
    }
    
    double** Q = (double**)malloc(n*sizeof(double*));
    gramm_schmidt(Q, A, n);
    write_matrix_to_file(Q, n, output_file);
    
    double** R = (double**)malloc(n*sizeof(double*));
    find_R_matrix(R, Q, A, n);
    write_matrix_to_file(R, n, output_file);
    
    fclose(input_file);
    fclose(output_file);
    
    free(A);
    free(Q);
    free(R);
    return 0;
}