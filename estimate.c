#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printM(double **arr, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%0.0lf", arr[i][j]);
        }
        printf("\n");
    }
    return;
}

void freeM(double** arr, int size)
{
    double* curr;
    for(int i = 0; i < size; i++)
    {
        curr = arr[i];
        free(curr);
        curr = NULL;
    }
    free(arr);
    arr = NULL;
}

double** transpose(double **matrix, int a, int b){
    double **result = NULL;
    result = (double**) malloc(b * sizeof(double*));
    for(int i=0;i<b;i++){
        result[i] = (double*) malloc(a * sizeof(double));
    }
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

double** multiplyM(double** mat1, int row1, int col1, double** mat2, int row2, int col2){

    if(col1 != row2){
        return NULL;
    }
    else {
        double** res;
        res = (double**)malloc(row1*sizeof(double*));
        for(int i=0;i<row1;i++){
            res[i] = (double*)malloc(col2*sizeof(double));
        }

        for(int i=0;i<row1;i++){
            for(int j=0;j<col2;j++){
                res[i][j]=0;
                for(int k=0;k<col1;k++){
                    res[i][j]+= (mat1[i][k]*mat2[k][j]);
                }
            }
        }

        return res;
    }
}

double** findInv(double** matrix, int size)
{
    int count = size;
    double counter;
    double cols = 2*size;
    double **invMatrix = (double**) malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        invMatrix[i] = (double*) malloc(cols * sizeof(double));
    }
    double **finalInvMatrix = (double **) malloc (size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        finalInvMatrix[i] = (double*) malloc (size * sizeof(double));
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < (cols); j++){
            if(j == count){
                invMatrix[i][j] = 1;
            }
            else if(j > (size-1)){
                invMatrix[i][j] = 0;
            }
            else{
                invMatrix[i][j] = matrix[i][j];
            }
        }
        count++;
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i > j){
                continue;
            }
            if((i==j) && (invMatrix[i][j] != 1)){
                counter = invMatrix[i][j];
                for(int k = 0; k < (cols); k++){
                    invMatrix[i][k] = invMatrix[i][k] / counter;
                }
            }
            else if(i!=j && invMatrix[j][i] != 0){
                for(int v = j; v < size; v++){
                    counter = invMatrix[v][i];
                    for(int k = 0; k < (cols); k++){
                        invMatrix[v][k] = invMatrix[v][k] + ((-1*counter)* invMatrix[j-1][k]);
                    }
                }
            }
        }
    }
    for(int i = (size-2); i > -1; i--){
        for(int j = (size-1); invMatrix[i][j] != 1; j--){
            for(int v = i; v > -1; v--){
                counter = invMatrix[i][j];
                for(int k = 0; k < (cols); k++){
                    invMatrix[v][k] = invMatrix[v][k] + ((-1*counter)* invMatrix[j][k]);
                }
            }
        }
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            finalInvMatrix[i][j] = invMatrix[i][j+size];
        }
    }
    freeM(invMatrix, size);
    return finalInvMatrix;
}

double** predictOutput(double** matrix1, int rows1, int cols1, double** matrix2, int rows2, int cols2)
{
    double** output;
    output=(double**) malloc(rows1* sizeof(double*));

    for (int i = 0; i < rows1; i++) {
        output[i]=(double*) malloc(1* sizeof(double));
    }

    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < rows2 ;j++){
            if(j == 0){
                output[i][0] = matrix2[j][0];
            }
            else{
                output[i][0] += (matrix2[j][0] * matrix1[i][j-1]);
            }
        }
    }
    return output;
}

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("error\n");
        exit(0);
    }
    FILE *file1 = fopen(argv[1], "r");
    if(file1 == NULL) {
        exit(0);
    }
    FILE *file2 = fopen(argv[2], "r");
    if(file2 == NULL){
        exit(0);
    }
    char word[10];
    int k, n, k2, n2;
    double number;
    fscanf(file1, "%s\n", word);
    fscanf(file2, "%s\n", word);
    fscanf(file1, "%d\n", &k);
    fscanf(file2, "%d\n", &k2);
    fscanf(file1, "%d\n", &n);
    fscanf(file2, "%d\n", &n2);
    double** matrixX= (double**)malloc(n*sizeof(double*));
    for(int i=0; i<n; i++){
        matrixX[i] = (double*)malloc((k+1)*sizeof(double));
    }
    double** matrixY= (double**)malloc(n*sizeof(double*));
    for(int i=0; i<n; i++){
        matrixY[i] = (double*)malloc(1*sizeof(double));
    }
    double** inputData = (double**)malloc(n2*sizeof(double*));
    for(int i=0; i<n2; i++){
        inputData[i] = (double*)malloc(k2*sizeof(double));
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < k+2; j++){
            if(j == 0){     
                matrixX[i][j] = 1.0;
                if(i < n2){
                    fscanf(file2, "%lf ", &number);
                    inputData[i][j] = number;
                }
            }
            else if(j == k+1){
                fscanf(file1, "%lf\n", &number);
                matrixY[i][0] = number;
            }else{
                fscanf(file1, "%lf ", &number);
                matrixX[i][j] = number;
                if(i < n2 && j == k2-1){
                    fscanf(file2, "%lf\n", &number);
                    inputData[i][j] = number;                            
                }
                else if(i < n2 && j < k2){ 
                    fscanf(file2, "%lf ", &number);
                    inputData[i][j] = number;
                }
            }
        }
    }
    fclose(file1); 
    fclose(file2);

    double **transposedMatrix = transpose(matrixX, n, k+1);
    double **multipliedMatrix = multiplyM(transposedMatrix, (k+1), n, matrixX, n, (k+1));
    double **inversedMatrix = findInv(multipliedMatrix, k+1);
    double **finalEstimate = multiplyM(inversedMatrix, k+1, k+1, transposedMatrix, k+1, n);
    double **coefficients = multiplyM(finalEstimate, k+1, n, matrixY, n, 1);
    double **predictedValues = predictOutput(inputData, n2, k2, coefficients, k+1, 1);
    printM(predictedValues, n2, 1);

    freeM(matrixX, n);
    freeM(matrixY, n);
    freeM(inputData, n2);
    freeM(transposedMatrix, k+1);
    freeM(multipliedMatrix, k+1);
    freeM(inversedMatrix, k+1);
    freeM(finalEstimate, k+1);
    freeM(coefficients, k+1);
    freeM(predictedValues, n2);

    return 0;
}

