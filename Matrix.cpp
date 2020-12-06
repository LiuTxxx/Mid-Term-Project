//
// Created by 刘通 on 2020/12/6.
//

#include "Matrix.h"
#include <immintrin.h>
#include<string>
#include <omp.h>
//default constructor
Matrix::Matrix(){
    cnt = new int{0};
    name = "NoName";
    column = 0;
    row = 0;
    size = 0;
    std::cout << "The size is 0, matrix " << name << " will be NULL\n";
    data = NULL;
}
//constructor with matrix's name
Matrix::Matrix(std::string name){
    cnt = new int{0};
    this->name = name;
    column = 0;
    row = 0;
    size = 0;
    std::cout << "The size is 0, matrix " << name << " will be NULL\n";
    data = NULL;
}
//constructor with matrix's name, column and row of the matrix
Matrix::Matrix(std::string name, int column, int row){
    if (column < 0)
        column = 0;
    if (row < 0)
        row = 0;
    cnt = new int{0};
    this->name = name;
    this->column = column;
    this->row = row;
    size = column * row;
    if (size)
        data = new float[size]();
    else{
        data = NULL;
        std::cout << "The size is 0, matrix " << name << " will be NULL\n";
    }
}
//constructor with matrix's name, a float array which will be assigned to data, the size of the float array, column and row of the matrix
Matrix::Matrix(std::string name, float * data, size_t dataSize, int column, int row){
    if (column < 0)
        column = 0;
    if (row < 0)
        row = 0;
    cnt = new int{0};
    this->name = name;
    if (!dataSize){
        this->data = NULL;
        this->size = 0;
        this->column = 0;
        this->row = 0;
        std::cout << "The size is 0, matrix " << name << " will be NULL\n";
    } else {
        if (dataSize == column * row) {
            this->column = column;
            this->row = row;
            this->data = data;
            size = column * row;
        } else {
            std::cout << "Size is not matched, the matrix " << name << " will be 1*" << dataSize << ".\n";
            this->column = dataSize;
            this->row = 1;
            this->size = dataSize;
            this->data = data;
        }
    }
}
//copy constructor
Matrix::Matrix(Matrix const & mat){
    name = mat.name + ".copy";
    column = mat.column;
    row = mat.row;
    size = mat.size;
    data = mat.data;
    cnt = mat.cnt;
    (*cnt)++;
}
//denstructor
Matrix::~Matrix(){
    if ((*cnt)){
        (*cnt)--;
    } else {
        delete[] data;
        delete cnt;
        //std::cout << "data was deleted once\n";
    }
}
//assingment operator
Matrix Matrix::operator=(Matrix const & mat){
    column = mat.column;
    row = mat.row;
    size = mat.size;
    data = mat.data;
    cnt = mat.cnt;
    (*cnt)++;
}
//output stream operator
std::ostream & operator<< (std::ostream & os, Matrix const & mat){
    if (mat.data == NULL){
        os << "Matrix is NULL!\n";
    } else {
        os << "Matrix " << mat.name << " with " << mat.row << " rows and " << mat.column << " columns: \n";
        os << '[';
        for (int i = 0; i < mat.row; ++i) {
            for (int j = 0; j < mat.column - 1; ++j) {
                os << mat.data[i * mat.column + j] << ", ";
            }
            if (i < mat.row - 1) {
                os << mat.data[(i + 1) * mat.column - 1] << '\n';
            } else {
                os << mat.data[(i + 1) * mat.column - 1] << "]\n";
            }
        }
    }
    return os;
}
//input stream operator
std::istream & operator>> (std::istream & is, Matrix & mat){
    std::cout << "Please input the name of this matrix: \n";
    is >> mat.name;
    std::cout << "Please input the row and column: \n";
    is >> mat.row >> mat.column;
    mat.size = mat.row * mat.column;
    if ((*mat.cnt)){
        (*mat.cnt)--;
    } else {
        delete[] mat.data;
        //std::cout << "data was deleted once\n";
    }
    mat.cnt = new int{0};
    if (!mat.size){
        std::cout << "The size is 0, matrix " << mat.name << " will be NULL\n";
    } else {
        mat.data = new float[mat.size]();
        std::cout << "Input matrix data or not? (Y/N): \n";
        char ch;
        is >> ch;
        if (ch == 'Y') {
            std::cout << "Input matrix data: \n";
            for (size_t i = 0; i < mat.size; i++) {
                is >> mat.data[i];
            }
        } else {
            std::cout << "OK, the matrix will be filled with 0!\n";
        }
    }
    return is;
}
//scalar plus matrix
Matrix & operator+(float scalar, Matrix mat){
    return mat + scalar;
}
//scalar mul matrix
Matrix & operator*(float scalar, Matrix mat){
    return mat * scalar;
}
//matrix plus matrix
Matrix & Matrix::operator+ (Matrix const & mat){
    if (column != mat.column || row != mat.row){
        std::cout << "Size mismatched, plus is not allowed, NULL matrix will be returned!\n";
        Matrix *x = new Matrix(name + "+" + mat.name);
        return *x;
    } else {
        float *dataC = new float[size];
        /*__m256 a, b;
        __m256 c;*/
        #pragma omp parallel for
        for (size_t i = 0; i < size; i++){
            dataC[i] = data[i] + mat.data[i];
        }
        Matrix *x = new Matrix(name + "+" + mat.name, dataC, size, column, row);
        return *x;
    }
}

Matrix & Matrix::operator+ (float scalar){
    float *dataC = new float[size];
    /*__m256 a, b;
    __m256 c;*/
#pragma omp parallel for
    for (size_t i = 0; i < size; i++){
        dataC[i] = data[i] + scalar;
    }
    Matrix *x = new Matrix(name + "+" + std::to_string(scalar), dataC, size, column, row);
    return *x;
}

Matrix & Matrix::operator- (Matrix const & mat){
    if (column != mat.column || row != mat.row){
        std::cout << "Size mismatched, minus is not allowed, NULL matrix will be returned!\n";
        Matrix *x = new Matrix(name + "-" + mat.name);
        return *x;
    } else {
        float *dataC = new float[size];
        /*__m256 a, b;
        __m256 c;*/
#pragma omp parallel for
        for (size_t i = 0; i < size; i++){
            dataC[i] = data[i] - mat.data[i];
        }
        Matrix *x = new Matrix(name + "-" + mat.name, dataC, size, column, row);
        return *x;
    }
}

Matrix & Matrix::operator- (float scalar){
    float *dataC = new float[size];
    /*__m256 a, b;
    __m256 c;*/
#pragma omp parallel for
    for (size_t i = 0; i < size; i++){
        dataC[i] = data[i] - scalar;
    }
    Matrix *x = new Matrix(name + "-" + std::to_string(scalar), dataC, size, column, row);
    return *x;
}

Matrix & Matrix::operator* (float scalar){
    float *dataC = new float[size];
    /*__m256 a, b;
    __m256 c;*/
#pragma omp parallel for
    for (size_t i = 0; i < size; i++){
        dataC[i] = data[i] * scalar;
    }
    Matrix *x = new Matrix(name + "*" + std::to_string(scalar), dataC, size, column, row);
    return *x;
}

Matrix & Matrix::operator/ (float scalar) {
    float *dataC = new float[size];
    /*__m256 a, b;
    __m256 c;*/
    if (!scalar) {
        std::cout << "Scalar is 0, divide is not allowed, NULL matrix will be returned!\n";
        Matrix *x = new Matrix(name + "/" + std::to_string(scalar));
        return *x;
    } else {
#pragma omp parallel for
        for (size_t i = 0; i < size; i++) {
            dataC[i] = data[i] / scalar;
        }
        Matrix *x = new Matrix(name + "/" + std::to_string(scalar), dataC, size, column, row);
        return *x;
    }
}

Matrix & Matrix::operator* (Matrix const & mat){
    if (column != mat.row) {
        std::cout << "Size mismatched, mul is not allowed, NULL matrix will be returned!\n";
        Matrix *x = new Matrix(name + "*" + mat.name);
        return *x;
    } else {
        float *dataC = new float[size]();
#pragma omp parallel for
        for (int i = 0; i < row; i++){
            for (int j = 0; j < mat.column; j++){
                for (int k = 0; k < column; k++){
                    dataC[i * mat.column + j] += data[i * column + k] * mat.data[k * mat.column + j];
                }
            }
        }
        Matrix *x = new Matrix(name + "*" + mat.name, dataC, size, column, row);
        return *x;
    }
}
