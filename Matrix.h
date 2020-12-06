//
// Created by 刘通 on 2020/12/6.
//

#ifndef ASSIGNMENT4_MATRIX_H
#define ASSIGNMENT4_MATRIX_H

#include <iostream>

class Matrix {
private:
    std::string name;
    int * cnt;
    int row;
    int column;
    size_t size;
    int step;
    float * data;
public:
    //Constructor
    explicit Matrix();
    explicit Matrix(std::string name);
    explicit Matrix(std::string name, int column, int row);
    explicit Matrix(std::string name, float * data, size_t dataSize, int column, int row);
    //Copy constructor
    Matrix(Matrix const & mat);
    //Destructor
    ~Matrix();
    //Operator
    Matrix operator= (Matrix const & mat);
    friend std::ostream & operator<< (std::ostream & os, Matrix const & mat);
    friend std::istream & operator>> (std::istream & is, Matrix & mat);
    friend Matrix & operator+(float scalar, Matrix mat);
    friend Matrix & operator*(float scalar, Matrix mat);
    Matrix & operator+ (Matrix const & mat);
    Matrix & operator+ (float scalar);
    Matrix & operator- (Matrix const & mat);
    Matrix & operator- (float scalar);
    Matrix & operator* (Matrix const & mat);
    Matrix & operator* (float scalar);
    Matrix & operator/ (float scalar);
};


#endif //ASSIGNMENT4_MATRIX_H
